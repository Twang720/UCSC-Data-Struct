
//-----------------------------------------------------------------------------
// Timmy Wang
// tqwang CS12M
// Stack.h
// Header file for the Stack ADT
// Array implmentation with stack size limitation
// Array of points to arbitrary structures, users will have to cast the pointer
// to set pointer type and keep track of their own logical use of pointers
//
//-----------------------------------------------------------------------------

#ifndef _STACK_H_INCLUDE_
#define _STACK_H_INCLUDE_

#define MAX_STACK 100

typedef struct StackObj {
    void *items[MAX_STACK];
    int	 top;
} StackObj;

/*
 * newStack
 *
 * Allocates space for a new stack object
 *
 * Returns the created stack object
 *
 * No preconditions
 *
 * No side effects
 */
StackObj 	*newStack();

/*
 * deletestack
 *
 * Frees and empties stack
 *
 * No return values
 *
 * Stack shouldn't be null, no null check
 *
 * No side effects
 */
void 		deleteStack(StackObj * S);

/*
 * stackSize
 *
 * Returns the size of the stack
 *
 * Returns size of stack
 *
 * Stack shouldn't be null, no null check
 *
 * No side effects
 */
int 		stackSize( StackObj * S);

/*
 * pop
 *
 * Pops the top element from the stack, and reduces size by 1.
 *
 * Returns node popped
 *
 * Stack shouldn't be null, no null check
 *
 * Returns null if stack is empty
 */
void 		*pop(StackObj *S);

/*
 * push
 *
 * Pushes an element on top of stack, and increases size by 1
 *
 * No return values
 *
 * Parameters shouldn't be null, no null check
 *
 * If no space to push onto stack, prints to stderr.
 */
void 		push(StackObj *S,  void *ref);

/*
 * printStack
 *
 * Prints stack to stdout
 *
 * No return values
 *
 * Stack shouldn't be null, no null check
 *
 * No side effects
 */
void		printStack(StackObj *S);
#endif

