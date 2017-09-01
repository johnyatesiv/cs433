// ====================================================
// John Yates
// 8/30/2017
// CS433 HW1
// File Summary
//=====================================================

using namespace std;

#include <iostream>
#include "ready_queue.h"
#include "pcb.h"

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
    int x; //Holder for integers removed by deleteFront()
    cout << "Calling the ReadyQueue destructor." << endl;
    while(!this->isEmpty()) {
        this->deleteFront(x);
    }
};

// Return true if Front and Rear are both pointing to NULL and Count is 0.
// All 3 conditions must be checked.
bool ReadyQueue::isEmpty() {
    return (this->Rear == NULL && this->Front == NULL && this->Count == 0);
};

// displayAll() should show all the elements of the list, or output empty if there are none.
// Regular: displays each element of the list horizontally starting from Front in [ ].
// Special case: if the list is empty, display [ empty ] ).
void ReadyQueue::displayAll() {
    cout << "[ ";
    if(!this->isEmpty()) {
        PCB *aNode = this->Front;
        int i = 0;
        while(i != this->Count) {
            cout << aNode->Elem << " ";
            aNode = aNode->Next;
            i++;
        }
    } else {
        cout << "empty ";
    }
    
    cout << "]" << endl;
};

// addRear() will add an element to the end of the list and update the pointers.
// Regular case: adds a new node at the rear and puts newNum in the Elem field
// of this new node. Count is updated.
// Special case: if this is going to be the very first node, you must create 
// a new node and make Front and Rear point to it. Place newNum and Count is updated.

void ReadyQueue::addRear(el_t newNum) {     
    if(!this->isEmpty()) {
        PCB *newNode;
        newNode = new Node;
        Rear->Next = newNode;
        Rear = Rear->Next;
        Rear->Elem = newNum;
        Rear->Next = NULL;
        this->Count++;
    } else {
        PCB *newPCB;
        newPCB = new PCB;
        newPCB->Elem = newNum;
        this->Front = newPCB;
        this->Rear = newPCB;
        this->Count++;
    }
};

// addFront() will add an element to the front of the list and update the pointers.
// Regular case: add a new node to the front of the list and Count is updated.
// Special case: if this is going to be the very first node, you must
// create a new node and make Front and Rear point to it. Place newNum and Count is updated.

void ReadyQueue::addFront(el_t newNum) {
    if(!this->isEmpty()) {
        PCB *newPCB;
        newPCB = new PCB;
        newPCB->Next = Front;
        this->Front = newPCB;
        this->Front->Elem = newNum;
        this->Count++;
    } else {
        PCB *newPCB;
        newPCB = new PCB;
        newPCB->Elem = newNum;
        this->Front = newPCB;
        this->Rear = newPCB;
        this->Count++;
    }
};

//deleteFront() will remove the front element of the list and update the pointers.
// Error case: if the List is empty, throw Underflow.
// Regular: give back the front node element through OldNum (pass by reference)
// and also removes the front node.  Count is updated.
// Special case: if currently only one PCB,
// give back the front node element through OldNum (pass by reference) and
// make sure both Front and Rear become NULL. Count is updated.

void ReadyQueue::deleteFront(el_t& OldNum) {
    if(this->isEmpty()) {
        throw ReadyQueue::Underflow();
    } else if(this->Count != 1) {
        OldNum = Front->Elem;
        PCB *Second;
        Second = Front->Next;
        delete Front;
        Front = Second;
        this->Count--;
    } else {
        this->Front->Elem = NULL;
    }
};

// deleteRear() should delete the last element of the list and update the pointers.
// Error case: if empty, throw Underflow.
// Regular: give back the rear node element through OldNum (pass by reference)
// and also remove the rear node. Count is updated.
// Special case: if currently only one node,
// give back the rear node element through OldNum (pass by reference) and
// make sure both Front and Rear become NULL. Count is updated.

void ReadyQueue::deleteRear(el_t& OldNum) {
    if(this->isEmpty()) {
        throw ReadyQueue::Underflow();
    } else if(this->Count != 1) {
        OldNum = this->Rear->Elem;
        PCB *p = this->Front;
        
        //Make p go to the one right before rear (using while)
        while(p != this->Rear) {
            p = p->Next;
        }
        
        //delete this->Rear;
        this->Rear = p;
        this->Count--;
    } else {
        OldNum = this->Rear->Elem;
        this->Front = NULL;
        this->Rear = NULL;
        this->Count--;
    }  
};

// deleteIth() will delete the PCB at the specified index and update the pointers.
// Error case: If I is an illegal value (i.e. > Count or < 1) throw OutOfRange.
// Special case 1: this should call deleteFront when I is 1
// Special case 2: this should call deleteRear when I is Count
// Regular case: delete the Ith node (I starts out at 1).  Count is updated.
// <see the template loops in the notes to move 2 pointers to the right nodes;
// and make sure you indicate the purposes of these local pointers>

void ReadyQueue::deleteIth(int I, el_t& OldNum) {
    if(I > this->Count || I < 1) {
        throw ReadyQueue::OutOfRange();
    } else if(I == 1) {
        this->deleteFront(OldNum);
    } else if(I == this->Count) {
        this->deleteRear(OldNum);
    } else {
        PCB* activePCB = this->Front;
        PCB* removedPCB;
        
        for(int i=1; i<I; i++) {
            if(i == I-1) {
                //Identify the PCB to remove
                removedPCB = activePCB->Next;
                //Return its value in the holder
                OldNum = removedPCB->Elem;
                //Set the PCB before the removed PCB to point to the .Next of the removed
                activePCB->Next = removedPCB->Next;
                delete removedPCB;
            } else {
                activePCB = activePCB->Next;
            }
        }
        
        this->Count--;
    }
};

// addbeforeIth() will add a PCB before the specified index and update the pointers.
// Error case: If I is an illegal value (i.e. > Count+1 or < 1) throw OutOfRange.
// Special case 1: call addFront when I is 1
// Special case 2: call addRear when I is Count+1
// Regular case: add right before the Ith node. Cout if updated.
// <see the template loops in the notes to move 2 pointers to the right nodes
// and make sure you indicate the purposes of these local pointers>

void ReadyQueue::addbeforeIth(int I, el_t newNum) {
    if(I > this->Count+1 || I < 1) {
        throw ReadyQueue::OutOfRange();
    } else if(I == 1) {
        this->addFront(newNum);
    } else if(I == this->Count+1) {
        this->addRear(newNum);
    } else {
        int i = 1;
        PCB *activePCB = this->Front;
        PCB *prevPCB = this->Front;
        
        while(activePCB->Next != NULL) {
            if(i == I) {
                PCB *newPCB;
                newPCB = new PCB;
                newPCB->Elem = newNum;
                newPCB->Next = activePCB;
                prevPCB->Next = newPCB;
                this->Count++;
            }
            
            prevPCB = activePCB;
            activePCB = activePCB->Next;
            i++;
        }
    }
};
