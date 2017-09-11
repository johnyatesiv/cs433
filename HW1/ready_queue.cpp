// ====================================================
// John Yates
// 8/30/2017
// CS433 HW1
// This file is the implementation file for the ReadyQueue class, which is utilized
// to store PCB objects by the PCB handler class. It contains methods to insert and
// remove PCB objects, as well as to display its contents. Also included are exception
// classes which can be used for Out of Range and Underflow conditions.
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

/*
 * insertProc
 * Adds a PCB to the Queue 
 * 
 */
void ReadyQueue::insertProc(PCB *proc) {
    if(this->isEmpty()) {
        //cout << "Inserting proc, empty case." << endl;
        this->Front = proc;
        this->Rear = proc;
        this->Count++;
    } else {
        //cout << "Nonempty case: Queue size is " << this->Count << endl;
        PCB* next = this->Front;
        PCB* prev = next;

        do {
//            cout << proc << " | " <<next << endl;
            if(proc->getPriority() < next->getPriority()) {
                break; // exit and insert
            } else {
                prev = next;
                next = next->Next;   
            }
        } while(next != NULL);

        proc->Next = next;
        
        if(proc->getPriority() < this->Front->getPriority()) {
            this->Front = proc;
        } else {
            prev->Next = proc;
        }
        
        this->Count++;
    }
}

/*
 * removeHighestProc
 * 
 * Removes and returns highest priority PCB (SHOULD ALWAYS BE FRONT NODE!)
 */

void ReadyQueue::removeHighestProc(PCB *proc) {
    // set the active node to the front node and the removal target to the front node
    if(!this->isEmpty()) {
        /* Single node case, null the front and rear and pass the node back*/
        if(this->Count == 1) {
            proc = this->Front;
            this->Front = NULL;
            this->Rear = NULL;
        } else {
            /* More than one node, return current front and set new front */
            proc = this->Front;
            this->Front = this->Front->Next;
        }
         
       this->Count--;
    } else {
        /* Throw underflow, trying to dequeue from an empty queue */
        throw new ReadyQueue::Underflow;
    }
}

/* 
 * size
 * 
 * Calculates the number of PCBs in the Queue and returns it
 */

int ReadyQueue::size() {
    return this->Count;
}

/*
 * displayQueue
 * 
 * Displays PID and priority for each process in the queue
 */

void ReadyQueue::displayQueue() {
    cout << "[ ";
    if(!this->isEmpty()) {
        PCB *proc = this->Front;
        
        while(proc != NULL) {
            proc->print();
            proc = proc->Next;
        }
    } else {
        cout << "empty";
    }
    
    cout << " ]" << endl;
}

/*
 * isInQueue
 * 
 * Returns true if a PCB with the specified ID is in the Queue, false if not. 
 */

bool ReadyQueue::isInQueue(int id) {
    if(!this->isEmpty()) {
        PCB *proc = this->Front;
        
        while(proc != NULL) {
            if(proc->id == id) {
                return true;
            } else {
                proc = proc->Next;
            }
            
        }
        
        return false;
    } else {
        return false;
    }
}

/*
 * isEmpty
 * 
 * Returns true if Front and Rear are both pointing to NULL and Count is 0.
 * All 3 conditions must be checked.
 */

bool ReadyQueue::isEmpty() {
    return (this->Count == 0 && this->Rear == NULL && this->Front == NULL);
};
