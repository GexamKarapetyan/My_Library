#ifndef TUPLE_H
#define TUPLE_H

#include <type_traits>

namespace mylib
{
    template <typename... Types>
    class tuple;
   
    template <typename T, typename... Types>
    class tuple <T, Types...>
    {
    public:
        typedef T value_type;
        constexpr tuple() = default;
        constexpr tuple(const T& val, const Types&... types) : value (val), pack(types...) {}
        tuple(const tuple<T, Types...>& rhs) = default;
        tuple(tuple<T, Types...>&& rhs) = default;
        tuple<T, Types...>& operator=(const tuple<T, Types...>& rhs) = default;
        tuple<T, Types...>& operator=(tuple<T, Types...>&& rhs) = default;
        tuple(const tuple<T>& rhs) : value(rhs.value) {}
        template <typename U>
        tuple(const tuple<U>& rhs) : value(rhs.value) {}
        template <typename U>
        tuple(tuple<U>& rhs) : value(rhs.value) {}
        template <typename U, typename... UTypes>
        tuple(tuple<U, UTypes...>& rhs) : value(rhs.value), pack (rhs.pack) {}
        template <typename U, typename... UTypes>
        tuple(const tuple<U, UTypes...>& rhs) : value(rhs.value), pack (rhs.pack) {}        
        template <typename U, typename... UTypes>
        tuple(tuple<U, UTypes...>&& rhs) :  value(std::move(rhs.value)), pack(std::move(rhs.pack)) {}
        template <typename U, typename... UTypes>
        tuple<T, Types...>& operator=(const tuple<U, UTypes...>& rhs) {
            value = rhs.value;
            if constexpr(sizeof...(UTypes) > 1){
                pack = rhs.pack;
            }
            return *this;
        }
        template <typename U, typename... UTypes>
        tuple<T, Types...>& operator=(tuple<U, UTypes...>&& rhs) {
            value = std::move(rhs.value);
            pack = std::move(rhs.pack);
            return *this;
        }
        
        T& operator[](size_t index) {
            if(index == 0) {
                return value;
            }
           return pack[--index];
        }
        const T& operator[](size_t index) const {
            if(index == 0) {
                return value;
            }
            return pack[--index];
        }
        
        auto& get_val() {return value;}
        constexpr auto& get_pack() {return pack;}
        template <typename U>
        U& operator[](size_t index) 
        {
            if(index == 0) {
                return value;
            }
           return pack[--index];
        }
        template <typename U>
        const U& operator[](size_t index) const
        {
            if(index == 0) {
                return value;
            }
            return pack[--index];
        }

        void swap(tuple& rhs)
        {
            tuple tmp = std::move(*this);
            *this = std::move(rhs);
            rhs = std::move(tmp);
        }
         
        ~tuple() = default;
    public:
        T value;
        tuple<Types...> pack; 
    };

    template <typename T>
    class tuple <T>
    {
    public:
        typedef T value_type;
        constexpr tuple() = default;
        constexpr tuple(T val) : value {val} {}
        tuple(const tuple<T>& rhs) = default;
        tuple(tuple<T>&& rhs) = default;
        tuple<T>& operator=(const tuple<T>& rhs) = default;
        tuple<T>& operator=(tuple<T>&& rhs) = default;
        template <typename U>
        tuple(const tuple<U>& rhs) : value(rhs.value) {}
        template <typename U>
        tuple(tuple<U>&& rhs) :  value(std::move(rhs.value)) {}
        template <typename U>
        tuple<T>& operator=(const tuple<U>& rhs) {
            value = rhs.value;
            return *this;
        }
        template <typename U>
        tuple<T>& operator=(tuple<U>&& rhs) {
            value = std::move(rhs.value);
            return *this;
        }
        auto& operator[](size_t index) {return value;}
        const auto& operator[](size_t index) const 
        {
            return value;
        }
        auto& get_val() {return value;}
        void swap(tuple& rhs)
        {
            tuple tmp = std::move(*this);
            *this = std::move(rhs);
            rhs = std::move(tmp);
        }
        ~tuple() = default;
    public:
        T value;
    };

    template <typename Tuple, size_t IDX>
    struct get_pack_
    {
        static auto& help(Tuple& v) {
            return get_pack_<decltype(v.get_pack()), IDX - 1>::help(v.get_pack());
        }
    };

    template <typename Tuple>
    struct get_pack_<Tuple, 1>
    {
        static auto& help(Tuple& v) {
            return v.get_pack();
        }
    };

    template <typename Tuple>
    struct get_pack_<Tuple, 0>
    {
        static auto help(Tuple& v) {
            return v;
        }
    };

    template <typename Tuple, size_t i>
    auto& gett(Tuple& t) { 
        return get_pack_<Tuple, i>::help(t).get_val(); 
    }

    template <size_t i, typename T>
    auto& get(T& t) {  
        return gett<decltype(t), i>(t); 
    }

} // namespace mylib

#endif //TUPLE_H