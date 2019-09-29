/*
 * Timmy Wang
 * tqwang
 * CS12B
 * list.h
 * Contains the list node definition and list function prototypes.
 */
typedef struct NodeObj{
   int value;
   struct NodeObj* prev;
   struct NodeObj* next;
} NodeObj;


NodeObj * create_new_node (int id);
void insert(NodeObj **list_head, NodeObj *to_be_inserted);
void ordered_insert(NodeObj **list_head, NodeObj *to_be_inserted);
void delete_all(NodeObj *list_head);
void delete(NodeObj **list_head, NodeObj *to_be_deleted);
