#ifndef UTILITY_H_
#define UTILITY_H_

#include "../Tuple/tuple.h"

namespace mylib
{
    size_t strlen(const char *s)
    {
        size_t count = 0;
        while(*s!='\0')
        {
            count++;
            s++;
        }
        return count;
    }
} // namespace mylib
 
namespace mylib
{
    template <typename T1, typename T2>
    struct pair
    {
    public:
        constexpr pair();
        constexpr pair(const T1& x, const T2& y);
        constexpr pair(T1&& x, T2&& y);
        pair(const pair<T1, T2>& rhs);
        pair(pair<T1, T2>&& rhs);
        template <typename U1, typename U2>
        pair(const pair<U1, U2>& rhs);
        template <typename U1, typename U2>
        constexpr pair(mylib::tuple<U1, U2>&& rhs);
        // template <typename... Args1, typename... Args2>
        // constexpr pair(std::piecewise_construct_t,
        //     std::tuple<Args1...> first_args, std::tuple<Args2...> second_args);
        bool operator<(const pair& rhs) {
            return this->first < rhs.first;
        }
    public:
        T1 first;
        T2 second;
    };
    
    template <typename T1, typename T2>
    mylib::pair<T1, T2> make_pair(T1 in_first, T2 in_second)
    {
        return mylib::pair<T1, T2>(in_first, in_second);
    }

} // namespace mylib

template <typename T1, typename T2>
constexpr mylib::pair<T1, T2>::pair() : first {}, second {} {}

template <typename T1, typename T2>
constexpr mylib::pair<T1, T2>::pair(const T1& x, const T2& y) : first {x}, second {y} {}

template <typename T1, typename T2>
constexpr mylib::pair<T1, T2>::pair(T1&& x, T2&& y) : first {x}, second {y} {}

template <typename T1, typename T2>
mylib::pair<T1, T2>::pair(const mylib::pair<T1, T2>& rhs) :
first {rhs.first}, second {rhs.second} {}

template <typename T1, typename T2>
mylib::pair<T1, T2>::pair(mylib::pair<T1, T2>&& rhs) :
first {rhs.first}, second {rhs.second} {}

template <typename T1, typename T2>
template <typename U1, typename U2>
mylib::pair<T1, T2>::pair(const mylib::pair<U1, U2>& rhs) :
first (rhs.first), second (rhs.second) {} //()-> enabled narrowing convert

template <typename T1, typename T2>
template <typename U1, typename U2>
constexpr mylib::pair<T1, T2>::pair(mylib::tuple<U1, U2>&& rhs) 
        : first(mylib::get<0>(std::forward<U1>(rhs))),
          second(mylib::get<1>(std::forward<U2>(rhs))) {}

#endif //UTILITY_H_