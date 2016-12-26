#include <stdarg.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct subscriber{
  int id;
  void (*process)(struct subscriber *sub,int count, void *args);
  void (*call)(struct subscriber *sub,int count, void *args);
  void (*end)(struct subscriber *sub);
  void (*init)(struct subscriber *sub, 
	       void (*process)(struct subscriber *sub,int count, void *args));
  void (*runner)(void*);
  pthread_t thread;
  pthread_cond_t cond;
  pthread_mutex_t mutex;
  volatile bool stop;
  volatile bool called;
} Subscriber;

typedef struct subscriberThreadData{
  struct subscriber *sub;
  void *data;
} SubscriberThreadData;

void initSubscriber (struct subscriber *sub, 
	       void (*call)(struct subscriber *sub,int count, void *args));

typedef struct subscriberItem{
  Subscriber *item;
  struct subscriberItem *next;
} SubscriberItem;

typedef struct publisher{
  int nextSubscriberId;
  int noOfSubscribers;
  struct subscriberItem *subscribers;
  struct subscriberItem *lastSubscriber;
  void (*init)(struct publisher *pub);
  void (*subscribe)(struct publisher *pub, Subscriber *subscriber);
  void (*unsubscribe)(struct publisher *pub, Subscriber *subscriber);
  void (*publish)(struct publisher *pub,int count, void* args);
} Publisher;

void subscribeToPublisher(struct publisher *pub, Subscriber *s);
void unsubscribeFromPublisher(struct publisher *pub,Subscriber *s);
void publish(struct publisher *pub,int count, void *args);
void initPublisher(struct publisher *pub);
