#include "queue.h"

queue_t * create_queue(int capacity){
  QindivData * pQindivData = (QindivData *) malloc(sizeof(QindivData));
  queue_t * pQueue = (queue_t *)malloc(sizeof(queue_t));
  pQueue->pThousands = (thousands *) malloc(sizeof(thousands));
  pQueue->pThousands->pNext = NULL;
  pQindivData->pData = NULL;
  pQueue->cap = 0;
  pQueue->pHead = pQindivData;
  pQueue->pTail = pQindivData;
  if (capacity > 1){
    for (int i = 0; i < (capacity - 1); i++){
      pQindivData->pNext = (QindivData *)malloc(sizeof(QindivData));
      pQindivData->pData = NULL;
      pQindivData->popped = true;
      }
      pQindivData = pQindivData->pNext;
  }
  pQindivData->pNext = pQueue->pHead;
  pQindivData->pData = NULL;
  pQindivData->popped = true;
  pQueue->numOfPopped = 0;

  QindivData * TempInd = pQueue->pHead;
  thousands * TempTh = pQueue->pThousands;

  for (int i = 0; i <= capacity; i++){
    if ((i % 500) == 0){
      TempTh->pQindivData = TempInd;
      TempTh = TempTh->pNext;
      TempTh =(thousands *) malloc(sizeof(thousands));
      TempTh->pNext = NULL;
    }
    TempInd = TempInd->pNext;
  }
  return pQueue;
}

bool push_to_queue (queue_t * pQueue, void * data)
{
  QindivData * pQindivData = pQueue->pHead;
  if (pQindivData->popped == true){
    pQindivData->pData = data;
    pQindivData->popped = false;
    pQueue->pHead = pQindivData->pNext;
    pQueue->cap ++;
    return true;
  }
  return false;
}

int get_queue_size(queue_t * pQueue){
  return pQueue->cap;
}

void * get_from_queue(queue_t * pQueue, int index){
  QindivData * Temp = pQueue->pTail;
  if (index >= 0 && index < pQueue->cap){
    thousands * TempTh = pQueue->pThousands;
    int a = 0;
    for (; (a * 500) < (index / 500); a++){
      TempTh = TempTh->pNext;
    }
    QindivData * TempInd = TempTh->pQindivData;
    a *= 500;
    while (a < index){
      TempInd = TempInd->pNext;
      a++;
    }
    return TempInd->pData;
  }
  else return NULL;
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
    pQueue->numOfPopped ++;
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
  thousands * pThousands = pQueue->pThousands;
  thousands * pTempThousands = pThousands->pNext;
  while(pTempThousands != NULL){
    free (pThousands);
    pThousands = pTempThousands;
    pTempThousands = pTempThousands->pNext;
  }
  free (pThousands);
  free (Temp);
  free (pQueue);
}
