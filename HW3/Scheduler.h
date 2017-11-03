/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Scheduler.h
 * Author: johnyates
 *
 * Created on October 18, 2017, 10:52 AM
 */

using namespace std;

#include "Process.h"
#include "Event.h"
#include <queue>
#include <map>
#include <unordered_map>

#ifndef SCHEDULER_H
#define SCHEDULER_H

class Scheduler {
public:
    Scheduler();
    Scheduler(const Scheduler& orig);
    virtual ~Scheduler();
    void handleEvent(Event* e);
    void handleProcArrival(Event* e);
    void handleCPUCompletion(Event* e);
    void handleIOCompletion(Event* e);
    void handleTimerExpiration(Event* e);
    void schedule();
    void popProcQueue();
    void printProcessTable();
  
    int CPUState;
    int preemptive;
    int clock;
    Process* process;
    
    /* Priority field comparison */
    struct LowerProcessPriority {
        bool operator()(Process* left, Process* right) {
            return left->priority < right->priority;
        }
    };
    
    /* Comparison for arrival time */
    struct LowerEventPriority {
        bool operator()(Event* left, Event* right) {
            return left->arrived > right->arrived;
        }
    };
    
    priority_queue<Process*, vector<Process*>, LowerProcessPriority> processQueue;
    priority_queue<Event*, vector<Event*>, LowerEventPriority> eventQueue;
    
    unordered_map<int, Process*> processTable;
    
    class ProcessNotFoundException {};
    class Underflow {};
private:

};

#endif /* SCHEDULER_H */

