/* 
 * Timmy Wang
 * tqwang
 * CS12M
 * charType.c
 * Takes two command line files, an input and an output, then
 * classifies the characters from the input file into the following categories:
 * Alphabetic, Numeric, Punctuation, and Whitespace.
 * Any characters not part of these categories are ignored.
 * It will also print a report to the output file stating how many of each category,
 * and what characters are part of said category.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

/*
 * extract_chars
 *
 * Extracts chars from string, and categorizes them into 
 * alphabet, decimal, punctuation, or whitespace.
 *
 * No return values.
 *
 * Preconditions: s must be a string
 *
 * No side effects.
 */
void extract_chars(char* s, char* a, char* d, char* p, char* w) {
	/* Initializing counters */
	int i, ac, dc, pc, wc;
	ac = 0;	
	dc = 0;
	pc = 0;
	wc = 0;

	assert(s != NULL);

	/* Goes through every character and sorts */
	for( i=0; s[i] != '\0'; i++) {
		if(isalpha((int)s[i])!=0) {
			a[ac++]=s[i];
		}
		else if(isdigit((int)s[i])!=0) {
			d[dc++]=s[i];
		}
		else if(ispunct((int)s[i])!=0) {
			p[pc++]=s[i];
		}
		else if(isspace((int)s[i])!=0) {
			w[wc++]=s[i];
		}
	}
	
	/* Ends string by adding \0 */
	a[ac] = '\0';
	d[dc] = '\0';
	p[pc] = '\0';
	w[wc] = '\0';
}

int main(int argc, char* argv[]){
   	FILE* in;       // handle for input file                  
   	FILE* out;      // handle for output file                 
   	char* line;     // string holding input line              
   	char* a; 	// string holding all letters 
   	char* d; 	// string holding all numbers
   	char* p;	// string holding all punctuation
   	char* w; 	// string holding all whitespace
	int count = 1;	// counter for while loop

	/* Checks command line for correct number of arguments */
	if( argc != 3 ){
		printf("Usage: %s input-file output-file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Opens input file for reading */
	if( (in=fopen(argv[1], "r"))==NULL ){
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	/* Opens output file for writing */ 
	if( (out=fopen(argv[2], "w"))==NULL ){
		printf("Unable to write to file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	/* Allocate strings line, a, d, p, and w on the heap */
	line = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
	a = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
	d = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
	p = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
	w = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
	assert( line!=NULL && a!=NULL && d!=NULL && p!=NULL && w!=NULL );

   	/* Reads each line in input file, and extracts and sorts characters */
   	while( fgets(line, MAX_STRING_LENGTH, in) != NULL ){
      		extract_chars(line, a, d, p, w);
     		fprintf(out, "\nLine %d contains:\n", count);
		fprintf(out, "%d letters: %s\n", (int)strlen(a), a);
		fprintf(out, "%d numbers: %s\n", (int)strlen(d), d);
		fprintf(out, "%d punctuation characters: %s\n", (int)strlen(p), p);
		fprintf(out, "%d whitespace characters: %s\n", (int)strlen(w), w);
		count++;
	}

 	/* Frees heap memory */
	free(line);
	free(a);
	free(d);
	free(p);
	free(w);

	/* Closes input and output files */
	fclose(in);
	fclose(out);

	return EXIT_SUCCESS;
}
