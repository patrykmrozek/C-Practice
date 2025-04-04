#include "dll.h"

Node* _create_dummy() {
  //private helper function to create dummy head and tail
  Node* dummy = (Node*)malloc(sizeof(Node));
  if (!dummy) {
    perror("DUMMY - malloc error\n");
    return NULL;
  }
  
  *dummy = (Node) {
    .data = 0;
    .prev = NULL,
    .next = NULL
  };
  return dummy;
}

//private helper to create node
Node* _create_node() {
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (!newNode) {
    perror("NODE - malloc error\n");
    return NULL;
  }
  
  *newNode = {
    .data = 0,
    .prev = NULL,
    .next = NULL
  };
  return newNode;
}


static *Node _add_node(int item, *Node prev, *Node next) {
  node = _create_node()
  if (node) {
    node->data = item;
    node->prev = prev;
    node->next = next;

    if (prev) prev->next = node;
    if (next) next->prev = node;
  }
  return node;
}


dll* create_dll() {
  //allocate space for dll
  dll* dll = (dll*)malloc(sizeof(dll));
  if (!dll) {perror("DLL - malloc error\n"); return NULL;}
  
  dll->head = _create_dummy();
  dll->tail = _create_dummy();
  
  //if malloc failed, return null
  if (!new_dll->head || !new_dll->tail) {
        free(new_dll->head);
        free(new_dll->tail);
        free(new_dll);
        return NULL;
  }

  //initialize dummy values
  dll->head->next = dll->tail;
  dll->tail->prev = dll->head;
  dll->size = 0;

  return new_dll;
}


void add_first(dll* dll, int item) {
  if (!dll) return;
  _add_node(item, dll->head, dll->head->next);
  dll->size++;
}


void add_last(dll* dll, int item) {
  if (!dll) return;
  _add_node(item, dll->tail->prev, dll->tail);
  dll->size ++;
}


void add_after(dll* dll, int item, Node* node) {
  if (!dll || !node) return;
  Node* newNode = _add_node(item, node, node->next);
  dll->size++;
}

