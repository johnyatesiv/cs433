/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ready_queue.h"
#include "pcb_table.h"
#include "pcb_handler.h"

PCBHandler::PCBHandler();     // constructor to create a list object
PCBHandler::~PCBHandler();     // destructor to destroy all nodes

void PCBHandler::addPCB(PCB) {
    this->Queue->addProc(PCB);
}

void PCBHandler::removePCB(id) {
    this->Queue->removeProc(id);
    // iterate over procs in table and remove when id match
}

PCB PCBHandler::getPCB(id) {
    // iterate over procs in table and return id match
}

PCB PCBHandler::getHighestPriority() {
    // iterate over procs in table and return highest priority found
}