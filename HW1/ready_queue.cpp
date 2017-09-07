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
    if(this->isEmpty()) {
        cout << "Inserting proc, empty case." << endl;
        this->Front = proc;
        this->Rear = proc;
        this->Count++;
    } else {
        cout << "Nonempty case: Count is at " << this->Count << endl;
        PCB* activePCB = this->Front;
        PCB* nextPCB = activePCB->Next;
        
        int exit = 0;
        
        while(exit != 1) {
            if(nextPCB == NULL) {
                cout << "Inserting proc, encountered end of queue." << endl;
                activePCB->Next = proc;
                this->Rear = proc;
                this->Count++;
                exit = 1;
            } else {
                if(activePCB->priority > nextPCB->priority) {
                    //Needs to set activePCB to Front?
                    cout << "Inserting proc, encountered priority slot." << endl;
                    activePCB->Next = proc;
                    proc->Next = nextPCB;
                    this->Count++;
                    exit = 1;
                } else {
                    cout << "Iterating." << endl;
                    activePCB = nextPCB;
                    nextPCB = activePCB->Next;
                }   
            }
        }
    }
}

/* Removes and returns highest priority PCB */
PCB *ReadyQueue::removeHighestProc() {
    // set the active node to the front node and the removal target to the front node
    PCB* activePCB = this->Front;
    PCB* removedPCB = activePCB;

    for(int i=1; i<this->Count; i++) {
        if(activePCB->priority > removedPCB->priority) {
            cout << "Changing removal target.";
            // the active PCB is higher priority than the currently selected, update
            removedPCB = activePCB;
            activePCB = activePCB->Next;
        } else {
            // it is not, keep iterating
            activePCB = activePCB->Next;
        }
    }
    
    return removedPCB;
}

/* Calculates the number of PCBs in the Queue and returns it */
int ReadyQueue::size() {
    return this->Count;
}

/* Displays ID and priority for each process in the queue */
void ReadyQueue::displayQueue() {
    cout << "[ ";
    if(!this->isEmpty()) {
        PCB *proc = this->Front;
        int i = 0;
        while(i != this->Count) {
            cout << "{PID:" << proc->id << "|PRI:" << proc->priority << "},";
            proc = proc->Next;
            i++;
        }
    } else {
        cout << "empty ";
    }
    
    cout << " ]" << endl;
}

// Return true if Front and Rear are both pointing to NULL and Count is 0.
// All 3 conditions must be checked.
bool ReadyQueue::isEmpty() {
    //cout << "Rear: " << this->Rear << " | Front: " << this->Front << " | Count: " << this->Count << endl;
    return (this->Rear == NULL && this->Front == NULL && this->Count == 0);
};
