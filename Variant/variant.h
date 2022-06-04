#ifndef VARIANT_H
#define VARIANT_H

#include <type_traits>

namespace mylib
{
    template <typename... Types>
    class variant;
   
    template <typename T, typename... Types>
    class variant <T, Types...>
    {
    public:
        typedef T value_type;
        constexpr variant() = default;
        constexpr variant(const T& val, const Types&... types) : value (val), pack(types...) {}
        variant(const variant<T, Types...>& rhs) = default;
        variant(variant<T, Types...>&& rhs) = default;
        variant<T, Types...>& operator=(const variant<T, Types...>& rhs) = default;
        variant<T, Types...>& operator=(variant<T, Types...>&& rhs) = default;
        variant(const variant<T>& rhs) : value(rhs.value) {}
        template <typename U>
        variant(const variant<U>& rhs) : value(rhs.value) {}
        template <typename U>
        variant(variant<U>& rhs) : value(rhs.value) {}
        template <typename U, typename... UTypes>
        variant(variant<U, UTypes...>& rhs) : value(rhs.value), pack (rhs.pack) {}
        template <typename U, typename... UTypes>
        variant(const variant<U, UTypes...>& rhs) : value(rhs.value), pack (rhs.pack) {}        
        template <typename U, typename... UTypes>
        variant(variant<U, UTypes...>&& rhs) :  value(std::move(rhs.value)), pack(std::move(rhs.pack)) {}
        template <typename U, typename... UTypes>
        variant<T, Types...>& operator=(const variant<U, UTypes...>& rhs) {
            value = rhs.value;
            if constexpr(sizeof...(UTypes) > 1){
                pack = rhs.pack;
            }
            return *this;
        }
        template <typename U, typename... UTypes>
        variant<T, Types...>& operator=(variant<U, UTypes...>&& rhs) {
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
        // T& operator[](size_t index) {
        //     if(index == 0) {
        //         return value;
        //     }
        //    return pack[--index];
        // }
        // const T& operator[](size_t index) const {
        //     if(index == 0) {
        //         return value;
        //     }
        //     return pack[--index];
        // }

        // auto& get_pack_val() {
        //     return pack.pack.pack.value;
        // } 

        auto& get_val() {
            return value;
        }

       constexpr auto& get_pack() {
            return pack;
        }
        
        


        //  T& operator[](size_t index) {
        //     if(index == 0) {
        //         return value;
        //     }
        //     auto* pk = &pack;
        //     while (index != 1)
        //     {
        //         pk = &pk.pack;
        //     }
        //    return *pk.value;
        // }

        // const T& operator[](size_t index) const {
        //     if(index == 0) {
        //         return value;
        //     }
        //     auto * pk = &pack;
        //     while (index != 1)
        //     {
        //         pk = &(*pk.pack);
        //     }
        //    return *pk.value;
        // }
        
        template <typename U>
       U& operator[](size_t index) {
            if(index == 0) {
                return value;
            }
           return pack[--index];
        }
        template <typename U>
        const U& operator[](size_t index) const {
            if(index == 0) {
                return value;
            }
            return pack[--index];
        }
         
       
        ~variant() = default;
    public:
        T value;
        variant<Types...> pack; 
       
    };

    // template <typename T1, typename T2>
    // class variant <T1, T2>
    // {
    // public:
    //     typedef T1 fisrt_type;
    //     typedef T2 second_type;
    //     constexpr variant() = default;
    //     constexpr variant(T1 val1, T2 val2) : first {val1}, second {val2} {}
    //     variant(const variant<T1, T2>& rhs) = default;
    //     variant(variant<T1, T2>&& rhs) = default;
    //     variant<T1, T2>& operator=(const variant<T1, T2>& rhs) = default;
    //     variant<T1, T2>& operator=(variant<T1, T2>&& rhs) = default;
    //     template <typename U1, typename U2>
    //     variant(const variant<U1, U2>& rhs) : first(rhs.first), second(rhs.second) {}
    //     template <typename U1, typename U2>
    //     variant(variant<U1, U2>&& rhs) : first(std::move(rhs.first)), second(std::move(rhs.second)) {}
    //     template <typename U1, typename U2>
    //     variant<T1, T2>& operator=(const variant<U1, U2>& rhs) {
    //         first = rhs.fisrt;
    //         second = rhs.second;
    //         return *this;
    //     }
    //     template <typename U1, typename U2>
    //     variant<T1, T2>& operator=(variant<U1, U2>&& rhs) {
    //         first = std::move(rhs.fisrt);
    //         second = std::move(rhs.second);
    //         return *this;
    //     }
    //     ~variant() = default;
    // public:
    //     T1 first;
    //     T2 second;
    // };

    template <typename T>
    class variant <T>
    {
    public:
        typedef T value_type;
        constexpr variant() = default;
        constexpr variant(T val) : value {val} {}
        variant(const variant<T>& rhs) = default;
        variant(variant<T>&& rhs) = default;
        variant<T>& operator=(const variant<T>& rhs) = default;
        variant<T>& operator=(variant<T>&& rhs) = default;
        template <typename U>
        variant(const variant<U>& rhs) : value(rhs.value) {}
        template <typename U>
        variant(variant<U>&& rhs) :  value(std::move(rhs.value)) {}
        template <typename U>
        variant<T>& operator=(const variant<U>& rhs) {
            value = rhs.value;
            return *this;
        }
        template <typename U>
        variant<T>& operator=(variant<U>&& rhs) {
            value = std::move(rhs.value);
            return *this;
        }
        auto& operator[](size_t index) {
            return value;
        }
        const auto& operator[](size_t index) const {
            return value;
        }
        auto& get_val() {
            return value;
        }
        // constexpr void get_pack() {
        //     return;
        // }
       
        ~variant() = default;
    public:
        T value;
    };


    // template <typename... Args>
    // class variant
    // {
    // public:
    //     constexpr variant() = default;
    //     // constexpr variant(Args... pack) {
    //     //     mylib::assign_value<0, decltype(*this), Args...>
    //     //     (*this, pack...);  
    //     // }
            
        
        
    //     //variant(const variant<T>& rhs) = default;
    //     //variant(variant<T>&& rhs) = default;
    //     // variant<T>& operator=(const variant<T>& rhs) = default;
    //     // variant<T>& operator=(variant<T>&& rhs) = default;
    //     // template <typename U>
    //     // variant(const variant<U>& rhs) : value(rhs.value) {}
    //     // template <typename U>
    //     // variant(variant<U>&& rhs) :  value(std::move(rhs.value)) {}
    //     // template <typename U>
    //     // variant<T>& operator=(const variant<U>& rhs) {
    //     //     value = rhs.value;
    //     //     return *this;
    //     // }
    //     // template <typename U>
    //     // variant<T>& operator=(variant<U>&& rhs) {
    //     //     value = std::move(rhs.value);
    //     //     return *this;
    //     // }
    //     ~variant() = default;
    // public:
    //     variant<Args...> value;
    // };

    template <>
    class variant <> {};








} // namespace mylib

#endif //VARIANT_H