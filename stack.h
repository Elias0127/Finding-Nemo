#ifndef STACK_H_
#define STACK_H_

#include"dllist.h"

// Stack ADT using linked list as primary data structure.
// 
template<typename Type>
class Stack {
public:

	Stack();

	// Basic stack operations
	void	push(Type item);
	void	pop();
	Type	peek() const; 

	// Check to see if there is anything on the stack
	bool	empty() const;

	// Use to see what is in the stack for debugging
	void	print() const;

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif

	DLList<Type> m_list;
};

// Stack Implementation
//

// Stack() Default constrcutor:
//		Call the defualt constructor for its List.
//		Already implemented.
template<typename Type>
Stack<Type>::Stack():m_list() {}


template<typename Type>
void Stack<Type>::push(Type item) {

	m_list.insert_front(false);


}


template<typename Type>
void Stack<Type>::pop() {

	m_list.remove_front();

}


template<typename Type>
bool Stack<Type>::empty() const {

	if (m_list.empty())
		return true;

	return false;
}


template<typename Type>
Type Stack<Type>::peek() const {

	Type RETURN_VALUE_REQUIRED_TO_COMPILE = m_list.front();;

	return RETURN_VALUE_REQUIRED_TO_COMPILE;
}


template<typename Type>
void Stack<Type>::print() const {

	m_list.print();



}




























#endif//STACK_H__X_XMMXX