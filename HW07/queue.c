#include "queue.h"

queue_t * pHead = NULL;   //Ukazatel na naposledy zapsany clen
queue_t * pTail = NULL;   //Ukazatel na naposledy popnuty clen

queue_t * create_queue(int capacity){
  queue_t * pFirst;
  queue_t * pCurrentStruct = (queue_t *)malloc(sizeof(queue_t));
  pCurrentStruct->pData = NULL;
  pFirst = pCurrentStruct;
  if (capacity > 1){
    for (int i = 0; i < (capacity - 1); i++){
      pCurrentStruct->pNext = (queue_t *)malloc(sizeof(queue_t));
      pCurrentStruct->pData = NULL;
      pCurrentStruct = pCurrentStruct->pNext;
    }
  }
  pCurrentStruct->pNext = NULL;
  pCurrentStruct->pData = NULL;
  pHead = pFirst;
  pTail = pFirst;
  return pFirst;
}

bool push_to_queue (queue_t *queue, void * data)
{
  if (pHead != NULL){
    pHead->pData = data;
    pHead = pHead->pNext;
    return true;
  }
  return false;
}

int get_queue_size(queue_t *queue){

  int numOfElements = 0;
  if (queue != NULL){
    queue_t * Temp = queue;
    numOfElements = 1;
    while (Temp->pNext != NULL){
      numOfElements++;
      Temp = Temp->pNext;
    }
  }
  //printf(" %d ", numOfElements);
  return numOfElements;
}

void* get_from_queue(queue_t *queue, int idx){
  queue_t * Temp = queue;
  if (queue != NULL){
    if (idx <= 0){
      for (int i = 0; Temp->pNext != NULL && i < idx; i++){
        Temp = Temp->pNext;
      }
      return Temp->pData;
    }
    else {
      for (int i = get_queue_size(queue); i + idx != 0; i--){
        if (Temp->pNext == NULL) return NULL;
        else Temp = Temp->pNext;
      }
      return Temp->pData;
    }
  }
  else return NULL;
}

void * pop_from_queue (queue_t *queue)
{
  if (pTail != NULL){
    void * pLastVoid = pTail->pData;
    pTail = pTail->pNext;
    return (int*) pLastVoid;
  }
  return NULL;
}

void delete_queue(queue_t *queue){
  queue_t * tmp = queue;
  while(1){
    //free (tmp->pData);
    //free (tmp->pNext);
    queue = tmp->pNext;
    free (tmp);
    if (tmp->pNext == NULL) break;
    tmp = queue;
  }
  free (tmp);
}
