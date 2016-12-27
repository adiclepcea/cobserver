#include "observer.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void processSubscriber(struct subscriber *sub){
  if(sub->data && sub->dataSize>0){
    printf("%d has %s data\n",sub->id,sub->data);
  }else{
    printf("%d was called\n", sub->id);
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

  pub.subscribe(&pub, &s);
  pub.subscribe(&pub, &s1);
  pub.subscribe(&pub, &s2);

  int i;
  for(i=0;i<10;i++){
    if(i%2){
      pub.publish(&pub,sizeof(data),(void*)data);
    }else{
      pub.publish(&pub,0,NULL);
    }
    sleep(1);
  }
  pub.unsubscribe(&pub, &s);
  pub.unsubscribe(&pub, &s2);
  pub.unsubscribe(&pub, &s1);

  pthread_exit(NULL);

}
