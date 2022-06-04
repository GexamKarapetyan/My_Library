#ifndef LIST_
#define LIST_

#include <iterator>
#include <iostream>
#include <initializer_list>

namespace mylib {

    template <class T>
    class list;

    template <class T>
    class Node 
    {
    public:
        Node() : m_data{}, m_next{}, m_prev{} {}
        Node(const T& data, Node* next, Node* prev) : m_data{data}, m_next{next}, m_prev{prev} {}
        Node(const Node& rhs) : m_data {rhs.m_data}, m_next{rhs.m_next}, m_prev{rhs.m_prev} {}
        Node(Node && rhs) noexcept = default;
        Node& operator=(const Node& rhs) = default;
        Node& operator=(Node&& rhs) = default;
       
        ~Node() = default;
    private:
        template <class U>
        friend class list;
        T m_data;
        Node* m_next;
        Node* m_prev;
    };

    template <class U>
    class list
    {
    public:
        typedef U value_type;
        typedef size_t size_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;

    public:
        class Iterator : public std::iterator<std::bidirectional_iterator_tag, U>
        {
        public:
            Iterator(): it{} {}
            Iterator(const Iterator& rhs) : it {rhs.it} {}
            Iterator(Iterator&& rhs) : it {rhs.it} {}
        public:
            Iterator& operator++();
            Iterator operator++(int);
            Iterator& operator--();
            Iterator operator--(int);
            Iterator& operator=(const Iterator& rhs);
            Iterator& operator=(Iterator&& rhs);
            bool operator==(Iterator& rhs);
            bool operator!=(Iterator& rhs);
            U& operator*();
            U* operator->();
            Node<U>*& get() {return it;}
        private:
            friend class list;
            Node<U>* it;
        };

        class Const_Iterator : public std::iterator<std::bidirectional_iterator_tag, U>
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
            Const_Iterator& operator--();
            Const_Iterator operator--(int);
            const U& operator*() const;
            U* operator->();
            const Node<U>*& get() const {return it;}
        private:
            friend class list;
            const Node<U>* it;
        };

         class Reverse_Iterator : public std::iterator<std::bidirectional_iterator_tag, U>
        {
        public:
            Reverse_Iterator(): it{} {}
            Reverse_Iterator(const Reverse_Iterator& rhs) : it {rhs.it} {}
            Reverse_Iterator(Reverse_Iterator&& rhs) : it {rhs.it} {}
        public:
            Reverse_Iterator& operator++();
            Reverse_Iterator operator++(int);
            Reverse_Iterator& operator--();
            Reverse_Iterator operator--(int);
            Reverse_Iterator& operator=(const Reverse_Iterator& rhs);
            Reverse_Iterator& operator=(Reverse_Iterator&& rhs);
            bool operator==(Reverse_Iterator& rhs);
            bool operator!=(Reverse_Iterator& rhs);
            U& operator*();
            U* operator->();
            Node<U>*& get() {return it;}
        private:
            friend class list;
            Node<U>* it;
        };

        class Const_Reverse_Iterator : public std::iterator<std::bidirectional_iterator_tag, U>
        {
        public:
            Const_Reverse_Iterator(): it{} {}
            Const_Reverse_Iterator(const Const_Reverse_Iterator& rhs) : it {rhs.it} {}
            Const_Reverse_Iterator(Const_Reverse_Iterator&& rhs) : it {rhs.it} {}
            Const_Reverse_Iterator(const Iterator& rhs) : it {rhs.it} {}
            Const_Reverse_Iterator(Iterator&& rhs) : it {rhs.it} {}
        public:
            Const_Reverse_Iterator& operator=(const Const_Reverse_Iterator& rhs);
            Const_Reverse_Iterator& operator=(Const_Reverse_Iterator&& rhs);
            bool operator==(Const_Reverse_Iterator& rhs);
            bool operator!=(Const_Reverse_Iterator& rhs);
            Const_Reverse_Iterator& operator++();
            Const_Reverse_Iterator operator++(int);
            Const_Reverse_Iterator& operator--();
            Const_Reverse_Iterator operator--(int);
            const U& operator*() const;
            U* operator->();
            const Node<U>*& get() const {return it;}
        private:
            friend class list;
            const Node<U>* it;
        };


    public:
        list();
        ~list();
        list(const list&);
        list(list&&) noexcept;
        list& operator=(const list&);
        list& operator=(list&&) noexcept;
        list(size_t count);
        list(size_t count, const U& element);
        list(std::initializer_list<U> ilist);
    public:
        U& front();
        U& back();
        const U& front() const;
        const U& back() const;
        bool empty() const;
        void pop_front();
        void pop_back();
        void clear();
        void push_back(const U& element);
        void push_front(const U& element);
        Iterator insert(Iterator pos, const U& element);
        template <class... Args>
        Iterator emplace(Iterator pos, Args&&... args);
        template <class... Args>       
        Iterator emplace_back(Args&&... args);
        template <class... Args>
        Iterator emplace_front(Args&&... args);
        Iterator erase(Iterator pos);
        void swap(list& rhs);
        void sort();
        void reverse();
        void assign(size_t count, const U& element);
        template <typename InputIter>
        void assign(InputIter first, InputIter last);
        void assign(std::initializer_list<U> ilist);
        mylib::Node<U>* do_reverse(Node<U>* head, mylib::Node<U>* tail);
        void merge(list<U>& rhs);
        bool is_sorted_list() const;
        size_t unique();
        Iterator begin();
        Iterator end();
        size_t size() const;
        Const_Iterator cbegin() const;
        Const_Iterator cend() const;
        Reverse_Iterator rbegin();
        Reverse_Iterator rend();
        Const_Reverse_Iterator crbegin() const;
        Const_Reverse_Iterator crend() const;

    public:
        bool operator==(const list<U>& rhs) const;
        bool operator!=(const list<U>& rhs) const;  
        bool operator<(const list<U>& rhs) const;      
        bool operator>(const list<U>& rhs) const;      
        bool operator<=(const list<U>& rhs) const;      
        bool operator>=(const list<U>& rhs) const; 
        friend std::ostream& operator<<(std::ostream& os, list<U>& lst) 
        {
            if(!lst.empty()) {
                for(auto it : lst) {
                    os << it << " ";
                }
            }
            return os;
        } 

    private:
        U& operator[](int index) const;
        void mergeSort(int begin, int end);
        void merge_for_sort(int left, int mid, int right);
        Node<U>* m_head;
        Node<U>* m_tail;
        size_t m_size;
    };
}

#include "list.hpp"

#endif //LIST_