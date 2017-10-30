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
#include "Event.h"
#include "FCFSScheduler.h"
#include "SJFScheduler.h"
#include "SRTFScheduler.h"
#include "RRScheduler.h"

using namespace std;

void printClock(int clock) {
    printf("Clock: ");
    printf("%i", clock);
    printf("\n");
}

/*
 * 
 */
int main(int argc, char** argv) {
    // pass arguments to get different scheduling algorithms, instantiate appropriate scheduler
    FCFSScheduler scheduler;
    srand(time(NULL)); // seed random function
    
    //int run = false; //Loop flag
    int clock = 0; //Clock counter
    int endClock = 300001;
    
    // generate some events
    for(int i = 0; i < 10; i++) {
        /* Instantiate a Process Arrival Event */
        Event* rEvent = new Event(1);
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
        e = scheduler.eventQueue.top();
        e->print();
        /* Set the Clock to the Event Arrival Time */
        clock = e->arrived;
        printClock(clock);
        /* Handle the next Event */
        scheduler.handleEvent(e);
        printf("\nEventQ size: ");
        printf("%i", scheduler.eventQueue.size());
        printf("\n");
        scheduler.eventQueue.pop(); // remove from queue
        //update stats
    }
    
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
