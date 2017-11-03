/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: johnyates
 *
 * Created on October 10, 2017, 5:41 PM
 */

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include "Event.h"
#include "FCFSScheduler.h"
#include "SJFScheduler.h"
#include "SRTFScheduler.h"
#include "RRScheduler.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    // pass arguments to get different scheduling algorithms, instantiate appropriate scheduler
    FCFSScheduler scheduler;
    
    if(argv[1] == "fcfs") {
        printf("Using the FCFS algorithm!");
        FCFSScheduler scheduler;
    } else if(argv[2] == "sjf") {
        printf("Using the SJF algorithm!");
        SJFScheduler scheduler;
    } else if(argv[3] == "srtf") {
        printf("Using the SRTF algorithm!");
        SRTFScheduler scheduler;
    } else {
        printf("Using the FCFS algorithm!");
        FCFSScheduler scheduler;
    }
    
    srand(time(NULL)); // seed random function
    
    //int run = false; //Loop flag
    int clock = 0; //Clock counter
    int pastClock = 0;
    int endClock = 300001;
    
    // generate some events
    for(int i = 0; i < 20; i++) {
        /* Instantiate a Process Arrival Event */
        Event* rEvent = new Event();
        /* Instantiate the process the event describes */
        Process* rProcess = new Process(rEvent);
        //rProcess->print();
        /* Index the process */
        scheduler.processTable.insert(pair<int,Process*>(rProcess->id, rProcess));
        /* Add the event to the EventQueue*/
        scheduler.eventQueue.push(rEvent);
    }
    
    Event* e;
    
    while(clock < endClock && !scheduler.eventQueue.empty()) {
        /* Get the next Event in EventQueue */
        //printf("\nFetching Event...");
        e = scheduler.eventQueue.top();
        e->print();
        /* Set the Clock to the Event Arrival Time */
        printf("Updating clock from %i ", clock);
        printf("to %i", e->arrived);
        clock = e->arrived;
        scheduler.clock = clock;
        if(clock != pastClock) {
            printf("\nClock: %i", clock);
            pastClock = clock;
        }
        /* Handle the next Event */
        scheduler.handleEvent(e);
//        printf("\nEventQ size: ");
//        printf("%i", scheduler.eventQueue.size());
//        printf("\nProcQ size: ");
//        printf("%i", scheduler.processQueue.size());
        scheduler.eventQueue.pop(); // remove from queue
        //update stats
        //sleep(2);
    }
    
    int numProc = 0;
    int totalTime = 0;
    int temp = 0;
    
    for(auto it = scheduler.processTable.begin(); it != scheduler.processTable.end(); ++it) {
        //std::cout << " " << it->first << ":" << it->second;   
        printf("\nProcess %i:", it->second->id);
        printf("\nArrival Time: %i milliseconds", it->second->start);
        printf("\nFinish Time: %i milliseconds", it->second->finish);
        printf("\nIO Time: %i milliseconds", it->second->ioTime);
        printf("\n");
        
        if(it->second->finish > 0) {
            temp = it->second->finish - it->second->start;
            totalTime = totalTime + temp;
            numProc++;
        }
    }
    
    int avgTurnAround = totalTime/numProc;
    int throughput = numProc/endClock;
    printf("\n\n\n\nAverage Turnaround Time: %i milliseconds", avgTurnAround);
    printf("\nThroughput: %i jobs/millisecond\n", throughput);
    
    return 0;
}


//Shortest Remaining Time Next:
//Process 1:
//arrival time: 0 s
//finish time: 45 s
//service time: 32 s
//I/O time: 3.0 s
//turnaround time: 45 s
//waiting time: 10s
//Process 2:
//arrival time: 5 s
//finish time: 140 s
//...
//CPU Utilization is 100%
//Throughput is 1.5 jobs / s
//Average turnaround time: 35.3 s
