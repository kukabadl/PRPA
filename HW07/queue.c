#include "queue.h"

queue_t * pHead = NULL;   //Ukazatel na naposledy zapsany clen

queue_t * create_queue(int capacity){
  queue_t * pFirst;
  queue_t * pCurrentStruct = (queue_t *)malloc(sizeof(queue_t));
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
  return pFirst;
}

bool push_to_queue (queue_t *queue, void *data)
{
  if (pHead->pNext != NULL){
    pHead = pHead->pNext;
  }
  else return false;
	pHead->pData = data;
	return true;
}

int get_queue_size(queue_t *queue){
  int numOfElements = 0;
  if (queue =! NULL){
    queue_t * Temp = queue;
    numOfElements = 1;
    while (Temp->pNext != NULL){
      numOfElements++;
      Temp = Temp->pNext;
    }
  }
  return numOfElements;
}

void* get_from_queue(queue_t *queue, int idx){
  queue_t * Temp = queue;
  if (queue =! NULL){
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
  if (queue != NULL){
    void * pLastVoid = queue->pData;
    queue_t * pLastQ = queue;
    queue = queue->pNext;
    free (pLastQ->pData);
    free (pLastQ->pNext);
    free (pLastQ);
    return pLastVoid->pData;
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
