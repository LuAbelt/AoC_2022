//
// Created by lukas on 25/11/2022.
//

#ifndef ADVENTOFCODE2022_LIB_H
#define ADVENTOFCODE2022_LIB_H

#if __APPLE__
#include <iostream>
#include <map>
#include <vector>
#include <compare>
#include <queue>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <algorithm>
#include <sstream>
#endif

#include <bits/stdc++.h>

#include <utility>

//Definitions
#define impossible "impossible"

struct WeightedEdge;

//Using declarations
using namespace std;
using i64 = int64_t;
using i32 = int32_t;
using ui64 = uint64_t;
using ui32 = uint32_t;
using st = ::size_t;

template<typename T>
using V = vector<T>;

using Adj = V<V<i64>>;
using AdjWeighted = V<V<WeightedEdge>>;

using ipair = pair<i32,i32>;
using uipair = pair<ui32,ui32>;
using i64pair = pair<i64,i64>;
using ui64pair = pair<ui64,ui64>;

template <typename T>
constexpr T maxval(){
    return numeric_limits<T>::max();
}

template<class ContainerTy, typename ValTy>
concept HasEmplaceBack = requires (ContainerTy &C, ValTy v) {
        C.emplace_back(v);
};

template<class ContainerTy, typename ValTy>
concept HasEmplaceFront = requires (ContainerTy &C, ValTy v) {
    C.emplace_front(v);
};

template<class ContainerTy, typename ValTy>
concept HasEmplace = requires (ContainerTy &C, ValTy v) {
    C.emplace(v);
};

template <class ContainerTy>
concept HasPopFront = requires (ContainerTy &C) {
    C.pop_front();
};

template <class ContainerTy>
concept HasPopBack = requires (ContainerTy &C) {
    C.pop_back();
};

template <class ContainerTy>
concept HasPop = requires (ContainerTy &C) {
    C.pop();
};


// Forbidden Operator Overloads

template<class>
inline constexpr bool dependent_false = false;

/**
 * Adds a convenient operator to simply "add" elements to a vector
 * @param val Value to be added
 */
template<class T1, typename T2>
T1& operator+=(T1 &v, const T2 val)
requires HasEmplaceBack<T1, T2> || HasEmplace<T1,T2>
{
    if constexpr (HasEmplaceBack<T1,T2>) {
        v.emplace_back(val);
    } else if constexpr(HasEmplace<T1,T2>){
        v.emplace(val);
    } else {
        static_assert(dependent_false<T1>, "Could not invoke += operator");
    }
    return v;
}

template<class T1, typename T2>
T2& operator+=(T2 val, T1 &v)
requires HasEmplaceFront<T1, T2> || HasEmplace<T1,T2>
{
    if constexpr (HasEmplaceFront<T1,T2>) {
        v.emplace_front(val);
    } else if constexpr(HasEmplace<T1,T2>){
        v.emplace(val);
    } else {
        static_assert(dependent_false<T1>, "Could not invoke += operator");
    }
    return val;
}

template<class ContainerTy, typename ValueTy>
ContainerTy operator+(ContainerTy &C, const ValueTy &V)
requires HasEmplaceBack<ContainerTy, ValueTy> || HasEmplace<ContainerTy, ValueTy>
{
    if constexpr (HasEmplaceBack<ContainerTy,ValueTy>){
        C.emplace_back(V);
    } else {
        C.emplace(V);
    }

    return C;
}

template<class ContainerTy, typename ValueTy>
ContainerTy operator+(const ValueTy &V, ContainerTy &C)
requires HasEmplaceFront<ContainerTy, ValueTy> || HasEmplace<ContainerTy, ValueTy>
{
    if constexpr (HasEmplaceBack<ContainerTy,ValueTy>){
        C.emplace_front(V);
    } else {
        C.emplace(V);
    }

    return C;
}

template<typename T>
T& operator--(T &d)
requires HasPopFront<T> || HasPop<T>
{
    if constexpr (HasPopFront<T>){
        d.pop_front();
    } else if constexpr (HasPop<T>) {
        d.pop();
    } else {
        static_assert(dependent_false<T>, "Could not invoke -- operator");
    }
    return d;
}

template<typename T>
T& operator--(T &d,int)
requires HasPopBack<T> || HasPop<T>
{
    if constexpr (HasPopBack<T>) {
        d.pop_back();
    } else if constexpr (HasPop<T>){
        d.pop();
    } else {
        static_assert(dependent_false<T>, "Could not invoke -- operator");
    }
    return d;
}

template<typename T>
T& operator+(T &Instance){
    for (auto &value : Instance) {
        value = abs(value);
    }

    return Instance;
}

template<typename T>
T& operator-(T &Instance){
    for (auto &value : Instance) {
        value = -value;
    }

    return Instance;
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

    template<typename T>
    void sort(T &first, T &second){
        if(second<first){
            std::swap(first,second);
        }
    }

    void strip(string &s, char stripChar = ' ') {
        st begin = s.find_first_not_of(stripChar);
        st end = s.find_last_not_of(stripChar);

        if(end!=string::npos){
            ++end;
        }

        s = s.substr(begin,end-begin);
    }

    V<string> split(const string &input, string separator = " ", bool strip = true) {
        assert(separator.length()>0 && "util::split called with an empty separator string");

        V<string> result;
        const st sepLength = separator.length();

        st begin = 0;
        st end = input.find(separator);

        while(begin!=string::npos){
            auto element = input.substr(begin, end-begin);

            if(strip){
                util::strip(element);
            }

            result.emplace_back(element);

            if( end != string::npos) {
                begin = end+sepLength;
            } else {
                begin = end;
            }

            end = input.find(separator,end+sepLength);

        }

        return result;
    }

    template <typename T>
    V<T> fromString(const V<string> &input) {
        V<T> result;
        result.reserve(input.size());

        for( const auto& line : input ){
            stringstream ss{line};

            T element;
            ss >> element;

            result.emplace_back(element);
        }

        return result;
    }

    template<class... Ts>
    struct Visitor : Ts... {using Ts::operator()...;};
}

//I/O
namespace IO {
    template<typename ...Args>
#if __cplusplus >= 202002L
    requires (sizeof...(Args) > 0)
#endif
    void read(Args &&... args) {
        (cin >> ... >> args);
    }

    template<typename ...Args>
    void print(Args &&... args) {
        ((cout << args << ' '), ...);
        cout << endl;
    }
#if 0
    template <typename T>
    class Generator
    : public ranges::view_base
    {
        class Promise
        {
        public:
            using value_type = T;

            Promise() = default;
            std::suspend_always initial_suspend() { return {}; }
            std::suspend_always final_suspend() noexcept { return {}; }
            void unhandled_exception() {
                std::rethrow_exception(std::move(std::current_exception()));
            }

            std::suspend_always yield_value(T value) {
                this->value = std::move(value);
                return {};
            }

            /*void return_value(T value){
                this->value = move(value);
                _finished = true;
            }*/

            void return_void() {
                _finished = true;
            }

            inline Generator get_return_object();

            value_type get_value() {
                return std::move(value);
            }

            bool finished() {
                return _finished;
            }

        private:
            value_type value{};
            bool _finished = false;
        };

    public:
        using value_type = T;
        using promise_type = Promise;

        explicit Generator(std::coroutine_handle<Promise> handle)
                : handle (handle)
        {}

        Generator(const Generator&) = default;

        ~Generator() {
            if (handle) { handle.destroy(); }
        }

        typename Promise::value_type next() {
            if (handle) {
                handle.resume();
                return handle.promise().get_value();
            }
            else {
                return {};
            }
        }

        struct end_iterator {};

        class iterator
        : public forward_iterator_tag
        {
        public:
            using value_type = typename Promise::value_type;
            using difference_type =  std::ptrdiff_t;
            using iterator_category = std::input_iterator_tag;

            iterator() = default;
            iterator(const Generator& generator) : generator(&generator)
            {}

            value_type operator*() const {
                if (generator) {
                    return generator->handle.promise().get_value();
                }
                return {};
            }

            value_type operator->() const {
                if (generator) {
                    return generator->handle.promise().get_value();
                }
                return {};
            }

            iterator& operator++() {
                if (generator && generator->handle) {
                    generator->handle.resume();
                }
                return *this;
            }

            iterator& operator++(int) {
                if (generator && generator->handle) {
                    generator->handle.resume();
                }
                return *this;
            }

            bool operator== (const end_iterator&) const {
                return generator ? generator->handle.promise().finished() : true;
            }

        private:
            const Generator* generator{};
        };

        [[nodiscard]] iterator begin() const {
            iterator it{*this};
            return ++it;
        }

        const end_iterator end() const {
            return end_sentinel;
        }

    private:
        end_iterator end_sentinel{};
        std::coroutine_handle<Promise> handle;
    };


    template <typename T>
    inline Generator<T> Generator<T>::Promise::get_return_object()
    {
        return Generator{ std::coroutine_handle<Promise>::from_promise(*this) };
    }


    template <typename T>
    class Generator
    : public ranges::view_base
    {
        class Promise
        {
        public:
            using value_type = std::optional<T>;

            Promise() = default;
            std::suspend_always initial_suspend() { return {}; }
            std::suspend_always final_suspend() noexcept { return {}; }
            void unhandled_exception() {
                std::rethrow_exception(std::move(std::current_exception()));
            }

            std::suspend_always yield_value(T value) {
                this->value = std::move(value);
                return {};
            }

            // void return_value(T value) {
            //     this->value = std::move(value);
            // }

            void return_void() {
                this->value = std::nullopt;
            }

            inline Generator get_return_object();

            value_type get_value() {
                return std::move(value);
            }

            bool finished() {
                return !value.has_value();
            }

        private:
            value_type value{};
        };

    public:
        using value_type = T;
        using promise_type = Promise;

        explicit Generator(std::coroutine_handle<Promise> handle)
                : handle (handle)
        {}

        ~Generator() {
            if (handle) { handle.destroy(); }
        }

        Promise::value_type next() {
            if (handle) {
                handle.resume();
                return handle.promise().get_value();
            }
            else {
                return {};
            }
        }

        struct end_iterator {};

        class iterator
        {
        public:
            using value_type = Promise::value_type;
            using difference_type =  std::ptrdiff_t;
            using iterator_category = std::input_iterator_tag;

            iterator() = default;
            iterator(Generator& generator) : generator{&generator}
            {}

            value_type operator*() const {
                if (generator) {
                    return generator->handle.promise().get_value();
                }
                return {};
            }

            value_type operator->() const {
                if (generator) {
                    return generator->handle.promise().get_value();
                }
                return {};
            }

            iterator& operator++() {
                if (generator && generator->handle) {
                    generator->handle.resume();
                }
                return *this;
            }

            iterator& operator++(int) {
                if (generator && generator->handle) {
                    generator->handle.resume();
                }
                return *this;
            }

            bool operator== (const end_iterator&) const {
                return generator ? generator->handle.promise().finished() : true;
            }

        private:
            Generator* generator{};
        };

        iterator begin() {
            iterator it{*this};
            return ++it;
        }

        end_iterator end() {
            return end_sentinel;
        }

    private:
        end_iterator end_sentinel{};
        std::coroutine_handle<Promise> handle;
    };


    template <typename T>
    inline Generator<T> Generator<T>::Promise::get_return_object()
    {
        return Generator{ std::coroutine_handle<Promise>::from_promise(*this) };
    }
f
    Generator<string> from_cin(){
        string s;
        while(getline(cin,s)){
            co_yield std::move(s);
        }
        co_return;
    }
#endif

    V<string> fromCin() {
        V<string> result;

        for(string line;getline(cin,line);){
            result.emplace_back(line);
        }

        return result;
    }
}

namespace data_structures {

    template <typename ValueTy>
    class RecursiveList {
        using VectorTy = V<shared_ptr<RecursiveList>>;

        variant<ValueTy,VectorTy> _data;
    public:
        explicit RecursiveList(ValueTy &data)
                :_data(data)
        {}

        explicit RecursiveList(VectorTy &data)
                :_data(data)
        {}

        void print(st indent = 0) const {

            string prefix;
            for(st i=0;i<indent;++i){
                prefix+="\t";
            }
            std::visit(util::Visitor{
                    [&prefix](ValueTy arg) -> void { cout << prefix << arg;},
                    [&prefix, &indent](VectorTy contents) -> void {
                        cout << prefix << "[" << endl;
                        for(auto& item : contents){
                            item->print(indent+1);
                            cout << "," <<endl;
                        }
                        cout << prefix << "]";

                        if(indent==0){
                            cout << endl;
                        }
                    }
            }, _data);
        }

        [[nodiscard]] string toString() const {
            string r;

            r = std::visit<string>(util::Visitor{
                [this](ValueTy value){
                    stringstream ss;
                    ss << value;
                    string res = ss.str();
                    return res;
                },
                [this](VectorTy contents){
                    string res;
                    res += "[";
                    for(auto& item : contents){
                        res+=item->toString();
                        if(item !=contents.back() ) res+= ",";
                    }
                    res+= "]";

                    return res;
                }
            }, _data);

            return r;
        }

        void printFlat(st indent = 0) const {
            cout << toString() << endl;
        }

        strong_ordering operator<=>(RecursiveList<ValueTy> const& Other) const {
            return std::visit(
                    util::Visitor{
                        [](ValueTy left, ValueTy right){ return left <=> right; },
                        [this](ValueTy, VectorTy right){
                            if(right.size()>0){
                                auto cmpRes = *this <=> *right[0];
                                if(cmpRes == 0 && right.size()>1) {
                                    return strong_ordering::less;
                                }
                                return cmpRes;
                            } else {
                                return strong_ordering::greater;
                            }
                        },
                        [Other](VectorTy left, ValueTy){
                            if(left.size()>0){
                                auto cmpRes = *left[0] <=> Other;
                                if(cmpRes == 0 && left.size()>1){
                                    return strong_ordering::greater;
                                }
                                return cmpRes;
                            } else {
                                return strong_ordering::less;
                            }
                        },
                        [](VectorTy left, VectorTy right){
                            for(st idx = 0;idx<left.size() && idx<right.size();++idx){
                                auto compRes = *left[idx] <=> *right[idx];
                                if(compRes!=0) {
                                    return compRes;
                                }
                            }

                            return left.size() <=> right.size();
                        }
                        }
                    , _data, Other._data
                    );
        }
    };

    template<typename ValueTy, char ListBegin = '[', char ListEnd = ']', char Delimiter = ','>
    shared_ptr<RecursiveList<ValueTy>> parseRecList(string &input, st &idx) {
        using ListTy = RecursiveList<ValueTy>;
        using PtrTy = shared_ptr<ListTy>;
        using VecTy = V<PtrTy>;
        VecTy contents;
        while(idx < input.size() && input[idx]!=ListEnd){
            //TODO: Generalize value parsing?
            if(isdigit(input[idx])) {
                i64 value = 0;
                while(isdigit(input[idx])){
                    value *= 10;
                    value += input[idx]-'0';
                    idx++;
                }
                contents.emplace_back(make_shared<ListTy>(value));
            }

            if(input[idx]==ListBegin){
                idx+=1;
                contents.emplace_back(parseRecList<ValueTy>(input,idx));
            }

            if(input[idx]==Delimiter) {
                ++idx;
            }

            /*
            ValueTy value = parseValue(input,idx);
            contents.emplace_back(make_shared<ListTy>(value));*/
        }
        ++idx;

        return make_shared<ListTy>(contents);
    }

    template<typename ValueTy = i64, char ListBegin = '[', char ListEnd = ']', char Delimiter = ','>
    shared_ptr<RecursiveList<ValueTy>> parseRecList(string input) {
        st idx = 1;
        return parseRecList<ValueTy,ListBegin,ListEnd,Delimiter>(input,idx);
    }

    template<typename ValueType=i64>
    class Tree {
        using MapTy = map<string,shared_ptr<Tree>>;
        ValueType _value;
        string _name;
        MapTy _children;
        shared_ptr<Tree> _parent;
    public:
        explicit Tree(string name, ValueType value, shared_ptr<Tree> parent = nullptr)
        :_value(value)
        ,_name(std::move(name))
        ,_parent(parent)
        {}

        Tree(Tree&) = default;
        Tree(Tree &&) = default;

        shared_ptr<Tree> parent() const {
            return _parent;
        }

        [[nodiscard]] string name() const{
            return name;
        }

        [[nodiscard]] ValueType value() const {
            return _value;
        }

        const MapTy &getChildren() const {
            return _children;
        }

        bool hasChild(const string &name) const {
            return _children.find(name)!=_children.end();
        }

        void addChild(shared_ptr<Tree<>> child){
            _children[child->_name] = child;
        }

        template<typename InitTy = ValueType, typename BinaryOp = std::plus<InitTy>>
        InitTy evaluate(BinaryOp Op = std::plus<InitTy>{}, InitTy Init = ValueType{}){
            auto result = Init;

            for(const auto& child : _children) {
                result = Op(result,child.second->evaluate(Op,Init));
            }

            return Op(result, _value);
        }
    };

    class UnionFind{
    private:
        vector<i64> parent, rank;
    public:
        explicit UnionFind(i64 size){
            parent = V<i64>(size);
            rank.assign(size, 0);
            for (i64 i = 0; i < size; ++i) {
                parent[i] = i;
            }
        }

        void unionSet(i64 i, i64 j) {
            i = findSet(i), j = findSet(j);

            if(!isSameSet(i,j)){
                if(rank[i] > rank[j]){
                    parent[j] = i;
                } else {
                    parent[i] = j;
                    if(rank[i]==rank[j]){
                        rank[j]++;
                    }
                }
            }
        }

        i64 findSet(i64 i){
            if(parent[i] == i){
                return i;
            } else {
                return parent[i] = findSet(parent[i]);
            }
        }

        bool isSameSet(i64 i, i64 j){
            return findSet(i) == findSet(j);
        }
    };

    /**
 * A generic segment tree that supports range queries and point updates
 * @tparam OpType
 * @tparam Neutral
 */
    template<typename OpType = std::plus<i64>, i64 Neutral = 0>
    class SegTree{
        vector<i64> values;
        st size;
        OpType BinaryOp;
        [[nodiscard]] st parent(st idx) const { return idx / 2;}
        [[nodiscard]] st left(st idx) const { return 2*idx;}
        [[nodiscard]] st right(st idx) const { return 2*idx+1;}

        void update_rec(st idx) {
            values[idx] = BinaryOp(values[left(idx)], values[right(idx)]);
            if(idx>1){
                update_rec(parent(idx));
            }
        }

        i64 query_rec(i64 i, i64 j, i64 l, i64 r, i64 cur_node) const {
            if(r <= i || j<= l){
                return Neutral;
            }

            if(r<=j && i<=l){
                return values[cur_node];
            }

            i64 m = (l+r)/2;
            return BinaryOp(query_rec(i,j,l,m,left(cur_node)),
                            query_rec(i,j,m,r, right(cur_node)));
        }

    public:
        SegTree(st size, OpType Op)
                :BinaryOp(Op)
        {
            this->size = 1 << (st)ceil(log2(size));

            values.assign(2 * this->size, 0);
        }

        SegTree(V<i64> &Data, OpType Op)
                :SegTree(Data.size(), Op){
            for(st idx = 0; idx < Data.size(); ++idx){
                values[idx+size] = Data[idx];
            }

            for(st idx = size-1;idx>0;--idx){
                values[idx] = BinaryOp(values[left(idx)],values[right(idx)]);
            }
        }

        i64 query(st left, st right){
            return query_rec(left, right, 0, size, 1);
        }

        void update(st idx, i64 val){
            values[idx + size] = val;
            update_rec(parent(idx+size));
        }


    };
}

namespace bits {
    /**
 * Checks whether a given bit is set in a number
 * @param v Value to check against
 * @param pos Bit to check for (0 means checking LSB)
 * @return true if the pos-th bit is set to 1
 */
    bool is_bit_set(i64 v, ::size_t pos){
        return (v & (1 << pos)) != 0;
    }

    void flip_bit(i64 x, st pos){
        x ^= (1 << pos);
    }

    void set_bit(i64 x, st pos){
        x |= (1 << pos);
    }

    void unset_bit(i64 x, st pos){
        x &= ~(1 << pos);
    }

    void set_right_bits(i64 x, st bits){
        x |= (1 << bits) - 1;
    }
}

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
#if __APPLE__
            for(st idx = 0; idx < Dimensions;++idx){
                auto res = _coords[idx] <=> Other._coords[idx];
                if(res!=0) {
                    return res;
                }
            }
            return decltype(_coords[0]<=>Other._coords[0])::equivalent;
#else
            return _coords <=> Other._coords;
#endif
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
        i64 x,y;

	    auto operator<=>(const Point&) const = default;
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

namespace math {
    /**
* A class that holds Prefix sums of a 1D array.
*
* Can be queried easily for a given index or range
*/
    template <typename ValueTy>
    class PrefixSum {
    private:
        V<ValueTy> _prefixSums;
    public:
        /**
         * Initialize a PrefixSum data structure
         * @param input Vecot to calculate prefix sums for
         */
        PrefixSum(V<ValueTy> &input){
            _prefixSums = V<i64>(input.size());

            _prefixSums[0] = input[0];

            for (st i = 1; i < input.size(); ++i) {
                _prefixSums[i] = _prefixSums[i-1]+input[i];
            }
        }

        /**
         * Query a given range for it's sum
         * @param begin first index to include
         * @param end last index to include
         * @return The sum of all values between begin and end (both inclusive)
         */
        ValueTy query(st begin, st end) const{
            if(begin>0){
                return _prefixSums[end]-_prefixSums[begin];
            }

            return query(end);
        }

        ValueTy query(st end) const{
            return query(end);
        }
    };

/**
 * A class that holds Prefix sums of a 2D array.
 *
 * Can be queried easily for a given index or range
 */
    template<typename ValueTy>
    class PrefixSum2D {
    private:
        V<V<ValueTy>> _prefixSums;
    public:
        using PairType = pair<st,st>;

        PrefixSum2D(const V<V<ValueTy>> &input){
            _prefixSums = V<V<i64>>(input.size(), V<i64>(input[0].size()));

            _prefixSums[0][0] = input[0][0];

            for (st i = 1; i < input.size(); ++i) {
                _prefixSums[0][i] = _prefixSums[0][i-1]+input[0][i];
            }

            for (st i = 1; i < input.size(); ++i) {
                _prefixSums[i][0] = input[i][0];
                for (st j = 1; j < input[i].size(); ++j) {
                    _prefixSums[i][j] = _prefixSums[i-1][j] + _prefixSums[i][j-1] - _prefixSums[i-1][j-1] + input[i][j];
                }
            }
        }

        ValueTy query(PairType &Pos){
            return _prefixSums[Pos.first][Pos.second];
        }

        ValueTy query(PairType &begin, PairType &end){
            auto res = query(end);

            if(begin.first>0){
                res -= _prefixSums[begin.first-1][end.second];
            }

            if(begin.second > 0){
                res -= _prefixSums[end.first][begin.second-1];
            }

            if(begin.first > 0 && begin.second > 0){
                res += _prefixSums[begin.first-1][begin.second-1];
            }

            return res;
        }
    };
/**
 * Calculates the longest increasing subsequence in a given vector of numbers
 * @tparam Cmp Comparator to use to check for increasing
 * @param input input vector
 * @param cmp Instance of Cmp
 * @return The length of the longest increasing subsequence
 */
    template <typename Cmp>
    st longest_increasing_subsequence(vector<i64> input, Cmp cmp = less_equal<i64>{}) {
        vector<i64> lis(input.size());
        vector<i64> g(input.size()+1, numeric_limits<i64>::max());

        i64 result = 1;
        lis[0] = 1;
        g[0] = numeric_limits<i64>::lowest();

        g[lis[0]] = min(input[0],g[lis[0]]);

        for (st i = 1; i < input.size(); ++i) {
            auto l_itr = std::upper_bound(g.begin(), std::next(g.begin(),i+1), input[i], less_equal<i64>{});
            i64 l = distance(g.begin(),l_itr);

            lis[i] = l;

            g[lis[i]] = min(input[i],g[lis[i]]);
            result = max(l,result);
        }

        return result;
    };

}

namespace graphs {
    //Graph Stuff
/**
 * A general BFS implementation
 * @param adj Adjacency list for the graph
 * @param startNode Node to start from
 */
    void breadth_first_search(vector<vector<i64>> &adj, i64 startNode){
        vector<bool> visited(adj.size(), false);
        queue<i64> Q;

        Q.push(startNode);
        visited[startNode] = true;

        while (!Q.empty()){
            i64 currentNode = Q.front();
            Q.pop();

            for (auto &neighbour : adj[currentNode]) {
                if(!visited[neighbour]){
                    Q.push(neighbour);
                    visited[neighbour] = true;
                }
            }
        }
    }

/**
 * Function for the recursive call of the DFS, maintainging the visited vector list
 */
    void depth_first_search(vector<vector<i64>> &adj, i64 startNode, vector<bool> &visited){
        stack<i64> open;

        open.push(startNode);
        visited[startNode] = true;

        while (!open.empty()){
            i64 currentNode = open.top();
            open.pop();

            for (auto &neighbour : adj[currentNode]) {
                if(!visited[neighbour]){
                    open.push(neighbour);
                    visited[neighbour] = true;
                }
            }
        }
    }

/**
 * A general DFS implementation
 * @param adj Adjacency list for the graph
 * @param startNode node to start from
 */
    void depth_first_search(vector<vector<i64>> &adj, i64 startNode){
        vector<bool> visited(adj.size(), false);
        depth_first_search(adj,startNode,visited);
    }

/**
 * Finds a eulerian walk for a given start node
 * @note only works on graphs where either:
 *      Each node has exactly as many incoming edges as outcoming edges
 *      OR
 *      Graphs with exactly one node of indegree 1 and 1 node of outdegree 1
 * @param node Node to start from
 * @param walk The resulting walk
 * @param adj Adjacency list for the matrix
 */
    void find_eulerian_walk(i64 node, deque<i64> &walk, vector<vector<i64>> &adj){
        while (!adj[node].empty()){
            i64 v = adj[node].back();
            adj[node].pop_back();
            find_eulerian_walk(v, walk, adj);
        }

        walk.push_front(node);
    }

/**
 * Counts the number of connected components on a graoh
 * @param adj Adjacency List for the graph
 * @return The number of connected components in the graph
 * @note Only works on undirected graphs
 */
    st count_connected_components(vector<vector<i64>> &adj){
        st result = 0;
        vector<bool> visited(adj.size(), false);

        for (int i = 0; i < adj.size(); ++i) {
            if(!visited[i]){
                depth_first_search(adj,i,visited);
                ++result;
            }
        }

        return result;
    }


/**
 * Gets a list of all the connected components in a graph
 * @param adj Adjacency list for this graph
 * @return All connected components in the graph
 * @note Only works on undirected graphs
 */
    vector<vector<i64>> get_connected_components(vector<vector<i64>> &adj){
        vector<bool> visited(adj.size(), false);
        vector<vector<i64>> result;

        for (int i = 0; i < adj.size(); ++i) {
            if(!visited[i]){
                //dfs
                vector<i64> component{};

                stack<i64> open;

                open.push(i);
                visited[i] = true;

                while (!open.empty()){
                    i64 currentNode = open.top();
                    open.pop();
                    component.emplace_back(currentNode);

                    for (auto &neighbour : adj[currentNode]) {
                        if(!visited[neighbour]){
                            open.push(neighbour);
                            visited[neighbour] = true;
                        }
                    }
                }

                result.emplace_back(component);
            }
        }

        return result;
    }

/**
 * Recursive part of a topological sort
 * @return
 */
    bool topological_sort(vector<vector<i64>> &adj, vector<bool> &visited, vector<bool> &tmp, i64 current, deque<i64> &topo_sort){
        if(visited[current]){
            return true;
        }

        if(tmp[current]){
            topo_sort.clear();
            return false;
        }
        tmp[current] = true;

        for (auto next : adj[current]) {
            if(!topological_sort(adj,visited, tmp, next, topo_sort)){
                return false;
            }
        }

        tmp[current] = false;
        visited[current] = true;
        topo_sort.push_front(current);
        return true;
    }

/**
 * Returns a full topological sort over a graph
 * @param adj Adjacency list of this graph
 * @return A topological order of the nodes in the graph
 * @note Beware that nodes of different connected components may appear in arbitrary order
 */
    deque<i64> full_topological_sort(vector<vector<i64>> &adj){
        vector<bool> visited(adj.size(), false);
        vector<bool> tmp(adj.size(), false);
        deque<i64> result{};

        for (int i = 0; i < adj.size(); ++i) {
            if(!visited[i]){
                if(!topological_sort(adj,visited,tmp,i,result)){
                    return {};
                }
            }
        }

        return result;
    }

/**
 * Calculates a topological sort for a specific set of nodes in a graph
 */
    deque<i64> topological_sort(vector<vector<i64>> &adj, vector<i64> &nodes){
        vector<bool> visited(adj.size(), false);
        vector<bool> tmp(adj.size(), false);
        deque<i64> result{};

        for (auto i : nodes) {
            if(!visited[i]){
                if(!topological_sort(adj,visited,tmp,i,result)){
                    return {};
                }
            }
        }

        return result;
    }

    struct WeightedEdge {
        i64 weight;
        i64 target;
    };

    namespace graph_detail {
        constexpr i64 UNVISITED = -1;
        constexpr i64 VISITED = -2;
        void bridge_dfs(i64 node, const Adj &adj, V<i64> &dfs_min, V<i64> &dfs_num
                ,V<i64> &dfs_parent,i64 &dfs_root, i64 &dfs_cnt, i64 &rootChildren,
                        set<i64pair> &bridges, set<i64> &ap){
            dfs_min[node] = dfs_num[node] = dfs_cnt++;

            for (const auto v : adj[node]) {
                if(dfs_num[v] == UNVISITED) {
                    dfs_parent[v] = node;

                    if (node == dfs_root) {
                        rootChildren++;
                    }

                    bridge_dfs(v, adj, dfs_min, dfs_num, dfs_parent, dfs_root,
                               dfs_cnt, rootChildren, bridges, ap);

                    if (dfs_num[node] <= dfs_min[v] && node != dfs_root) {
                        ap.emplace(node);
                    }

                    if (dfs_num[node] < dfs_min[v]) {
                        bridges.emplace(node, v);
                    }

                    dfs_min[node] = min(dfs_min[node], dfs_min[v]);
                } else if (v != dfs_parent[node]) {
                    dfs_min[node] = min(dfs_min[node], dfs_num[v]);
                }
            }
        }

        pair<set<i64pair>,set<i64>> getAPAndBridges(const Adj &adj){
            set<i64pair> bridges;
            set<i64> ap;


            i64 dfs_cnt = 0;

            i64 dfsRoot, rootChildren;

            V<i64> dfs_num(adj.size(),UNVISITED);
            V<i64> dfs_min(adj.size(),UNVISITED);
            V<i64> dfs_parent(adj.size(),UNVISITED);

            for (i64 i = 0; i < adj.size(); ++i) {
                if (dfs_num[i] == UNVISITED){
                    dfsRoot = i;
                    rootChildren = 0;
                    bridge_dfs(i, adj, dfs_min, dfs_num, dfs_parent, dfsRoot,dfs_cnt,rootChildren,bridges,ap);

                    if(rootChildren > 1){
                        ap.emplace(i);
                    }
                }
            }

            return {bridges, ap};
        }

        void ssc_dfs(i64 node, Adj &adj, V<i64> &dfs_num, V<i64> &dfs_min, V<bool> &on_stack, i64 &dfsCnt, stack<i64> &S, deque<V<i64>> &ssc){
            dfs_min[node] = dfs_num[node] = dfsCnt++;

            S.push(node);
            on_stack[node] = true;

            for (auto v: adj[node]) {
                if (dfs_num[v] == UNVISITED) {
                    ssc_dfs(v, adj, dfs_num, dfs_min, on_stack, dfsCnt, S, ssc);
                    dfs_min[node] = min(dfs_min[node], dfs_min[v]);
                } else if (on_stack[v]) {
                    dfs_min[node] = min(dfs_min[node], dfs_min[v]);
                }
            }
            if (dfs_min[node] == dfs_num[node]) {
                V<i64> component;
                i64 v = -1;

                while(v != node){
                    v = S.top();
                    S.pop();
                    on_stack[v] = false;
                    component.push_back(v);
                }

                ssc.push_front(component);
            }
        }

        using data_structures::UnionFind;

        void lca_dfs(i64 node, Adj &adj, UnionFind &UF, V<i64> &ancestor, V<bool> &visited,V<V<pair<i64,st>>> &queries, V<i64> &results){
            for(auto &v : adj[node]){
                lca_dfs(v, adj, UF, ancestor, visited,queries,results);
                UF.unionSet(node,v);
                ancestor[UF.findSet(node)] = node;
            }

            visited[node] = true;
            for (auto &query : queries[node]) {
                int v,id;
                tie(v,id) = query;

                if(visited[v]){
                    results[id] = ancestor[UF.findSet(v)];
                }
            }
        }

        void maxflow_bfs(st source, Adj &adj, Adj &capacity, V<st> &parent){
            parent.assign(adj.size(), UNVISITED);
            parent[source] = VISITED;

            queue<st> Q;
            Q.push(source);

            while(!Q.empty()){
                int current = Q.front(); Q.pop();
                for (auto next : adj[current]) {
                    if(parent[next] == -1 && capacity[current][next]>0){
                        Q.push(next);
                        parent[next] = current;
                    }
                }
            }
        }

        /**
         * Assuming we have a topological order on a DAG
         *
         * We can use this DP DFS approach to easily calculate a lot of stuff
         * (in this example shortest path) in O(N)
         */
        void dp_dfs(V<V<WeightedEdge>> &adj, V<i64> &topological_order){
            V<i64> dist(topological_order.size());

            // Initialization
            st start = 0;
            dist[start] = 0;

            for (auto node : topological_order) {
                for (auto edge : adj[node]) {

                    // Change this line for other applications
                    dist[edge.target] = min(dist[edge.target], dist[node] + edge.weight);
                }
            }
        }
    }

/**
 * Gets all bridges in a graph
 */
    set<i64pair> getBridges(const Adj &adj){
        return graph_detail::getAPAndBridges(adj).first;
    }

/**
 * Gets all articulation points in a graph
 */
    set<i64> getArticulationPoints(const Adj &adj){
        return graph_detail::getAPAndBridges(adj).second;
    }

/**
 * Gets all strongly connected components in a graph
 * @param adj Adjacency list of this graph
 * @param nodes Nodes to limit the search to (May be useful when working on multiple disconnected components)
 * @return A topological order of all strongly connected components
 */
    deque<vector<i64>> getStronglyConnectedComponents(Adj &adj, vector<i64> &nodes){
        using graph_detail::UNVISITED;

        stack<i64> S;
        i64 dfsCnt = 0;

        V<i64> dfs_num(adj.size(), UNVISITED);
        V<i64> dfs_min(adj.size(), UNVISITED);
        V<bool> on_stack(adj.size(), false);

        deque<V<i64>> res;

        for (auto node : nodes) {
            if(dfs_num[node]==UNVISITED){
                graph_detail::ssc_dfs(node, adj, dfs_num, dfs_min, on_stack, dfsCnt , S, res);
            }
        }

        return res;
    }

/**
 * Standard Dijkstra implementation
 */
    vector<i64> dijkstra(vector<vector<WeightedEdge>> &adj, i64 start){
        vector<i64> dist(adj.size(), maxval<i64>());
        dist[start] = 0;

        priority_queue<i64pair,vector<i64pair>,greater<>> frontier;

        frontier.push({0, start});

        while (!frontier.empty()){
            auto front = frontier.top();
            frontier.pop();

            i64 cur_d = front.first;
            i64 node = front.second;

            if(cur_d > dist[node]){
                continue;
            }

            for ( auto edge : adj[node]) {
                i64 target = edge.target;
                i64 weight = edge.weight;

                if(dist[node] + weight < dist[target]){
                    dist[target] = dist[node] + weight;
                    frontier.push({dist[target], target});
                }
            }
        }

        return dist;
    }

    vector<i64> dijkstra_unit(Adj &adj, i64 start){
        vector<i64> dist(adj.size(), maxval<i64>());
        dist[start] = 0;

        priority_queue<i64pair,vector<i64pair>,greater<>> frontier;

        frontier.push({0, start});

        while (!frontier.empty()){
            auto front = frontier.top();
            frontier.pop();

            i64 cur_d = front.first;
            i64 node = front.second;

            if(cur_d > dist[node]){
                continue;
            }

            for ( auto edge : adj[node]) {
                i64 target = edge;
                i64 weight = 1;

                if(dist[node] + weight < dist[target]){
                    //if(target==targetId)IO::print("Updated target dist to ", dist[node] + weight, "from node",node);
                    dist[target] = dist[node] + weight;
                    frontier.push({dist[target], target});
                }
            }
        }

        return dist;
    }

    auto dijkstra(V<V<i64pair>> &adj, i64 start){
        vector<i64> dist(adj.size(), maxval<i64>());
        dist[start] = 0;
        V<i64> parent(adj.size(),0);

        priority_queue<i64pair,vector<i64pair>,greater<>> frontier;

        frontier.push({0, start});

        while (!frontier.empty()){
            auto front = frontier.top();
            frontier.pop();

            i64 cur_d = front.first;
            i64 node = front.second;

            if(cur_d > dist[node]){
                continue;
            }

            for ( auto edge : adj[node]) {
                i64 target = edge.first;
                i64 weight = edge.second;

                if(dist[node] + weight < dist[target]){
                    //if(target==targetId)IO::print("Updated target dist to ", dist[node] + weight, "from node",node);
                    dist[target] = dist[node] + weight;
                    parent[target] = node;
                    frontier.push({dist[target], target});
                }
            }
        }

        return make_tuple(dist,parent);
    }

/**
 * Calculates a minimum spanning tree
 * @param nNodes Number of nodes in the graph
 * @param edges A list of all edges in the graph. An edge is represented as a tuple of:
 * (weight, origin, destination, edgeID)
 * @return
 */
    set<i64> minimum_spanning_tree(i64 nNodes, V<tuple<i64,i64,i64,i64>> edges){
        using data_structures::UnionFind;
        sort(edges.begin(), edges.end());
        UnionFind UF = UnionFind(nNodes);

        set<i64> result;

        for (auto &edge : edges){
            int weight, u, v, id;
            tie(weight, u, v, id) = edge;

            if(!UF.isSameSet(u,v)){
                result.emplace(id);
                UF.unionSet(u,v);
            }
        }

        return result;
    }

/**
 * Calculates all lowest common ancestors based on a list of queries
 * @param adj Adjacency list for this query
 * @param queries Queries for the LCA in form of pairs (first, second)
 * @return A list of the lowest common ancestors in the same order as the queries
 */
    V<i64> lowest_common_ancestor(Adj &adj, V<i64pair> &queries){
        using data_structures::UnionFind;
        auto n = adj.size();
        V<bool> visited(n, false);

        auto UF = UnionFind(n);

        V<V<pair<i64,st>>> lca_queries(n);
        V<i64> result(queries.size());

        i64 id = 0;
        for (auto & query:queries) {
            lca_queries[query.first] += make_pair(query.second, id);
            lca_queries[query.second] += make_pair(query.first, id);
            ++id;
        }

        V<i64> ancestors(n);
        for(i64 i = 0; i<n; ++i){
            ancestors[i] = i;
        }

        graph_detail::lca_dfs(0,adj,UF,ancestors, visited, lca_queries, result);

        return result;
    }

/**
 * Calculates the maximum flow of a graph
 * @param source Source node
 * @param sink Sink node
 * @param adj Adjacency list for the graph
 * @param capacity Capacities for each edge as a adjacency MATRIX
 * @return The maximum flow of the graph
 */
    i64 maxflow(st source, st sink, Adj &adj, Adj &capacity){
        i64 result = 0;
        V<st> parent(adj.size());

        while (true){
            graph_detail::maxflow_bfs(source, adj, capacity, parent);

            if(parent[sink] == -1){
                break;
            }

            i64 bottleneck = maxval<i64>();

            st curNode = sink;

            while(curNode!=source){
                st p = parent[curNode];
                bottleneck = min(bottleneck, capacity[p][curNode]);
                curNode = p;
            }

            curNode = sink;

            while(curNode!=source){
                st p = parent[curNode];
                capacity[p][curNode] -= bottleneck;
                capacity[curNode][p] += bottleneck;
                curNode = p;
            }
            result += bottleneck;
        }

        return result;
    }

}

namespace strings {
    /**
* Calculates the longest suffix prefix vector for a given string
* @param s String to compute LSP for
* @return A vector of LSP for each index of s
*/
    V<st> longest_suffix_prefix(string &s){
        V<st> result(s.length(), 0);
        st prev = 0;
        for (st i = 1; i < s.size();) {
            if(s[i] == s[prev]){
                prev++;
                result[i] = prev;
                i++;
            } else if (prev == 0){
                result[i] = 0;
                i++;
            } else {
                prev = result[prev-1];
            }
        }

        return result;
    }

/**
 * An efficient string matching implementation using LSP
 * @param s String in which to search
 * @param t String to search for in s
 * @return Whether t occurs in s or not
 */
    bool string_match(string &s, string &t){
        st n = s.length();
        st m = t.length();

        st start =0, len = 0;

        auto lsp = longest_suffix_prefix(t);

        while(start+len < n){
            while(len >= m || s[start+len] != t[len]){
                if(len==0){
                    ++start;
                    len = -1;
                    break;
                }

                st skip = len - lsp[len-1];
                start += skip;
                len -= skip;
            }
            ++len;
            if(len==m){
                return true;
            }
        }

        return false;
    }

/**
 * Computes the length of the longest common subsequence of two strings
 * @param first
 * @param second
 * @return Length of the LCS of the two strings
 */
    st longest_common_subsequence(string &first, string & second){
        V<V<st>> dp(first.length(),V<st>(second.length(), 0));

        //Init DP array
        for(st i = 0; i<first.length(); ++i){
            if(first[i]==second[0]){
                dp[i][0] = 1;
            } else if(i>0){
                dp[i][0] = dp[i-1][0];
            }
        }

        for(st i = 0; i<second.length(); ++i){
            if(second[i]==first[0]){
                dp[0][i] = 1;
            } else if (i>0){
                dp[0][i] = dp[0][i-1];
            }
        }

        //Fill DP array
        for (st i = 1; i < first.length(); ++i) {
            for (st j = 1; j < second.length(); ++j) {
                if(first[i] == second[j]){
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        return dp[first.length()-1][second.length()-1];
    }

    /**
 * A simple Trie that can be used for matching sets of strings
 */
    class Trie{
        bool isEndOfString = false;
        st numMatches = 0;
        map<char, unique_ptr<Trie>> children = {};

    public:

        void insert(string &s, st pos = 0){
            numMatches++;
            if(pos==s.length()){
                isEndOfString = true;
                return;
            }

            if(children.count(s[pos])==0){
                children[s[pos]] = make_unique<Trie>();
            }

            children[s[pos]]->insert(s, pos+1);
        }

        bool contains(string &s, st pos = 0) {
            if(pos == s.length()){
                return isEndOfString;
            }

            if(children.count(s[pos])>0){
                return children[s[pos]]->contains(s, pos + 1);
            }

            return false;
        }

        st findPartialMatches(string &query, st pos = 0){
            if(pos == query.length()){
                return numMatches;
            }

            if(children.count(query[pos])>0){
                return children[query[pos]]->findPartialMatches(query, pos + 1);
            }

            return 0;
        }
    };

/**
 * An Abra-Cadabra trie that is fancier than a normal Trie
 */
    class ACTrie{
    public:
        using CallbackType = function<void(st,st,map<st,st>&)>;
    private:
        bool isEndOfString = false;
        st numMatches = 0;
        st numEndings = 0;
        map<char, shared_ptr<ACTrie>> children = {};
        map<st,st> endingLengths;
        shared_ptr<ACTrie> lsp;

        CallbackType callBack;

        friend void preprocess_ACTrie(shared_ptr<ACTrie>);
    public:
        ACTrie() = default;

        ACTrie(CallbackType cb):callBack(cb){};

        void setCallback(CallbackType newCallback){
            callBack = newCallback;
            for (auto c:children) {
                c.second->setCallback(callBack);
            }
        }

        void insert(string &s, st pos = 0){
            numMatches++;
            if(pos==s.length()){
                numEndings++;
                ++endingLengths[s.length()];
                isEndOfString = true;
                return;
            }

            if(children.count(s[pos])==0){
                children[s[pos]] = make_shared<ACTrie>(callBack);
            }

            children[s[pos]]->insert(s, pos+1);
        }

        bool contains(string &s, st pos = 0) {
            if(pos == s.length()){
                return isEndOfString;
            }

            if(children.count(s[pos])>0){
                return children[s[pos]]->contains(s, pos + 1);
            }

            return false;
        }

        st findMatches(string &query, st pos = 0){
            if(pos == query.length()){
                return numMatches;
            }

            if(children.count(query[pos])>0){
                return children[query[pos]]->findMatches(query,pos+1);
            }

            return 0;
        }

        void search(string &s, int i = 0, bool print = true) {
            if(print){
                cout << "Found " << numEndings << " endings at index " << i << endl;
            }

            if (i == s.length()) return; // processing of the string is done

            if (children.count(s[i]) == 0) {
                // The trie node doesn't have the needed character edge...
                if (lsp == nullptr) search(s, i+1, true); // we are at the root node
                else lsp->search(s, i, false); // try to continue search at the LSP
            } else {
                // Edge was found, continue search there and advance the string
                // pointer by one...
                children[s[i]]->search(s, i+1, true);
            }
        }

    };

    void preprocess_ACTrie(shared_ptr<ACTrie> root){
        queue<shared_ptr<ACTrie>> q;
        root->lsp = nullptr;
        q.push(root);

        while (!q.empty()) {
            shared_ptr<ACTrie> u = q.front();
            q.pop();
            for (const auto& it : u->children) { // edge u--c-->v
                char c = it.first;
                shared_ptr<ACTrie> v = it.second;

                // the 'lsp' and 'cnt' values of v will be calculated now...
                shared_ptr<ACTrie> l = u->lsp;
                while (l != nullptr && l->children.count(c) == 0)
                    l = l->lsp;
                if (l == nullptr) {
                    v->lsp = root; // there is no strict suffix-prefix
                } else {
                    v->lsp = l->children[c];
                    v->numEndings += v->lsp->numEndings;
                }
                q.push(v);
            }
        }

    }
}

namespace modulus_calc {
    i64 add(i64 lhs, i64 rhs, i64 p){
        return ((lhs % p) + (rhs % p)) % p;
    }

    i64 mult(i64 lhs, i64 rhs, i64 p){
        return ((lhs % p) * (rhs % p)) % p;
    }

    i64 diff(i64 lhs, i64 rhs, i64 p){
        return ((lhs % p) - (rhs % p)) % p;
    }

    i64 exp(i64 lhs, i64 rhs, i64 p){
        if(rhs == 0){
            return 1;
        } else if(rhs %2 == 1){
            return(lhs*exp(lhs,rhs-1,p)) % p;
        } else {
            i64 r = exp(lhs,rhs/2,p);
            return (r*r) % p;
        }
    }

    i64 div(i64 lhs, i64 rhs, i64 p){
        i64 rhs_inverse = exp(rhs,p-2,p);

        return mult(lhs, rhs_inverse, p);
    }

    i64 binomial_coefficient(i64 n, i64 k, i64 p){
        i64 top = n;

        for(i64 i = 1; i<k ; ++i){
            top = mult(top,n-i,p);
        }

        i64 k_fac = 1;

        for (i64 i = 1; i <= k; ++i) {
            k_fac = mult(k_fac, i, p);
        }

        return div(top,k_fac,p);
    }

    i64 greatest_common_divisor(i64 lhs, i64 rhs){
        if(rhs==0){
            return lhs;
        } else {
            return greatest_common_divisor(rhs,lhs%rhs);
        }
    }

    i64 least_common_multiple(i64 lhs, i64 rhs){
        return (lhs*rhs) / greatest_common_divisor(lhs,rhs);
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
