#include "myFlist.h"

template <class U>
mylib::Forward_list<U>::Forward_list() : m_head{} {}

template <class U>
mylib::Forward_list<U>::Forward_list(int count,const U& elem):m_head{}
{
  while(count)
  {
      push_front(elem);
      --count;
  }
}

template <class U>
mylib::Forward_list<U>::Forward_list(std::initializer_list<U> ilist)
{
    auto cur=ilist.begin();
    while(cur!=ilist.end())
    {
        push_front(*cur);
        ++cur;
    }
    reverse();
}

template <class U>
mylib::Forward_list<U>::~Forward_list()
{
    if(!is_empty()){
    clear();
}
}

template <class U>
void mylib::Forward_list<U>::push_front(const U& element)
{
    m_head = new Node(element, m_head);
}

template <class U>
U& mylib::Forward_list<U>::front()
{
    return m_head->m_data;
}

template <class U>
const U& mylib::Forward_list<U>::front() const
{
    return m_head->m_data;
}

template <class U>
bool mylib::Forward_list<U>::is_empty() const 
{
    return m_head == nullptr;
}

template <class U>
void mylib::Forward_list<U>::pop_front() 
{
    if(m_head == nullptr) {
        return;
    }
    if(m_head->m_next != nullptr) {
        Node<U>* tmp = m_head;
        m_head = m_head->m_next;
        delete tmp;
        tmp=nullptr;
    } else if (m_head->m_next == nullptr) {
        delete m_head;
        m_head = nullptr;
    }
}

template <class U>
mylib::Forward_list<U>::Forward_list(int count) : m_head {}
{
    while (count)
    {
       push_front(U{});
        --count;
    }
}

template <class U>
U& mylib::Forward_list<U>::operator[](int index) const 
{
    Node<U>* current  = m_head;
    while(index) {
        current = current->m_next;
        --index;
    }
    return current->m_data;
}

template <class U>
void mylib::Forward_list<U>::clear() 
{
    if(!is_empty()) {
        while (m_head)
        {
            this->pop_front();
        }
    }
}

template <class U>
mylib::Forward_list<U>::Forward_list(const Forward_list& rhs)
{
    Iterator it = rhs.begin();
    int i{};
    while(it != rhs.end()) {
        this->push_front(rhs[i]);
        ++i;
    }
}

template <class U>
mylib::Forward_list<U>::Forward_list(Forward_list&& rhs) noexcept 
{
    m_head = rhs.m_head;
    rhs.m_head = nullptr;
}

template <class U>
mylib::Forward_list<U>& mylib::Forward_list<U>::operator=(const Forward_list<U>& rhs) 
{
    if(this == &rhs) {
        return *this;
    }
    if(m_head!=nullptr){
    clear();
   }
    Const_Iterator it = rhs.cbegin();
    int i{};
    while(it != rhs.cend()) {
        this->push_front(rhs[i]);
        ++i;
        ++it;
    }
    return *this;
}

template <class U>
mylib::Forward_list<U>& mylib::Forward_list<U>::operator=(Forward_list<U>&& rhs) noexcept 
{
    if(this == &rhs) {
        return *this;
    }
    if(!is_empty())
    clear();
    this->m_head = rhs.m_head;
    rhs.m_head = nullptr;
    return *this;
}

template <class U>
typename mylib::Forward_list<U>::Iterator mylib::Forward_list<U>::insert_after
(mylib::Forward_list<U>::Iterator pos, const U& element) 
{
    if(pos == before_begin()) {
        push_front(element);
        return begin();
    } 
        
        pos.get()->m_next = new Node<U> (element,  pos.get()->m_next);
        return pos++;
}

template <class U>
typename mylib::Forward_list<U>::Iterator mylib::Forward_list<U>::erase_after
(mylib::Forward_list<U>::Iterator pos) 
{
    if(pos == before_begin()) {
        pop_front();
        return begin();
    } 
        Node<U>* tmp = pos.get()->m_next;
        pos.get()->m_next = tmp->m_next;
        delete tmp;
        return ++pos;
}

template <class U>
void mylib::Forward_list<U>::swap(int index1, int index2)
{
        Node<U>* cur_1 = m_head;
        Node<U>* cur_2 = m_head;
        while(index1) {
            cur_1 = cur_1->m_next;
            --index1;
        }
        while(index2) {
            cur_2 = cur_2->m_next;
            --index2;
        }
        U tmp = std::move(cur_1->m_data);
        cur_1->m_data = std::move(cur_2->m_data);
        cur_2->m_data = std::move(tmp); 
}

template <class U>
void mylib::Forward_list<U>::sort() 
{
    int end=0;
    for(auto it:*this)
    {
        ++end;
    }
    mergeSort(0,end-1);
}

template <class U>
void mylib::Forward_list<U>::merge_for_sort( int const left, int const mid, int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

     mylib::Forward_list<U> leftList (subArrayOne);
     mylib::Forward_list<U> rightList(subArrayOne);
  
       for (auto i = 0; i < subArrayOne; i++)
        leftList[i] = (*this)[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightList[j] = (*this)[mid + 1 + j];
  
    auto indexOfSubArrayOne = 0,
        indexOfSubArrayTwo = 0; 
    int indexOfMergedArray = left; 
  
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftList[indexOfSubArrayOne] <= rightList[indexOfSubArrayTwo]) {
            (*this)[indexOfMergedArray] = leftList[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            (*this)[indexOfMergedArray] = rightList[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    while (indexOfSubArrayOne < subArrayOne) {
        (*this)[indexOfMergedArray] = leftList[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
        (*this)[indexOfMergedArray] = rightList[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

template <class U>
void mylib::Forward_list<U>::mergeSort(int const begin, int const end)
{
    if (begin >= end)
        return; 
  
    auto mid = begin + (end - begin) / 2;
    mergeSort(begin, mid);
    mergeSort(mid + 1, end);
    merge_for_sort(begin, mid, end);
}


template <class U>
mylib::Node<U>* mylib::Forward_list<U>::do_reverse(mylib::Node<U>* head) 
{
   if (head == nullptr || head->m_next == nullptr) return head;
	Node<U>* ptr = do_reverse(head->m_next);
	head->m_next->m_next = head;
	head->m_next=nullptr ;
	return ptr;
}

template <class U>
void mylib::Forward_list<U>::reverse() 
{
   m_head=do_reverse(m_head);
   
}
   
template <class U>
bool mylib::Forward_list<U>::is_sorted_list() const
{
    Node<U>* cur=m_head;
    Node<U>* after_cur=m_head->m_next;
    while (cur!=nullptr && cur->m_next != nullptr && after_cur->m_next !=nullptr)
    {
        if(cur->m_data > after_cur->m_data)
        {
            return false;
        }
        cur=cur->m_next;
        after_cur=after_cur->m_next;
    }
    return true;
    
}

template <class U>
void mylib::Forward_list<U>::merge(Forward_list<U>& rhs) 
{
   if(is_sorted_list() && rhs.is_sorted_list())
   {
       Node<U>* tmp=m_head;
       while(m_head!=nullptr && tmp->m_next!=nullptr)
       {
           tmp=tmp->m_next;
       }
       tmp->m_next=rhs.m_head;  
       sort();
   }
   else std::cout<<"Not sorted lists"<<std::endl;
}

template <class U>
typename mylib::Forward_list<U>::Iterator mylib::Forward_list<U>::begin() const 
{
    Iterator tmp;
    tmp.it = m_head;
    return tmp;
}

template <class U>
typename mylib::Forward_list<U>::Const_Iterator mylib::Forward_list<U>::cbegin() const 
{
    Const_Iterator tmp;
    tmp.it = m_head;
    return tmp;
}

template <class U>
typename mylib::Forward_list<U>::Iterator mylib::Forward_list<U>::before_begin() const 
{
    Iterator tmp;
    tmp.it = m_head-1;
    return tmp;
}

template <class U>
typename mylib::Forward_list<U>::Iterator mylib::Forward_list<U>::end() const 
{
    Iterator tmp;
    tmp.it = m_head;
    while(tmp.it != nullptr) {
       ++tmp;
    }
    return tmp;
}

template <class U>
typename mylib::Forward_list<U>::Const_Iterator mylib::Forward_list<U>::cend() const 
{
    Const_Iterator tmp;
    tmp.it = m_head;
    while(tmp.it != nullptr) {
       ++tmp;
    }
    return tmp;
}

template <class U>
bool mylib::Forward_list<U>::operator==(const mylib::Forward_list<U>& rhs) const 
{
    Const_Iterator it = cbegin();
    int i{};
    while(it != cend()) {
        if(*this[i] != rhs[i]) {
            return false;
        }
        ++i;
    }
    return true;
}

template <class U>
bool mylib::Forward_list<U>::operator!=(const mylib::Forward_list<U>& rhs) const 
{
    return !(*this == rhs);
}

template <class U>
bool mylib::Forward_list<U>::operator<(const mylib::Forward_list<U>& rhs) const 
{
   Const_Iterator it = cbegin();
    int i{};
    while(it != cend()) {
        if(*this[i] > rhs[i]) {
            return false;
        }
        ++i;
    }
    return true;
}

template <class U>
bool mylib::Forward_list<U>::operator>(const mylib::Forward_list<U>& rhs) const 
{
    return !(*this <= rhs);
}

template <class U>
bool mylib::Forward_list<U>::operator<=(const mylib::Forward_list<U>& rhs) const 
{
    Const_Iterator it = cbegin();
    int i{};
    while(it != cend()) {
        if(*this[i] >= rhs[i]) {
            return false;
        }
        ++i;
    }
    return true;
}

template <class U>
bool mylib::Forward_list<U>::operator>=(const mylib::Forward_list<U>& rhs) const 
{
    return !(*this < rhs);
}

template <class U>
typename mylib::Forward_list<U>::Iterator& 
mylib::Forward_list<U>::Iterator::operator++() 
{
    it = it->m_next;
    return (*this);
}

template <class U>
typename mylib::Forward_list<U>::Iterator 
mylib::Forward_list<U>::Iterator::operator++(int) 
{
    Iterator tmp;
    tmp.it = this->it;
    ++(*this);
    return tmp;
}

template <class U>
bool mylib::Forward_list<U>::Iterator::operator==(Iterator& rhs)
{
    return (this->it == rhs.it);
}

template <class U>
bool mylib::Forward_list<U>::Iterator::operator!=(Iterator& rhs)
{
    return !(this->it == rhs.it);
}

template <class U>
typename mylib::Forward_list<U>::Iterator& 
mylib::Forward_list<U>::Iterator::operator=(const Iterator& rhs) 
{
    if(this == &rhs) {
        return *this;
    }
    if(this != nullptr) {
        delete this;
    }
    this->it = rhs.it;
    return *this;
}

template <class U>
typename mylib::Forward_list<U>::Iterator& 
mylib::Forward_list<U>::Iterator::operator=(Iterator&& rhs) 
{
    if(this == &rhs) {
        return *this;
    }
    if(this != nullptr) {
        delete this;
    }
    this->it = rhs.it;
    return *this;
}

template <class U>
U& mylib::Forward_list<U>::Iterator::operator*() 
{
    return it->m_data;
}

template <class U>
U* mylib::Forward_list<U>::Iterator::operator->()
{
    return &(*it);
}

template <class U>
typename mylib::Forward_list<U>::Const_Iterator&
mylib::Forward_list<U>::Const_Iterator::operator++() 
{
    it = it->m_next;
    return (*this);
}

template <class U>
typename mylib::Forward_list<U>::Const_Iterator 
mylib::Forward_list<U>::Const_Iterator::operator++(int) 
{
    Const_Iterator tmp;
    tmp.it = this->it;
    ++(*this);
    return tmp;
}

template <class U>
bool mylib::Forward_list<U>::Const_Iterator::operator==(Const_Iterator& rhs)
{
    return (this->it == rhs.it);
}

template <class U>
bool mylib::Forward_list<U>::Const_Iterator::operator!=(Const_Iterator& rhs)
{
    return !(this->it == rhs.it);
}

template <class U>
typename mylib::Forward_list<U>::Const_Iterator& 
mylib::Forward_list<U>::Const_Iterator::operator=(const Const_Iterator& rhs) 
{
    if(this == &rhs) {
        return *this;
    }
    if(this != nullptr) {
        delete this;
    }
    this->it = rhs.it;
    return *this;
}

template <class U>
typename mylib::Forward_list<U>::Const_Iterator& 
mylib::Forward_list<U>::Const_Iterator::operator=(Const_Iterator&& rhs) 
{
    if(this == &rhs) {
        return *this;
    }
    if(this != nullptr) {
        delete this;
    }
    this->it = rhs.it;
    return *this;
}

template <class U>
const U& mylib::Forward_list<U>::Const_Iterator::operator*() const
{
    return it->m_data;
}

template <class U>
U* mylib::Forward_list<U>::Const_Iterator::operator->()
{
    return &(*it);
}

template <class U>
size_t mylib::Forward_list<U>::unique()
{
    if(m_head==nullptr)
    {
        return -1;
    }
    size_t count=0;
    Iterator j=begin();
    ++j;
    for(Iterator i=begin(); j!=end();)
    {
        if(*i == *j)
        {
            erase_after(i);
            ++count;
            ++j;
            continue;
        }
        ++i;
        ++j;
    }
    return count;
}

template <class U>
template <class... Args>
typename mylib::Forward_list<U>::Iterator mylib::Forward_list<U>::emplace_after(mylib::Forward_list<U>::Iterator pos,Args&&... args)
{
    if(pos==before_begin())
    {
        push_front(U{args...});
        return begin();
    }
        pos.get()->m_next=new Node<U> (U{args...},pos.get()->m_next);
        return pos++;
    
}

template <class U>
void mylib::Forward_list<U>::assign(size_t count,const U& element)
{
 if(m_head!=nullptr)
 {
     clear();
 }
 while (count)
 {
     push_front(element);
     --count;
 }
}

template <class U>
template <class InputIter>
void mylib::Forward_list<U>::assign(InputIter first,InputIter last)
{
    if(first>= last)
    {
        return;
    }
    if(m_head!=nullptr)
    {
        clear();
    }
    InputIter& cur=first;
    while(cur!=last)
    {
        push_front(*cur);
        ++cur;
    }
    reverse();
}

template <class U>
void mylib::Forward_list<U>::assign(std::initializer_list<U> ilist)
{
     if(m_head!=nullptr)
    {
        clear();
    }
    auto cur=ilist.begin();
    while(cur!=ilist.end())
    {
        push_front(*cur);
        ++cur;
    }
    reverse();
}
