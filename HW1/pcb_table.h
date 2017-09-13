// John Yates
// 8/30/2017
// CS433 HW1
//
// This file is the header for the PCBTable class, which is a hash table for holding
// PCBs currently being handled by the OS.
//=======================================================

//#include "pcb.h"

class TableEntry { 
    private: 
        int key;
        PCB* value; 
    public: 
        TableEntry(int key, PCB* value);
        int getKey();
        PCB* getValue();
};

class PCBTable {
    public:
        int Size;
        PCBTable();
        PCBTable(const PCBTable& orig);
        virtual ~PCBTable();
        void put(int id, PCB* value);
        PCB* get(int id);
        void print();
        PCB* getRandom();
        PCB* remove(int id);

        class NullIndexException{};
        TableEntry **table;
    private:
};

