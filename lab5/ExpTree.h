//-----------------------------------------------------------------------------
// Timmy Wang
// tqwang CS12M
// ExpTree.h
// Header file for the ExpTree ADT
// NINA COMMENTS
//-----------------------------------------------------------------------------

#ifndef _EXPTREE_H_INCLUDE_
#define _EXPTREE_H_INCLUDE_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Stack.h"


#define MAX_INPUT_STR 80
#define MAX_TOKEN_LENGTH 80
#define MAX_OPERATOR_LENGTH 1
typedef enum {PLUS, MINUS, MUL, DIV, OPERAND, END} tokenType;
    
typedef StackObj ExpT;

typedef struct TNode{
    tokenType type;
    int value;
    struct TNode *leftOperand;
    struct TNode *rightOperand;
} TNode;


/*
 * expressionEval
 *
 * Evaluates the expression tree.
 *
 * Returns the total value of the expression tree.
 *
 * Tree should be a complete tree, and not empty.
 *
 * If tree is empty, prints to stderr.
 */
int expressionEval( TNode *T);

/*
 * inorderTraverse
 *
 * Traverses the tree inorder
 *
 * No return values
 *
 * No preconditions
 *
 * If output file is null, print to stderr
 */
void inorderTraverse(FILE *out, TNode  *T);

/*
 * outputExpressionTree
 *
 * Pops all nodes from the stack into the tree, prints out the expression, and returns the total.
 *
 * No return values.
 *
 * No pre-conditions
 *
 * If there are too many operands or operators, prints to stderr
 */
void outputExpressionTree(ExpT *T);

/*
 * inputExpressionTree
 *
 * Scans user inputs for operators and operands, and puts them onto a stack.
 *
 * No return values
 *
 * No pre-conditions
 *
 * If there are too many operators or operands, print to stderr.
 */
void inputExpressionTree(ExpT *T);

/*
 * deleteExpressionTree
 *
 * Deletes the entire expression tree
 *
 * No return values
 *
 * No preconditions
 *
 * No side effects
 */
void deleteExpressionTree(ExpT *T);

/*
 * newExpressionTree
 *
 * Allocates space for a new Expression Tree
 *
 * Returns the created expression tree
 *
 * No pre-conditons
 *
 * No side effects
 */
ExpT *newExpressionTree();
#endif

