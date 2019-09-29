/*
 * Timmy Wang
 * tqwang CS12B
 * Dictionary.c
 * Functions for a hash table, 
 */
#include "Dictionary.h"

/*
 * rotate_left
 *
 * rotates the bits into an unsigned int
 *
 * returns the created unsigned int
 *
 * no preconditions
 *
 * no side effects
 */
unsigned int rotate_left(unsigned int value, int shift) {
        int sizeInBits = 8*sizeof(unsigned int);
        shift = shift & (sizeInBits - 1);
        if ( shift == 0 )
                return value;
        return (value << shift) | (value >> (sizeInBits - shift));
}

/*
 * pre_hash
 *
 * turns a string into an unsigned int
 *
 * returns the created unsigned int
 *
 * no preconditions
 *
 * no side effects
 */
unsigned int pre_hash(char* input) {
        unsigned int result = 0xBAE86554;
        while (*input) {
                result ^= *input++;
                result = rotate_left(result, 5);
        }
        return result;
}

/* hash()
 *
 * turns a string into an int in the range 0 to tableSize-1
 *
 * returns the newly hashed key
 *
 * no preconditions
 *
 * no side effects
 */
int hash(char* key, int tableSize){
        return pre_hash(key)%tableSize;
}

/*
 * newHashTable
 *
 * creates a new hash table object with size size and bucket array of size size.
 *
 * returns newly allocated hash table object
 *
 * size must be positive
 *
 * if size is negative, prints to stderr and exits with a failure
 */
HashTableObj *newHashTable(int size) {
	if(size < 0) {
		fprintf(stderr, "size can't be 0\n");
		exit(EXIT_FAILURE);
	}
	HashTableObj *H = (HashTableObj *) malloc(sizeof(HashTableObj) + sizeof(bucketListObj) * size);
//	HashTableObj *H = (HashTableObj *) malloc(sizeof(H->size) + sizeof(bucketList)*size);	
	H->size = size;
	for(int i=0; i<size; i++) {
		H->bucket[i] = NULL;
	}
	return H;
}

/*
 * deleteHashTable
 *
 * deletes the hash table and all its contents
 *
 * no returns
 *
 * no precondition
 *
 * if hash table parameter is null, print to stderr
 */
void deleteHashTable(HashTableObj * H) {
	if(H == NULL) {
		fprintf(stderr, "NULL pointer detected.\n");
		return;
	}
	int count = 0;
	while(count<H->size) {
		bucketList temp = H->bucket[count];
		while(temp!=NULL) {
			bucketList temp2 = temp->next;
			free(temp);
			temp = temp2;
		}
		count++;
	}
	H->size = 0;
	free(H);
	return;
}

/*
 * member
 *
 * determines if string str is stored in the hast table
 *
 * returns true if it is, false if not
 *
 * no pre conditions
 *
 * prints to stderr if hash table or string is null
 */
bool member(HashTableObj *H, char *str) {
	if(H==NULL || str == NULL) {
		fprintf(stderr, "NULL pointer detected.\n");
		return false;
	}
	int h = hash(str, H->size);
	bucketList temp = H->bucket[h];
	while(temp!=NULL) {
		if(strcmp(temp->item, str) == 0)
			return true;
		temp = temp->next;
	}
	return false;
}

/*
 * insert
 *
 * inserts a string into the hash table
 *
 * no returns
 * 
 * no preconditions
 *
 * if hash table or string is null, prints to stderr
 */
void insert(HashTableObj *H, char *str) {
	if(H==NULL || str==NULL) {
		fprintf(stderr, "NULL pointer detected.\n");
		return;
	}
	int h = hash(str, H->size);
	bucketList new = malloc(sizeof(strlen(str)) + sizeof(bucketList));
	strcpy(new->item, str);
	bucketList temp = H->bucket[h];
	new->next = temp;
	H->bucket[h] = new;
	return;
}

/*
 * delete
 *
 * deletes a specific string str from the hash table, if it exists.
 *
 * if it is deleted, returns true. if it doesn't exist, return false
 *
 * no preconditons
 *
 * if hash table or string is null, prints to stderr
 */
bool delete(HashTableObj *H, char *str) {
	if(H==NULL || str == NULL) {
		fprintf(stderr, "NULL pointer detected.\n");
		return false;
	}
	if(member(H, str) == false)
		return false;
	int h = hash(str, H->size);
	bucketList temp = H->bucket[h];
	if(strcmp(temp->item, str) == 0) {
		bucketList temp2 = temp->next;
		free(temp);
		H->bucket[h] = temp2;
		return true;
	}
	while(temp->next!=NULL) {
		if(strcmp(temp->next->item, str) == 0) {
			bucketList temp2 = temp->next->next;
			free(temp->next);
			temp->next = temp2;
			return true;
		}
		temp = temp->next;
	}
	return false;
}

/*
 * printHashTable
 *
 * prints entire hash table to output file
 *
 * no returns
 *
 * no preconditions
 *
 * if output stream or hash table is null, print to stderr
 */
void printHashTable(FILE *out, HashTableObj *H) {
	if(out==NULL || H==NULL) {
		fprintf(stderr, "NULL Pointer detected.\n");
		return;
	}
	int count = 0;
	fprintf(out, "Hash table contents\n");
	while(count<H->size) {
		bucketList temp = H->bucket[count];
		fprintf(out, "bucket %d\n", count);
		while(temp!=NULL) {
			fprintf(out, "    bucket list item = %s\n", temp->item);
			temp=temp->next;
		}
		count++;
	}
	return;
}
