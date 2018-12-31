#include "queue.h"

queue_t * pHead = NULL;   //Ukazatel na na posledy zapsany clen
queue_t * pTail = NULL;   //Ukazatel na na posledy popnuty clen
int cap;
int size;
int popStop = 0;
queue_t * create_queue(int capacity){
  cap = capacity;
  queue_t * pFirst;
  queue_t * pCurrentStruct = (queue_t *)malloc(sizeof(queue_t));
  pCurrentStruct->pData = NULL;
  pFirst = pCurrentStruct;
  if (capacity > 1){
    for (int i = 0; i < (capacity - 1); i++){
      pCurrentStruct->pNext = (queue_t *)malloc(sizeof(queue_t));
      pCurrentStruct->pData = NULL;
      pCurrentStruct->popped = true;
      pCurrentStruct = pCurrentStruct->pNext;
    }
  }
  pCurrentStruct->pNext = pFirst;
  pCurrentStruct->pData = NULL;
  pCurrentStruct->popped = true;
  pHead = pFirst;
  pTail = pFirst;
  return pFirst;
}

bool push_to_queue (queue_t *queue, void * data)
{
  if (pHead != NULL){
    pHead->pData = data;
    pHead->popped = false;
    pHead = pHead->pNext;
    size++;
    return true;
  }
  return false;
}

int get_queue_size(queue_t *queue){
  return size;
}

void* get_from_queue(queue_t *queue, int idx){
  queue_t * Temp = pTail;
  if (abs(idx) >= cap){
    return NULL;
  }
  if (idx >= 0){
    for (int i = 0; Temp->pNext != NULL && i < idx; i++){
      Temp = Temp->pNext;
    }
    return Temp->pData;
  }
  else {
    for (int i = cap; i + idx != 0; i--){
      if (Temp->pNext == NULL) return NULL;
      else Temp = Temp->pNext;
    }
    return Temp->pData;
  }
}

void * pop_from_queue (queue_t *queue)
{
  void * pLastVoid = pTail->pData;
  if (pTail->popped == false){
    pTail->pData = NULL;
    pTail->popped = true;
    pTail = pTail->pNext;
    size--;
    return (int*) pLastVoid;
  }
  else return NULL;
}

void delete_queue(queue_t *queue){
  queue_t * Temp = queue->pNext;
  queue->pNext = NULL;
  while(Temp->pNext != NULL){
    queue = Temp->pNext;
    free (Temp);
    Temp = queue;
  }
  free (Temp);
}
