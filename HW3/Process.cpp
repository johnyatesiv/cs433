/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Process.cpp
 * Author: johnyates
 * 
 * Created on October 11, 2017, 10:26 AM
 */

#include <stdio.h>
#include "Process.h"

Process::Process() {
    
}

Process::Process(Event* e) {
    this->id = e->processId; // unique id for reference by other processes
    this->start = e->arrived; // start time
    this->initCpuTime = ranInt(1000, 60000);
    this->cpuTime = this->initCpuTime;
    this->avgCpuBurst = ranInt(5, 100);
    this->priority = ranInt(1, 50);
    this->status = 1; //ready state
    this->finish = -1;
    this->runTime = 0; //total running time tally
}

Process::Process(Process* orig) {
    
}

Process::~Process() {}

int Process::nextCPUBurst() {
    static long n = -10;
    //static long n = time(NULL);
    float x = poidev((float) this->avgCpuBurst, &n);
    return (int) x;
}

int Process::IOBurst() {
    int io = ranInt(30, 100);
    this->ioTime = this->ioTime + io;
    return io;
}

void Process::adjustCPUTime() {
    //printf("\nAdjusting CPU time %i ", this->cpuTime);
    int next = this->nextCPUBurst();
    //printf(" - %i ", next);
    this->cpuTime = this->cpuTime - next;
    if(this->cpuTime < 0) {
        this->cpuTime = 0;
    }
    
    this->runTime = this->runTime + next;
    
    //printf(" = %i", this->cpuTime);
}

void Process::adjustCPUTime(int burst) {
    //printf("\nAdjusting CPU time %i ", this->cpuTime);
    //printf(" - %i ", burst);
    this->cpuTime = this->cpuTime - burst;
    if(this->cpuTime < 0) {
        this->cpuTime = 0;
    }
    
    this->runTime = this->runTime + burst;
    
    //printf(" = %i", this->cpuTime);
}

int Process::turnAroundTime() {
    return this->finish - this->start;
}

int Process::waitingTime() {
    return this->turnAroundTime() - this->runTime;
}

void Process::print() {
    printf("\nID    |Priority   | Start\n");
    printf("%i", this->id);
    printf("        ");
    printf("%i", this->priority);
    printf("        ");
    printf("%i", this->start);
}