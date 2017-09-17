//#include <random>
#include <stdio.h>
#include "test.h"
#include "pcb_handler.h"
#include <stdio.h>      /* printf */
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include <stdlib.h>     /* srand, rand */
#include <sys/time.h>   /* gettimeofday */

int main(int argc, char* argv[]) {
	printf("----CS 433 Assignment 1----\n");
	printf("Group memebers: John Yates and Joseph Colarossi\n");
        
        PCBHandler *handler = new PCBHandler();
        
        /* Test 1 */
        PCB *pid1 = new PCB(1, 1);
        PCB *pid2 = new PCB(2, 2);
        PCB *pid3 = new PCB(3, 3);
        PCB *pid4 = new PCB(4, 4);
        PCB *pid5 = new PCB(5, 5);
        PCB *pid6 = new PCB(6, 6);
        PCB *pid7 = new PCB(7, 7);
        PCB *pid8 = new PCB(8, 8);
        PCB *pid9 = new PCB(9, 9);
        PCB *pid10 = new PCB(10, 10);
        PCB *pid11 = new PCB(11, 11);
        PCB *pid12 = new PCB(12, 12);
        PCB *pid13 = new PCB(13, 13);
        PCB *pid14 = new PCB(14, 14);
        PCB *pid15 = new PCB(15, 15);
        PCB *pid16 = new PCB(16, 16);
        PCB *pid17 = new PCB(17, 17);
        PCB *pid18 = new PCB(18, 18);
        PCB *pid19 = new PCB(19, 19);
        PCB *pid20 = new PCB(20, 20);
        
        /* Add PID 5, 1, 8 and 11 */
        printf("Adding PID 5, 1, 8 and 11.\n");
        handler->add(pid5);
        handler->add(pid1);
        handler->add(pid8);
        handler->add(pid11);
        
        handler->showTable();
        
        /* Display Queue, should be ordered 1, 5, 8, 11 */
        handler->Queue.displayQueue();
        
        /* Remove highest priority */
        printf("Removing Highest Priority Process.\n");
        PCB *removed;
        handler->Queue.removeHighestProc(removed);
        
        /* Redisplay, should be ordered 5, 8, 11 */
        handler->Queue.displayQueue();
        
        /* Add PID 3, 7, 2, 12, 9 */
        printf("Adding PID 3, 7, 2, 12 and 9.\n");
        handler->add(pid3);
        handler->add(pid7);
        handler->add(pid2);
        handler->add(pid12);
        handler->add(pid9);
       
        /* Redisplay, should be ordered 2, 3, 5, 7, 8, 9, 11, 12 */
        handler->Queue.displayQueue();
        
        /* Iterate over the remaining processes and display each time */
        while(!handler->Queue.isEmpty()) {
            handler->Queue.removeHighestProc(removed);
            handler->Queue.displayQueue();
        }
        
        printf("Queue empty, starting Test 2.\n");
        
        /* Test 2 */
        
        /* Select 10 random PCB objects from the existing Handler's table and reassign a random priority between 1 and 50 */
        
        int i = 0;
        int max = 1000000; //target iterations
        srand(time(NULL)); //seed the random number generator
        double randomChance; // double for holding the chance for each iteration
        int randomPriority; // for random priority on insertion
        PCB *randomEl; //for holding PCBs from the table
        
        /* Benchmark start */
        //time_t start = time(NULL);
        struct timeval start, end;
        gettimeofday(&start, NULL);
        
        
        while(i != max) {
//            printf("\nIteration ");
//            printf("%i", i);
//            printf(": ");
            
            //randomChance = dis(gen);
            randomChance = (rand() % 10);
            
            /* Random 50/50 chance to either */
            if(randomChance < 5) {
                /* Remove a process */
                //printf("Removing a process from Queue.\n");
                
                if(!handler->Queue.isEmpty()) {
                    handler->Queue.removeHighestProc(removed);
                }
            } else {
                //printf("HERE");
                /* If there is a process in the table READY state not in the queue, insert it */
                //printf("Adding a process from table.\n");
                randomEl = handler->randomFromTable();
                randomPriority = (rand() % 50)+1;
                randomEl->setPriority(randomPriority);
                //randomEl->print();
//                printf("%f", randomChance);
//                printf("\n");
//                printf("%i", randomPriority);
//                printf("\n");
                
                if(!handler->Queue.isInQueue(randomEl->id)) {
                    /* Before inserting, randomize its priority between 1 and 50 */
                    //printf("Not in Queue, inserting.\n");
                    handler->Queue.insertProc(randomEl);
                }

                /* If the process is in the queue already, do not reinsert it */
            }
            
            i++;
        }
        
        /* Benchmark finish */
        
        gettimeofday(&end, NULL);
        
        printf("Execution time: %ld microseconds\n",
            ((end.tv_sec - start.tv_sec)*1000000L
           +end.tv_usec) - start.tv_usec
          );
        
        printf("Finished Test 2, displaying queue.\n");
        handler->Queue.displayQueue();
        
	return 0;
}