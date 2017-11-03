/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Scheduler.cpp
 * Author: johnyates
 * 
 * Created on October 18, 2017, 10:52 AM
 */

#include <stdio.h>
#include <queue>
#include <map>
#include "Scheduler.h"
#include "Event.h"
#include "Process.h"

Scheduler::Scheduler() {
    this->preemptive = 0;
    this->CPUState = 0;
}

Scheduler::Scheduler(const Scheduler& orig) {
    
}

Scheduler::~Scheduler() {
    
}

void Scheduler::handleEvent(Event* e) {
    switch(e->type) {
        case 1: //process arrival
            handleProcArrival(e);
        break;
        case 2: //cpu completion
            handleCPUCompletion(e);
        break;
        case 3: //io completion
            handleIOCompletion(e);
        break;
        case 4: //timer expiration
            handleTimerExpiration(e);
        break;
    }
};

void Scheduler::handleProcArrival(Event* e) {
//    printf("\nProcess ");
//    printf("%i", e->processId);
//    printf(" Arrived!\n");
    
    this->printProcessTable();
    
    this->process = this->processTable[e->processId]; //proc = e.procId

    //this->process->print();
    this->process->nextCPUBurst(); //generate length of next CPU burst
    this->processQueue.push(this->process); //add proc to ready queue
    this->schedule(); //invoke schedule();
};

void Scheduler::handleCPUCompletion(Event* e) {
    //printf("\nCPU Complete!");
    this->process = this->processTable[e->processId];
    //printf("\nRemaining CPU Time: %i", this->process->cpuTime);
   
    //if proc has completed its total time, remove it
    if(this->process != NULL) {
        //printf("\nProcess is not null %i", this->process);
        if(this->process->cpuTime == 0) {
            //printf("\nClearing Process %i", this->process->id);
            //this->processTable.erase(this->process->id); //remove the process
            this->processTable[this->process->id]->finish = this->clock;
            this->process = NULL;
            this->popProcQueue();
            //printf(" Next: %i", this->process->id);
        } else {
            this->process->adjustCPUTime(e->burst);
            //printf("\nScheduling IO Burst for ");
            //printf("%i", this->process->id);
            int burst;
            burst = this->process->IOBurst(); //generate a random IO burst length
            Event* e = new Event(3, this->clock+burst, burst, this->process->id);
            this->eventQueue.push(e); //add the new event into Event Queue   
        }
    }
    
    this->CPUState = 0; //then set CPU state to idle
    this->schedule(); //invoke schedule()
}

void Scheduler::handleIOCompletion(Event* e) {
    //printf("\nIO Complete!");
    this->process = this->processTable[e->processId]; //proc = e.procId
    this->process->ioTime = this->process->ioTime + e->burst;
    //generate length of next CPU burst
    //Decrement the CPU time by a random burst
    this->processQueue.push(this->process); //add the proc to the ready queue
    this->schedule(); //invoke schedule()
    
}

void Scheduler::handleTimerExpiration(Event* e) {
    //printf("\nTimer Expired :(");
    this->process = this->processTable[e->processId]; //proc = e.procId
    //move running proc to ready queue and update its burst length
    this->processQueue.push(this->process);
    this->CPUState = 0; //CPU state = idle
    this->schedule(); //invoke schedule()
}

void Scheduler::schedule() {
    //printf("\n\nScheduling...\n");
    if(!this->processQueue.empty()) {
        int burst = this->process->nextCPUBurst();
        
        if(!this->CPUState) { //cpu is idle*
            this->popProcQueue(); //select and dispatch a proc from ready queue
            //printf("\nPushing CPU Completion Event for Process %i", this->process->id);
            //printf("%i", this->process->id);
            Event* e = new Event(2, this->clock+burst, burst, this->process->id);
            this->eventQueue.push(e); //create a CPU completion event and add the new event into Event Queue
        } else if(this->preemptive) { //preemptive mode
            this->processQueue.push(this->process); //move the running proc to ready queue
            this->popProcQueue(); //dispatch a proc from ready queue
            //printf("\nPushing CPU Completion Event (Preemptive).\n");
            Event* e = new Event(2, this->clock+burst, burst, this->process->id);
            this->eventQueue.push(e); //create a CPU completion event and add the new event into Event Queue
        }
    }
}

/*
 * Retrieves top of process queue and pops the element out 
 */
void Scheduler::popProcQueue() {
    //printf("\nPopping Proc Queue which has size %i", this->processQueue.size());
    if(!this->processQueue.empty()) {
        this->process = this->processQueue.top(); //select and dispatch a proc from ready queue
        this->processQueue.pop();
    } else {
        //printf("\nDidn't pop!");
    }
}

void Scheduler::printProcessTable() {
    for(auto it = this->processTable.begin(); it != this->processTable.end(); ++it) {
        //std::cout << " " << it->first << ":" << it->second;   
        printf("%i", it->first);
        printf("\n");
    }
}