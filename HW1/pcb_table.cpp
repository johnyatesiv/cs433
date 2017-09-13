// John Yates
// 8/30/2017
// CS433 HW1
//
// This file is the implementation for the PCBTable class, which is a hash table for holding
// PCBs currently being handled by the OS. It contains methods to put new PCB objects in,
// as well as retrieve them, remove them and iterate.
//=======================================================

#include<iostream>
#include <stdlib.h>
#include <time.h>
#include "pcb_table.h"
using namespace std;

const int TABLE_SIZE = 128;

TableEntry::TableEntry(int key, PCB* value) {
    this->key = key;
    this->value = value;
} 

int TableEntry::getKey() {
    return key; 
} 

PCB* TableEntry::getValue() {
    return value; 
} 

/**
 * Purpose: Constructor for PCBTable
 */
PCBTable::PCBTable() {
    this->table = new TableEntry*[TABLE_SIZE];
    this->Size = 0;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        this->table[i] = NULL;
    }
}

/**
 * Purpose: Destructor for HashMap
 */
PCBTable::~PCBTable() { 
    for(int i = 0; i < TABLE_SIZE; i++) {
        if(table[i] != NULL) {
            delete table[i];
        }
    }

    delete[] table;
} 

/**
 * Purpose: retrieve a value from the hash table from the given key.
 * @param key
 * @return 
 */
PCB* PCBTable::get(int key) { 
    int hash = (key % TABLE_SIZE);
    while (table[hash] != NULL && table[hash]->getKey() != key) {
        hash = (hash + 1) % TABLE_SIZE;
    }

    if (table[hash] == NULL) {
        throw new PCBTable::NullIndexException;
    }
    
    return table[hash]->getValue();
}


/**
 * Purpose: Insert a value into the Hash table with the given key.
 * @param key
 * @param value
 */
void PCBTable::put(int key, PCB* value) {
    int hash = (key % TABLE_SIZE);
    
    cout << "Putting: " << this->Size << " " << hash << endl;
    cout << this->table[1] << endl;
    
    while(table[hash] != NULL && table[hash]->getKey() != key) {
        hash = (hash + 1) % TABLE_SIZE;
    }

    if(table[hash] != NULL) {
        delete table[hash];
    }

    table[hash] = new TableEntry(key, value);
    
    //this->keys[key] = hash;
    this->Size++;
    cout << "Finished putting: " << this->Size << endl;
}

/*
 * 
 */
PCB* PCBTable::remove(int id) {
    PCB* removed = table[id]->getValue();
    table[id] = NULL;
    return removed;
}

void PCBTable::print() {
    cout << "|Key   |Value  |\n";
    for(int i=0; i<this->Size; i++) {
        if(table[i] != NULL) {
            cout << "|" << i << "|" << table[i]->getKey() << "|\n";   
        }
    }
}

PCB* PCBTable::getRandom() {
    int randIndex;
    int hash;

    srand(time(NULL));
    randIndex = (rand() % (this->Size)) + 1;
    
    hash = (randIndex % TABLE_SIZE);

    if(table[hash] == NULL) {
        cout << "Random index " << hash << " accessed a null element." << endl;
        //throw new PCBTable::NullIndexException;
        return this->getRandom();
    } else {
        return table[hash]->getValue();   
    }
}