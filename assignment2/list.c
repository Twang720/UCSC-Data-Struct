/*
 * Timmy Wang
 * tqwang
 * CS12B
 * list.c
 * Contains the list manipulation routines.
 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*
 * create_new_node
 *
 * Allocates the space for a new node and initializes the value field. Returns a pointer the node or NULL if memory allocation failed.
 *
 * Returns a NodeObj, or NULL if memory allocation failed.
 *
 * Assume id is a unique number.
 *
 * No side effects.
 */
NodeObj *create_new_node (int id) {
	NodeObj *new_node = malloc(sizeof(NodeObj));
	if(new_node == NULL) {
		return NULL;
	}
	new_node->value = id;
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

/*
 * insert
 *
 * Inserts the node at the end of the list. Does nothing if NodeObj to be inserted is null.
 *
 * No return value.
 *
 * No pre-conditions.
 *
 * Prints to stderr if there is an error.
 */
void insert(NodeObj **list_head, NodeObj *to_be_inserted) {
	if(to_be_inserted == NULL || list_head == NULL) {
		fprintf(stderr, "Null pointer not valid argument.\n");
		return;
	}
	if(*list_head == NULL) {
		*list_head = to_be_inserted;
		return;
	}
	NodeObj *temp = *list_head;
	while(temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = to_be_inserted;
	to_be_inserted->prev = temp;
	return;
}

/*
 * ordered_insert
 *
 * Inserts a node into the increasing value ordered linked list.
 *
 * No return value.
 *
 * Assumes list is ordered. If list is unordered, will put node in front of first node that has greater value than node to be inserted.
 *
 * Prints to stderr if there is an error.
 */
void ordered_insert(NodeObj **list_head, NodeObj *to_be_inserted) {
	if(list_head == NULL || to_be_inserted == NULL ) {
		fprintf(stderr, "Null pointer not valid argument.\n");
		return;
	}
	if(*list_head == NULL) {
		insert(list_head, to_be_inserted);
		return;
	}
	NodeObj *temp = *list_head;
	while(temp != NULL) {
		if(to_be_inserted->value < temp->value) {
			to_be_inserted->prev = temp->prev;
			to_be_inserted->next = temp;
			temp->prev = to_be_inserted;
			if(*list_head == temp){
				*list_head = to_be_inserted;
			}
			else {
				(to_be_inserted->prev)->next = to_be_inserted;
			}
			return;
		}
		temp = temp->next;
	}
	insert(list_head, to_be_inserted);
	return;
}

/*
 * delete_all
 *
 * Removes all the nodes from the list and deallocates the memory allocated to the list.
 * If list is already empty, does nothing.
 *
 * No return value.
 *
 * Assumes list head will be set to null after calling function.
 *
 * No side effects.
 */
void delete_all(NodeObj *list_head) {
	while(list_head != NULL) {
		NodeObj *temp = list_head->next;
		free(list_head);
		list_head = temp;
	}
	return;
}

/*
 * delete
 *
 * Deleted the node from the list and set the list head to null if the resulting list is empty.
 *
 * No return value.
 *
 * No pre-conditions.
 *
 * Prints to stderr if there is an error.
 */
void delete(NodeObj **list_head, NodeObj *to_be_deleted) {
	if(list_head==NULL || to_be_deleted == NULL) {
		fprintf(stderr, "Null pointer not valid argument.\n");
		return;
	}
	if(*list_head == NULL) {
		fprintf(stderr, "List is already empty.\n");
		return;
	}
	if(*list_head == to_be_deleted) {
		NodeObj *t = *list_head;
		*list_head = to_be_deleted->next;
		free(t);
		return;
	}
	NodeObj *temp = *list_head;
	while(temp->next != NULL) {
		if(temp == to_be_deleted) {
			(temp->prev)->next = temp->next;
			(temp->next)->prev = temp->prev;
			free(temp);
			return;
		}
		temp = temp->next;
	}
	if(temp == to_be_deleted) {
		(temp->prev)->next = temp->next;
		free(temp);
		return;
	}
	fprintf(stderr, "NodeObj does not exist in list.\n");
	return;
}
