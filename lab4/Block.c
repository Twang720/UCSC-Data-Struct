
//-----------------------------------------------------------------------------
// Timmy Wang
// tqwang CS12M
// Block.C
// Implementation file for the Block ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Block.h"

/*
 * struct BlockObj
 *
 * Defines struct BlockObj with components data, id, and previous hash as BlockObj.
 */
typedef struct BlockObj {
	char *data;
	int id;
	long prevhash;
} BlockObj;

/*
 * BlockObj*
 *
 * Defines BlockObj* as Block.
 */
typedef BlockObj* Block;

/*
 * newBlock
 *
 * Creates a new block with data, id, and the previous block's hash.
 * If data is NULL, replaces it with an empty string.
 *
 * Returns the newly made block.
 *
 * Hash is presumed to be of previous block's hash.
 *
 * No side effects.
 */
Block newBlock(char* data, int id, long hash){
	Block B = malloc(sizeof(BlockObj));
	assert(B != NULL);
	if(data == NULL) 
		B->data = "";
	else
		B->data = data;
	B->id = id;
	B->prevhash = hash;
	return B;
}

/*
 * freeBlock
 *
 * Frees and deletes all components of the block.
 *
 * No returns.
 *
 * No pre-conditions.
 *
 * If block is null, print to stderr.
 */
void freeBlock(Block B) {
	if(B == NULL) {
		fprintf(stderr, "Cannot free NULL block.\n");
		return;
	}
	free(B->data);
	B->data = NULL;
	free(B);
}

/*
 * data
 *
 * Returns data of block
 *
 * Returns data of block.
 *
 * No pre-condition.
 *
 * If block is NULL, print to stderr.
 */
char* data(Block B) {
	char *data = NULL;
	if(B == NULL) {
		fprintf(stderr, "NULL Block.\n");
		return data;
	}
	data = B->data;
	return data;
}

/*
 * previousHash
 *
 * Returns stored value of previous hash in block.
 *
 * Returns previous hash.
 *
 * No preconditions.
 *
 * If block is null, prints to stderr.
 */
long previousHash(Block B) {
	long prevhash = 0;
	if(B == NULL) {
		fprintf(stderr, "NULL Block.\n");
		return prevhash;
	}
	prevhash = B->prevhash;
	return prevhash;
}

/*
 * hash
 *
 * Computes the current block's hash by summing its components.
 * The sum of every char value in data, its id, and the previous block's hash.
 *
 * Returns current block's hash.
 *
 * No pre-conditions.
 *
 * If block is null, prints to stderr.
 */
long hash(Block B) {
	long hash = 0;
	if(B == NULL) {
		fprintf(stderr, "NULL Block.\n");
		return hash;
	}
	int len = strlen(B->data);
	char *d = B->data;
	for(int i = 0; i<len; i++) {
		hash += *d;
		d++;
	}
	hash += B->id + B->prevhash;
	return hash;
}

/*
 * printBlock
 *
 * Prints the block to output file given in the form:
 * id:data
 *
 * No returns.
 *
 * No preconditions.
 *
 * If block or output file is null, prints to stderr.
 */
void printBlock(FILE* out, Block B) {
	if(B == NULL) {
		fprintf(stderr, "NULL Block.\n");
		return;
	}
	if(out == NULL) {
		fprintf(stderr, "No output file.\n");
		return;
	}
	fprintf(out, "%d:%s\n", B->id, B->data);
}
