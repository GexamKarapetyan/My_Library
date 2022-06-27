#ifndef _POOL_ALLOC_H_
#define _POOL_ALLOC_H_

#include <iostream>
#include <forward_list>
#include <exception>

namespace mylib
{
    template <class T>
    class Pool_alloc
    {
        public:
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
        public:
            Pool_alloc(size_t block_size = 1000000 , size_t subblock_size = 4);
            pointer allocate (size_t count);
            void deallocate (T* start , size_t count);
            void free();
        private:
            size_t m_chunk;
            size_t m_block_count;
            size_t m_block_size;
            size_t m_free_size;
            int8_t* m_start;
            int8_t* m_end;
            std::forward_list<int8_t*> m_buffer;
    };


} // nemaspace mylib

#include "pool_alloc.hpp"

#endif //_POOL_ALLOC_H_