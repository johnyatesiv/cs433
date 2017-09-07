// John Yates
// 8/30/2017
// CS433 HW1
// File Summary
//=======================================================

typedef int el_t ;  // elements will be **

class PCB {
    public:
        PCB(int priority, int id);
        PCB(const PCB& orig);
        virtual ~PCB();
        //el_t Elem;   // elem is the element stored
        PCB *Next;  // next is the pointer to the next node
        int id;
        int state; //0 - Running, 1 - Waiting, 2 - Stopped, 3 - Pending Cleanup
        int programCounter;
        int priority; // 1-20 with 1 being highest
    private:
};

