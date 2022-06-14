#ifndef RB_TREE_H
#define RB_TREE_H

#include <iostream>
#include <iterator>
#include <functional>

#include "../Pair/pair.h"

#define BLACK 0
#define RED 1

namespace mylib
{
    template <typename Key, typename T, typename Compare = std::less<Key>>
    class rb_tree
    {
    public:
        typedef Key key_type;
        typedef Key& key_type_reference;
        typedef T mapped_type;
        typedef mylib::pair<Key, T> value_type;
        typedef value_type& reference;
        typedef size_t size_type;
    private:
        struct node
        {
            friend class rb_tree;
            node() : m_parent {}, m_left {}, 
            m_right {}, m_color {} {}
            node(node* parent, node* left,
             node* right, bool color, const value_type& value) 
            : m_parent {parent}, m_left {left}, 
            m_right {right}, m_color {color}, m_value{value} {}
            const value_type& get() const {return m_value;} 
        private:
            node* m_parent;
            node* m_left;
            node* m_right;
            bool m_color;
            value_type m_value;
        };
    public:
        class Iterator : public std::iterator<std::bidirectional_iterator_tag, Key>
        {
        public:
            Iterator() : m_node{} {}    
            Iterator(node* ptr) : m_node {ptr} {}
            Iterator(const Iterator& rhs) : m_node {rhs.m_node} {}
            Iterator(Iterator&& rhs) noexcept : m_node {rhs.m_node} {}
            Iterator& operator=(const Iterator& rhs) = default;
            Iterator& operator=(Iterator&& rhs) noexcept = default;
            Iterator& operator++();
            Iterator operator++(int);
            Iterator& operator--();
            Iterator operator--(int);
            value_type& operator*() {return m_node->m_value;}
            node* get() {return m_node;}
            friend bool operator==(const Iterator& first, const Iterator& second) {
                return first.m_node == second.m_node;
            } 
            friend bool operator!=(const Iterator& first, const Iterator& second) {
                return first.m_node != second.m_node;
            }
        private:
            node* m_node;
        };
        class Const_Iterator : public std::iterator<std::bidirectional_iterator_tag, Key>
        {
        public:
            Const_Iterator() : m_node{} {}    
            Const_Iterator(node* ptr) : m_node {ptr} {}
            Const_Iterator(const Const_Iterator& rhs) : m_node {rhs.m_node} {}
            Const_Iterator(Const_Iterator&& rhs) noexcept : m_node {rhs.m_node} {}
            Const_Iterator& operator=(const Const_Iterator& rhs) = default;
            Const_Iterator& operator=(Const_Iterator&& rhs) noexcept = default;
            Const_Iterator& operator++();
            Const_Iterator operator++(int);
            Const_Iterator& operator--();
            Const_Iterator operator--(int);
            const value_type& operator*() const {return m_node->m_value;}
            friend bool operator==(const Const_Iterator& first, const Const_Iterator& second) {
                return first.m_node == second.m_node;
            } 
            friend bool operator!=(const Const_Iterator& first, const Const_Iterator& second) {
                return first.m_node != second.m_node;
            }
        private:
            const node* m_node;
        };

    public:
        rb_tree();
        rb_tree(const rb_tree& rhs);
        rb_tree(rb_tree&& rhs) noexcept;
        rb_tree& operator=(const rb_tree& rhs);
        rb_tree& operator=(rb_tree&& rhs) noexcept;
        void insert(const value_type& value);
        Const_Iterator search(const Key& value) const;
        Iterator search(const Key& value);
        void remove(const Key& value);
        void clear();
        bool empty() const;
        void print_in_order();
        Iterator begin();
        Iterator end();
        Const_Iterator cbegin() const noexcept;
        Const_Iterator cend() const noexcept;
        Compare& get_compare();
    private:
        void m_print_in_order(node* root);
        void balance(node* current);
        void left_rotate(node* current);
        void right_rotate(node* current);
        node* search_in_order_predecessor(node* current);
        node* search_in_order_successor(node* current);
        void remove_case_1(node* currect);
        void remove_case_2(node* currect);
        void remove_case_3(node* currect);
        void remove_case_4(node* currect);
        void remove_case_5(node* currect);
        void remove_case_6(node* currect);
        void remove_case_7(node* currect);
        void remove_case_8(node* currect);
        void remove_case_9(node* currect);
    private:
        node* m_root;
        Compare cmp;
    };
    
} // namespace mylib

#include "rb_tree.hpp"

#endif //RB_TREE_H
