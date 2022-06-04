#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "../List/list.h"

namespace mylib{

template <typename T,typename Container=mylib::list<T>>
class Queue
{
public:
    typedef T value_type;
    typedef value_type& referance;
    typedef const value_type& const_referance;
    typedef size_t size_type;
    typedef Container container_type;
public:
    Queue():m_cont(){}
    explicit Queue(const Container& cont):m_cont(cont) {}
    explicit Queue(Container& cont):m_cont{cont} {}
    Queue (const Queue& rhs)=default;
    Queue (Queue&& rhs) noexcept =default;
    Queue& operator=(const Queue& rhs)=default;
    Queue& operator=(Queue&& rhs)noexcept =default;
    ~Queue()=default;
public:
    referance front(){return m_cont.front();}
    const_referance front() const {return m_cont.front();}
    referance back(){return m_cont.back();}
    const_referance back() const{return m_cont.back();}
    [[nodiscard]] bool empty() const {return m_cont.empty();}
    size_type size() const {return m_cont.size();}
    void push(const value_type& value) {m_cont.bush_back(value);}
    void push(value_type&& value) {m_cont.push_back(value);}
    template <typename... Args>
    decltype(auto) emplace (Args&&... args){m_cont.emplace_back(args...);}
    void pop(){m_cont.pop_front();}
    void swap(Queue& rhs) noexcept (std::is_nothrow_swappable_v<Container>)
    {
        Queue tmp=std::move(*this);
        *this=std::move(rhs);
        rhs=std::move(tmp);
    }
public:
     friend bool operator==(const Queue& first,const Queue& second)
    {
        return first.m_cont==second.m_cont;
    }
    friend bool operator!=(const Queue& first,const Queue& second)
    {
        return first.m_cont!=second.m_cont;
    }
    friend bool operator<(const Queue& first,const Queue& second)
    {
        return first.m_cont<second.m_cont;
    }
    friend bool operator>(const Queue& first,const Queue& second)
    {
        return first.m_cont>second.m_cont;
    }
    friend bool operator<=(const Queue& first,const Queue& second)
    {
        return first.m_cont<=second.m_cont;
    }
    friend bool operator>=(const Queue& first,const Queue& second)
    {
        return first.m_cont>=second.m_cont;
    }
protected:
    Container m_cont;

};
} //namespace mylib

#endif //_QUEUE_H_