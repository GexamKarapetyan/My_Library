#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <iterator>

namespace mylib {

    template<typename T>
    class vector
    {
    public:
        vector();
        vector(int colum,const T& value);
        vector(int col);
        vector(const vector & other);
        vector(vector && other) noexcept;
        vector & operator=(const vector & other);
        vector & operator=(vector && other) noexcept;
        T& operator[] (int index);
        const T& operator[] (int index) const;
        ~vector();
        vector(const std::initializer_list<T>& elems);
    public:
        void push_back(const T& value);
        void pop_back();
        int size() const;
        int capacity() const;
        void shrink_to_fit();
    public:
        class iterator : public std::iterator<std::random_access_iterator_tag,T>
        {
        public:
            iterator(T * p = nullptr);
            iterator(const iterator& it);
            iterator & operator= (const iterator& it);
            iterator operator+(int add);
            iterator operator-(int sub);
            iterator& operator+=(int add);
            iterator& operator-=(int sub);
            T& operator++();
            T& operator++(int);
            T& operator--();
            T& operator--(int);
            bool operator!=(const iterator& other) const;
            bool operator==(const iterator& other) const;
            T& operator*() const;
        private:
            T * iter;
        };

        iterator begin();
        iterator end();
        void insert(iterator& iter,const T& value);
        void erease(iterator& iter);
        void clear();
        const T * data() const { return m_buffer; }

    private:
        T * m_buffer;
        int m_size;
        int m_capacity;
    };
} //namespace mylib

template<typename T>
mylib::vector<T>::vector()
{
    m_size = 0;
    m_capacity = 1;
    m_buffer = new T[1];
}

template<typename T>
mylib::vector<T>::vector(int col)
{
    m_size=col;
    m_capacity = 2 *m_size;
    m_buffer = new T[m_capacity];
}

template<typename T>
mylib::vector<T>::vector(const std::initializer_list<T>& elems) 
{
    m_size = elems.m_size();
    m_capacity = m_size * 2;
    m_buffer = new T[m_capacity];
    int i = 0;
    for(auto it = elems.begin(); it != elems.end(); ++it, ++i) 
    {
        m_buffer[i] = *it;
    }
}

template<typename T>
mylib::vector<T>::vector(int colum,const T& value)
{
    m_size = colum;
    m_capacity = m_size * 2;
    m_buffer = new T[m_capacity];
    for(int i = 0; i < m_size; i++) 
    {
        m_buffer[i] = value;
    }
}

template<typename T>
mylib::vector<T>::~vector()
{
    delete[] m_buffer;
}

template<typename T>
void mylib::vector<T>::push_back(const T& value) 
{
    if(m_capacity == m_size) 
    {
        T *tmp = new T[m_capacity * 2];
        for(int i = 0; i < m_capacity; ++i) 
        {
            tmp[i] = m_buffer[i];
        }
        delete[] m_buffer;
        m_buffer = tmp;
        m_capacity *= 2;
        tmp = nullptr;
    }
    m_buffer[m_size++] = value;
}

template<typename T>
void mylib::vector<T>::pop_back() 
{
    T *tmp = new T[m_capacity - 1];
    for(int i = 0; i < m_size - 1; i++) 
    {
        tmp[i] = m_buffer[i];
    }
    delete [] m_buffer;
    m_buffer = tmp;
    m_capacity--;
    m_size--;
}

template<typename T>
int mylib::vector<T>::size() const
{
    return m_size;
}

template<typename T>
int mylib::vector<T>::capacity() const
{
    return m_capacity;
}

template<typename T>
mylib::vector<T>::vector(const vector & other)
{
    this->m_size = other.m_size;
    this->m_capacity = other.m_capacity;
    this->m_buffer = new T [other.m_capacity];
    for(int i = 0;i < m_size; i++) 
    {
        this->m_buffer[i] = other.m_buffer[i];
    }
}

template<typename T>
mylib::vector<T>::vector(vector && other) noexcept
{
    m_buffer = other.m_buffer;
    this->m_size = other.m_size;
    this->m_capacity = other.m_capacity;
    other.m_buffer = nullptr;
    this->m_size = 0;
    this->m_capacity = 0;
}

template<typename T>
mylib::vector<T> & mylib::vector<T>::operator=(const vector & other)
{
    if(this == &other) 
    {
        return * this;
    }
    delete [] m_buffer;
    this->m_size = other.m_size;
    this->m_capacity = other.m_capacity;
    this->m_buffer = new T [other.m_capacity];
    for(int i = 0;i < m_size; i++){
    
        this->m_buffer[i] = other.m_buffer[i];
    }
    return *this;
}

template<typename T>
mylib::vector<T> & mylib::vector<T>::operator=(vector && other) noexcept
{
    if(this == &other) 
    {
        return *this;
    }
    delete[] m_buffer;
    this->m_size = other.m_size;
    this->m_capacity = other.m_capacity;
    this->m_buffer = other.m_buffer;
    other.m_buffer = nullptr;
    return *this;
}

template<typename T>
T& mylib::vector<T>::operator[](int index) 
{
    return m_buffer[index];
}

template<typename T>
const T& mylib::vector<T>::operator[](int index) const
{
    return m_buffer[index];
}


template<typename T>
void mylib::vector<T>::shrink_to_fit() 
{
    m_capacity = m_size;
}

template<typename T>
void mylib::vector<T>::insert(mylib::vector<T>::iterator& iter,const T& value) 
{
    if(m_size < m_capacity) 
    {
        for(iterator i = this->end(); i != iter; --i) 
        {
            *i = *(i - 1);
        }
        *iter = value;
    }
    else
    {
        m_capacity *= 2;
        T* tmp = new T [m_capacity]; 
        int j = 0;
        for(auto i = this->begin();i != iter;++i )
        {
            tmp[j++] = *i;
        }
        tmp[j] = value;
        for(;iter != this->end(); ++iter)
        {
            tmp[++j] = *iter;
        }
        delete[] m_buffer;
        m_buffer = tmp;
    }
    m_size++;
}

template<typename T>
void mylib::vector<T>::erease(mylib::vector<T>::iterator& iter) 
{
    T *tmp = new T[m_capacity];
    int i = 0;
    for(i = 0; i < m_size; i++) 
    {
        if(m_buffer[i] == *iter) 
        {
            break;
        } 
        tmp[i] = m_buffer[i];
    }
    for(int j = i + 1;j < m_size; ++j) 
    {
        tmp[i] = m_buffer[j];
        i++;
    }
    delete [] m_buffer;
    m_buffer = tmp;
    tmp = nullptr;
    m_size--;
}

template<typename T>
typename mylib::vector<T>::iterator mylib::vector<T>::begin() 
{
    mylib::vector<T>::iterator it(m_buffer);
    return it;
}

template<typename T>
typename mylib::vector<T>::iterator mylib::vector<T>::end() 
{
    mylib::vector<T>::iterator it(m_buffer + m_size);
    return it;
}

template <typename T>
mylib::vector<T>::iterator::iterator(T* p)
{
    iter = p;
}

template <typename T>
mylib::vector<T>::iterator::iterator(const iterator& r)
{
    iter = r.iter;
}

template <typename T>
typename mylib::vector<T>::iterator & mylib::vector<T>::iterator::operator=(const iterator& r)
{
    if(this == &r) { return *this; }
    this->iter = r.iter;
    return *this;
}

template <typename T>
typename mylib::vector<T>::iterator mylib::vector<T>::iterator::operator+(int add)
{
    iterator it;
    it.iter = iter + add;
    return it;
}

template <typename T>
typename mylib::vector<T>::iterator mylib::vector<T>::iterator::operator-(int sub)
{
    iterator it;
    it.iter = iter - sub;
    return it;
}


template <typename T>
typename mylib::vector<T>::iterator& mylib::vector<T>::iterator::operator+=(int add) 
{
    this->iter += add;
    return *this;
}

template <typename T>
typename mylib::vector<T>::iterator& mylib::vector<T>::iterator::operator-=(int sub) 
{
    this->iter -= sub;
    return *this;
}

template <typename T>
T& mylib::vector<T>::iterator::operator++() 
{
    ++iter;
    return *iter;
}

template <typename T>
T& mylib::vector<T>::iterator::operator++(int) 
{
    T *tmp = iter;
    ++iter;
    return *tmp;
}

template <typename T>
T& mylib::vector<T>::iterator::operator--() 
{
    --iter;
    return *iter;
}

template <typename T>
T& mylib::vector<T>::iterator::operator--(int) 
{
    T *tmp = iter;
    --iter;
    return *tmp;
}

template <typename T>
bool mylib::vector<T>::iterator::operator!=(const iterator& other) const 
{
    return this->iter != other.iter;
}

template <typename T>
bool mylib::vector<T>::iterator::operator==(const iterator& other) const 
{
    return this->iter == other.iter;
}

template <typename T>
T& mylib::vector<T>::iterator::operator*() const 
{
    return *iter;
}

template <typename T>
void mylib::vector<T>::clear()
{
    delete []m_buffer;
    m_size = 0;
    m_capacity = 1;
    m_buffer = new T[m_capacity];
}

//bool specialization
#define int_bit_size 32

namespace mylib {
    template <>
    class vector <bool>
    {
    public:
        class reference {
        public:
            reference(bool state, int index, vector<bool> * ptr, int separate) : m_bit {state} , m_index{index}, m_vec {ptr}, m_separate{separate} {}
            reference() = default;
            reference(const reference&) = default;
            reference(reference&&) noexcept = default;
            constexpr ~reference() = default;
            reference& operator=(bool state) {
                m_bit = state;
                int musk = state;
                musk <<= m_index;
                if(state) {
                    (*m_vec).data()[m_separate] |= musk;
                } else {
                    (*m_vec).data()[m_separate] &= musk;
                }
                return *this;
            }
            constexpr reference& operator=(const reference&) = default;
            reference& operator=(reference&&) noexcept = default;
            void flip() {
                int musk = 1;
                musk <<= m_index;
                int tmp_state = musk;
                tmp_state &= (*m_vec).data()[m_separate];
                if(tmp_state) {
                    musk = 0;
                    (*m_vec).data()[m_separate] &= musk;
                } else {
                    (*m_vec).data()[m_separate] |= musk;
                }
            }
            operator bool() const {
                return m_bit;
            }
        private:
            vector<bool>* m_vec;
            int m_index;
            bool m_bit;
            int m_separate;
        };

    public:
        vector();
        vector(int bit_size);
        ~vector();
        int32_t* data() const;
    public:
        bool operator[](int index) const;
        reference operator[](int index); 
    private:
        int32_t* m_buffer;
        int m_size;
    };
} //namespace mylib

mylib::vector<bool>::vector() : m_buffer {}, m_size {} {}

mylib::vector<bool>::vector(int bit_size) : m_buffer {}, m_size {bit_size}
{
    int separate = bit_size / int_bit_size;
    if(bit_size % int_bit_size) {
        ++separate;
    }
    m_buffer = new int[separate];
}

bool mylib::vector<bool>::operator[](int index) const
{
    int separate = index / int_bit_size;
    int musk = 1;
    if(index > 32) {
        musk <<= index % int_bit_size;
    } else {
        musk <<= index;
    }
    musk &= m_buffer[separate];
    return musk;
}

mylib::vector<bool>::reference mylib::vector<bool>::operator[](int index)
{
    int separate = index / int_bit_size;
    int musk = 1;
    int tmp_index;
    if(index > 32) {
        musk <<= index % int_bit_size;
        tmp_index = index % int_bit_size;
    } else {
        musk <<= index;
        tmp_index = index;
    }
    musk &= m_buffer[separate];
    mylib::vector<bool>::reference ref(musk, tmp_index, this, separate);
    return ref;
}

int32_t* mylib::vector<bool>::data() const
{
    return m_buffer;
}

mylib::vector<bool>::~vector() 
{
    delete[] m_buffer;
}

#endif //VECTOR_H