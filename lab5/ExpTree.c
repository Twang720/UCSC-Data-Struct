#include "ExpTree.h"
/*
 * Timmy Wang
 * tqwang CS12M
 * ExpTree.c
 *
 * Read input string with contains a post-fix expression and buid the corresponding expression evaluation
 *
 * handles input of one post-fix expressio of integers n read from stdin. Examples:
 *   a b c + +    a b - c +   where a,b,c are integers
 * ignores all white space and uses C's sscanf to find acceptable integer formats. Input can flow over
 * multiple lines and is terminated with EOF. 
 *
 * This program only handles regular ints on your machine. So if you input very long int values they will be either
 * truncated or wrap around due to overflow, depening on what sscanf does will integer conversion from too long
 * string values.
 * 
 * Does not handle overflow in general, so if you have a resulting expression too large for an int, an overflow
 * generate unexpected results. 
 *
 */


/*
 * convertToken
 *
 * Takes inputs from stdin and determines what operator it is.
 *
 * Returns operator type
 *
 * Parameters should not be null, no null check.
 *
 * If there's an error, print to stderr.
 */
tokenType convertToken( char *tokenStr, int *tokenVal);

/*
 * newTNode
 *
 * Creates a new node to be put into the expression tree. Call this function when inputting
 * an operand or an operator into the expression tree.
 *
 * Returns node created
 *
 * Parameters should not be null, no null check.
 *
 * No side effects
 */
TNode * newTNode(tokenType inputToken, int tokenVal, TNode *op1, TNode *op2);

/*
 * tokenToStr
 *
 * Converts the token to a string
 *
 * Return the operator string
 *
 * tokenT cannot be null, no null check.
 *
 * No side effects
 */
const char *tokenToStr(tokenType tokenT);

/*
 * printNode
 *
 * Prints node to stdout
 *
 * No return value
 *
 * Node should not be null, there is no null check
 *
 * No side effects.
 */
void printNode( TNode * node);

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
ExpT *
newExpressionTree() {
    StackObj *S;
    
    S = newStack();
    return S;
}


/*
 * deleteTree
 *
 * Deletes the current node in the tree
 *
 * No return values
 *
 * No preconditions
 *
 * No side effects
 */
void
deleteTree(TNode *T) {
    
    if (T != NULL) {
	T->value = 0;	// neurotic
       	deleteTree(T->leftOperand);
       	deleteTree(T->rightOperand);
        free(T);
    }
}
    
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
void
deleteExpressionTree(ExpT *T) {
  
    TNode *node;
    StackObj *S = T;

    while ((node = (TNode *) pop(S)) != NULL) {
	deleteTree(node);
    }
    deleteStack(S);
}

/*
 * printNode
 *
 * Prints node to stdout
 *
 * No return value
 *
 * Node should not be null, there is no null check
 *
 * No side effects.
 */
void 
printNode( TNode * node) {
  
        printf(" node addr = %p, type = %d, value = %d, leftOp = %p, rightOp = %p\n", node, node->type, 
			node->value, node->leftOperand, node->rightOperand);

}

/*
 * convertToken
 *
 * Takes inputs from stdin and determines what operator it is.
 *
 * Returns operator type
 *
 * Parameters should not be null, no null check.
 *
 * If there's an error, print to stderr.
 */
tokenType
convertToken( char *tokenStr, int *tokenVal) {
   
    tokenType retVal;
    char      junkChars[MAX_TOKEN_LENGTH];
    int	      scanCount;

    // check what the token string might be
    scanCount = sscanf (tokenStr, "%d%s", tokenVal, junkChars);
    
    if (scanCount == 1) {
        //printf("token is an integer,str is %s, value = %d\n", tokenStr, *tokenVal);
        return OPERAND;
    }
    if (scanCount == 2) {  // check no trailing characters
        fprintf(stderr, "ERROR, unaccceptable format, had some extra characters in the integer %d\n", *tokenVal);
        exit(EXIT_FAILURE);
    }
 

    if (scanCount > 2 ) {
        fprintf(stderr, "something weird in input parsing, exiting with str = %s\n", tokenStr);
        exit(EXIT_FAILURE);
    }
    // maybe an operator, try and check the format
    else { 
        if (strlen(tokenStr) > MAX_OPERATOR_LENGTH) {
            printf("sorry, can't handle operators longer than 1 character\n");
            return END;
        }
        switch (tokenStr[0]) {
  	    case '+':
		 retVal = PLUS;
		 break;
  	    case '-': 
		retVal = MINUS; 
                break;
  	    case '*': 
		retVal = MUL;
		break;
  	    case '/':
		retVal = DIV;
		break;
            default: 
		fprintf(stderr, "sorry, don't recognize this operator %c\n", tokenStr[0]);
                exit(EXIT_FAILURE);
	}
        //printf("got operator = %d\n", retVal);
        return retVal;
    }

}

/*
 * newTNode
 *
 * Creates a new node to be put into the expression tree. Call this function when inputting
 * an operand or an operator into the expression tree.
 *
 * Returns node created
 *
 * Parameters should not be null, no null check.
 *
 * No side effects
 */
TNode *
newTNode(tokenType inputToken, int tokenVal, TNode *op1, TNode *op2)  {
    
    TNode *node;
    
    node = (TNode *) malloc ((size_t)(sizeof(TNode)));
    node->type = inputToken;
    if (inputToken == OPERAND ) { // this will be a leaf
        node->value = tokenVal;
        node->leftOperand = NULL;
        node->rightOperand = NULL;
    }
    else { // this will be an internal node 
        node->leftOperand = op1;
        node->rightOperand = op2;
    }
    //printf("tree node created\n");
    //printNode(node);
    return node;
}

/*
 * tokenToStr
 *
 * Converts the token to a string
 *
 * Return the operator string
 *
 * tokenT cannot be null, no null check.
 *
 * No side effects
 */
const char *
tokenToStr(tokenType tokenT) {

const static char *tokenChars[] = {"+", "-", "*",  "/", "^D"};

	return tokenChars[tokenT];

}

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
int 
expressionEval(TNode *T) {
        if(T == NULL) {
		fprintf(stderr, "Empty Tree error.\n");
		return 0;
	}
	if(T->leftOperand == NULL && T->rightOperand == NULL) {
		return T->value;
	}
	if(T->type == PLUS) {
		return expressionEval(T->leftOperand) + expressionEval(T->rightOperand);
	}
	else if(T->type == MINUS) {
		return expressionEval(T->leftOperand) - expressionEval(T->rightOperand);
	}
	else if(T->type == MUL) {
		return expressionEval(T->leftOperand) * expressionEval(T->rightOperand);
	}
	return expressionEval(T->leftOperand) / expressionEval(T->rightOperand);
}

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
void
inorderTraverse(FILE *out, TNode  *T) {
   	if(out == NULL) {
                fprintf(stderr, "No output file\n");
                return;
        }
        if(T == NULL) {
                return;
        }
        if(T->leftOperand == NULL && T->rightOperand == NULL) {
                fprintf(out, "%d", T->value);
                return;
        }
        else {
		fprintf(out, "(");
                inorderTraverse(out, T->leftOperand);
		fprintf(out, "%s", tokenToStr(T->type));
                inorderTraverse(out, T->rightOperand);
		fprintf(out, ")");
                return;
	}	
}

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
void
outputExpressionTree(ExpT *T){

   
    TNode *node;
    StackObj *S = T;

    // check if the expression tree is correct for evaluation
    // check overflow or underflow of operands
    if (stackSize(S) > 1 ) {
        fprintf (stderr, "ERROR extra operands in expression\n");
    }
    else {
       node = (TNode *) pop(S);
       inorderTraverse(stdout, node);
       printf(" = %d\n", expressionEval(node));
    }
}

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
void
inputExpressionTree(ExpT *T){

    char  inputToken[MAX_TOKEN_LENGTH + 1];
    tokenType token;
    TNode  *node, *op1, *op2;
    int   tokenVal;
    StackObj *S;
  
    S = T;
    while (scanf( "%s", inputToken) > 0) {	
	
	//printf("input token = %s\n", inputToken);
      
        token = convertToken (inputToken, &tokenVal);
        //printf( "converted token %d \n", token);
        if (token == OPERAND ) {
	    if ((node = newTNode(OPERAND, tokenVal, NULL, NULL)) == NULL) 
		fprintf(stderr, "problem creating node\n");
            else
                push(S, (void *)node);
        }
        else {
	   if ((op2 = pop(S)) == NULL) {
		fprintf(stderr, "sorry, out of operands for operators\n");
 		exit(EXIT_FAILURE);
           }

	   if ((op1 = pop(S)) == NULL) {
		fprintf(stderr, "sorry, out of operands for operator\n");
 		exit(EXIT_FAILURE);
           }
           node = newTNode(token, 0, op1, op2);
           push(S, node);
        }
    }
}

