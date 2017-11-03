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
#include <sstream>
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
    
    if(string(argv[1]) == "fcfs") {
        printf("Using the FCFS algorithm!");
        FCFSScheduler scheduler;
    } else if(string(argv[1]) == "sjf") {
        printf("Using the SJF algorithm!");
        SJFScheduler scheduler;
    } else if(string(argv[1]) == "srtf") {
        printf("Using the SRTF algorithm!");
        SRTFScheduler scheduler;
    } else {
        printf("Using the FCFS algorithm!");
        FCFSScheduler scheduler;
    }
    
    istringstream ss(argv[2]);
    int processes;
    if (!(ss >> processes)) {
        cerr << "Invalid number " << argv[2] << '\n';
        return 0;
    }
    
    //int run = false; //Loop flag
    int clock = 0; //Clock counter
    int endClock = 300001;
    
    // generate some process arrival events
    for(int i = 0; i < processes; i++) {
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
        //e->print();
        /* Set the Clock to the Event Arrival Time */
        //printf("Updating clock from %i ", clock);
        //printf("to %i", e->arrived);
        clock = e->arrived;
        scheduler.clock = clock;
        
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
    int totalWait = 0;
    int temp = 0;
    
    for(auto it = scheduler.processTable.begin(); it != scheduler.processTable.end(); ++it) {
        //std::cout << " " << it->first << ":" << it->second;   
        printf("\nProcess %i:", it->second->id);
        printf("\nArrival Time: %i milliseconds", it->second->start);
        printf("\nFinish Time: %i milliseconds", it->second->finish);
        printf("\nIO Time: %i milliseconds", it->second->ioTime);
        printf("\nWait Time: %i milliseconds", it->second->waitingTime());
        printf("\n");
        
        if(it->second->finish > 0) {
            temp = it->second->finish - it->second->start;
            totalTime = totalTime + temp;
            temp = it->second->waitingTime();
            totalWait = totalWait + temp;
            numProc++;
        }
    }
    
    printf("Total wait: %i", totalWait);
    
    int avgTurnAround = totalTime/numProc;
    int avgWait = totalWait/numProc;
    int throughput = (numProc*100000)/endClock;
    int cpuUtilization = (((endClock - avgWait)*100)/endClock);
    
    printf("\n\nJobs Completed: %i", numProc);
    printf("\nAverage Turnaround Time: %i milliseconds", avgTurnAround);
    printf("\nAverage Wait Time: %i milliseconds", avgWait);
    printf("\nThroughput: 0.0%i jobs/millisecond", throughput);
    printf("\nCPU Utilization: %i\n", cpuUtilization);
    
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
