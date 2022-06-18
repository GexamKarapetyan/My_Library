#ifndef _PR_QUEUQ_H_
#define _PR_QUEUQ_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "../Heap/heap.h"

namespace mylib{

template <class T,class Container = std::vector<T>,
class Compare = std::less<typename Container::value_type>>
class priority_queue
{
public:
   typedef Container container_type; 
   typedef Compare value_compare;
   typedef typename Container::value_type value_type;
   typedef typename Container::size_type size_type;
   typedef typename Container::reference reference;
   typedef typename Container::const_reference const_reference;
public:
    priority_queue():m_cont{},m_comp{} {}
    explicit priority_queue(const Compare& comp):m_cont{},m_comp{comp} {} 
    priority_queue(const Container& ctor,const Compare& comp):m_cont{ctor}, m_comp{comp}{}
    priority_queue(const Container&& ctor,const Compare& comp):m_cont{std::move(ctor)}, m_comp{comp}{}
    priority_queue(const priority_queue& ob):m_cont{ob.m_cont}, m_comp{ob.m_comp} {}
    priority_queue(priority_queue&& ob):m_cont{std::move(ob.m_cont)}, m_comp{std::move(ob.m_comp)} {}
    priority_queue& operator=(const priority_queue& ob);
    priority_queue& operator=(priority_queue&& ob) noexcept;
 public:
    [[nodiscard]] bool empty() const;
    const_reference top() const;
    void push(const value_type& value);
    void push(value_type&& value);
    size_type size() const;
    template <typename... Args>
    void emplace(Args&&... arg);
    void pop();
    void swap(priority_queue & rhs);
    
 private:
    Container m_cont;
    Compare m_comp;
};

} //namespace mylib

#include "pr_queue.hpp"

#endif //_PR_QUEUQ_H