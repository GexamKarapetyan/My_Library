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
        map(const map& rhs) : m_tree {rhs.m_tree}, m_size {rhs.m_size} {}
        map(map&& rhs) noexcept : m_tree {rhs.m_tree}, m_size {rhs.m_size} {}
        map& operator=(const map& rhs);
        map& operator=(map&& rhs) noexcept;
        explicit map(const Compare& comp);
        map(std::initializer_list<value_type> ilist);
        ~map();
        
        T& at(const Key& key);
        const T& at(const Key& key) const;
        T& operator[](const Key& key);	
        T& operator[](Key&& key);
        Iterator begin() noexcept;
        void print();
        Const_Iterator cbegin() const noexcept;
        Iterator end() noexcept;
        Const_Iterator cend() const noexcept;
        [[nodiscard]] bool empty() const noexcept;
        size_type size() const noexcept;
        void clear() noexcept;
        void insert(const value_type& value);
        Iterator erase(Iterator pos);
    private:
        mylib::rb_tree<Key, T, Compare> m_tree;
        size_type m_size;
    };

} // namespace mylib

#include "map.hpp"

#endif //MAP_H
