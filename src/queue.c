#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void enqueue(struct queue *me, void *item){
  //we stop the creation
  pthread_mutex_lock(&me->mutex);
  if(me->noOfItems>=me->maxItems){
    pthread_mutex_unlock(&me->mutex);
    return;
  }
  struct queueItem *elem = malloc(sizeof(struct queueItem));
  me->noOfItems++;
  elem->item = item;
  elem->next = NULL;
  if(me->head==NULL){
    me->head = elem;
    me->tail = elem;
    pthread_mutex_unlock(&me->mutex);
    return;
  }

  me->tail->next = elem;
  me->tail = elem;
  pthread_mutex_unlock(&me->mutex);
}

void* dequeue(struct queue *me){
  pthread_mutex_lock(&me->mutex);
  void *item = NULL;
  if(me->head){
    item = me->head->item;
    struct queueItem *temp = me->head;
    me->head = me->head->next;
    me->noOfItems--;
    free(temp);
    temp = NULL;
    if(me->head==NULL){
      me->tail = NULL;
      me->noOfItems = 0;
    }
  }
  pthread_mutex_unlock(&me->mutex);
  return item;
}

void initQueue(struct queue *me){
  me->head = NULL;
  me->tail = NULL;
  me->enqueue = enqueue;
  me->dequeue = dequeue;
  me->noOfItems = 0;
  me->maxItems = 20;
  pthread_mutex_init(&me->mutex,NULL);
}
