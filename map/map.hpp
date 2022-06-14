#include "map.h"

template <typename Key, typename T, typename Compare>    
void mylib::map<Key, T, Compare>::insert(const value_type& value)
{
    m_tree.insert(value);
    ++m_size;
}

template <typename Key, typename T, typename Compare>    
mylib::map<Key, T, Compare>::~map()
{
    clear();
}

template <typename Key, typename T, typename Compare>    
typename mylib::map<Key, T, Compare>::Iterator  
 mylib::map<Key, T, Compare>::begin() noexcept
{
    return  m_tree.begin();
}

template <typename Key, typename T, typename Compare>    
typename mylib::map<Key, T, Compare>::Iterator 
 mylib::map<Key, T, Compare>::end() noexcept
{
    return  m_tree.end();
}

template <typename Key, typename T, typename Compare>    
typename mylib::map<Key, T, Compare>::Const_Iterator 
 mylib::map<Key, T, Compare>::cbegin() const noexcept
{
    return  m_tree.cbegin();
}

template <typename Key, typename T, typename Compare>    
typename mylib::map<Key, T, Compare>::Const_Iterator 
 mylib::map<Key, T, Compare>::cend() const noexcept
{
    return  m_tree.cend();
}

template <typename Key, typename T, typename Compare>
void mylib::map<Key, T, Compare>::print() 
{
    m_tree.print_in_order();
}

template <typename Key, typename T, typename Compare>
[[nodiscard]] bool mylib::map<Key, T, Compare>::empty() const noexcept
{
    return m_tree.empty();
}

template <typename Key, typename T, typename Compare>
T& mylib::map<Key, T, Compare>::operator[](const Key& key)
{
    auto it = m_tree.search(key);
    if(it == end()) {
        insert(mylib::make_pair(key, T{}));
    }
    it = m_tree.search(key);
    return (*m_tree.search(key)).second;
}	

template <typename Key, typename T, typename Compare>
T& mylib::map<Key, T, Compare>::operator[](Key&& key)
{
    auto it = m_tree.search(key);
    if(it == end()) {
        insert(mylib::make_pair(key, T{}));
    }
    it = m_tree.search(key);
    return (*m_tree.search(key)).second;
}	

template <typename Key, typename T, typename Compare>
T& mylib::map<Key, T, Compare>::at(const Key& key) 
{
    mylib::map<Key, T, Compare>::Iterator it;
    try
	{
        it = m_tree.search(key);
        if(it == end()) {
            throw std::invalid_argument("Invalid argument!");
        }
    }
	catch (const std::exception& ex)
	{
        std::cerr << '\n' << ex.what() << '\n';
        exit(0);
	}
    return (*it).second;
}

template <typename Key, typename T, typename Compare>
const T& mylib::map<Key, T, Compare>::at(const Key& key) const 
{
    mylib::map<Key, T, Compare>::Const_Iterator it;
    try
	{
        it = m_tree.search(key);
        if(it == cend()) {
            throw std::invalid_argument("Invalid argument!");
        }
    }
	catch (const std::exception& ex)
	{
        std::cerr << '\n' << ex.what() << '\n';
        exit(0);
	}
    return (*it).second;
}

template <typename Key, typename T, typename Compare>
typename mylib::map<Key, T, Compare>::size_type mylib::map<Key, T, Compare>::size() const noexcept
{
    return m_size;
}

template <typename Key, typename T, typename Compare>
void mylib::map<Key, T, Compare>::clear() noexcept
{
    m_tree.clear();
    m_size = 0;
}

template <typename Key, typename T, typename Compare>
typename mylib::map<Key, T, Compare>::Iterator mylib::map<Key, T, Compare>::erase(Iterator pos)
{
    Iterator tmp = pos;
    ++tmp;
    m_tree.remove((*pos).first);
    --m_size;
    return tmp;
}

template <typename Key, typename T, typename Compare>
mylib::map<Key, T, Compare>::map(const Compare& comp)
{
    m_tree.get_compare() = comp;
}

template <typename Key, typename T, typename Compare>
mylib::map<Key, T, Compare>::map(std::initializer_list<value_type> ilist)
{
    auto cur = ilist.begin();
    while(cur != ilist.end()) {
        insert(*cur);
        ++cur;
    }
}

template <typename Key, typename T, typename Compare>    
mylib::map<Key, T, Compare>& 
mylib::map<Key, T, Compare>::operator=(const mylib::map<Key, T, Compare>& rhs)
{
    if(this == &rhs) {
        return *this;
    }
    if(!empty()) {
        clear();
    }
    m_tree = rhs.m_tree;
    m_size = rhs.m_size;
    return *this;
}

template <typename Key, typename T, typename Compare>    
mylib::map<Key, T, Compare>& 
mylib::map<Key, T, Compare>::operator=(mylib::map<Key, T, Compare>&& rhs) noexcept
{
    if(this == &rhs) {
        return *this;
    }
    if(!empty()) {
        clear();
    }
    m_tree = std::move(rhs.m_tree);
    m_size = std::move(rhs.m_size);
    return *this;
}

template <typename Key, typename T, typename Compare>    
typename mylib::map<Key, T, Compare>::Iterator 
mylib::map<Key, T, Compare>::find(const Key& key) 
{
    auto it = m_tree.search(8);
    return it;
}

template <typename Key, typename T, typename Compare>    
typename mylib::map<Key, T, Compare>::Const_Iterator 
mylib::map<Key, T, Compare>::find(const Key& key) const
{
    auto it = m_tree.search(8);
    return it;
}
