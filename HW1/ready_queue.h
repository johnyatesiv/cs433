// John Yates
// 8/30/2017
// CS433 HW1
// 
// This file is the header file for the ReadyQueue class, which is utilized
// to store PCB objects by the PCB handler class. It contains methods to insert and
// remove PCB objects, as well as to display its contents. Also included are exception
// classes which can be used for Out of Range and Underflow conditions.
//=======================================================

#include "pcb.h"

class ReadyQueue {
  
 private:
 public:
    PCB *Front;       // pointer to the front node
    PCB *Rear;        // pointer to the rear node
    int Count;        // counter for the number of nodes
    // Exception handling classes 
    class Underflow{}; // Thrown when the list Underflows
    class OutOfRange{};  // Thrown when the specified Process is out of range

    ReadyQueue();     // constructor to create a list object
    ~ReadyQueue();     // destructor to destroy all nodes
    
    /* Required Queue Methods */
    void insertProc(PCB *proc);
    
    void removeHighestProc(PCB *proc);
    
    int size();
    
    void displayQueue();
    
    /* Extra Methods */
    
    //Checks to see if this Front and Rear point to NULL and Count == 0
    bool isEmpty();
    
    bool isInQueue(int id);
};
