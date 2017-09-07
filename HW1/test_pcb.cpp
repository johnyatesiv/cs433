#include <stdio.h>
#include "test.h"
#include "pcb_handler.h"
#include <stdio.h>      /* printf */
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */

int main(int argc, char* argv[]) {
	printf("----CS 433 Assignment 1----\n");
	printf("Group memebers: ??? \n");
        
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
        handler->add(pid5);
        handler->add(pid1);
        handler->add(pid8);
        handler->add(pid11);
        
        /* Display Queue, should be ordered 1, 5, 8, 11 */
        handler->showQueue();
        
        /* Remove highest priority */
        handler->removeHighestPriority();
        
        /* Redisplay, should be ordered 5, 8, 11 */
        handler->showQueue();
        
        /* Add PID 3, 7, 2, 12, 9 */
        handler->add(pid3);
        handler->add(pid7);
        handler->add(pid2);
        handler->add(pid12);
        handler->add(pid9);
       
        /* Redisplay, should be ordered 2, 3, 5, 7, 8, 9, 11, 12 */
        handler->showQueue();
        
        /* Iterate over the remaining processes and display each time */
        while(!handler->queueEmpty()) {
            handler->removeHighestPriority();
            handler->showQueue();
        }
        
        
        /* Test 2 */
        
        /* Select 10 random PCB objects from the existing Handler's table and reassign a random priority between 1 and 50 */
        
        int i = 0;
//        int max = 1000000;
        int max = 10;
        
        /* Benchmark start */
//        struct timeval start;
//        struct timeval end;
//
//        gettimeofday(&start, NULL);
        time_t start = time(0);
        
        
        while(i != max) {
            /* Random 50/50 chance to either */
//            if(case1) {
//                /* Remove a process */
//                handler->removeHighestPriority();
//            } else {
//                /* If there is a process in the table READY state not in the queue, insert it */
//                /* Before inserting, randomize its priority between 1 and 50 */
//                /* If the process is in the queue already, do not reinsert it */
//            }
            
            i++;
            printf("%f", i);
        }
        
        /* Benchmark finish */
//        gettimeofday(&end, NULL);
//        
//        uint64 time = start.tv_usec - end.tv_usec;
        
        time_t end = time(0);
        double time = difftime(end, start) * 1000.0;
        
        printf("Ran in ");
        printf("%f", time);
        printf("microseconds.");
        
	return 0;
}

