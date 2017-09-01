// John Yates
// 8/30/2017
// CS433 HW1
// File Summary
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
  
    //Checks to see if this Front and Rear point to NULL and Count == 0
    bool isEmpty();
    
    //Displays all elements or [empty] if isEmpty() is true
    void displayAll();

    //**
    void addFront(PCB);
    
    //**
    void addRear(PCB);

    //**
    void deleteFront(PCB&);

    //**
    void deleteRear(PCB&);

    //**
    void deleteIth(int, PCB&);

    //**    
    void addbeforeIth(int, PCB);
};
