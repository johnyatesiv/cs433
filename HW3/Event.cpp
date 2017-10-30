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

Event::Event() {
}

Event::Event(int type) {
    this->type = type;
    this->arrived = ranInt(0, 300000);
    this->processId = ranInt(0, 9999);
    printf("\nEvent created! ");
    printf("PID: ");
    printf("%i", this->processId);
}

Event::Event(Event* orig) {
}

Event::~Event() {
}

void Event::print() {
    printf("Type: ");
    printf("%i", this->type);
    printf("\n");
    printf("Arrived: ");
    printf("%i", this->arrived);
    printf("\n");
}