#include "pool_alloc.h"

template <class T>
mylib::Pool_alloc<T>::Pool_alloc(size_t block_size , size_t subblock_size)
{
    m_block_size = subblock_size;
    m_block_count = 0;
    m_chunk = (block_size / subblock_size) * subblock_size;
    m_free_size = m_chunk;
    m_start = (int8_t*)::operator new(m_chunk);
    m_end = m_start + block_size;
    int8_t * tmp =m_start;

    while (tmp != m_end)
    {
        m_buffer.push_front(tmp);
        tmp+=m_block_size;
        ++m_block_count;
    }
}

template <class T>
mylib::Pool_alloc<T>::pointer
mylib::Pool_alloc<T>::allocate(size_t count)
{

    if((count * sizeof(T) > m_free_size))
    {
        throw (std::out_of_range("out of range"));
        exit(1);
    }
    
    int tmp_count = (count * sizeof(T) / m_block_size);
    if(count * sizeof(T) % m_block_size != 0 )
    {
        tmp_count++;
    } 

    int8_t* beg = m_buffer.front();

    while (tmp_count >= 0)
    {
        m_buffer.pop_front();
        --tmp_count;
        --m_block_count;
    }
    m_free_size -= sizeof(T) * count;

    return (T*)beg;
}

template <class T>
void mylib::Pool_alloc<T>::deallocate(T* start , size_t count)
{
    int8_t* st =(int8_t*) start;

    if(st < m_start || st >= m_end)
    {
        throw (std::out_of_range("out of range"));
        exit(2);
    }

    count =(count * sizeof(T) ) / m_block_size;
     
    if(! count)
    {
        count = 1;
    }

    int8_t* beg = m_buffer.front();

    while (count--)
    {
        m_buffer.push_front(st);
        st+=m_block_size;
        ++m_block_count;
    }

}