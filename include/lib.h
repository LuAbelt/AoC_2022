//
// Created by lukas on 25/11/2022.
//

#ifndef ADVENTOFCODE2022_LIB_H
#define ADVENTOFCODE2022_LIB_H
#include <iostream>
#include <vector>
#include <memory>
#include <numeric>
#include <cassert>



namespace transform {
    template <uint8_t Dimensions>
    class Coord {
        std::array<int64_t, Dimensions> _coords;
    public:

        template<typename... Args>
        Coord(Args... args)
        requires (
                Dimensions >=2
                && Dimensions <= 4
                && sizeof...(Args)==Dimensions
                && (... && std::convertible_to<Args, int64_t>)
        )
        :_coords({args...})
        {
        }

        [[nodiscard]] int x() const{
            return _coords[0];
        }

        [[nodiscard]] int y() const{
            return _coords[1];
        }

        [[nodiscard]] int z() const
        requires (Dimensions > 2)
        {
            return _coords[2];
        }

        [[nodiscard]] int w() const
        requires (Dimensions > 3)
        {
            return _coords[3];
        }

        [[nodiscard]] uint64_t manhattanLength() const{
            return std::accumulate(_coords.begin(), _coords.end(), 0, [](uint64_t left, int64_t right){
                return left + std::abs(right);
            });
        }

        bool operator==(Coord const & Other) const {
            return std::equal(_coords.begin(), _coords.end(), Other._coords.begin());
        }
        bool operator<(Coord const & Other) const {
            return _coords < Other._coords;
        }

        auto operator<=>(Coord const & Other) const {
            return _coords <=> Other._coords;
        }

        Coord & operator+=(Coord const & Other) {
            for(size_t i = 0; i<_coords.size(); ++i){
                _coords[i] += Other._coords[i];
            }
            return *this;
        }

        Coord operator+(Coord const & Other) const{
            Coord result = *this;
            result+=Other;
            return result;
        }

        Coord & operator-=(Coord const & Other) {
            for(size_t i = 0; i<_coords.size(); ++i){
                _coords[i] += Other._coords[i];
            }
            return *this;
        }

        Coord operator-(Coord const & Other) const{
            Coord result = *this;
            result-=Other;
            return result;
        }
    };

    using Coord3 = Coord<3>;
    using Coord4 = Coord<4>;

    Coord3 rotateCoord(const Coord3& coord, size_t rotation){
        assert(rotation<24);


        // We rotate in two steps
        // Imagine the 24 possibilities as the following:
        // The sensor can face 6 different directions (Like on a dice)
        // For each side, there are four possible "roll" values
        // We first determine the side to turn to
        // Then we apply the roll
        Coord3 result=coord;
        switch (rotation/4) {
            // case 0: Omitted, no change in rotation
            case 1:
                // Face "right"
                result = {result.y(),-result.x(),result.z()};
                break;
            case 2:
                // Face "back"
                result = {-result.x(),-result.y(),result.z()};
                break;
            case 3:
                // Face "left"
                result = {-result.y(),result.x(),result.z()};
                break;
            case 4:
                // Face "up"
                result = {result.z(),result.y(),-result.x()};
                break;
            case 5:
                // Face "down"
                result = {-result.z(),result.y(),result.x()};
                break;
        }

        switch(rotation%4){
            //case 0: Omitted, no roll
            case 1:
                //Roll 90 degree
                result = {result.x(),result.z(),-result.y()};
                break;
            case 2:
                //Roll 180 degree
                result = {result.x(),-result.y(),-result.z()};
                break;
            case 3:
                //Roll 270 Degree
                result = {result.x(),-result.z(),result.y()};
                break;
        }

        return result;
    }

    std::vector<Coord3> rotateCoords(const std::vector<Coord3> &Coords, size_t rotation){
        std::vector<Coord3> result;
        result.reserve(Coords.size());
        for (const auto& coord:Coords) {
            result.push_back(rotateCoord(coord,rotation));
        }

        sort(result.begin(),result.end());
        return result;
    }

    template <uint8_t Dims>
    void applyTranslation(Coord<Dims> &Pos, std::vector<Coord<Dims>> &Coords){
        for (auto &coord:Coords) {
            coord+=Pos;
        }
    }
}

namespace geometry {
    struct Point{
        int x,y;
    };

    struct Line{
        Point begin,end;


        [[nodiscard]] bool isOrthogonal() const{
            return (begin.x==end.x)||(begin.y==end.y);
        }

        [[nodiscard]] bool isDiagonal() const{
            return abs(end.x-begin.x)==abs(end.y-begin.y);
        }

        [[nodiscard]] std::vector<Point> getPoints() const{
            if(!(isOrthogonal()||isDiagonal())){
                return {};
            }
            std::vector<Point> res;

            if(isDiagonal()){

                int dist = abs(end.x-begin.x);
                for (int i = 0; i <= dist; ++i) {
                    int x,y;
                    if(begin.x<=end.x){
                        x=begin.x+i;
                    }else{
                        x=begin.x-i;
                    }

                    if(begin.y<=end.y){
                        y=begin.y+i;
                    }else{
                        y=begin.y-i;
                    }

                    res.push_back({x,y});
                }

                return res;
            }

            if(begin.x==end.x){
                int beg = begin.y;
                int en = end.y;
                if(begin.y>end.y){
                    beg = end.y;
                    en = begin.y;
                }

                for (int y = beg; y <= en; ++y) {
                    res.push_back({begin.x,y});
                }
            }else if(begin.y==end.y){
                int beg = begin.x;
                int en = end.x;
                if(begin.x>end.x){
                    beg = end.x;
                    en = begin.x;
                }

                for (int x = beg; x <= en; ++x) {
                    res.push_back({x,begin.y});
                }
            }

            return res;
        }
    };


    class BoundingBox{
        using Coord = transform::Coord3;
        Coord _min;
        Coord _max;
    public:
        BoundingBox(Coord min, Coord max)
                : _min(min),
                  _max(max)
        {assert(min<=max);}

        [[nodiscard]] bool intersects(const BoundingBox &Other) const {
            return !(Other._min.x()>_max.x()
                     ||Other._max.x()<_min.x()
                     ||Other._max.y()<_min.y()
                     ||Other._min.y()>_max.y()
                     ||Other._max.z()<_min.z()
                     ||Other._min.z()>_max.z()
            );
        }

        [[nodiscard]] BoundingBox intersection(const BoundingBox &Other) const{
            Coord intMin={std::max(_min.x(),Other._min.x())
                    ,std::max(_min.y(),Other._min.y())
                    ,std::max(_min.z(),Other._min.z())};

            Coord intMax={std::min(_max.x(),Other._max.x()),
                          std::min(_max.y(),Other._max.y()),
                          std::min(_max.z(),Other._max.z())};

            return {intMin,intMax};
        }

        [[nodiscard]] uint64_t volume() const{
            return (abs(_max.x()-_min.x())+1)*(abs(_max.y()-_min.y())+1)*(abs(_max.z()-_min.z())+1);
        }

        [[nodiscard]] std::vector<BoundingBox> dissect(const BoundingBox &Other) const{
            assert(Other._min>=_min);
            assert(Other._max<=_max);
            std::vector<BoundingBox> Result;

            // 1
            Coord min = Coord{_min.x(),_min.y(),Other._min.z()};
            Coord max = Coord{Other._min.x()-1,Other._min.y()-1,Other._max.z()};
            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 2
            min = Coord{Other._min.x(),_min.y(),Other._min.z()};
            max = Coord{Other._max.x(),Other._min.y()-1,Other._max.z()};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 3
            min = Coord{Other._max.x()+1,_min.y(),Other._min.z()};
            max = Coord{_max.x(),Other._min.y()-1,Other._max.z()};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 4
            min = Coord{_min.x(),Other._min.y(),Other._min.z()};
            max = Coord{Other._min.x()-1,Other._max.y(),Other._max.z()};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 5
            min = Coord{Other._max.x()+1,Other._min.y(),Other._min.z()};
            max = Coord{_max.x(),Other._max.y(),Other._max.z()};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 6
            min = Coord{_min.x(),Other._max.y()+1,Other._min.z()};
            max = Coord{Other._min.x()-1,_max.y(),Other._max.z()};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 7
            min = Coord{Other._min.x(),Other._max.y()+1,Other._min.z()};
            max = Coord{Other._max.x(),_max.y(),Other._max.z()};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 8
            min = Coord{Other._max.x()+1,Other._max.y()+1,Other._min.z()};
            max = Coord{_max.x(),_max.y(),Other._max.z()};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 1
            min = Coord{_min.x(),_min.y(),_min.z()};
            max = Coord{Other._min.x()-1,Other._min.y()-1,Other._min.z()-1};
            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 2
            min = Coord{Other._min.x(),_min.y(),_min.z()};
            max = Coord{Other._max.x(),Other._min.y()-1,Other._min.z()-1};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 3
            min = Coord{Other._max.x()+1,_min.y(),_min.z()};
            max = Coord{_max.x(),Other._min.y()-1,Other._min.z()-1};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 4
            min = Coord{_min.x(),Other._min.y(),_min.z()};
            max = Coord{Other._min.x()-1,Other._max.y(),Other._min.z()-1};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // Middle
            min = Coord{Other._min.x(),Other._min.y(),_min.z()};
            max = Coord{Other._max.x(),Other._max.y(),Other._min.z()-1};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 5
            min = Coord{Other._max.x()+1,Other._min.y(),_min.z()};
            max = Coord{_max.x(),Other._max.y(),Other._min.z()-1};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 6
            min = Coord{_min.x(),Other._max.y()+1,_min.z()};
            max = Coord{Other._min.x()-1,_max.y(),Other._min.z()-1};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 7
            min = Coord{Other._min.x(),Other._max.y()+1,_min.z()};
            max = Coord{Other._max.x(),_max.y(),Other._min.z()-1};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 8
            min = Coord{Other._max.x()+1,Other._max.y()+1,_min.z()};
            max = Coord{_max.x(),_max.y(),Other._min.z()-1};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 1
            min = Coord{_min.x(),_min.y(),Other._max.z()+1};
            max = Coord{Other._min.x()-1,Other._min.y()-1,_max.z()};
            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 2
            min = Coord{Other._min.x(),_min.y(),Other._max.z()+1};
            max = Coord{Other._max.x(),Other._min.y()-1,_max.z()};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 3
            min = Coord{Other._max.x()+1,_min.y(),Other._max.z()+1};
            max = Coord{_max.x(),Other._min.y()-1,_max.z()};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 4
            min = Coord{_min.x(),Other._min.y(),Other._max.z()+1};
            max = Coord{Other._min.x()-1,Other._max.y(),_max.z()};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // Middle
            min = Coord{Other._min.x(),Other._min.y(),Other._max.z()+1};
            max = Coord{Other._max.x(),Other._max.y(),_max.z()};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 5
            min = Coord{Other._max.x()+1,Other._min.y(),Other._max.z()+1};
            max = Coord{_max.x(),Other._max.y(),_max.z()};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 6
            min = Coord{_min.x(),Other._max.y()+1,Other._max.z()+1};
            max = Coord{Other._min.x()-1,_max.y(),_max.z()};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 7
            min = Coord{Other._min.x(),Other._max.y()+1,Other._max.z()+1};
            max = Coord{Other._max.x(),_max.y(),_max.z()};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            // 8
            min = Coord{Other._max.x()+1,Other._max.y()+1,Other._max.z()+1};
            max = Coord{_max.x(),_max.y(),_max.z()};

            if(min<=max){
                Result.emplace_back(min,max);
            }

            return Result;
        }

        [[nodiscard]] Coord min() const{
            return _min;
        }

        [[nodiscard]] Coord max() const{
            return _max;
        }
    };
}

namespace util {
    using namespace std;
    string hexToBinary(const string &input){
        string result;

        for (auto character : input) {
            switch (character) {
                case '0':
                    result.append("0000");
                    break;
                case '1':
                    result.append("0001");
                    break;
                case '2':
                    result.append("0010");
                    break;
                case '3':
                    result.append("0011");
                    break;
                case '4':
                    result.append("0100");
                    break;
                case '5':
                    result.append("0101");
                    break;
                case '6':
                    result.append("0110");
                    break;
                case '7':
                    result.append("0111");
                    break;
                case '8':
                    result.append("1000");
                    break;
                case '9':
                    result.append("1001");
                    break;
                case 'A':
                    result.append("1010");
                    break;
                case 'B':
                    result.append("1011");
                    break;
                case 'C':
                    result.append("1100");
                    break;
                case 'D':
                    result.append("1101");
                    break;
                case 'E':
                    result.append("1110");
                    break;
                case 'F':
                    result.append("1111");
                    break;
                default:
                    cout << "Unexpected character! "<<character<<endl;
            }
        }
        return result;
    }
}

namespace PacketParser {
    //AoC 2021 Day 16
    using namespace std;
    class Packet{
    protected:
        uint64_t version;
        uint64_t typeID;
    public:
        Packet(uint64_t version, uint64_t typeID)
                :version(version)
                ,typeID(typeID){}

        virtual uint64_t sumVersions() const {return 0;};
        virtual uint64_t evaluate() const { return 0; };
    };

    class Literal
            : public Packet
    {
        uint64_t literal_value;
    public:
        Literal(uint64_t version,uint64_t value)
                : Packet(version,4)
                ,literal_value(value)
        {}

        virtual uint64_t evaluate() const override{
            return literal_value;
        }

        virtual uint64_t sumVersions() const override{
            return version;
        }
    };

    class Operator
            :public Packet
    {
        std::vector<std::shared_ptr<Packet>> _subPackets;
    public:
        using Packets = std::vector<std::shared_ptr<Packet>>;
        Operator(uint64_t version, uint64_t typeId, Packets subPackets)
                : Packet(version,typeId)
                ,_subPackets(subPackets){}

        virtual uint64_t sumVersions() const override{
            return std::accumulate(_subPackets.begin(),_subPackets.end(),version,[](uint64_t current, const auto& packet){
                return current+packet->sumVersions();
            });
        }

        virtual uint64_t evaluate() const override{
            switch(typeID){
                case 0:
                    return std::accumulate(_subPackets.begin(), _subPackets.end(),(uint64_t)0LL,[](uint64_t current, auto& pack){
                        return current+pack->evaluate();
                    });
                case 1:
                    return std::accumulate(_subPackets.begin(), _subPackets.end(),(uint64_t)1LL,[](uint64_t current, auto& pack){
                        return current*pack->evaluate();
                    });
                case 2:
                    return std::accumulate(_subPackets.begin(), _subPackets.end(),std::numeric_limits<uint64_t>::max(),[](uint64_t current, auto& pack){
                        return min(current,pack->evaluate());
                    });
                case 3:
                    return std::accumulate(_subPackets.begin(), _subPackets.end(),0LL,[](uint64_t current, auto& pack){
                        return max(current,pack->evaluate());
                    });
                case 5:
                    assert(_subPackets.size()==2);
                    if(_subPackets[0]->evaluate()>_subPackets[1]->evaluate()){
                        return 1;
                    }else{
                        return 0;
                    }
                case 6:
                    assert(_subPackets.size()==2);
                    if(_subPackets[0]->evaluate()<_subPackets[1]->evaluate()){
                        return 1;
                    }else{
                        return 0;
                    }
                case 7:
                    assert(_subPackets.size()==2);
                    if(_subPackets[0]->evaluate()==_subPackets[1]->evaluate()){
                        return 1;
                    }else{
                        return 0;
                    }
                default:
                    cout << "Should not happen" << endl;
                    return -1;
            }
        }
    };

}
#endif //ADVENTOFCODE2022_LIB_H
