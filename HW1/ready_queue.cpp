// ====================================================
// John Yates
// 8/30/2017
// CS433 HW1
// File Summary
//=====================================================

using namespace std;
#include <iostream>
#include "ready_queue.h"

// Constructor
// Initialize Front and Rear to be NULL and Count = 0.
// This does not create any node.  The new list is empty.
ReadyQueue::ReadyQueue() {
    this->Front = NULL;
    this->Rear = NULL;
    this->Count = 0;
};

// Linked List Destructor
// While the list is not empty, call deleteFront repeatedly to delete all nodes.
// Place a cout in this function "calling the ReadyQueue destructor."
ReadyQueue::~ReadyQueue() {
    //PCB *x; //Holder for integers removed by deleteFront()
    cout << "Calling the ReadyQueue destructor." << endl;
//    while(!this->isEmpty()) {
//       this->delete(x);
//    }
};

/* Required Methods */

/* Adds a PCB to the Queue */
void ReadyQueue::insertProc(PCB *proc) {
    proc->Next = this->Front;
    this->Front = proc;
    if(this->isEmpty()) {
        this->Front = proc;
        this->Rear = proc;
    } else {
        PCB* activePCB = this->Front;
        PCB* nextPCB = activePCB->Next;
        
        for(int i=1; i<this->Count; i++) {
            if(nextPCB == NULL) {
                activePCB->Next = proc;
            } else if(activePCB->priority > nextPCB->priority) {
                activePCB->Next = proc;
                proc->Next = nextPCB;
                return;
            } else {
                activePCB = nextPCB;
                nextPCB = activePCB->Next;
            }
        }
    }
}

/* Removes and returns highest priority PCB */
PCB *ReadyQueue::removeHighestProc() {
    PCB* activePCB = this->Front;
    PCB* removedPCB = activePCB;

    for(int i=1; i<this->Count; i++) {
        if(activePCB->priority > removedPCB->priority) {
            // the active PCB is higher priority than the currently selected, update
            removedPCB = activePCB;
            activePCB = activePCB->Next;
        } else {
            activePCB = activePCB->Next;
        }
    }
    
    return removedPCB;
}

/* Calculates the number of PCBs in the Queue and returns it */
int ReadyQueue::size() {
    
}

/* Displays ID and priority for each process in the queue */
void ReadyQueue::displayQueue() {
    cout << "[ ";
    if(!this->isEmpty()) {
        PCB *proc = this->Front;
        int i = 0;
        while(i != this->Count) {
            cout << proc->id << " " << proc->priority << "\n";
            proc = proc->Next;
            i++;
        }
    } else {
        cout << "empty ";
    }
    
    cout << "]" << endl;
}

// Return true if Front and Rear are both pointing to NULL and Count is 0.
// All 3 conditions must be checked.
bool ReadyQueue::isEmpty() {
    return (this->Rear == NULL && this->Front == NULL && this->Count == 0);
};
