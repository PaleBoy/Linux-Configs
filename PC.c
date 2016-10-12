#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>

#define MAX 3		/* max allowed in buffer */
pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer = 0;
int maxProds = 4;
int maxCons = 3;

void* producer(void *ptr) {
  int i;
  pid_t x = syscall(__NR_gettid);

  for (i = 1; i <= MAX; i++) {
    pthread_mutex_lock(&the_mutex);
    while (buffer != 0){		       /* If there is something in the buffer then wait */
    pthread_cond_wait(&condp, &the_mutex);
    printf("Thread ID: %d Producer is waiting. \n", x);
    }
    buffer = i;
    printf("Thread ID: %d Produced: %d  \n", x, buffer);
    pthread_cond_signal(&condc);	/* wake up consumer */
    pthread_mutex_unlock(&the_mutex);	/* release the buffer */
  }
  pthread_exit(0);
}

void* consumer(void *ptr) {
  int i;
  pid_t x = syscall(__NR_gettid);

  for (i = 1; i <= MAX; i++) {
    pthread_mutex_lock(&the_mutex);
    while (buffer == 0){			/* If there is nothing in the buffer then wait */
    pthread_cond_wait(&condc, &the_mutex);
    printf("Thread ID: %d Consumer is waiting. \n", x);
    }
    buffer = 0;
    printf("Thread ID: %d Consumed: %d  \n", x, buffer);
    pthread_cond_signal(&condp);	/* wake up consumer */
    pthread_mutex_unlock(&the_mutex);	/* release the buffer */
  }
  pthread_exit(0);
}

int main(int argc, char **argv)
{
  pthread_t prod[maxProds], cons[maxCons];

  pthread_mutex_init(&the_mutex, NULL);
  pthread_cond_init(&condc, NULL);
  pthread_cond_init(&condp, NULL);

  /* Create the threads */
  for (int i = 0; i < maxProds; i++)
  {
      pthread_create(&prod[i], NULL, producer, NULL);
  }

  for (int i = 0; i < maxCons; i++)
  {
      pthread_create(&cons[i], NULL, consumer, NULL);
  }

  /* join the threads */
 for (int i = 0; i < maxProds; i++)
 {
     pthread_join(prod[i], NULL);
 }

 for (int i = 0; i < maxCons; i++)
 {
     pthread_join(cons[i], NULL);
 }

  /* clean up */
  pthread_mutex_destroy(&the_mutex);
  pthread_cond_destroy(&condc);
  pthread_cond_destroy(&condp);
}
