#include "observer.h"
#include <stdio.h>
#include <unistd.h>

void processSubscriber(struct subscriber *sub, int count, void *args){
  printf("%d was called\n", sub->id);
}

int main(){
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

  pub.subscribe(&pub, &s);
  pub.subscribe(&pub, &s1);
  pub.subscribe(&pub, &s2);
  int i;
  for(i=0;i<10;i++){
    pub.publish(&pub,0,NULL);
    pub.publish(&pub,0,NULL);
    sleep(1);
  }
  pub.unsubscribe(&pub, &s);
  pub.unsubscribe(&pub, &s2);
  pub.unsubscribe(&pub, &s1);
  
  pthread_exit(NULL);

}

