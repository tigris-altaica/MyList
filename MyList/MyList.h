#pragma once

template <typename Type> 
class MyList
{
private:
	struct elem
	{
		Type data;
		elem* prev;
		elem* next;
	};

	elem* first;
	elem* last;

	size_t Size;

	elem* delet(elem* el)
	{
		elem* ret = el->next;

		el->next->prev = el->prev;
		el->prev->next = el->next;
		el->next = nullptr;
		el->prev = nullptr;

		Size--;
		delete el;

		return ret;
	}

public:
	class MyIterator
	{
		friend class MyList;

	private:
		MyIterator(elem* p) : ptr(p) {}
		elem* ptr;

	public:
		MyIterator() {};
		MyIterator(const MyIterator& it) : MyIterator(it.ptr) {}
		MyIterator& operator = (const MyIterator& other)
		{
			ptr = other.ptr;
			return *this;
		}
		bool operator != (MyIterator const other) const
		{
			return (ptr != other.ptr);
		}
		bool operator == (MyIterator const other) const
		{
			return (ptr == other.ptr);
		}
		Type& operator * ()
		{
			return ptr->data;
		}
		MyIterator& operator ++ ()
		{
			ptr = ptr->next;
			return *this;
		}
		MyIterator operator ++ (int)
		{
			MyIterator it(*this);
			++(*this);
			return it;
		}
		MyIterator& operator -- ()
		{
			ptr = ptr->prev;
			return *this;
		}
		MyIterator operator -- (int)
		{
			MyIterator it(*this);
			--(*this);
			return it;
		}
		MyIterator operator + (unsigned int shift)
		{
			MyIterator tmp(*this);
			while (shift--)
				++tmp;
			return tmp;
		}
		MyIterator operator - (unsigned int shift)
		{
			MyIterator tmp(*this);
			while (--shift)
				--tmp;
			return tmp;
		}
		std::ptrdiff_t operator - (const MyIterator it) const
		{
			return std::distance(*this, it);
		}
		bool operator < (const MyIterator& tmp) const
		{
			return (*this - tmp < 0);
		}
		bool operator > (const MyIterator& tmp) const
		{
			return (*this - tmp > 0);
		}
		bool operator <= (const MyIterator& tmp) const
		{
			return (*this - tmp <= 0);
		}
		bool operator >= (const MyIterator& tmp) const
		{
			return (*this - tmp >= 0);
		}
	};

	MyList()
	{
		first = new elem;
		last = new elem;

		first->prev = nullptr;
		first->next = last;
		last->prev = first;
		last->next = nullptr;

		Size = 0;
	}

	MyList(const MyList& list) : MyList()
	{
		MyIterator iter;
		for (iter = list.begin(); iter != list.end(); ++iter)
			push_back(*iter);
	}

	MyList(unsigned int n, Type t) : MyList()
	{
		while (n--)
			push_back(t);
	}

	MyList(MyIterator i, MyIterator j) : MyList()
	{
		while (i != j)
			push_back(*i++);
	}

	MyList(std::initializer_list<Type> il) : MyList(il.begin(), il.end()) {}

	~MyList()
	{
		clear();

		first->next = nullptr;
		last->prev = nullptr;

		delete first;
		delete last;
	}

	void push_front(Type newel)
	{
		push_before(begin(), newel);
	}

	void push_back(Type newel)
	{
		push_before(end(), newel);
	}

	void pop_front()
	{
		MyIterator tmp = begin();
		delet(tmp.ptr);
	}

	void pop_back()
	{
		MyIterator tmp = --end();
		delet(tmp.ptr);
	}

	template <class... Args>
	void emplace_front(Args&&... args)
	{
		emplace(begin(), Type(std::forward<Args>(args)...));
	}

	template <class... Args>
	void emplace_back(Args&&... args)
	{
		emplace(end(), Type(std::forward<Args>(args)...));
	}

	MyIterator emplace(MyIterator p, Type t)
	{
		return insert(p, 1, t);
	}

	template <class... Args>
	MyIterator emplace(MyIterator p, Args&&... args)
	{
		MyIterator ret = MyIterator(p.ptr->prev);
		push_before(p, Type(std::forward<Args>(args)...));
		return ++ret;
	}

	MyIterator insert(MyIterator p, unsigned int n, Type t)
	{
		MyIterator ret = MyIterator(p.ptr->prev);
		while (n--)
			push_before(p, t);
		return ++ret;
	}

	MyIterator insert(MyIterator p, MyIterator i, MyIterator j)
	{
		MyIterator ret = MyIterator(p.ptr->prev);
		while (i != j)
			push_before(p, *i++);
		return ++ret;
	}

	MyIterator insert(std::initializer_list<Type> il)
	{
		return insert(il.begin(), il.end());
	}

	MyIterator erase(MyIterator q)
	{
		return MyIterator(delet(q.ptr));
	}

	MyIterator erase(MyIterator p, MyIterator q)
	{
		while (p != q)
			p = MyIterator(delet(p.ptr));
		return p;
	}

	void clear()
	{
		while (!empty())
			delet(first->next);
	}

	void assign(unsigned int n, Type t)
	{
		clear();
		while (n--)
			push_back(t);
	}

	void assign(MyIterator i, MyIterator j)
	{
		clear();
		while (i != j)
			push_back(*i++);
	}

	void assign(std::initializer_list<Type> il)
	{
		assign(il.begin(), il.end());
	}

	void swap(MyList& that)
	{
		std::swap(first, that.first);
		std::swap(last, that.last);
		std::swap(Size, that.Size);
	}

	bool empty()
	{
		return (Size == 0);
	}

	size_t size()
	{
		return Size;
	}

	MyIterator begin() const
	{
		return MyIterator(first->next);
	}

	MyIterator end() const
	{
		return MyIterator(last);
	}

	Type& front()
	{
		return *(begin());
	}

	Type& back()
	{
		MyIterator tmp(end());
		--tmp;
		return *(tmp);
	}

	bool operator != (MyList const& other)
	{
		return !(*this == other);
	}

	bool operator == (MyList const& other)
	{
		MyIterator it1 = begin(), it2 = other.begin();
		while (*it1 == *it2 && it1 != end())
		{
			++it1;
			++it2;
		}
		return (it1 == end() && it2 == other.end());
	}

	void sort()
	{
		MyIterator iter1, iter2;
		for (iter1 = begin(); iter1 != end(); ++iter1)
		{
			for (iter2 = iter1 + 1; iter2 != end(); ++iter2)
			{
				if (*iter1 > *iter2)
				{
					Type tmp = *iter1;
					*iter1 = *iter2;
					*iter2 = tmp;
				}
			}
		}

	}

private:
	void push_before(MyIterator p, Type newel)
	{
		elem* el = new elem;
		el->data = newel;

		p.ptr->prev->next = el;
		el->prev = p.ptr->prev;
		p.ptr->prev = el;
		el->next = p.ptr;

		Size++;
	}
};