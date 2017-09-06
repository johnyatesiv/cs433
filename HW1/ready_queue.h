// John Yates
// 8/30/2017
// CS433 HW1
// File Summary
//=======================================================

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
    void insertProc(PCB proc);
  
    PCB removeHighestProc();
    
    int size();
    
    void displayQueue();
    
    /* Extra Methods */
    
    //Checks to see if this Front and Rear point to NULL and Count == 0
    bool isEmpty();
    
    //Displays all elements or [empty] if isEmpty() is true
    void displayAll();

    //**
    void addFront(PCB pcb);
    
    //**
    void addRear(PCB pcb);

    //**
    void deleteFront(PCB& pcb);

    //**
    void deleteRear(PCB& pcb);

    //**
    void deleteIth(int, PCB& pcb);

    //**    
    void addbeforeIth(int i, PCB pcb);
};
