#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"
/*
 * Timmy Wang
 * tqwang CS12M
 * Stack.c
 * Makes a stack with all the expected stack functions.
 */


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
StackObj *
newStack() {
    StackObj *S;

    S = (StackObj *) malloc ((size_t) sizeof(StackObj));
    S->top = -1;	//nothing in the stack
    return S;
}

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
void
printStack (StackObj *S) {
    int i;

    printf("goign to print stack contents %d element \n", S->top +1);
    for (i=0; i<= S->top; i++) {
	printf("stack index %d = %p\n", i, S->items[i]);

    }
}

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
void
deleteStack(StackObj * S) {
   S->top = -1;		// being neurotic
   free(S);
}

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
int
stackSize( StackObj * S) {

    return (S->top + 1);

}

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
void
*pop(StackObj *S){
    if (S->top < 0 ) {  // out of stack items
        //printf("returning nothing, stack empty\n");
        return NULL;
    }
    else {
        //printf("pop returning node");
	return (S->items[S->top--]);
    }
}

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
void
push(StackObj *S,  void *ref){

    //printf("pushing token ");
    if (S->top <  MAX_STACK - 1) {  // out of stack items
	S->items[++(S->top)] = ref;
    }
    else {
	fprintf(stderr, "sorry out of stack space\n");
    }

}

