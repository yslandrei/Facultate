#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

int stop; 
pthread_mutex_t m;
pthread_cond_t c;
int inc = 1;
int v[1000];
int nr = 0;
int fin = 0;
int nrThreaduri;

void* produce(void* arg) {
  int x = *((int*) arg);
  free(arg);
  while(fin == 0) {
    sleep(1);
    pthread_mutex_lock(&m);

    while(nr > 5 * nrThreaduri) {
      pthread_cond_wait(&c, &m);
      if(fin == 1)
        return NULL;
    }

    v[++nr] = inc * x;

    printf("Am produs %d = %d * %d\n", v[nr - 1], inc, x);
    inc++;
    
    pthread_cond_signal(&c);

    pthread_mutex_unlock(&m);      
  }
  pthread_cond_signal(&c);
  return NULL;
}

void* consume(void* arg) {
  while(fin == 0) {
    sleep(1);
    pthread_mutex_lock(&m);

    while(nr == 0) {
      pthread_cond_wait(&c, &m);
      if(fin == 1)
        return NULL;
    }
    nr--;
    printf("Am consumat %d\n", v[nr]);
    if(v[nr] >= stop){
      fin = 1;
      return NULL;
    }

    pthread_cond_signal(&c);

    pthread_mutex_unlock(&m);
  }
  pthread_cond_signal(&c);
  return NULL;
}

int main(int argc, char** argv) {
  pthread_t t[2 * atoi(argv[1])];
  pthread_cond_init(&c, NULL);
  pthread_mutex_init(&m, NULL);

  nrThreaduri = atoi(argv[1]);
  stop = atoi(argv[2]);
  for(int i = 0; i < atoi(argv[1]); i ++) {
    int* a = malloc(sizeof(int));
    *a = i;
    printf("a: %d\n", *a);
    pthread_create(&t[i], NULL, produce,a);
    pthread_create(&t[i + atoi(argv[1])], NULL, consume, NULL);
  }

  for(int i = 0; i < atoi(argv[1]); i ++) {
    pthread_join(t[i], NULL);
    pthread_join(t[i + atoi(argv[1])], NULL);
  }

  pthread_mutex_destroy(&m);
  pthread_cond_destroy(&c);
}
