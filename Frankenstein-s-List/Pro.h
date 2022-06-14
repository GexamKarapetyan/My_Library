#ifndef _PRO_
#define _PRO_
#include <iostream>
#include <exception>

namespace FL
{
	template <typename T>
	class Node
	{
	public:
		T data{};
		Node* next{};
		Node* prev{};
		Node* smaller{};
		Node* greater{};

		Node() = default;
		Node(const T& d,Node* n=nullptr,Node* p=nullptr,
		Node* s=nullptr,Node* g=nullptr):data(d),next(n),prev(p),smaller(s),greater(g){}
	};

	template <typename T>
	class F_List
	{
		F_List() = default;
		F_List(const T& elem);
		~F_List();
		int size() const;
		void push_back(const T& elem);
		void push_front(const T& elem);
		void insert(const T&, int);
		void pop_back();
		void pop_front();
		void sorted(Node*);//helper functions
	private:
		Node* m_head{};
		Node* m_tail{};
		Node* m_min{};
		Node* m_max{};
		int m_size{};
	};

}
#include "Impl.hpp"
#endif //_PRO_
