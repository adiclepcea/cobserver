#include "observer.h"
#include "stdlib.h"
#include <stdio.h>

Publisher publisher;

static int nextSubscriberId;

void initSubscriber(struct subscriber *sub,
		    void (*call)(struct subscriber *sub, int count, void *args),
		    void (*end)(struct subscriber *sub)){
  sub->call = call;
  sub->end = end;
}

void initPublisher(struct publisher *pub){
  pub->nextSubscriberId = 0;
  pub->subscribe = subscribeToPublisher;
  pub->unsubscribe = unsubscribeFromPublisher;
  pub->publish = publish;
  pub->subscribers = NULL;
  pub->lastSubscriber = NULL;
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
  
    if(si==pub->subscribers){
      pub->subscribers = si->next;
    }else if(parent!=NULL){
      parent->next = NULL;
    }
    
    free(si);
    
    pub->noOfSubscribers--;
  }
}

void publish(struct publisher *pub, int count, void *args){
  int i;

  SubscriberItem *si = pub->subscribers;

  while(si!=NULL){
    si->item->call(si->item, count, args);
    si=si->next;
  }
}
