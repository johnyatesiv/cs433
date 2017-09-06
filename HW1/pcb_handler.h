// John Yates
// 8/30/2017
// CS433 HW1
// File Summary
//=======================================================

#include "pcb.h"
#include "ready_queue.h"

class PCBHandler {
 private:
 public:
    PCB table[9999];       // Array containing PCB objects
    ReadyQueue Queue;        // Priority queue containing handle PCBs
    int Count;        // counter for the number of nodes

    PCBHandler();     // constructor to create a PCBHandler
    ~PCBHandler();     // destructor to destroy a PCBHandler
    
    /*
     * addPCB
     * 
     * Adds a PCB object to the PCBTable for loading into the ReadyQueue
     */
    void add(PCB pcb); 
    
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
    PCB get(int id);
    
    /*
     * getHighestPriority
     * 
     * Returns the highest priority PCB known to the PCBHandler
     */
    PCB getHighestPriority();
};


