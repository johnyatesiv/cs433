// John Yates
// 8/30/2017
// CS433 HW1
//
// This file is the implementation file for the PCBHandler class, which is utilized
// to manage PCB objects. It contains methods to insert and remove PCB objects
// from a Unordered Map and a Priority Queue. This class is intended as a wrapper class
// for the Queue and table in order to allow for single function calls for common actions
// requiring multiple steps.
//=======================================================

using namespace std;
#include <random>
#include <unordered_map>
#include <iostream>
#include "pcb_handler.h"

PCBHandler::PCBHandler() { // constructor to create a list object
    //PCB *table = *PCB[9999];
}


PCBHandler::~PCBHandler() { // destructor to destroy all nodes
    
}

/*
 * add
 * 
 * Inserts an new PCB object into the ReadyQueue as well as the PCBTable.
 * 
 */
void PCBHandler::add(PCB *proc) {
    Queue.insertProc(proc);
    //push to table
    Table.insert(make_pair(proc->id, proc));
}

/*
 * remove
 * 
 * Permanently removes a process from both the Queue and the table.
 * 
 */
void PCBHandler::remove(int id) {
    // Remove proc with id from Queue
    // iterate over procs in table and remove when id match
}

/*
 * get
 * 
 * Finds and returns an element at the specified index in the table.
 */
PCB PCBHandler::get(int id) {
    // iterate over procs in table and return id match
}

/*
 * queueEmpty
 * 
 * Wrapper method for Queue.isEmpty()
 * 
 */
bool PCBHandler::queueEmpty() {
    cout << "is Empty? " << Queue.isEmpty() << endl;
    return Queue.isEmpty();
}

/*
 * showTable
 * 
 * Iterates through the table and prints the details of each element.
 * 
 */
void PCBHandler::showTable() {
    cout << "|Key   |Value  |\n";
    for( const auto& entry : this->Table ) {
        cout << "|" << entry.first << "|" << entry.second << "|\n";
    }
}

/*
 * randomFromTable
 * 
 * Selects a random index from 0 to the highest index and passes the element at that index back by reference.
 * 
 */
void PCBHandler::randomFromTable(PCB *proc) {
    double random;
    int randomInt;
    
    std::unordered_map<int, PCB*>::const_iterator found;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0, Table.size());
    
    random = dis(gen);
    randomInt = (int) random;
    
    found = Table.find(random);
    cout << found->first << " is " << found->second << endl;
    found->second->print();
    cout << "Segfault?" << endl;
    
    proc = found->second;
    
    cout << "Segfault again?" << endl;
    
    //TODO segfault after this point in test
}