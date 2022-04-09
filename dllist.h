#ifndef CS20A_DLLIST_H
#define CS20A_DLLIST_H

#include <iostream>
#include <assert.h>
// Linked DLList object that maintains both head and tail pointers
// and the count of the list.  Note that you have to keep the head,
// tail and count consistent with the intended state of the DLList
// otherwise very bad things happen.
template <typename Type>
class DLList
{
public:
	DLList();

	DLList(const DLList<Type> &other);

	DLList<Type> &operator=(const DLList<Type> &other);

	~DLList();

	void print() const;
	bool empty() const;

	void insert_front(const Type &value);
	void insert_rear(const Type &value);
	void insert(int idx, const Type &value);

	// Note that the user must first ensure the list is not empty
	// prior to calling these functions.
	Type front() const;
	Type rear() const;
	Type get(int idx) const;

	int size() const;
	int find(const Type &value) const;

	bool remove_front();
	bool remove_rear();
	bool remove(int idx);
	int remove_value(const Type &value);

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif
	// Forward declare the nodes for our DLList.
	// Will be implemented along with list
	// member functions
	struct Node;

	// We'll have both head and tail points for
	// Fast insertion/deletion from both ends.
	Node *head;
	Node *tail;

	// Keep track of number of nodes in the list
	int count;
};

/* DLList Implementation
//
//  Since DLList is a template class (which is not an actual
//  class yet, not until we actually instantiate the list)
//  we need to keep the implementation together with
//  the definition.  There are ways to simulate having
//  separate "implementation/definition" with templates,
//  but they aren't necessary and can be confusing.
*/

/* Node definition
//		Already implemented, nothing to do here but to use it.
*/
template <typename Type>
struct DLList<Type>::Node
{
	Node() : next(nullptr), prev(nullptr) {}
	Node(Type it, Node *p, Node *n) : value(it), next(n), prev(p) {}

	Type value;
	Node *next;
	Node *prev;
};

/* DLList default constructor
//		Set head and tail pointer to point to nothing, count is zero
//		Already implemented, nothing to do.
*/
template <typename Type>
DLList<Type>::DLList() : head(nullptr), tail(nullptr), count(0)
{
	/*  DONE  */
}

/* Copy constructor
 */
template <typename Type>
DLList<Type>::DLList(const DLList<Type> &other)
{

	count = 0;

	head = nullptr;
	tail = nullptr;

	int i = 0;
	Node *n = other.n_head;

	while (n != nullptr)
	{
		insert(i, n->value);
		n = n->next;
		i++;
	}
}
/* Overloaded assignment operator
 */
template <typename Type>
DLList<Type> &DLList<Type>::operator=(const DLList<Type> &other)
{

	if (this == &other)
		return *this;
	else
	{
		count = 0;

		while (head != nullptr)
		{
			Node *p = head;
			head = p->next;
			delete p;
		}

		head = nullptr;
		tail = nullptr;

		int i = 0;
		Node *n = other.n_head;

		while (n != nullptr)
		{
			insert(i, n->value);
			n = n->next;
			i++;
		}
	}

	return *this;
}

/* DLList destructor
 */
template <typename Type>
DLList<Type>::~DLList()
{

	while (head != nullptr)
	{
		Node *s = head->next;
		delete head;
		head = s;
	}
	tail = nullptr;
}

/* DLList print
 */
template <typename Type>
void DLList<Type>::print() const
{

	if (head == nullptr)
		return;
	else
	{
		Node *pr;
		pr = head;
		while (pr != nullptr)
		{
			std::cout << pr->value << " ";
			pr = pr->next;
		}
	}
	std::cout << "\n";
}

/* DLList empty
 */
template <typename Type>
bool DLList<Type>::empty() const
{

	if (head == nullptr)
	{
		return true;
	}

	return false;
}

/* DLList insert_front
 */
template <typename Type>
void DLList<Type>::insert_front(const Type &value)
{

	if (head == nullptr)
	{
		head = new Node;
		tail = new Node;
		head->value = value;
		head->prev = nullptr;
		head->next = nullptr;
		tail = head;
	}

	else
	{
		Node *k = new Node;
		k->next = head;
		k->prev = nullptr;
		k->value = value;
		head->prev = k;
		head = k;
	}

	count += 1;
}

/* DLList insert_rear
 */
template <typename Type>
void DLList<Type>::insert_rear(const Type &value)
{

	if (count == 0)
	{
		insert_front(value);
	}
	else
	{
		Node *b = new Node;
		tail->next = b;
		b->next = nullptr;
		b->prev = tail;
		b->value = value;
		tail = b;

		count += 1;
	}
}

/* DLList insert
 */
template <typename Type>
void DLList<Type>::insert(int idx, const Type &value)
{

	if (idx <= 0)
	{
		insert_front(value);
	}
	else if (idx >= count)
	{
		insert_rear(value);
	}
	else
	{
		int i = 0;
		Node *p = head;

		while (i < idx)
		{
			p = p->next;
			i += 1;
		}
		Node *k = new Node(value);
		if (p->next != nullptr)
		{
			k->next = p->next;
			p->next->prev = k;
			p->next = k;
			k->prev = p;
		}
		else
		{
			p->next = k;
			k->prev = p;
			tail = k;
		}
		count += 1;
	}
}

/*  DLList front
 */
template <typename Type>
Type DLList<Type>::front() const
{

	// This should never be tripped, this is just here to let
	// you know that you messed up with your usage, this function
	// is never called on an empty list.
	assert(head != nullptr);

	Type returnValue = head->value;
	return returnValue;
}

/* DLList rear
 */
template <typename Type>
Type DLList<Type>::rear() const
{

	// This should never be tripped, this is just here to let
	// you know that you messed up with your usage, this function
	// is never called on an empty list.
	assert(tail != nullptr);

	Type returnValue = tail->value;
	return returnValue;
}

/* DLList get
 */
template <typename Type>
Type DLList<Type>::get(int idx) const
{

	// Assert that index is correct before getting the Item
	assert(idx >= 0 && idx < count);

	int i = 0;
	Node *p;
	p = head;
	while (p->next != nullptr)
	{
		i += 1;
		if (i == idx)
		{
			return p->value;
		}
		p = p->next;
	}
}

/* DLList size
 */
template <typename Type>
int DLList<Type>::size() const
{

	return count;
}

/* DLList find
 */
template <typename Type>
int DLList<Type>::find(const Type &value) const
{

	int idx = 0;
	Node *p;
	p = head;
	while (p->next != nullptr)
	{
		idx++;
		if (p->value == value)
		{
			return idx;
		}
		p = p->next;
	}

	return -2;
}

/* DLList remove_front
 */
template <typename Type>
bool DLList<Type>::remove_front()
{

	if (head == nullptr)
		return false;
	else
	{
		Node *s = head;
		head = s->next;
		head->prev = nullptr;
		count--;
		delete s;
		if (count == 0)
		{
			tail = nullptr;
		}
		return true;
	}
}
/* DLList remove_rear
 */
template <typename Type>
bool DLList<Type>::remove_rear()
{

	if (tail != nullptr)
	{
		if (tail->prev != nullptr)
		{
			Node *s = tail;
			tail = s->prev;
			tail->next = nullptr;
			count--;
			delete s;
		}
		else
		{
			Node *s = tail;
			tail = nullptr;
			head = nullptr;
			count--;
			delete s;
		}

		return true;
	}

	return false;
}

/* DLList remove on index
 */
template <typename Type>
bool DLList<Type>::remove(int idx)
{

	if (idx == 0)
	{
		remove_front();
	}
	else if (idx == count)
	{
		remove_rear();
	}
	else
	{
		int i = 0;
		Node *p = head;
		while (p->next != nullptr)
		{
			i++;
			if (i == (idx - 1))
				break;
			p = p->next;
		}
		if (p != nullptr)
		{
			Node *s = p->next;
			p->next = s->next;
			delete s;
			return true;
		}
	}

	return false;
}

/* DLList remove_value on value
 */
template <typename Type>
int DLList<Type>::remove_value(const Type &value)
{

	int idx = 0;
	Node *p = head;
	while (p != nullptr)
	{
		if (p->value == value)
		{
			return idx;
		}
		p = p->next;
		idx++;
	}

	return -2;
}

#endif

// _X_XMXXXI