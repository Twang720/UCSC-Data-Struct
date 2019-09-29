/*
 * Timmy Wang
 * tqwang 10/15/2018
 * CS12B
 * list_funcs.c
 * Lists and defines all funcs to be used in main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*
 * create_new_rider
 *
 * Creates a new rider structure and returns it. If pre-conditions not met, return null.
 * Assumes ID is unique and a natural number.
 *
 * Returns a rider structure new_rider, returns null if pre-conditions not met.
 * 
 * Pre-conditions: ave_rating must be a double between 1.0 and 5.0, distance must be positive.
 *
 * No side effects.
 */
rider_st *create_new_rider(int id, char *first_name, char *last_name, double ave_rating, double distance) {
	rider_st *new_rider = malloc(sizeof(rider_st)); /* Allocates space for new rider struct */
	
	if(ave_rating<1||ave_rating>5) { /* Checks if ave rating is btwn 1 and 5. */
		return NULL;
	}
	if(distance<0) { /* Checks if dist is positive */
		return NULL;
	}
	
	/* If all conditions pass, create new rider struct. */
	new_rider->ID = id;
	new_rider->first_name = first_name;
	new_rider->last_name = last_name;
	new_rider->ave_rating = ave_rating;
	new_rider->distance = distance;
	new_rider->next = NULL;
	
	return new_rider;
}

/*
 * front_insert
 *
 * Inserts rider node at beginning of list. If list doesn't exist, make new list.
 *
 * No return values.
 *
 * No pre-conditions.
 * 
 * No side-effects.
 */
void front_insert(rider_st **list_head, rider_st *to_be_inserted) {
	to_be_inserted->next = *list_head; 
	*list_head = to_be_inserted;
	return; 
}

/* 
 * end_insert
 *
 * Inserts rider node at end of list. If list doesn't exist, make new list.
 *
 * No return values.
 *
 * No pre-conditions.
 *
 * No side-effects.
 */
void end_insert (rider_st **ptr_to_list_head, rider_st *to_be_inserted) {
	if(*ptr_to_list_head == NULL) { /* Checks if list exists, if it doesn't, make new list */
		front_insert(ptr_to_list_head, to_be_inserted);
		return;
	}
	rider_st *temp = *ptr_to_list_head;
	while(temp->next != NULL) { /* Traverses list to get to list tail. */
		temp = temp->next;
	}
	temp->next = to_be_inserted; /* Inserts at tail. */
	return;
}

/*
 * ordered_insert
 *
 * Inserts rider node based on distance, least to greatest. If list doesn't exist, make new list.
 * If list is not ordered, then node will be put in front of the first node that is greater than the node to be inserted.
 *
 * No return values.
 *
 * No pre-conditions.
 *
 * No side-effects.
 */
void ordered_insert (rider_st **ptr_to_list_head, rider_st *to_be_inserted) {
	if(*ptr_to_list_head == NULL) { /* Checks if list is empty */
		front_insert(ptr_to_list_head, to_be_inserted);
		return;
	}
	rider_st *temp = *ptr_to_list_head;
	if(temp->distance > to_be_inserted->distance) { /* Checks if node should be added at list head */
		front_insert(ptr_to_list_head, to_be_inserted);
		return;
	}
	while(temp->next != NULL) { /* Traverses list and checks  if node should be added in list body */
		if(temp->next->distance > to_be_inserted->distance) {
			to_be_inserted->next = temp->next;
			temp->next = to_be_inserted;
			return;
		}
		else {
			temp = temp->next;
		}
	}
	end_insert(ptr_to_list_head, to_be_inserted); /* Inserts at list tail if not inserted yet */
	return;
}

/*
 * empty
 *
 * Empties entire list.
 * Assumes that caller will set the list_head to null after calling function.
 *
 * No return values.
 *
 * No pre-conditions.
 *
 * Must set list_head to null after calling this function.
 */
void empty(rider_st *list_head) {
	if(list_head == NULL) { /* Checks if list is already empty */
		return;
	}
	rider_st *temp = list_head;
	while(list_head->next != NULL) { /* Traverse list and frees each node. */
		list_head = list_head->next;
		free(temp);
		temp = list_head;
	}
	free(list_head); /* Frees last node. */
	return;
}

/*
 * delete
 *
 * Removes specific rider node from list. If list is empty or node does not exist, then it does nothing.
 *
 * No return values.
 *
 * No pre-conditions.
 *
 * No side effects.
 */
void delete(rider_st **ptr_to_list_head, rider_st *to_be_deleted) {
	if(*ptr_to_list_head == NULL) { /* Checks if list is empty already */
		return;
	}
	rider_st *temp = *ptr_to_list_head;
	if(temp->ID == to_be_deleted->ID) { /* Checks if node to be deleted is list head */
		*ptr_to_list_head = temp->next;
		free(temp);
		return;
	}
	while(temp->next != NULL) { /* Checks if node to be deleted is in list body */
		if(temp->next->ID == to_be_deleted->ID) {
			rider_st *temp2 = temp->next->next;
			free(temp->next);
			temp->next = temp2;
			return;
		}
		else {
			temp = temp->next;
		}
	}
	if(temp->ID == to_be_deleted->ID) { /* Checks if node to be deleted is at list tail */
		free(temp);
	}
	return;
}

/*
 * find_next_distance_rider
 *
 * Finds the next rider node that is greater than min distance and returns it.
 * If pre-conditions not met, list doesn't exist, or no rider in the list is greater than min_distance, returns a rider with no values.
 * A rider with no values will have an ID of 0, first and last name of "none", a rating of 1, and a distance of 0.
 *
 * Returns next rider greater than min distance. Otherwise, return a rider with no values.
 *
 * Pre-conditions: min distance must be positive
 *
 * No side effects.
 */
rider_st find_next_distance_rider(rider_st *list_head, double min_distance) {
	rider_st temp = {0, "none", "none", 1, 0};
	if(list_head == NULL) { /* Checks if list is empty */
		return temp;
	}
	if(min_distance < 0) { /* Checks if distance is positive. */
		return temp;
	}
	rider_st *t = list_head;
	while(t != NULL) { /* Traverses list and searches for lowest dist rider greater than min dist. */
		if(t->distance >= min_distance) {
			temp = *t;
			return temp;
		}
		t = t->next;
	}
	/* Checks if any riders pass conditions */
	return temp;
}

/*
 * print
 *
 * Prints out rider node to console if it exists. Prints Rider is NULL if it doesn't.
 * 
 * No return values.
 *
 * No pre-conditions
 *
 * No side effects
 */
//void print (rider_st *rider) {
//	if (rider != NULL) { /* Checks if rider node exists */
//		printf("Rider Node: ID=%d, first_name=%s, last_name=%s, average_rating %.2f, distance %.2f, next=%p \n", rider->ID, rider->first_name, rider->last_name, rider->ave_rating, rider->distance, rider->next);
//	}
//	else { /* Prints rider is null otherwise. */
//		printf("Rider is NULL.\n");
//	}
//}

/*
 * printAll
 *
 * Prints out all rider nodes from list. If list is null, then prints Rider list is empty.
 *
 * No return values.
 *
 * No pre-conditions.
 *
 * No side effects.
 */
//void printAll (rider_st *list_head) {
//	if (list_head == NULL) { /* Checks if list is empty */
//		printf("Rider list is empty.\n");
//	}
//	while(list_head != NULL) { /* Else print all nodes to console. */
//		print(list_head);
//		list_head = list_head->next;
//	}
//}
