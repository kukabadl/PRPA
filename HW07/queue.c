#include "queue.h"

queue_t * create_queue(int capacity){
  QindivData * pQindivData = (QindivData *) malloc(sizeof(QindivData));
  queue_t * pQueue = (queue_t *)malloc(sizeof(queue_t));
  pQindivData->pData = NULL;
  pQueue->cap = 0;
  pQueue->pHead = pQindivData;
  pQueue->pTail = pQindivData;
  if (capacity > 1){
    for (int i = 0; i < (capacity - 1); i++){
      pQindivData->pNext = (QindivData *)malloc(sizeof(QindivData));
      pQindivData->pData = NULL;
      pQindivData->popped = true;
      pQindivData = pQindivData->pNext;
    }
  }
  pQindivData->pNext = pQueue->pHead;
  pQindivData->pData = NULL;
  pQindivData->popped = true;
  return pQueue;
}

bool push_to_queue (queue_t * pQueue, void * data)
{
  QindivData * pQindivData = pQueue->pHead;
  if (pQindivData->popped == true){
    pQindivData->pData = data;
    pQindivData->popped = false;
    pQueue->pHead = pQindivData->pNext;
    pQueue->cap += 1;
    return true;
  }
  return false;
}

int get_queue_size(queue_t * pQueue){
  return pQueue->cap;
}

void* get_from_queue(queue_t * pQueue, int idx){
  QindivData * Temp = pQueue->pTail;
  if (abs(idx) >= pQueue->cap){
    return NULL;
  }
  if (idx >= 0){
    for (int i = 0; Temp->pNext != NULL && i < idx; i++){
      Temp = Temp->pNext;
    }
    return Temp->pData;
  }
  else {/*
    for (int i = pQueue->cap; i + idx != 0; i--){
      if (Temp->pNext == NULL) return NULL;
      else Temp = Temp->pNext;
    }
    return Temp->pData;
    */
    return NULL;
  }
}

void * pop_from_queue (queue_t * pQueue)
{
  QindivData * pQindivData = pQueue->pTail;
  if (pQindivData->popped == false){
    void * pLastVoid = pQindivData->pData;
    pQindivData->pData = NULL;
    pQindivData->popped = true;
    pQueue->pTail = pQindivData->pNext;
    pQueue->cap --;
    return (int*) pLastVoid;
  }
  else return NULL;
}

void delete_queue(queue_t * pQueue){
  QindivData * pQindivData = pQueue->pTail;
  QindivData * Temp = pQindivData->pNext;
  pQindivData->pNext = NULL;
  while(Temp->pNext != NULL){
    pQindivData = Temp->pNext;
    free (Temp);
    Temp = pQindivData;
  }
  free (Temp);
  free (pQueue);
}
