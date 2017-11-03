/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Event.cpp
 * Author: johnyates
 * 
 * Created on October 11, 2017, 10:08 AM
 */

#include <stdio.h>
#include "Event.h"

/* Constructor for Process Arrival Event */
Event::Event() {
    this->type = 1;
    this->arrived = ranInt(0, 300000);
    this->processId = ranInt(0, 9999);
    //printf("\nProcess Arrival Event created! PID: %i", this->processId);
}

/* Constructor for other Event Types */
Event::Event(int type, int arrived, int burst, int pid) {
    this->type = type;
    this->arrived = arrived;
    this->burst = burst;
    this->processId = pid;
    //printf("\nType %i", this->type);
    //printf(" Event created for PID: %i", this->processId);
}

Event::Event(Event* orig) {
}

Event::~Event() {
}

void Event::print() {
    printf("\nType: %i Event", this->type);
    printf("\nPID: %i", this->processId);
    printf("\nArrived: %i", this->arrived);
}