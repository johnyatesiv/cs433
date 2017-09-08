/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pcb.cpp
 * Author: johnyates
 * 
 * Created on August 30, 2017, 1:36 PM
 */

using namespace std;
#include <iostream>
#include "pcb.h"

PCB::PCB(int priority, int id) {
    this->priority = priority;
    this->id = id;
    this->Next = NULL;
}

PCB::PCB(const PCB& orig) {
    
}

PCB::~PCB() {
    
}

void PCB::print() {
    cout << "{PID:" << this->id << "|PRI:" << this->priority << "|Next:" << this->Next << "},";
}

int PCB::getPriority() {
    return this->priority;
}