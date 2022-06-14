#ifndef MAP_H
#define MAP_H

#include <functional>
#include <initializer_list>
#include <cstddef>
#include <exception>
#include <stdexcept>

#include "../Pair/pair.h"
#include "../Red_Black_Tree/rb_tree.h"


namespace mylib
{
    template <typename Key, typename T, typename Compare = std::less<Key>>    
    class map
    {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef mylib::pair<Key, T> value_type;
        typedef size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef Compare key_compare;
        typedef value_type& reference;
        typedef const value_type& const_reference;

        class Const_Iterator;

        class Iterator : public std::iterator<std::bidirectional_iterator_tag, Key>
        {
        public:
            Iterator() : m_itr{} {}    
            Iterator(typename mylib::rb_tree<Key, T, Compare>::Iterator in_itr)
             : m_itr{in_itr} {}
            Iterator(const Iterator& rhs) : m_itr {rhs.m_itr} {}
            Iterator(Iterator&& rhs) noexcept : m_itr {rhs.m_itr} {}
            Iterator& operator=(const Iterator& rhs) = default;
            Iterator& operator=(Iterator&& rhs) noexcept = default;
            Iterator& operator++() {++m_itr; return *this;}
            Iterator operator++(int) {m_itr++;}
            Iterator& operator--() {--m_itr;}
            Iterator operator--(int) {m_itr--;}
            value_type& operator*() {return *m_itr;}
            friend bool operator==(const Iterator& first, const Iterator& second) {
                return first.m_itr == second.m_itr;
            } 
            friend bool operator!=(const Iterator& first, const Iterator& second) {
                return first.m_itr != second.m_itr;
            }
            friend bool operator==(const Iterator& first, const Const_Iterator& second) {
                return first.m_itr == second.m_itr;
            } 
            friend bool operator!=(const Iterator& first, const Const_Iterator& second) {
                return first.m_itr != second.m_itr;
            }
        private:
            typename mylib::rb_tree<Key, T, Compare>::Iterator m_itr;
        };
        class Const_Iterator : public std::iterator<std::bidirectional_iterator_tag, Key>
        {
        public:
            Const_Iterator() : m_itr{} {}    
            Const_Iterator(typename mylib::rb_tree<Key, T, Compare>::Const_Iterator in_itr)
             : m_itr{in_itr} {}
            Const_Iterator(const Const_Iterator& rhs) : m_itr {rhs.m_itr} {}
            Const_Iterator(Const_Iterator&& rhs) noexcept : m_itr {rhs.m_itr} {}
            Const_Iterator& operator=(const Const_Iterator& rhs) = default;
            Const_Iterator& operator=(Const_Iterator&& rhs) noexcept = default;
            Const_Iterator& operator++() {++m_itr; return *this;}
            Const_Iterator operator++(int) {m_itr++;}
            Const_Iterator& operator--() {--m_itr;}
            Const_Iterator operator--(int) {m_itr--;}
            const value_type& operator*() const {return *m_itr;}
            friend bool operator==(const Const_Iterator& first, const Const_Iterator& second) {
                return first.m_itr == second.m_itr;
            } 
            friend bool operator!=(const Const_Iterator& first, const Const_Iterator& second) {
                return first.m_itr != second.m_itr;
            }
            friend bool operator==(const Const_Iterator& first, const Iterator& second) {
                return first.m_itr == second.m_itr;
            } 
            friend bool operator!=(const Const_Iterator& first, const Iterator& second) {
                return first.m_itr != second.m_itr;
            }
        private:
            typename mylib::rb_tree<Key, T, Compare>::Const_Iterator m_itr;
        };

        map() : m_tree{}, m_size{} {}
        // explicit map(const Compare& comp);
        // template< class InputIt >
        // map(InputIt first, InputIt last,
        //  const Compare& comp = Compare());   
        // map(const map& rhs); 
        // map(map&& rhs) noexcept;
        // map(std::initializer_list<value_type> init,
        //  const Compare& comp = Compare());
        ~map();
        // map& operator=(const map& other);
        // map& operator=(map&& other) noexcept;
        // map& operator=(std::initializer_list<value_type> ilist);

        T& at(const Key& key);
        const T& at(const Key& key) const;
        T& operator[](const Key& key);	
        T& operator[](Key&& key);
        Iterator begin() noexcept;
        void print();
        // const_iterator begin() const noexcept;
        Const_Iterator cbegin() const noexcept;
        Iterator end() noexcept;
        // const_iterator end() const noexcept;
        Const_Iterator cend() const noexcept;
        // reverse_iterator rbegin() noexcept;
        // const_reverse_iterator rbegin() const noexcept;
        // const_reverse_iterator crbegin() const noexcept;
        // reverse_iterator rend() noexcept;
        // const_reverse_iterator rend() const noexcept;
        // const_reverse_iterator crend() const noexcept;

        [[nodiscard]] bool empty() const noexcept;
        size_type size() const noexcept;
        void clear() noexcept;
        
        //mylib::pair<Iterator, bool> 
        void insert(const value_type& value);
        // std::pair<iterator, bool> insert(value_type&& value);
        // iterator insert(const_iterator hint, const value_type& value);
        // iterator insert(const_iterator hint, value_type&& value);
        // template< class InputIt >
        // void insert(InputIt first, InputIt last);
        // void insert(std::initializer_list<value_type> ilist);
        // template <class M>
        // std::pair<iterator, bool> insert_or_assign(const Key& k, M&& obj);
        // template <class M>
        // std::pair<iterator, bool> insert_or_assign(Key&& k, M&& obj);
        // template <class M>
        // iterator insert_or_assign(const_iterator hint, const Key& k, M&& obj);
        // template <class M>
        // iterator insert_or_assign(const_iterator hint, Key&& k, M&& obj);
        // template< class... Args >
        // std::pair<iterator,bool> emplace(Args&&... args);
        // template <class... Args>
        // iterator emplace_hint(const_iterator hint, Args&&... args);
        // template <class... Args>
        // pair<iterator, bool> try_emplace(const Key& k, Args&&... args);
        // template <class... Args>
        // pair<iterator, bool> try_emplace(Key&& k, Args&&... args);
        // template <class... Args>
        // iterator try_emplace(const_iterator hint, const Key& k, Args&&... args);
        // template <class... Args>
        // iterator try_emplace(const_iterator hint, Key&& k, Args&&... args);
        Iterator erase(Iterator pos);
        // iterator erase(const_iterator pos);
        // iterator erase(const_iterator first, const_iterator last);
        // size_type erase(const Key& key);
        // void swap( map& other ) noexcept;
        // template<class C2>
        // void merge(std::map<Key, T, C2);
        // size_type count(const Key& key) const;
        // iterator find(const Key& key);
        // const_iterator find(const Key& key) const;
        // bool contains(const Key& key) const;
        // std::pair<iterator,iterator> equal_range(const Key& key);
        // std::pair<const_iterator,const_iterator> equal_range(const Key& key) const;
        // iterator lower_bound(const Key& key);
        // const_iterator lower_bound(const Key& key) const;
        // iterator upper_bound(const Key& key);
        // const_iterator upper_bound(const Key& key) const;
        // template <class Key, class T, class Compare>
        // bool operator==(const std::map<Key,T,Compare>& lhs,
        //                 const std::map<Key,T,Compare>& rhs);
        // template <class Key, class T, class Compare>
        // bool operator!=(const std::map<Key,T,Compare>& lhs,
        //                 const std::map<Key,T,Compare>& rhs);

    private:
        mylib::rb_tree<Key, T> m_tree;
        size_type m_size;
    };



} // namespace mylib

#include "map.hpp"

#endif //MAP_H