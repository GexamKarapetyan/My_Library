#ifndef FORWARD_LIST_
#define FORWARD_LIST_

#include <iterator>
#include <iostream>

#include <unordered_set>
#include <initializer_list>

namespace mylib {
    
    template <class T>
    class Forward_list;

    template <class T>
    class Node 
    {
    public:
        Node() : m_data{}, m_next{} {}
        Node(const T& data, Node* ptr) : m_data{data}, m_next{ptr} {}
        ~Node() = default;
    private:
        template <class U>
        friend class Forward_list;
        T m_data;
        Node* m_next;
    };

    template <class U>
    class Forward_list
    {
    public:
        typedef U value_type;
        typedef size_t size_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;

    public:
        class Iterator : public std::iterator<std::forward_iterator_tag, U>
        {
        public:
            Iterator(): it{} {}
            Iterator(const Iterator& rhs) : it {rhs.it} {}
            Iterator(Iterator&& rhs) : it {rhs.it} {}
        public:
            Iterator& operator++();
            Iterator operator++(int);
            Iterator& operator=(const Iterator& rhs);
            Iterator& operator=(Iterator&& rhs);
            bool operator==(Iterator& rhs);
            bool operator!=(Iterator& rhs);
            U& operator*();
            U* operator->();
            Node<U>*& get(){return it;}
        private:
            friend class Forward_list;
            Node<U>* it;
        };

        class Const_Iterator : public std::iterator<std::forward_iterator_tag, U>
        {
        public:
            Const_Iterator(): it{} {}
            Const_Iterator(const Const_Iterator& rhs) : it {rhs.it} {}
            Const_Iterator(Const_Iterator&& rhs) : it {rhs.it} {}
            Const_Iterator(const Iterator& rhs) : it {rhs.it} {}
            Const_Iterator(Iterator&& rhs) : it {rhs.it} {}
        public:
            Const_Iterator& operator=(const Const_Iterator& rhs);
            Const_Iterator& operator=(Const_Iterator&& rhs);
            bool operator==(Const_Iterator& rhs);
            bool operator!=(Const_Iterator& rhs);
            Const_Iterator& operator++();
            Const_Iterator operator++(int);
            const U& operator*() const;
            U* operator->();
            const Node<U>*& get() const {return it;}
        private:
            friend class Forward_list;
            const Node<U>* it;
        };

    public:
        Forward_list();
        ~Forward_list();
        Forward_list(const Forward_list&);
        Forward_list(Forward_list&&) noexcept;
        Forward_list& operator=(const Forward_list&);
        Forward_list& operator=(Forward_list&&) noexcept;
        Forward_list(int count);
        Forward_list(int count,const U& elem);
        Forward_list(std::initializer_list<U> ilist);

    public:
        void push_front(const U& element);
        U& front();
        const U& front() const;
        bool is_empty() const;
        void pop_front();
        void clear();
        Iterator insert_after(Iterator pos, const U& element);
        Iterator erase_after(Iterator pos);
        void swap(int index1, int index2);
        void sort();
        bool is_sorted_list() const;
        void reverse();
        Node<U>* do_reverse(Node<U>* head);
        void merge(Forward_list<U>&);
        Iterator begin() const;
        Iterator end() const;
        Const_Iterator cbegin() const;
        Const_Iterator cend() const;
        Iterator before_begin() const;
        size_t unique();
        template <class... Args>
        Iterator emplace_after(Iterator pos,Args&&... args);
        void assign(size_t count,const U& element);
        template <typename InputIter>
        void assign(InputIter first,InputIter second);
        void assign(std::initializer_list<U> ilist);

    public:
        bool operator==(const Forward_list<U>& rhs) const;
        bool operator!=(const Forward_list<U>& rhs) const;  
        bool operator<(const Forward_list<U>& rhs) const;      
        bool operator>(const Forward_list<U>& rhs) const;      
        bool operator<=(const Forward_list<U>& rhs) const;      
        bool operator>=(const Forward_list<U>& rhs) const; 
        friend std::ostream& operator<<(std::ostream& os, const Forward_list<U>& lst) {
            for(auto it : lst) {
                os << it << " ";
            }
            return os;
        } 

    private:
        U& operator[](int index) const;
        Node<U>* m_head;
    private:
        void merge_for_sort( int const , int const , int const);
        void mergeSort(int const begin, int const end);

     
    };
}

#include "myFlist.hpp"

#endif //FORWARD_LIST_