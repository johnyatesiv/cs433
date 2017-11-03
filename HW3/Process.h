/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Process.h
 * Author: johnyates
 *
 * Created on October 11, 2017, 10:26 AM
 */

#include <stdlib.h>
#include <time.h>
#include "randomLib.h"
#include "Event.h"

#ifndef PROCESS_H
#define PROCESS_H

class Process {
public:
    Process();
    Process(Event* e);
    Process(Process* orig);
    virtual ~Process();
    int id; // unique id for reference by other processes
    int start; // random over 5 minutes, from event
    int initCpuTime; // starting CPU time, random between 1 sec and 1 min
    int cpuTime; // remaining CPU burst duration
    int avgCpuBurst; //set at instantiation, between 5 and 100ms
    int priority; //used by queue
    int status; // ready, running, waiting or terminated
    int finish;
    int ioTime;
    int runTime;
    
    int turnAroundTime();
    int waitingTime();
    int nextCPUBurst(); //random, code for function provided on CC
    int IOBurst(); //random between 30 and 100ms
    void adjustCPUTime(); // decrements the remaining cpu time by a random burst from nextCPUBurst()
    void adjustCPUTime(int burst);
    void print(); // prints object stats
private:

};

#endif /* PROCESS_H */

