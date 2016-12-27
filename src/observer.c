#include "observer.h"
#include "stdlib.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

Publisher publisher;

static int nextSubscriberId;

void endSubscriber(struct subscriber *sub){
  printf("Ending %d\n", sub->id);
  sub->stop = true;
  sub->call(sub, 0, NULL);
}

//call will try to start the processor function.
//if the lock is not free, it means that the function
//has not finished yet so we ignore.
//you could use a buffer if you want
void call(struct subscriber *sub, size_t size, void *data){

  //if we try to stop then we wait for the lock
  if(sub->stop)
    pthread_mutex_lock(&sub->mutex);

  //else we just try the lock
  else if(pthread_mutex_trylock(&sub->mutex)!=0)
    return;

  if(sub->data){
    free(sub->data);
    sub->data = NULL;
  }

  if(size>0 && data){
    sub->data = malloc(size);
    memcpy(sub->data, data, size);
  }

  sub->dataSize = size;
  sub->called = true;

  pthread_cond_signal(&sub->cond);

  pthread_mutex_unlock(&sub->mutex);

}

//runnerSub will wait for the subscriber to receive data
//and will then run the executor function with the data
//received from the publisher
void *runnerSub(void* param){
  struct subscriber *sub = (struct subscriber*)param;
  while(true){
    pthread_mutex_lock(&sub->mutex);
    while(!sub->called)
      pthread_cond_wait(&sub->cond, &sub->mutex);
    if(sub->stop){
      pthread_mutex_unlock(&sub->mutex);
      break;
    }
    sub->process(sub);
    sub->called = false;
    pthread_mutex_unlock(&sub->mutex);
  }
  pthread_mutex_destroy(&sub->mutex);
  pthread_cond_destroy(&sub->cond);
  printf("Subscriber %d exiting\n",sub->id);
  pthread_exit(NULL);
}

void initSubscriber(struct subscriber *sub,
		    void (*process)(struct subscriber *sub)){
  sub->process = process;
  sub->call = call;
  sub->end = endSubscriber;
  sub->stop = false;
  sub->called = false;
  sub->data = NULL;
  pthread_mutex_init(&sub->mutex,NULL);
  pthread_cond_init(&sub->cond, NULL);
  pthread_create(&sub->thread, NULL, runnerSub, (void *)sub);
//  pthread_exit(NULL);
}

void initPublisher(struct publisher *pub){
  pub->nextSubscriberId = 0;
  pub->subscribe = subscribeToPublisher;
  pub->unsubscribe = unsubscribeFromPublisher;
  pub->publish = publish;
  pub->subscribers = NULL;
  pub->lastSubscriber = NULL;
  pub->noOfSubscribers = 0;
}

void subscribeToPublisher(struct publisher *pub,Subscriber *s){
  SubscriberItem *si = malloc(sizeof(SubscriberItem));
  si->item = s;
  s->id = pub->nextSubscriberId++;
  si->next = NULL;

  if(pub->noOfSubscribers>0){
    pub->lastSubscriber->next = si;
  }else{
    pub->subscribers = si;
  }

  pub->lastSubscriber = si;
  pub->noOfSubscribers++;
}

void unsubscribeFromPublisher(struct publisher *pub, Subscriber *s){
  struct subscriberItem *si = pub->subscribers;
  struct subscriberItem *parent = NULL;

  while(si->next!=NULL && si->item!=s){
    parent = si;
    si = si->next;
  }
  if(si->item==s){

    si->item->end(si->item);
    if(si==pub->subscribers){
      pub->subscribers = si->next;
    }else if(parent!=NULL){
      parent->next = NULL;
    }

    free(si);

    pub->noOfSubscribers--;
  }
}

void publish(struct publisher *pub, size_t size, void *data){
  int i;

  SubscriberItem *si = pub->subscribers;

  while(si!=NULL){
    si->item->call(si->item, size, data);
    si=si->next;
  }
}
