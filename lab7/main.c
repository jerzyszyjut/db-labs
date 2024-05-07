#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX_PRIME 100000

typedef struct dane {
  int primes[MAX_PRIME];
  int curr_p; 
  pthread_mutex_t m_p;
  pthread_mutexattr_t attr;
} dane_t;

typedef struct dane_dla_watku {
  dane_t *dane;
  int range_start;
  int range_end;
} dane_dla_watku_t;

void *f(void *i)
{
  dane_dla_watku_t* dane = (dane_dla_watku_t*) i;
  for(int i=dane->range_start; i<dane->range_end; i++)
  {
    int j, flag = 0;
    if (i == 0 || i == 1) flag = 1;
    for (j = 2; j <= i / 2; j++) {
      if (i % j == 0) {
        flag = 1;
        break;
      }
    }

    if (flag) continue;

    pthread_mutex_lock(&dane->dane->m_p);
    dane->dane->primes[dane->dane->curr_p] = i;
    dane->dane->curr_p += 1;
    pthread_mutex_unlock(&dane->dane->m_p);
  }
}

int main()
{
  dane_t zmienna_z_danymi;
  zmienna_z_danymi.curr_p = 0;
  
  if (pthread_mutexattr_init(&zmienna_z_danymi.attr) == -1) {                                    
    perror("mutexattr_init error");                                             
    exit(1);                                                                    
  }                                                                             
                                                                                
  if (pthread_mutex_init(&zmienna_z_danymi.m_p, &zmienna_z_danymi.attr) == -1) {                                  
    perror("mutex_init error");                                                 
    exit(2);                                                                    
  } 

  int number_of_threads = 8;
  int single_range = MAX_PRIME / number_of_threads;
  pthread_t* watki = (pthread_t*)malloc(sizeof(pthread_t) * number_of_threads);
  dane_dla_watku_t* dane_dla_watkow = (dane_dla_watku_t*)malloc(sizeof(dane_dla_watku_t) * number_of_threads);


  for(int i=0; i<number_of_threads; i++)
  {
    dane_dla_watkow[i].dane = &zmienna_z_danymi;
    dane_dla_watkow[i].range_start = i * single_range;
    dane_dla_watkow[i].range_end = (i + 1) * single_range;
    pthread_create(&watki[i], NULL, f, (void *)&dane_dla_watkow[i]);
  }

  for(int i=0; i<number_of_threads; i++)
  {
    pthread_join(watki[i], NULL);
  }


  for(int i=0; i<zmienna_z_danymi.curr_p; i++)
  {
    printf("%d\n", zmienna_z_danymi.primes[i]);
  }


  pthread_mutex_destroy(&zmienna_z_danymi.m_p);
  free(dane_dla_watkow);
  free(watki);

  return 0;
}
