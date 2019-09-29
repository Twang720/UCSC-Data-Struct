/*
 * Timmy Wang
 * tqwang
 * CS12B
 * listUtil.h
 * list utility functions to print out the content of the list
 */

/* print the values of each field of a single node */
void print_node(NodeObj *node);

/* traverse the linked list and print the values of each node */
void traverse_print(NodeObj *list_head);

/* traverese the linked list, then prints the values of each node backwards */
void backwards_traverse(NodeObj *list_head);
