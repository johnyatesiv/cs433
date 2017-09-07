/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

using namespace std;
#include <iostream>
#include "pcb_handler.h"

PCBHandler::PCBHandler() { // constructor to create a list object
    //PCB *table = *PCB[9999];
}


PCBHandler::~PCBHandler() { // destructor to destroy all nodes
    
}

void PCBHandler::add(PCB *proc) {
    Queue.insertProc(proc);
    //push to table
}

void PCBHandler::remove(int id) {
    // Remove proc with id from Queue
    // iterate over procs in table and remove when id match
}

PCB PCBHandler::get(int id) {
    // iterate over procs in table and return id match
}

void PCBHandler::showQueue() {
    Queue.displayQueue();
}

bool PCBHandler::queueEmpty() {
    cout << "is Empty? " << Queue.isEmpty() << endl;
    return Queue.isEmpty();
}

PCB *PCBHandler::removeHighestPriority() {
    return Queue.removeHighestProc();
}