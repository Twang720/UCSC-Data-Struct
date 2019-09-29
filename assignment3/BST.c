/*
 * Timmy Wang
 * tqwang CS12B
 * BST.c
 * Lists function for a binary search tree.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "BST.h"

/*
 * insert
 *
 * Creates a new node and puts it into the binary search tree.
 *
 * No return values.
 *
 * No pre-conditions.
 *
 * If either the data or the pointer to the tree is null, prints to stderr.
 */
void insert(char *new_data,  BSTObj **pBST) {
	if(pBST == NULL || new_data == NULL) {
		fprintf(stderr, "NULL pointer detected.\n");
		return;
	}
	if(*pBST == NULL) {
		BSTObj *new = malloc(sizeof(BSTObj));
		assert(new!=NULL);
		new->term = new_data;
		new->leftChild = NULL;
		new->rightChild = NULL;
		*pBST = new;
		return;
	}
	if(strcmp(new_data, (*pBST)->term) < 0) {
		insert(new_data, &((*pBST)->leftChild));
	}
	else {
		insert(new_data, &((*pBST)->rightChild));
	}
	return;
}

/*
 * inorderTraverse
 *
 * Prints a tree to the output file using inorder. If tree is empty, prints nothing.
 *
 * No return values.
 *
 * Output file should exist.
 *
 * If output file doesn't exist, prints to stderr.
 */
void inorderTraverse(FILE *out, BSTObj *T) {
	if(out == NULL) {
		fprintf(stderr, "No output file\n");
		return;
	}
	if(T == NULL) {
		return;
	}
	if(T->leftChild == NULL && T->rightChild == NULL) {
		fprintf(out, "%s\n", T->term);
		return;
	}
	else {
		inorderTraverse(out, T->leftChild);
		fprintf(out, "%s\n", T->term);
		inorderTraverse(out, T->rightChild);
		return;
	}
}

/*
 * preorderTraverse
 *
 * Prints a tree to the output file using preorder. If tree is empty, prints nothing.
 *
 * No return values.
 *
 * Output file should exist.
 *
 * If output file doesn't exist, prints to stderr.
 */
void preorderTraverse(FILE *out, BSTObj *T) {
	if(out == NULL) {
		fprintf(stderr, "No output file\n");
		return;
	}
	if(T == NULL) {
		return;
	}
	if(T->leftChild == NULL && T->rightChild == NULL) {
		fprintf(out, "%s\n", T->term);
		return;
	}
	else {
		fprintf(out, "%s\n", T->term);
		preorderTraverse(out, T->leftChild);
		preorderTraverse(out, T->rightChild);
		return;
	}
}

/*
 * postorderTraverse
 *
 * Prints a tree to the output file using postorder. If tree is empty, prints nothing.
 *
 * No return values.
 *
 * Output file should exist.
 *
 * If output file doesn't exist, prints to stderr.
 */
void postorderTraverse(FILE *out, BSTObj *T) {
	if(out == NULL) {
		fprintf(stderr, "No output file\n");
		return;
	}
	if(T == NULL) {
		return;
	}
	if(T->leftChild == NULL && T->rightChild == NULL) {
		fprintf(out, "%s\n", T->term);
		return;
	}
	else {
		postorderTraverse(out, T->leftChild);
		postorderTraverse(out, T->rightChild);
		fprintf(out, "%s\n", T->term);
		return;
	}
}

/*
 * inorderLeaves
 *
 * Prints a tree's leaves to the output file using inorder. If tree is empty, prints nothing.
 *
 * No return values.
 *
 * Output file should exist.
 *
 * If output file doesn't exist, prints to stderr.
 */
void inorderLeaves(FILE *out, BSTObj *T) {
	if(out == NULL) {
		fprintf(stderr, "No output file\n");
		return;
	}
	if(T == NULL) {
		return;
	}
	if(T->leftChild == NULL && T->rightChild == NULL) {
		fprintf(out, "%s\n", T->term);
		return;
	}
	else {
		inorderLeaves(out, T->leftChild);
		inorderLeaves(out, T->rightChild);
		return;
	}

}

/*
 * find
 *
 * Finds the given term in the binary search tree and, if it exists, returns 1. If term does not exist, returns 0.
 *
 * Returns 1 if term exists, 0 if it doesn't
 *
 * Term to find should exist.
 *
 * If term to find doesn't exist, prints to stderr.
 */
int find(char *term_to_find, BSTObj *T) {
	if(term_to_find == NULL) {
		fprintf(stderr, "NULL term.\n");
		return FALSE;
	}
	if(T == NULL) {
		return FALSE;
	}
	if(strcmp(T->term, term_to_find) == 0) {
		return TRUE;
	}
	else if(strcmp(term_to_find, T->term) < 0) {
		return find(term_to_find, T->leftChild);
	}
	else {
		return find(term_to_find, T->rightChild);
	}	
}

/*
 * treeHeight
 *
 * Computes and returns the tree height of the given tree.
 *
 * Returns the tree height.
 *
 * Height should be >= 0
 *
 * If height < 0, prints to stderr.
 */
int treeHeight(BSTObj *T, int height) {
	if(height < 0) {
		fprintf(stderr, "Height should not be less than 0\n");
		return -1;
	}
	if(T == NULL) {
		return height;
	}
	height = height + 1;
	int h1 = treeHeight(T->leftChild, height);
	int h2 = treeHeight(T->rightChild, height);
	if(h1 > h2) {
		return h1;
	}
	return h2;
}

/*
 * copyTree
 *
 * Copies the given tree and puts it into a new, memory independent, tree.
 *
 * Returns the head of the copied tree.
 *
 * No pre-conditions.
 *
 * No side effects.
 */
BSTObj *copyTree(BSTObj *T) {
	if(T == NULL) {
		return NULL;
	}
	BSTObj *tree = malloc(sizeof(BSTObj));
	assert(tree != NULL);
	tree->term = T->term;
	tree->leftChild = copyTree(T->leftChild);
	tree->rightChild = copyTree(T->rightChild);
	return tree;
}

/*
 * makeEmpty
 *
 * Frees and removes all nodes of the tree, and sets the tree to NULL.
 *
 * No return values.
 *
 * No pre-conditions
 *
 * If pointer to tree is null, prints to stderr.
 */
void makeEmpty(BSTObj **pT) {
	if(pT == NULL) {
		fprintf(stderr, "NULL pointer detected.\n");
		return;
	}
	if(*pT == NULL) {
		return;
	}
	if((*pT)->leftChild == NULL && (*pT)->rightChild == NULL) {
		free(*pT);
		(*pT)->term = NULL;
		*pT = NULL;
		return;
	}
	else {
		makeEmpty(&((*pT)->leftChild));
		makeEmpty(&((*pT)->rightChild));
		free(*pT);
		(*pT)->term = NULL;
		*pT = NULL;
		pT = NULL;
		return;
	}
}
