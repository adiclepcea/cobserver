#include "observer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void processSubscriber(struct subscriber *sub){
  /*if(sub->data && sub->dataSize>0){
    printf("%d has %s data\n",sub->id,(char*)sub->data);
  }else{
    printf("%d was called\n", sub->id);
  }*/
  sleep(1);
  //printf("here %d\n",sub->id);
  void *item;
  while((item=sub->queue.dequeue(&sub->queue))){
    printf("%d has %s data\n",sub->id,(char*)item);
    free(item);
    item = NULL;
  }

}

int main(){
  char data[]="TEST";

  printf("Starting\n");
  Publisher pub;
  pub.init = initPublisher;
  pub.init(&pub);

  Subscriber s;
  s.init = initSubscriber;
  s.init(&s,&processSubscriber);

  Subscriber s1;
  s1.init = initSubscriber;
  s1.init(&s1, &processSubscriber);

  Subscriber s2;
  s2.init = initSubscriber;
  s2.init(&s2,&processSubscriber);

  Subscriber s3;
  s3.init = initSubscriber;
  s3.init(&s3,&processSubscriber);

  pub.subscribe(&pub, &s);
  pub.subscribe(&pub, &s1);
  pub.subscribe(&pub, &s2);
  pub.subscribe(&pub, &s3);

  int i;
  for(i=0;i<10;i++){
      pub.publish(&pub,sizeof(data),(void*)data);
    //sleep(1);
  }
  sleep(3);
  pub.unsubscribe(&pub, &s);
  pub.unsubscribe(&pub, &s2);
  pub.unsubscribe(&pub, &s1);
  sleep(2);
  pub.unsubscribe(&pub, &s3);

  pthread_exit(NULL);

}
