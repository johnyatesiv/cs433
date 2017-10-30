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
    return ranInt(30, 100);
}

void Process::print() {
    printf("\nID    |Priority   | Start\n");
    printf("%i", this->id);
    printf("        ");
    printf("%i", this->priority);
    printf("        ");
    printf("%i", this->start);
}