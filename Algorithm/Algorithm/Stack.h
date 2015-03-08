#pragma once
#include <memory>
#include "DataTypes.h"
#include "Vector.h"

namespace veda
{
	template<class T>
	class Stack
	{
	public:
		typedef typename T value_type;
		typedef typename size_t size_type;

		void push(value_type&) = 0;
		void push(value_type&&) = 0;
		value_type pop() = 0;
		size_type getSize() const = 0;
		bool isEmpty() const = 0;
	};

	template <class T>
	class LinkListStack : public Stack < T >
	{
	public:
		typedef Stack<T> _Stack;
		typedef typename _Stack::size_type size_type;
		typedef typename _Stack::value_type value_type;
		typedef Node<T>* NodePtr;
		LinkListStack()
		{
			size = 0;
			ptr = new Node < T > ;
			ptr->next = nullptr;
		}
		~LinkListStack()
		{
			destory();
		}
		void push(value_type&v)
		{
			value_type vv = v;
			push(std::move(vv));
		}
		void push(value_type&&v)
		{
			NodePtr n = new Node < T > ;
			n->data = v;
			n->next = ptr->next;
			ptr->next = n;
			++size;
		}
		value_type pop()
		{
			if (isEmpty())
			{
				throw "stack is empty.";
			}
			NodePtr cur = ptr->next;
			value_type v = cur.data;

			ptr->next = cur->next;
			delete cur;
			--size;
			return std::move(v);
		}
		size_type getSize() const
		{
			return size;
		}

		bool isEmpty() const
		{
			return size == 0;
		}
	protected:
		void destory()
		{
			NodePtr p = ptr->next;
			NodePtr q;
			while (p != nullptr)
			{
				q = p;
				p = p->next;
				delete q;
			}
			delete ptr;
		}
	private:
		size_type size;
		NodePtr ptr;
	};

	template <class T>
	class ArrayStack : public Stack < T >
	{
	public:
		typedef Stack<T> _Stack;
		typedef typename _Stack::size_type size_type;
		typedef typename _Stack::value_type value_type;


		void push(value_type&v)
		{
			value_type vv = v;
			push(std::move(vv));
		}
		void push(value_type&&v)
		{
			data.add(v);
		}
		value_type pop()
		{
			if (isEmpty())
			{
				throw L"stack is empty.";
			}
			value_type v = data[data.getLength()-1];
			data.removeAt(data.getLength() - 1);
			return std::move(v);
		}
		size_type getSize() const
		{
			return data.getLength();
		}

		bool isEmpty() const
		{
			return data.getLength() == 0;
		}

	private:
		Vector<T> data;
	};
}