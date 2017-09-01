// John Yates
// 8/30/2017
// CS433 HW1
// File Summary
//=======================================================

class PCBHandler {
 private:
 public:
    PCB table[9999];       // pointer to the front node
    ReadyQueue Queue;        // pointer to the rear node
    int Count;        // counter for the number of nodes

    PCBHandler();     // constructor to create a list object
    ~PCBHandler();     // destructor to destroy all nodes
    
    void addPCB(PCB);
    
    void removePCB(id);
    
    PCB getPCB(id);
    
    PCB getHighestPriority()
};


