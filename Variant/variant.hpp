// #include "variant.h"

// template <typename T>
// mylib::Variant<T>::Variant(mylib::Variant<T>& tp) : val{tp.val}
// {}
// template <typename T>
// mylib::Variant<T>::Variant(const mylib::Variant<T>&& tp) : val{tp.val}
// {}
// template <typename T>
// mylib::Variant<T>::Variant(const T& value) : val{value}
// {}
// template <typename T>
// mylib::Variant<T>::Variant(T& value) : val{value}
// {}
// template <typename T>
// mylib::Variant<T>::Variant(T&& value) : val{std::move(value)}
// {}
// template <typename T>
// mylib::Variant<T>::Variant(const T&& value) : val{value}
// {}
// template <typename T>
// template <typename U>
// mylib::Variant<T>::Variant(U&& value) : val{std::forward<U>(value)}
// {
//     std::cout << 1 << std::endl;
// }
// template <typename T>
// template <typename U>
// mylib::Variant<T>::Variant(const mylib::Variant<U>& oth) : val{oth.val}
// {}
// template <typename T>
// template <typename U>
// mylib::Variant<T>::Variant(mylib::Variant<U>&& oth) : val{std::move(oth.val)}
// {}
// template <typename T>
// mylib::Variant<T>& mylib::Variant<T>::operator=(mylib::Variant<T>& tp)
// {
//     this->val = tp.val;
//     return *this;
// }
// template <typename T>
// mylib::Variant<T>& mylib::Variant<T>::operator=(const mylib::Variant<T>&& tp)
// {
//     this->val = tp.val;
//     return *this;
// }
// template <typename T>
// mylib::Variant<T>& mylib::Variant<T>::operator=(const T& value)
// {
//     this->val = value;
//     return *this;
// }
// template <typename T>
// mylib::Variant<T>& mylib::Variant<T>::operator=(T&& value)
// {
//     this->val = std::move(value);
//     return *this;
// }
// template <typename T>
// template <typename U>
// mylib::Variant<T>& mylib::Variant<T>::operator=(U&& value)
// {
//     this->val = std::forward<U>(value);
//     return *this;
// }
// template <typename T>
// template <typename U>
// mylib::Variant<T>& mylib::Variant<T>::operator=(const mylib::Variant<U>& oth)
// {
//     this->val = oth.val;
//     return *this;
// }
// template <typename T>
// template <typename U>
// mylib::Variant<T>& mylib::Variant<T>::operator=(mylib::Variant<U>& oth)
// {
//     this->val = oth.val;
//     return *this;
// }
// template <typename T>
// template <typename U>
// mylib::Variant<T>& mylib::Variant<T>::operator=(mylib::Variant<U>&& oth)
// {
//     this->val = std::move(oth.val);
//     return *this;
// }
// template <typename T>
// template <typename U>
// mylib::Variant<T>& mylib::Variant<T>::operator=(const mylib::Variant<U>&& oth)
// {
//     this->val = oth.val;
//     return *this;
// }


// //impl 2 arg

// template<typename T1,typename T2>
// mylib::Variant<T1,T2>::Variant(const std::pair<T1,T2>& ob):first{ob.first},second{ob.second}
// {}

// template<typename T1,typename T2>
// mylib::Variant<T1,T2>::Variant(std::pair<T1,T2>&& ob):first{std::move(ob.first)},second{std::move(ob.second)}
// {}

// template<typename T1,typename T2>
// mylib::Variant<T1,T2>::Variant(const T1& ob1,const T2& ob2):first{ob1},second{ob2}
// {}

// template<typename T1,typename T2>
// mylib::Variant<T1,T2>::Variant( T1&& ob1, T2&& ob2):first{std::move(ob1)},second{std::move(ob2)}
// {}

// template <typename T1,typename T2>
// template <typename U1,typename U2>
// mylib::Variant<T1,T2>::Variant(const mylib::Variant<U1,U2>& ob):first{ob.first},second{ob.second}
// {}

// template <typename T1,typename T2>
// template <typename U1,typename U2>
// mylib::Variant<T1,T2>::Variant(Variant<U1,U2>&& ob):first{std::move(ob.first)},second{std::move(ob.second)}
// {}

// template <typename T1,typename T2>
// template <typename U1,typename U2>
// mylib::Variant<T1,T2>::Variant(const std::pair<U1,U2>& ob):first{ob.first},second{ob.second}
// {}

// template <typename T1,typename T2>
// template <typename U1,typename U2>
// mylib::Variant<T1,T2>::Variant(std::pair<U1,U2>&& ob):first{std::move(ob.first)},second{std::move(ob.second)}
// {}

// template<typename T1,typename T2>
// template <typename U1,typename U2,typename std::enable_if<!std::is_same< typename std::decay<U1>::type,typename std::decay<T1>::type>::value || 
// std::is_same<typename std::decay<U2>::type,typename std::decay<T2>::type>::value>::type>
// mylib::Variant<T1,T2>::Variant(U1&& ob1,U2&& ob2):first{std::forward(ob1)},second{std::forward(ob2)}
// {}

// template <typename T1,typename T2>
// mylib::Variant<T1,T2>& mylib::Variant<T1,T2>::operator=(const std::pair<T1,T2>& ob)
// {
//   this->first=ob.first;
//   this->second=ob.second;
//   return *this;
// }

// template <typename T1,typename T2>
// mylib::Variant<T1,T2>& mylib::Variant<T1,T2>::operator=(std::pair<T1,T2>&& ob)
// {
//   this->first=std::move(ob.first);
//   this->second=std::move(ob.second);
//   return *this;
// }

// template <typename T1,typename T2>
// template <typename U1,typename U2>
// mylib::Variant<T1,T2>& mylib::Variant<T1,T2>::operator=(const std::pair<U1,U2>& ob)
// {
//   this->first=ob.first;
//   this->second=ob.second;
//   return *this;
// }

// template <typename T1,typename T2>
// template <typename U1,typename U2>
// mylib::Variant<T1,T2>& mylib::Variant<T1,T2>::operator=(std::pair<U1,U2>&& ob)
// {
//   this->first=std::move(ob.first);
//   this->second=std::move(ob.second);
//   return *this;
// }

// template <typename T1,typename T2>
// template <typename U1,typename U2>
// mylib::Variant<T1,T2>& mylib::Variant<T1,T2>::operator=(const mylib::Variant<U1,U2>& ob)
// {
//   this->first=ob.first;
//   this->second=ob.second;
//   return *this;
// }

// template <typename T1,typename T2>
// template <typename U1,typename U2>
// mylib::Variant<T1,T2>& mylib::Variant<T1,T2>::operator=(mylib::Variant<U1,U2>&& ob)
// {
//   this->first=std::move(ob.first);
//   this->second=std::move(ob.second);
//   return *this;
// }


// template <typename T,typename... Args>
// mylib::Variant<T,Args...>::Variant(const T& par,const Args&... args) : val{par}, rest{args...}
// {}

// template <typename T,typename... Args>
// mylib::Variant<T,Args...>::Variant(T&& par,Args&&... args) : val{std::move(par)}, rest{(std::move(args),...)}
// {}

// template <typename T,typename... Args>
// template <typename U,typename... Args2>
// mylib::Variant<T,Args...>::Variant(const mylib::Variant<U,Args2...>& ob) : val{ob.val}, rest{ob.rest}
// {}

// template <typename T,typename... Args>
// template <typename U,typename... Args2>
// mylib::Variant<T,Args...>::Variant(mylib::Variant<U,Args2...>&& ob) : val{std::move(ob.val)}, rest{std::move(ob.rest)}
// {}

// template <typename T,typename... Args>
// template <typename U,typename... Args2>
// mylib::Variant<T,Args...>& mylib::Variant<T,Args...>::operator=(const mylib::Variant<U,Args2...>& ob)
// {
//   this->val=ob.val;
//   this->rest=ob.rest;
//   return *this;
// }

// template <typename T,typename... Args>
// template <typename U,typename... Args2>
// mylib::Variant<T,Args...>& mylib::Variant<T,Args...>::operator=(mylib::Variant<U,Args2...>&& ob)
// {
//   this->val=std::move(ob.val);
//   this->rest=std::move(ob.rest);
//   return *this;
// }

