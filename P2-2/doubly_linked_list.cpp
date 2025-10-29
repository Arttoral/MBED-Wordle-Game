//=================================================================
// Implementation for DLL module.
//
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================
#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"

LLNode* create_llnode(void* data) {
    LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

DLinkedList* create_dlinkedlist(void) {
    DLinkedList* newList = (DLinkedList*)malloc(sizeof(DLinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}


int getSize(DLinkedList* dLinkedList){
  return dLinkedList->size;
}

LLNode* getHead(DLinkedList* dLinkedList){
  return dLinkedList->head;
}

LLNode* getTail(DLinkedList* dLinkedList){
  return dLinkedList->tail;
}

LLNode* getNext(LLNode* node){
  return node->next;
}

LLNode* getPrev(LLNode* node){
  return node->prev;
}

void* getData(LLNode* node){
  return node->data;
}

void insertAfter(DLinkedList* dLinkedList, LLNode* prev_node, void* data){
  if (prev_node == NULL) {
    printf("the given previous node cannot be NULL");
    return;
  }
  LLNode* new_node = create_llnode(data);
  new_node->prev = prev_node;
  new_node->next = prev_node->next;
  prev_node->next = new_node;
  if (new_node->next != NULL)
    new_node->next->prev = new_node;
  else
    dLinkedList->tail = new_node;
  dLinkedList->size++;
}

void insertBefore(DLinkedList* dLinkedList, LLNode* next_node, void* data){
  if (next_node == NULL) {
    printf("the given next node cannot be NULL");
    return;
  }
  LLNode* new_node = create_llnode(data);
  new_node->next = next_node;
  new_node->prev = next_node->prev;
  next_node->prev = new_node;
  if (new_node->prev != NULL)
    new_node->prev->next = new_node;
  else
    dLinkedList->head = new_node;
  dLinkedList->size++;
}

void insertHead(DLinkedList* dLinkedList, void* data){
  if(dLinkedList->head == NULL){
    LLNode* newNode = create_llnode(data);
    dLinkedList->head = newNode;
    dLinkedList->tail = newNode;
    dLinkedList->size++; 
  }else{
    insertBefore(dLinkedList, dLinkedList->head, data);
  }
}

void insertTail(DLinkedList* dLinkedList, void* data){
  if(dLinkedList->head == NULL){
    LLNode* newNode = create_llnode(data);
    dLinkedList->head = newNode;
    dLinkedList->tail = newNode;
    dLinkedList->size++; 
  }else{
    insertAfter(dLinkedList, dLinkedList->tail, data);
  }
}

void deleteNode(DLinkedList* dLinkedList, LLNode* Node){
  if (Node == dLinkedList->head)
    dLinkedList->head = Node->next;
  else
    (Node->prev)->next = Node->next;
  if (Node == dLinkedList->tail)
    dLinkedList->tail = Node->prev;
  else
    (Node->next)->prev = Node->prev;
  free(Node->data);
  free(Node);
  dLinkedList->size--;
}

void destroyList(DLinkedList* dLinkedList){
  LLNode* Node = dLinkedList->head;
  LLNode* Next;
  while(Node){
    free(Node->data);
    Next = Node->next;
    free(Node);
    Node = Next;
  }
  free(dLinkedList);
}

void reverse(DLinkedList* dLinkedList)
{
  LLNode* temp = NULL;  
  LLNode* current = dLinkedList->head;
  if(current != NULL)
    dLinkedList->tail = current;
  /* swap next and prev for all nodes of 
    doubly linked list */
  while (current !=  NULL)
  {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;              
    current = current->prev;
  }      
  
  /* Before changing head, check for the cases like empty 
    list and list with only one node */
  if(temp != NULL )
    dLinkedList->head = temp->prev;
}     
