#include "queue.h"

queue_t * pHead = NULL;   //Ukazatel na na posledy zapsany clen
queue_t * pTail = NULL;   //Ukazatel na na posledy popnuty clen
int cap;
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
      pCurrentStruct->popped = false;
      pCurrentStruct = pCurrentStruct->pNext;
    }
  }
  pCurrentStruct->pNext = pFirst;
  pCurrentStruct->pData = NULL;
  pCurrentStruct->popped = false;
  pHead = pFirst;
  pTail = pFirst;
  return pFirst;
}

bool push_to_queue (queue_t *queue, void * data)
{
  if (pHead != NULL){
    pHead->pData = data;
    pHead->popped = false;
    printf ("%d ",(int) pHead);
    printf ("%d\n",* ((int *) data));

    pHead = pHead->pNext;
    return true;
  }
  return false;
}

int get_queue_size(queue_t *queue){
  queue_t * Temp = pTail;
  int i = 0;
  while (1){
    if (Temp->popped == false) i++;
    Temp = Temp->pNext;
    if (Temp == pTail) break;
  }
  return i;
  //printf("num %d ", numOfElements);
}

void* get_from_queue(queue_t *queue, int idx){
  queue_t * Temp = pTail;
  if (pTail != NULL){
    if (idx >= 0){
      for (int i = 0; Temp->pNext != NULL && i < idx; i++){
        Temp = Temp->pNext;
      }
      return Temp->pData;
    }
    else {
      for (int i = get_queue_size(pTail); i + idx != 0; i--){
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
  void * pLastVoid = pTail->pData;
  if (pTail->popped == false){
    pTail->pData = NULL;
    pTail->popped = true;
    pTail = pTail->pNext;
    return (int*) pLastVoid;
  }
  else return NULL;
}

void delete_queue(queue_t *queue){
  queue_t * Temp = pTail->pNext;
  pTail->pNext = NULL;
  //printf ("%d\n",(int) Temp);
  //printf ("%d\n",(int) *((int *) Temp->pData));
  int i = 0;
  while(Temp->pNext != NULL){
    printf ("%d ", i);
    printf ("%d",(int) Temp);
    printf (" X %d\n",(int) pTail);
    Temp = Temp->pNext;
    free (Temp);
    i++;
  }
  free (Temp);
}
/*
printf ("%d",(int) Temp);
printf (" X %d\n",(int) pTail);
printf ("%d\n", i);*/
