template <class T , class Container , class Compare>
mylib::priority_queue<T,Container,Compare>& 
mylib::priority_queue<T,Container,Compare>::operator=(const priority_queue& ob)
{
    if(this==&ob)
    {
        return *this;
    }
    m_cont=ob.m_cont;
    m_comp=ob.m_comp;
    return *this;
}  

template <class T , class Container , class Compare>
mylib::priority_queue<T,Container,Compare>& 
mylib::priority_queue<T,Container,Compare>::operator=(priority_queue&& ob) noexcept
{
    if(this==&ob)
    {
        return *this;
    }
    m_cont=std::move(ob.m_cont);
    m_comp=std::move(ob.m_comp);
    return *this;
}  

template <class T , class Container , class Compare>
[[nodiscard]] bool mylib::priority_queue<T,Container,Compare>::empty() const
{
    return m_cont.empty();
}

template <class T , class Container , class Compare>
typename mylib::priority_queue<T,Container,Compare>::const_reference mylib::priority_queue<T,Container,Compare>::top() const
{
    if(!empty()){
    return m_cont[0];
    }
    return -1;
}

template <class T, class Container , class Compare>
void mylib::priority_queue<T,Container,Compare>::push( const value_type& value )
{
    m_cont.push_back(value);
    mylib::make_heap(m_cont.begin(),m_cont.end());
}

template <class T, class Container , class Compare>
void mylib::priority_queue<T,Container,Compare>::push(value_type&& value )
{
    m_cont.push_back(value);
    mylib::make_heap(m_cont.begin(),m_cont.end());
}

template <class T, class Container , class Compare>
mylib::priority_queue<T,Container,Compare>::size_type mylib::priority_queue<T,Container,Compare>::size() const
{
    return m_cont.size();
}

template <class T, class Container , class Compare>
template <typename... Args>
void mylib::priority_queue<T,Container,Compare>::emplace(Args&&... arg)
{
    m_cont.push_back(T{arg...});
}

template <class T, class Container , class Compare>
void mylib::priority_queue<T,Container,Compare>::pop()
{
    mylib::pop_heap(m_cont.begin() , m_cont.end());
}   

template <class T, class Container , class Compare>
void mylib::priority_queue<T,Container,Compare>::swap(priority_queue & rhs)
{
    std::swap(*this , rhs);
}

