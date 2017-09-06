/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "pcb_handler.h"

PCBHandler::PCBHandler() { // constructor to create a list object
    
}

PCBHandler::~PCBHandler() { // destructor to destroy all nodes
    
}

void PCBHandler::add(PCB proc) {
    this->Queue.insertProc(proc);
}

void PCBHandler::remove(int id) {
    // Remove proc with id from Queue
    // iterate over procs in table and remove when id match
}

PCB PCBHandler::get(int id) {
    // iterate over procs in table and return id match
}