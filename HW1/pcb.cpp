// John Yates
// 8/30/2017
// CS433 HW1
//
// This file is the implementation file for the PCB class, which represents a Process in the OS.
// It contains descriptive variables as well as a method to print itself.
//=======================================================

using namespace std;
#include <iostream>
#include "pcb.h"

/*
 * Constructor
 */
PCB::PCB(int priority, int id) {
    this->priority = priority;
    this->id = id;
    this->Next = NULL;
}

/*
 * Copy Constructor
 */

PCB::PCB(const PCB& orig) {
    
}

/*
 * Destructor
 */
PCB::~PCB() {
    
}

/*
 * print
 * 
 * This method displays the PID, Priority and address of Next node of the calling PCB object.
 */

void PCB::print() {
    cout << "{PID:" << this->id << "|PRI:" << this->priority << "|Next:" << this->Next << "},";
}

int PCB::getPriority() {
    return this->priority;
}