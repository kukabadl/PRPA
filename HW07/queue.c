#include "queue.h"

int Elems = 0;

queue_t * create_queue(int capacity){
  queue_t * pFirst;
  queue_t * pCurrentStruct = (queue_t *)malloc(sizeof(queue_t));
  pFirst = pCurrentStruct;
  if (capacity < 1){
    for (int i = 0; i < (capacity - 1); i++){
      pCurrentStruct->pNext = (queue_t *)malloc(sizeof(queue_t));
      pCurrentStruct = pCurrentStruct->pNext;
    }
  }
  pCurrentStruct->pData = NULL;
  return pFirst;
}

bool push_to_queue (queue_t *queue, void *data)
{
  queue_t * pCurrent = queue;
  for (int i = 0; i < Elems; i++){
    if (pCurrent->pNext != NULL){
      pCurrent = pCurrent->pNext;
    }
    else return false;
  }
	pCurrent->pData = data;
  Elems++;
	return true;
}

queue_t * pop_from_queue (queue_t *queue)
{
	*data = a->data;
	queue_t * tmp = a->predchozi;
	free (a);
	return tmp;
}

void delete_queue(queue_t *queue){
  while(pCurrent->pNext != NULL){
    free(pNext->pData);
    free(pNext->pData);
  }
}
