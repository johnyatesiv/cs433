/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: johnyates
 *
 * Created on November 4, 2017, 9:37 AM
 */

#include <stdio.h>
#include <pthread.h>

#define MAX 10000000000			/* Numbers to produce */
pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer = 0;

void* Producer(void *pointer) {
  int i;

  for (i = 1; i <= MAX; i++) {
    pthread_mutex_lock(&the_mutex);	/* protect buffer */
    while (buffer != 0)		       /* If there is something 
					  in the buffer then wait */
    pthread_cond_wait(&condp, &the_mutex);
    buffer = i;
    pthread_cond_signal(&condc);	/* wake up Consumer */
    pthread_mutex_unlock(&the_mutex);	/* release the buffer */
  }
  pthread_exit(0);
}

void* Consumer(void *pointer) {
  int i;

  for (i = 1; i <= MAX; i++) {
    pthread_mutex_lock(&the_mutex);	/* protect buffer */
    while (buffer == 0);	/* If there is nothing in the buffer then wait */
        
    pthread_cond_wait(&condc, &the_mutex);
    buffer = 0;
    pthread_cond_signal(&condp);	/* wake up Consumer */
    pthread_mutex_unlock(&the_mutex);	/* release the buffer */
  }
  
  pthread_exit(0);
}

int main(int argc, char **argv) {
  pthread_t pro, con;

  // Initialize the mutex and condition variables
  /* What's the NULL for ??? */
  pthread_mutex_init(&the_mutex, NULL);	
  pthread_cond_init(&condc, NULL);		/* Initialize Consumer condition variable */
  pthread_cond_init(&condp, NULL);		/* Initialize Producer condition variable */

  // Create the threads
  pthread_create(&con, NULL, Consumer, NULL);
  pthread_create(&pro, NULL, Producer, NULL);

  // Wait for the threads to finish
  // Otherwise main might run to the end
  // and kill the entire process when it exits.
  pthread_join(&con, NULL);
  pthread_join(&pro, NULL);

  // Cleanup -- would happen automatically at end of program
  pthread_mutex_destroy(&the_mutex);	/* Free up the_mutex */
  pthread_cond_destroy(&condc);		/* Free up Consumer condition variable */
  pthread_cond_destroy(&condp);		/* Free up Producer condition variable */

}
