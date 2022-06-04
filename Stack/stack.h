#ifndef _STACK_H_
#define _STACK_H_

#include <type_traits>

#include "../List/list.h"

namespace mylib{

template <typename T, typename Container=mylib::list<T>>

class Stack
{
public:
    typedef T value_type;
    typedef value_type& referance;
    typedef const value_type& const_referance;
    typedef size_t size_type;
    typedef Container container_type;
public:
    Stack():m_cont(){}
    explicit Stack(const Container & cont):m_cont{cont} {}
    explicit Stack(Container& cont):m_cont{cont} {}
    Stack (const Stack& rhs)=default;
    Stack (Stack&& rhs) noexcept =default;
    Stack& operator=(const Stack& rhs)=default;
    Stack& operator=(Stack&& rhs)noexcept =default;
    ~Stack()=default;
public:
    referance top() {return m_cont.back();}
    const_referance top() const {return m_cont.back();}
    [[nodiscard]] bool empty() const {return m_cont.empty();}
    size_type size() const {return m_cont.size();}
    void push(const value_type& value) {m_cont.bush_back(value);}
    void push(value_type&& value) {m_cont.push_back(value);}
    template <typename... Args>
    decltype(auto) emplace (Args&&... args){m_cont.emplace_back(args...);}
    void pop(){m_cont.pop_back();}
    void swap(Stack& rhs) noexcept (std::is_nothrow_swappable_v<Container>)
    {
        Stack tmp=std::move(*this);
        *this=std::move(rhs);
        rhs=std::move(tmp);
    }
public:
    friend bool operator==(const Stack& first,const Stack& second)
    {
        return first.m_cont==second.m_cont;
    }
    friend bool operator!=(const Stack& first,const Stack& second)
    {
        return first.m_cont!=second.m_cont;
    }
    friend bool operator<(const Stack& first,const Stack& second)
    {
        return first.m_cont<second.m_cont;
    }
    friend bool operator>(const Stack& first,const Stack& second)
    {
        return first.m_cont>second.m_cont;
    }
    friend bool operator<=(const Stack& first,const Stack& second)
    {
        return first.m_cont<=second.m_cont;
    }
    friend bool operator>=(const Stack& first,const Stack& second)
    {
        return first.m_cont>=second.m_cont;
    }
protected:
    Container m_cont;
};
} //namespace mylib

#endif //_STACK_H_