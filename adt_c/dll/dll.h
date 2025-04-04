#ifndef DLL_H
#define DLL_H

typedef struct Node {
  int data;
  struct Node* prev;
  struct Node* next;
} Node;

typedef struct dll {
  Node* head;
  Node* tail;
  int size;
} dll;

dll* create_dll();
void add(dll* list, int item);
void add_after(dll* list, int item, Node node);
void add_first(dll* list, int item);
void add_last(dll* list, int item);
Node* get_first(dll* list);
Node* get_last(dll* list);
void rm_first(dll* list);
void rm_last(dll* list);
void free_dll(dll* list);

#endif 
