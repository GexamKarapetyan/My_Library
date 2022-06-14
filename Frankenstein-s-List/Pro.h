#include "Pro.h"

template <typename T>
FL::F_List<T>::F_List(const T& elem)
{
	m_head = new Node(elem);
	m_tail = m_head;
	m_max = m_head;
	m_min = m_head;
	m_size = 1;
}

template <typename T>
FL::F_List<T>::~F_List()
{
	Node* tmp = m_head;
	Node* tmp2 = tmp;
	while (tmp != nullptr)
	{
		tmp2 = tmp->next;
		delete tmp;
		tmp = tmp2;
	}
}

template <typename T>
int FL::F_List<T>::size() const
{
	return m_size;
}

template <typename T>
void FL::F_List<T>::push_back(const T& elem)
{
	if (m_head == nullptr)
	{
		m_head = new Node(elem);
		m_tail = m_head;
		m_max = m_head;
		m_min = m_head;
		m_size++;
	}
	else
	{
		Node<T>* tmp = new Node(elem, nullptr, m_tail);
		m_tail->next = tmp;
		sorted(tmp);
		m_tail = tmp;
		m_size++;
	}
}

template <typename T>
void FL::F_List<T>::push_front(const T& elem)
{
	if (m_head == nullptr)
	{
		m_head = new Node<T>*new_elem;
		m_tail = m_head;
		m_max = m_head;
		m_min = m_head;
		m_size++;
	}

	else
	{
		Node* tmp = new Node(elem, m_head);
		m_head->prev = tmp;
		sorted(tmp);
		m_head = tmp;
		m_size++;
	}
}

template<typename T>
void FL::F_List<T>::insert(const T& elem, int ind)
{
	if (ind<0 && ind>m_size)
	{
		throw std::invalid_argument("is not a range number.");
	}
	if (ind == 0)
	{
		push_front(elem);
	}
	else if (ind == m_size)
	{
		push_back(elem);
	}

	else
	{
		int tmp_ind = 0;
		Node<T>* cur = m_head;
		while (tmp_ind != ind)
		{
			cur = cur->next;
			tmp_ind++;
		}
		Node<T>* temp = new Node<T>(elem);
		cur->prev->next = temp;
		temp->prev = cur->prev;
		temp->next = cur;
		cur->prev = temp;
		sorted(temp);
		m_size++;
	}
}

template <typename T>
void FL::F_List<T>::pop_back()
{
	if (m_head == nullptr)
	{
		std::cout << "The list is empty" << std::endl;
		return;
	}
	if (m_tail == m_min)
	{
		m_min = m_tail->greater;
	}

	else if (m_tail == m_max)
	{
		m_max = m_tail->smaller;
	}

	if (m_tail->smaller != nullptr)
	{
		m_tail->smaller->greater = m_tail->greater;
	}

	if (m_tail->greater != nullptr)
	{
		m_tail->greater->smaller = m_tail->smaller;
	}

	m_tail = m_tail->prev;
	delete m_tail->next;
	m_tail->next = nullptr;
	m_size--;
}

template <typename T>
void FL::F_List<T>::pop_front()
{
	if (m_head == nullptr)
	{
		std::cout << "The list is empty" << std::endl;
		return;
	}

	if (m_head == m_min)
	{
		m_min = m_head->greater;
	}

	else if (m_head == m_max)
	{
		m_max = m_head->smaller;
	}

	if (m_head->smaller != nullptr)
	{
		m_head->smaller->greater = m_head->greater;
		?
	}
	if (m_head->greater != nullptr)
	{
		m_head->greater->smaller = m_head->smaller;
		?
	}
	m_head = m_head->next;
	delete m_head->prev;
	m_head->prev = nullptr;
	m_size--;
}



//helper function

template <typename T>
void FL::F_List<T>::sorted (Node<T>* new_elem)
{
	Node<T>* tmp = m_min;
	while (tmp != nullptr && tmp->data < new_elem->data)
	{
		tmp = tmp->greater;
	}

	if (tmp == nullptr)
	{
		tmp = m_max;
		tmp->greater = new_elem;
		new_elem->smaller = tmp;
	}

	else
	{
		new_elem->smaller = tmp->smaller;
		if (tmp->smaller != nullptr)
		{
			tmp->smaller->greater = new_elem;
			tmp->smaller = new_elem;
			new_elem->greater = tmp;
		}
	}

	if (new_elem->data > = m_max->data)
	{
		m_max = new_elem;
	}
	else if (new_elem->data < = m_min->data)
	{
		m_min = new_elem;
	}
}
