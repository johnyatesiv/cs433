// John Yates
// 8/30/2017
// CS433 HW1
//
// This file is the header file for the PCBHandler class, which is utilized
// to manage PCB objects. It contains methods to insert and remove PCB objects
// from a Unordered Map and a Priority Queue. This class is intended as a wrapper class
// for the Queue and table in order to allow for single function calls for common actions
// requiring multiple steps.
//=======================================================

using namespace std;
#include "ready_queue.h"
#include "pcb_table.h"

class PCBHandler {
 private:
 public:
    PCBTable Table;
    //PCB *table[9999];       // Array containing PCB objects
    ReadyQueue Queue;        // Priority queue containing handle PCBs
    int Count;        // counter for the number of nodes

    PCBHandler();     // constructor to create a PCBHandler
    ~PCBHandler();     // destructor to destroy a PCBHandler
    
    /*
     * addPCB
     * 
     * Adds a PCB object to the PCBTable for loading into the ReadyQueue
     */
    void add(PCB *proc); 
    
    /*
     * removePCB
     * 
     * Removes a PCB object by ID from the PCB Table
     */
    void remove(int id);
    
    
    /*
     * getPCB
     * 
     * Returns a PCB object specified by the ID parameter
     */
    PCB* get(int id);
    
    /*
     * getHighestPriority
     * 
     * Returns the highest priority PCB known to the PCBHandler
     */
    PCB *removeHighestPriority();
    
    /* Calls the Queue for its function to check if empty */
    bool queueEmpty();
    
    void showTable();
    
    PCB* randomFromTable();
};


