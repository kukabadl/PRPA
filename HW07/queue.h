#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Queue structure which holds all necessary data */
typedef struct a {
   // TODO - Include your data structure here
   void * pData;
   struct a * pNext;
   bool popped;
} queue_t;

/* creates a new queue with a given size */
queue_t* create_queue(int capacity);

/*
 * inserts a reference to the element into the queue
 * returns: true on success; false otherwise
 */
bool push_to_queue(queue_t *queue, void *data);

/* gets number of stored elements */
int get_queue_size(queue_t *queue);

/*
 * gets idx-th element from the queue
 * returns the element that will be popped after idx calls of the pop_from_queue()
 * returns: the idx-th element on success; NULL otherwise
 */
void* get_from_queue(queue_t *queue, int idx);

/*
 * gets the first element from the queue and removes it from the queue
 * returns: the first element on success; NULL otherwise
 */
void* pop_from_queue(queue_t *queue);

/* deletes the queue and all allocated memory */
void delete_queue(queue_t *queue);

#endif /* __QUEUE_H__ */
