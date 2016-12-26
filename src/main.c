#include "observer.h"
#include <stdio.h>

void callSubscriber(struct subscriber *sub, int count, void *args){
  printf("%d was called\n", sub->id);
}

void endSubscriber(struct subscriber *sub){
  printf("%d was ended\n", sub->id);
}

int main(){
  printf("Starting\n");
  Publisher pub;
  pub.init = initPublisher;
  pub.init(&pub);

  Subscriber s;
  s.init = initSubscriber;
  s.init(&s,&callSubscriber, &endSubscriber);
  Subscriber s1;
  s1.init = initSubscriber;
  s1.init(&s1, &callSubscriber, &endSubscriber);
  Subscriber s2;
  s2.init = initSubscriber;
  s2.init(&s2,&callSubscriber, &endSubscriber);

  pub.subscribe(&pub, &s);
  pub.subscribe(&pub, &s1);
  printf("No of items:%d\n", pub.noOfSubscribers);
  pub.publish(&pub,0,NULL);
  pub.unsubscribe(&pub, &s);
  printf("No of items:%d\n", pub.noOfSubscribers);
  pub.publish(&pub,0,NULL);
  pub.subscribe(&pub, &s2);
  printf("No of items:%d\n", pub.noOfSubscribers);
  pub.publish(&pub,0,NULL);
  pub.unsubscribe(&pub, &s2);
  printf("No of items:%d\n", pub.noOfSubscribers);
  pub.publish(&pub,0,NULL);
  pub.unsubscribe(&pub, &s1);
  printf("No of items:%d\n", pub.noOfSubscribers);
  pub.publish(&pub,0,NULL);
  
}

