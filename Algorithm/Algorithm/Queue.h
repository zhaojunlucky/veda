#pragma once

#include "DataTypes.h"
#include "Array.h"
namespace veda
{
	template <class DT>
	class Queue
	{
	public:
		typedef typename size_t size_type;
		typedef typename DT value_type;

		virtual void enqueue(value_type&) = 0;
		virtual void enqueue(value_type&&) = 0;
		virtual value_type dequeue() = 0;
		virtual size_type getSize() const = 0;
		virtual bool isEmpty() const = 0;
	};


	template <class DT>
	class LinkListQueue : public Queue < DT >
	{
	public:
		typedef typename DT value_type;
		typedef Node<DT>* NodePtr;
		LinkListQueue()
		{
			size = 0;
			head = new Node<DT>();
			tail = new Node<DT>();
			head->next = tail->next = nullptr;
		}
		~LinkListQueue()
		{
			destory();
		}
		virtual void enqueue(value_type& v)
		{
			value_type vt = v;
			enqueue(std::move(vt));
		}
		virtual void enqueue(value_type&& v)
		{
			NodePtr n = new Node<DT>();
			n->data = v;
			n->next = tail->next;
			tail->next = n;
			if (isEmpty())
			{
				head->next = n;
			}
			++size;
		}
		virtual value_type dequeue()
		{
			if (isEmpty())
			{
				throw "queue is empty";
			}

			NodePtr n = head->next;
			head->next = n->next;
			if (size == 1)
			{
				tail->next = nullptr;
			}
			value_type v = n->data;
			delete n;
			--size;
			return std::move(v);
		}
		virtual size_type getSize() const
		{
			return size;
		}
		virtual bool isEmpty() const
		{
			return size == 0;
		}
	protected:
		void destory()
		{
			if (!isEmpty())
			{
				NodePtr n = head->next;
				NodePtr m;
				while (n != nullptr)
				{
					m = n;
					n = n->next;
					delete m;
				}
			}
			delete head;
			delete tail;
		}
	private:
		size_type size;
		NodePtr head;
		NodePtr tail;
	};


	template <class DT>
	class ArrayQueue : public Queue < DT >
	{
	public:
		typedef typename DT value_type;
		typedef typename size_t size_type;
		typedef Array<DT>* ArrQuPtr;
		ArrayQueue(size_type init_size)
		{
			arr = new Array<value_type>(init_size);
			head = tail = 0;
		}
		~ArrayQueue()
		{
			delete arr;
		}
		virtual void enqueue(value_type& v)
		{
			value_type vt = v;
			enqueue(std::move(vt));
		}
		virtual void enqueue(value_type&& v)
		{
			if (isFull())
			{
				adjust(getCapacity() * 2);
			}
			
			arr->at(tail) = v;
			tail = (tail + 1) % getCapacity();
			++size;
		}
		virtual value_type dequeue()
		{
			if (isEmpty())
			{
				throw "queue is empty";
			}
			
			value_type v = arr->at(head);
			head = (head + 1) % getCapacity();
			--size;

			if (size <= getCapacity() / 4 && getCapacity() > 256)
			{
				adjust(getCapacity() / 2);
			}
			
			return std::move(v);
		}
		virtual size_type getSize() const
		{
			return size;
		}
		virtual bool isEmpty() const
		{
			return size == 0;
		}

		size_type getCapacity() const
		{
			return arr->length();
		}

		bool isFull() const
		{
			return size >= getCapacity();
		}
	protected:

		void adjust(size_type capacity)
		{
			ArrQuPtr other = new Array<value_type>(capacity);
			for (size_type i = 0; i < size; i++)
			{
				other->at(i) = std::move(arr->at((head + i) % getCapacity()));
			}
			delete arr;
			arr = other;
			head = 0;
			tail = size;
		}

	private:
		size_type size;
		ArrQuPtr arr;
		size_type head;
		size_type tail;
	};
}