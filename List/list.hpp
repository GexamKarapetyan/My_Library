template <class U>
mylib::list<U>::list() : m_head{}, m_tail{m_head}, m_size{} {}

template <class U>
mylib::list<U>::list(list&& rhs) noexcept : m_head{rhs.m_head}, m_tail{rhs.m_tail}, m_size{rhs.m_size} 
{
    rhs.m_head = nullptr;
    rhs.m_tail = nullptr;
    rhs.m_size = 0;
}

template <class U>
mylib::list<U>& mylib::list<U>::operator=(const list<U>& rhs) 
{
    if(this == &rhs) {
        return *this;
    }
    if(m_head != nullptr)
        clear();
    Const_Iterator it = rhs.cbegin();
    int i {};
    while(it != rhs.cend()) {
        push_back(rhs[i]);
        ++i;
        ++it;
    }
    return *this;
}

template <class U>
mylib::list<U>::list(const list& rhs)
{
    m_size = rhs.m_size;
    m_head = nullptr;
    m_tail = nullptr;
    for (Const_Iterator it = rhs.cbegin(); it != rhs.cend(); ++it) {
        push_back(*it);
    }
}

template <class U>
mylib::list<U>& mylib::list<U>::operator=(list<U>&& rhs) noexcept 
{
    if(this == &rhs) {
        return *this;
    }
    if(!empty()) {
        clear();
    }
    this->m_head = rhs.m_head;
    this->m_tail = rhs.m_tail;
    rhs.m_head = nullptr;
    rhs.m_tail = nullptr;
    return *this;
}

template <class U>
U& mylib::list<U>::operator[](int index) const 
{
    Node<U>* current  = m_head;
    while(index) {
        current = current->m_next;
        --index;
    }
    return current->m_data;
}

template <class U>
void mylib::list<U>::push_back(const U& element)
{
    if(!m_tail) {
		m_head = m_tail = new Node<U>(element, nullptr, nullptr);
	} else {
		Node<U>* new_node = new Node<U>(element, nullptr, m_tail);
		m_tail->m_next = new_node;
		m_tail = new_node;
	}
    ++m_size;
}

template <class U>
void mylib::list<U>::push_front(const U& element)
{
    if(!m_head) {
		m_head = m_tail = new Node<U>(element, nullptr, nullptr);
	} else {
		Node<U>* new_node = new Node<U>(element, m_head, nullptr);
		m_head = new_node;
        new_node->m_next->m_prev = new_node;
	}
    ++m_size;
}

template <class U>
size_t mylib::list<U>::size() const
{
    return m_size;
}

template <class U>
mylib::list<U>::~list()
{
    if(!empty())
    clear();
}

template <class U>
void mylib::list<U>::clear() 
{
    if(!empty()) {
        while (m_head)
        {
            this->pop_front();
        }
        m_head = nullptr;
        m_tail = nullptr;
    }
}

template <class U>
bool mylib::list<U>::empty() const 
{
    return m_head == nullptr;
}

template <class U>
void mylib::list<U>::pop_front() 
{
    if(m_head == nullptr) {
        return;
    }
    if(m_head->m_next != nullptr) {
        Node<U>* tmp = m_head;
        m_head = tmp->m_next;
        tmp->m_next->m_prev = nullptr;
        delete tmp;
        tmp = nullptr;
    } else if (m_head->m_next == nullptr) {
        delete m_head;
        m_head = nullptr;
    }
}

template <class U>
void mylib::list<U>::pop_back() 
{
    if(m_head == nullptr) {
        return;
    }
    if(m_head->m_next != nullptr) {
        Node<U>* tmp = m_tail;
        m_tail = tmp->m_prev;
        m_tail->m_next = nullptr;
        delete tmp;
        tmp = nullptr;
    } else if (m_head->m_next == nullptr) {
        delete m_head;
        m_head = nullptr;
    }
}

template <class U>
mylib::list<U>::list(size_t count) : m_head {} , m_tail{}, m_size{}
{
    while (count) {
       push_back(U{});
        --count;
    }
}

template <class U>
mylib::list<U>::list(size_t count, const U& element) : m_head {}, m_tail{}, m_size{}
{
    while (count) {
       push_back(element);
        --count;
    }
}

template <class U>
mylib::list<U>::list(std::initializer_list<U> ilist) : m_head {}, m_tail{}, m_size{}
{
    auto cur = ilist.begin();
    while(cur != ilist.end()) {
        push_back(*cur);
        ++cur;
    }
}

template <class U>
typename mylib::list<U>::Iterator mylib::list<U>::insert
(mylib::list<U>::Iterator pos, const U& element) 
{
    if(pos == begin()) {
        push_front(element);
        return begin();
    }
    pos.get()->m_prev->m_next = new Node<U> (element, pos.get(), pos.get()->m_prev);
    pos.get()->m_prev->m_next->m_next->m_prev = pos.get()->m_prev->m_next;
    return --pos;
}

template <class U>
template <class... Args>
typename mylib::list<U>::Iterator mylib::list<U>::emplace
(mylib::list<U>::Iterator pos, Args&&... args) 
{
    if(pos == begin()) {
        push_front(U{args...});
        return begin();
    }
    pos.get()->m_prev->m_next = new Node<U> (U{args...}, pos.get(), pos.get()->m_prev);
    pos.get()->m_prev->m_next->m_next->m_prev = pos.get()->m_prev->m_next;
    return --pos;
}

template <class U>
template <class... Args>
typename mylib::list<U>::Iterator mylib::list<U>::emplace_back
(Args&&... args) 
{
    if(m_tail){
    mylib::list<U>::Iterator old_end=end();
    push_back(U{args...});
    return old_end;
    }
    else 
    {
        push_back(U{args...});
        return begin();
    }
}


template <class U>
template <class... Args>
typename mylib::list<U>::Iterator mylib::list<U>::emplace_front
(Args&&... args) 
{
    push_front(U{args...});
    return --back();
}

template <class U>
typename mylib::list<U>::Iterator mylib::list<U>::erase
(mylib::list<U>::Iterator pos) 
{
    if(pos == begin()) {
        pop_front();
        return begin();
    } else if(pos.get()->m_next == nullptr) {
        pop_back();
        return --pos;
    }
    Node<U>* tmp = pos.get();
    pos.get()->m_prev->m_next = pos.get()->m_next;
    pos.get()->m_next->m_prev = pos.get()->m_prev;
    ++pos;
    delete tmp;
    return pos;
}

template <class U>
void mylib::list<U>::swap(list<U>& rhs)
{
    Node<U>* tmp = m_head;
    m_head = rhs.m_head;
    rhs.m_head = tmp;
    tmp = m_tail;
    m_tail = rhs.m_tail;
    rhs.m_tail = tmp;
}

template <class U>
void mylib::list<U>::reverse()
{
    Node<U>* tmp = m_head;
    m_head = do_reverse(m_head, m_tail);
    m_tail = tmp;
}

template <class U>
mylib::Node<U>* mylib::list<U>::do_reverse(mylib::Node<U>* head, mylib::Node<U>* tail) 
{
    if ((head == nullptr || head->m_next == nullptr) ||
    (tail == nullptr || tail->m_prev == nullptr))
        return head;
    Node<U>* tmp = do_reverse(head->m_next, tail->m_prev);
    tail->m_prev->m_prev = tail;
    tail->m_prev = nullptr;
    head->m_next->m_next = head;
    head->m_next = nullptr;
    return tmp;
}

template <class U>
size_t mylib::list<U>::unique()
{
    size_t count = -1;
    if(m_head == nullptr) {
        return count;
    }
    count = 0;
    Iterator j = begin();
    ++j;
    for(Iterator i = begin(); j != end();) {
        if(*i == *j) {
            erase(j);
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
void mylib::list<U>::assign(size_t count, const U& element)
{
    if(m_head != nullptr) {
        clear();
    }
    while (count) {
       push_front(element);
        --count;
    }
}

template <class U>
template <typename InputIter>
void mylib::list<U>::assign(InputIter first, InputIter last)
{
    if(first >= last) {
        return;
    }
    if(m_head != nullptr) {
        clear();
    }
    InputIter& cur = first;
    while(cur != last) {
        push_back(*first);
        ++cur;
    }
}

template <class U>
void mylib::list<U>::assign(std::initializer_list<U> ilist)
{
    if(m_head != nullptr) {
        clear();
    }
    auto cur = ilist.begin();
    while(cur != ilist.end()) {
        push_back(*cur);
        ++cur;
    }
}

template <class U>
bool mylib::list<U>::is_sorted_list() const
{
    Node<U>* cur = m_head;
    Node<U>* after_cur = cur->m_next;
    while(cur != nullptr && cur->m_next != nullptr && after_cur->m_next != nullptr) {
        if(cur->m_data > after_cur->m_data) {
            return false;
        }
        cur = cur->m_next;
        after_cur = after_cur->m_next;
    }
    return true;
}

template <class U>
bool mylib::list<U>::operator==(const mylib::list<U>& rhs) const 
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
bool mylib::list<U>::operator!=(const mylib::list<U>& rhs) const 
{
    return !(*this == rhs);
}

template <class U>
bool mylib::list<U>::operator<(const mylib::list<U>& rhs) const 
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
bool mylib::list<U>::operator>(const mylib::list<U>& rhs) const 
{
    return !(*this <= rhs);
}

template <class U>
bool mylib::list<U>::operator<=(const mylib::list<U>& rhs) const 
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
bool mylib::list<U>::operator>=(const mylib::list<U>& rhs) const 
{
    return !(*this < rhs);
}

template <class U>
U& mylib::list<U>::front()
{
    return m_head->m_data;
}

template <class U>
const U& mylib::list<U>::front() const
{
    return m_head->m_data;
}

template <class U>
U& mylib::list<U>::back()
{
    return m_tail->m_data;
}

template <class U>
const U& mylib::list<U>::back() const
{
    return m_tail->m_data;
}

template <class U>
typename mylib::list<U>::Iterator& 
mylib::list<U>::Iterator::operator++() 
{
    it = it->m_next;
    return (*this);
}

template <class U>
typename mylib::list<U>::Iterator 
mylib::list<U>::Iterator::operator++(int) 
{
    Iterator tmp;
    tmp.it = this->it;
    ++(*this);
    return tmp;
}

template <class U>
typename mylib::list<U>::Iterator& 
mylib::list<U>::Iterator::operator--() 
{
    it = it->m_prev;
    return (*this);
}

template <class U>
typename mylib::list<U>::Iterator 
mylib::list<U>::Iterator::operator--(int) 
{
    Iterator tmp;
    tmp.it = this->it;
    --(*this);
    return tmp;
}

template <class U>
typename mylib::list<U>::Const_Iterator& 
mylib::list<U>::Const_Iterator::operator++() 
{
    it = it->m_next;
    return (*this);
}

template <class U>
typename mylib::list<U>::Const_Iterator 
mylib::list<U>::Const_Iterator::operator++(int) 
{
    Const_Iterator tmp;
    tmp.it = this->it;
    ++(*this);
    return tmp;
}

template <class U>
typename mylib::list<U>::Const_Iterator& 
mylib::list<U>::Const_Iterator::operator--() 
{
    it = it->m_prev;
    return (*this);
}

template <class U>
typename mylib::list<U>::Const_Iterator 
mylib::list<U>::Const_Iterator::operator--(int) 
{
    Const_Iterator tmp;
    tmp.it = this->it;
    --(*this);
    return tmp;
}

template <class U>
bool mylib::list<U>::Const_Iterator::operator==(Const_Iterator& rhs)
{
    return (this->it == rhs.it);
}

template <class U>
bool mylib::list<U>::Const_Iterator::operator!=(Const_Iterator& rhs)
{
    return !(this->it == rhs.it);
}

template <class U>
typename mylib::list<U>::Const_Iterator& 
mylib::list<U>::Const_Iterator::operator=(const Const_Iterator& rhs) 
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
typename mylib::list<U>::Const_Iterator& 
mylib::list<U>::Const_Iterator::operator=(Const_Iterator&& rhs) 
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
const U& mylib::list<U>::Const_Iterator::operator*() const
{
    return it->m_data;
}

template <class U>
U* mylib::list<U>::Const_Iterator::operator->()
{
    return &(*it);
}

template <class U>
bool mylib::list<U>::Iterator::operator==(Iterator& rhs)
{
    return (this->it == rhs.it);
}

template <class U>
bool mylib::list<U>::Iterator::operator!=(Iterator& rhs)
{
    return !(this->it == rhs.it);
}

template <class U>
typename mylib::list<U>::Iterator& 
mylib::list<U>::Iterator::operator=(const Iterator& rhs) 
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
typename mylib::list<U>::Iterator& 
mylib::list<U>::Iterator::operator=(Iterator&& rhs) 
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
U& mylib::list<U>::Iterator::operator*() 
{
    return it->m_data;
}

template <class U>
U* mylib::list<U>::Iterator::operator->()
{
    return it;
}

template <class U>
typename mylib::list<U>::Iterator mylib::list<U>::begin()
{
    Iterator tmp;
    tmp.it = m_head;
    return tmp;
}

template <class U>
typename mylib::list<U>::Iterator mylib::list<U>::end()
{
    Iterator tmp;
    tmp.it = m_tail->m_next;
    return tmp;
}

template <class U>
typename mylib::list<U>::Const_Iterator mylib::list<U>::cbegin() const 
{
    Const_Iterator tmp;
    tmp.it = m_head;
    return tmp;
}

template <class U>
typename mylib::list<U>::Const_Iterator mylib::list<U>::cend() const 
{
    Const_Iterator tmp;
    tmp.it = m_tail->m_next;
    return tmp;
}

template <class U>
void mylib::list<U>::sort()
{
    mergeSort(0, size() - 1);
}

template <class U>
void mylib::list<U>::mergeSort(int begin, int end)
{
    if (begin >= end)
        return;
  
    auto mid = begin + (end - begin) / 2;
    mergeSort(begin, mid);
    mergeSort(mid + 1, end);
    merge_for_sort(begin, mid, end);
}

template <class U>
void mylib::list<U>::merge_for_sort(int left, int mid, int right)
{
    int  sub_list_one = mid - left + 1;
    int  sub_list_two = right - mid;
    mylib::list<U> left_list(sub_list_one);
    mylib::list<U> right_list(sub_list_two);
    for (auto i = 0; i < sub_list_one; i++)
        left_list[i] = (*this)[left + i];
    for (auto j = 0; j < sub_list_two; j++)
        right_list[j] = (*this)[mid + 1 + j];
    int index_of_sub_list_one = 0;
    int index_of_sub_list_two = 0;
    int index_of_merged = left; 
    while (index_of_sub_list_one < sub_list_one && index_of_sub_list_two < sub_list_two) {
        if (left_list[index_of_sub_list_one] <= right_list[index_of_sub_list_two]) {
            (*this)[index_of_merged] = left_list[index_of_sub_list_one];
            index_of_sub_list_one++;
        }
        else {
            (*this)[index_of_merged] = right_list[index_of_sub_list_two];
            index_of_sub_list_two++;
        }
        index_of_merged++;
    }
    while (index_of_sub_list_one < sub_list_one) {
        (*this)[index_of_merged] = left_list[index_of_sub_list_one];
        index_of_sub_list_one++;
        index_of_merged++;
    }
    while (index_of_sub_list_two < sub_list_two) {
        (*this)[index_of_merged] = right_list[index_of_sub_list_two];
        index_of_sub_list_two++;
        index_of_merged++;
    }
} 

template <class U>
void mylib::list<U>::merge(list<U>& rhs) 
{
    if(is_sorted_list() && rhs.is_sorted_list()) {
        m_tail->m_next = rhs.m_head->m_next;
        m_tail->m_next->m_prev = m_tail;
        m_tail = rhs.m_tail;
        m_size += rhs.m_size - 1;
        sort();
        rhs.m_head = nullptr;
        rhs.m_tail = nullptr;
    } else {
        std::cout << "These lists are not sorted!\n";
    }
}







template <class U>
typename mylib::list<U>::Const_Reverse_Iterator& 
mylib::list<U>::Const_Reverse_Iterator::operator++() 
{
    it = it->m_next;
    return (*this);
}

template <class U>
typename mylib::list<U>::Const_Reverse_Iterator 
mylib::list<U>::Const_Reverse_Iterator::operator++(int) 
{
    Const_Reverse_Iterator tmp;
    tmp.it = this->it;
    ++(*this);
    return tmp;
}

template <class U>
typename mylib::list<U>::Const_Reverse_Iterator& 
mylib::list<U>::Const_Reverse_Iterator::operator--() 
{
    it = it->m_prev;
    return (*this);
}

template <class U>
typename mylib::list<U>::Const_Reverse_Iterator 
mylib::list<U>::Const_Reverse_Iterator::operator--(int) 
{
    Const_Reverse_Iterator tmp;
    tmp.it = this->it;
    --(*this);
    return tmp;
}

template <class U>
bool mylib::list<U>::Const_Reverse_Iterator::operator==(Const_Reverse_Iterator& rhs)
{
    return (this->it == rhs.it);
}

template <class U>
bool mylib::list<U>::Const_Reverse_Iterator::operator!=(Const_Reverse_Iterator& rhs)
{
    return !(this->it == rhs.it);
}

template <class U>
typename mylib::list<U>::Const_Reverse_Iterator& 
mylib::list<U>::Const_Reverse_Iterator::operator=(const Const_Reverse_Iterator& rhs) 
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
typename mylib::list<U>::Const_Reverse_Iterator& 
mylib::list<U>::Const_Reverse_Iterator::operator=(Const_Reverse_Iterator&& rhs) 
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
const U& mylib::list<U>::Const_Reverse_Iterator::operator*() const
{
    return it->m_data;
}

template <class U>
U* mylib::list<U>::Const_Reverse_Iterator::operator->()
{
    auto itr=it;
    --itr;
    return&(*itr);
}

template <class U>
typename mylib::list<U>::Reverse_Iterator& 
mylib::list<U>::Reverse_Iterator::operator++() 
{
    it = it->m_next;
    return (*this);
}

template <class U>
typename mylib::list<U>::Reverse_Iterator 
mylib::list<U>::Reverse_Iterator::operator++(int) 
{
    Reverse_Iterator tmp;
    tmp.it = this->it;
    ++(*this);
    return tmp;
}

template <class U>
typename mylib::list<U>::Reverse_Iterator& 
mylib::list<U>::Reverse_Iterator::operator--() 
{
    it = it->m_prev;
    return (*this);
}

template <class U>
typename mylib::list<U>::Reverse_Iterator 
mylib::list<U>::Reverse_Iterator::operator--(int) 
{
    Reverse_Iterator tmp;
    tmp.it = this->it;
    --(*this);
    return tmp;
}

template <class U>
bool mylib::list<U>::Reverse_Iterator::operator==(Reverse_Iterator& rhs)
{
    return (this->it == rhs.it);
}

template <class U>
bool mylib::list<U>::Reverse_Iterator::operator!=(Reverse_Iterator& rhs)
{
    return !(this->it == rhs.it);
}

template <class U>
typename mylib::list<U>::Reverse_Iterator& 
mylib::list<U>::Reverse_Iterator::operator=(const Reverse_Iterator& rhs) 
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
typename mylib::list<U>::Reverse_Iterator& 
mylib::list<U>::Reverse_Iterator::operator=(Reverse_Iterator&& rhs) 
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
U& mylib::list<U>::Reverse_Iterator::operator*()
{
    return it->m_data;
}

template <class U>
U* mylib::list<U>::Reverse_Iterator::operator->()
{
    auto itr=it;
    --itr;
    return&(*itr);
}

template <class U>
typename mylib::list<U>::Reverse_Iterator mylib::list<U>::rbegin()
{
    Reverse_Iterator tmp;
    tmp.it = m_tail;
    return tmp;
}

template <class U>
typename mylib::list<U>::Reverse_Iterator mylib::list<U>::rend()
{
    Reverse_Iterator tmp;
    tmp.it = m_head->m_prev;
    return tmp;
}

template <class U>
typename mylib::list<U>::Const_Reverse_Iterator mylib::list<U>::crbegin() const
{
    Const_Reverse_Iterator tmp;
    tmp.it = m_tail;
    return tmp;
}

template <class U>
typename mylib::list<U>::Const_Reverse_Iterator mylib::list<U>::crend() const
{
    Const_Reverse_Iterator tmp;
    tmp.it = m_head->m_prev;
    return tmp;
}