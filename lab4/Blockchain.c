//-----------------------------------------------------------------------------
// Timmy Wang
// tqwang CS12M
// Blockchain.c
// Implementation file for the Blockchain ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Blockchain.h"

#define MAX 100

/* 
 * struct BlockchainObj
 * 
 * Defines struct BlockchainObj as an array of blocks and its size. Defined as BlockchainObj.
 */
typedef struct BlockchainObj {
	Block array[MAX];
	int size;
} BlockchainObj;

/* 
 * BlockchainObj*
 *
 * Defines BlockchainObj* as Blockchain.
 */
typedef BlockchainObj* Blockchain;

/* 
 * newBlockchain
 *
 * Creates a new Blockchain. Array filled with NULL values and size set to 0.
 *
 * Returns an empty block chain.
 *
 * No pre-conditions.
 *
 * No side-effects.
 */
Blockchain newBlockchain() {
	Blockchain B = malloc(sizeof(BlockchainObj));
	assert(B != NULL);
	for(int i=0; i<MAX; i++) {
		B->array[i]=NULL;
	}
	B->size = 0;
	return B;
}

/* 
 * freeBlockchain
 *
 * Frees and deletes the Blockchain and its components.
 *
 * No return values.
 *
 * No pre-conditions.
 *
 * If Blockchain is NULL, prints to stderr.
 */
void freeBlockchain(Blockchain B) {
	if(B == NULL) {
		fprintf(stderr, "NULL Blockchain.\n");
		return;
	}
	for(int i=0; i<B->size; i++) {
		free(B->array[i]);
		B->array[i]=NULL;
	}
	free(B);
}

/* 
 * append
 *
 * Appends the data given to the end of the blockchain.
 *
 * Returns the size of the list, or 0 if it fails.
 *
 * No pre-conditions.
 *
 * If the blockchain or the data is NULL, prints to stderr.
 */
int append(Blockchain B, char* data) {
	if(B == NULL) {
		fprintf(stderr, "NULL Blockchain.\n");
		return 0;
	}
	if(data == NULL) {
		fprintf(stderr, "NULL Data.\n");
		return 0;
	}
	int count = 0;
	while(B->array[count]!=NULL) {
		count++;
	}
	if(count == 0) {
		B->array[count] = newBlock(data, count, 0);
		B->size += 1;
		return B->size;
		
	}
	B->array[count] = newBlock(data, count, hash(B->array[count-1]));
	B->size += 1;
	return B->size;
}

/*
 * size
 *
 * Returns size of Blockchain.
 *
 * No pre-conditions.
 *
 * IF blockchain is NULL, print to stderr.
 */
int size(Blockchain B) {
	if( B==NULL) {
		fprintf(stderr, "NULL Blockchain.\n");
		return 0;
	}
	return B->size;
}

/*
 * get
 *
 * Gets the block at index given in blockchain.
 *
 * Returns block gotten at index in blockchain.
 * If blockchain is null or index is out of scope, then return a 0, 0, 0 block isntead.
 *
 * idx must be within the scope of the array.
 *
 * If blockchain is null or idx is out of scope, prints to stderr.
 */
Block get(Blockchain B, int idx) {
	if( B==NULL) {
		fprintf(stderr, "NULL Blockchain.\n");
		return newBlock("0", 0, 0);
	}
	if(idx<0|| idx>=100) {
		fprintf(stderr, "Index out of bounds.\n");
		return newBlock("0", 0, 0);
	}
	return B->array[idx];
}

/*
 * valid
 *
 * Checks if the blockchain is valid.
 *
 * Returns 1 if valid, 0 if not
 *
 * No pre-conditions.
 *
 * If blockchain is NULL, prints to stderr.
 */
int valid(Blockchain B) {
	if( B==NULL) {
		fprintf(stderr, "NULL Blockchain.\n");
		return 0;
	}
	int count = 0;
	while(B->array[count]!=NULL) {
		if(B->array[count+1] == NULL) {
			break;
		}
		if(previousHash(B->array[count+1])!=hash(B->array[count])) {
			return 0;
		}
		count++;
	}
	return 1;
}

/*
 * removeLast
 *
 * Removes the last element in the blockchain.
 *
 * No returns.
 *
 * No pre-conditions.
 *
 * If blockchain is null, print to stderr.
 */
void removeLast(Blockchain B) {
	if( B== NULL) {
		fprintf(stderr, "NULL Blockchain.\n");
		return;
	}
	int count = 0;
	while(B->array[count]!=NULL) {
		count++;
	}
	if(count>0) {
		free(B->array[count-1]);
		B->array[count-1] = NULL;
		B->size -= 1;
	}
}

/*
 * printBlockchain
 *
 * Prints blockchain to given output file in the style of:
 * id:data
 *
 * No returns.
 *
 * No preconditions.
 *
 * If blockchain or output file is null, print to stderr.
 */
void printBlockchain(FILE* out, Blockchain B) {
	if( B== NULL) {
		fprintf(stderr, "NULL Block.\n");
		return;
	}
	if( out == NULL) {
		fprintf(stderr, "No output file.\n");
		return;
	}
	int count = 0;
	while(B->array[count]!=NULL) {
		fprintf(out, "%d:%s\n", count, data(B->array[count]));
		count++;
	}
}
