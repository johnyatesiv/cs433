// John Yates
// 8/30/2017
// CS433 HW1
//
// This file is the header file for the PCB class, which represents a Process in the OS.
// It contains descriptive variables as well as a method to print itself.
//=======================================================

typedef int el_t ;  // elements will be **

class PCB {
    public:
        PCB(int priority, int id);
        PCB(const PCB& orig);
        virtual ~PCB();
        PCB *Next;  // next is the pointer to the next node
        void print();
        int getPriority();
        int id;
        int state; //0 - Running, 1 - Waiting, 2 - Stopped, 3 - Pending Cleanup
        int programCounter;
        int priority; // 1-20 with 1 being highest
    private:
};

