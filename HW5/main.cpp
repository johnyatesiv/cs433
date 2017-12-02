/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: johnyates
 *
 * Created on November 4, 2017, 9:37 AM
 */

#include <bitset>
#include <cstdlib>
#include <fstream>
#include <list>
#include <stdio.h>
#include <string>

#define minPageSize 256*8
#define maxPageSize 8192*8
#define maxVirtualMemory 134217728*8

using namespace std;

int memoryReferences = 0;
int pageFaults = 0;
int flushes = 0;
int benchmark = 0;

class PageTableEntry {
    public:
        PageTableEntry(int address) {
            //check if address is odd, if so it is a write and mark it dirty
            this->bits = std::bitset<64>( 12345 ).to_string();
        }
        
        string bits;
        int frameNumber;
        int valid;
        int dirty;
        
        PageTableEntry::LSB() {
            return this->bits[this->bits.length()-1];
        }
    private:
};

int main(int argc, char **argv) {
    /* Determine if Random, FIFO or LRU replacement, initialize memory sizes */
    int numPages;
    int pageSize;
    int memSize;
    
    if(argv[1] != NULL) {
        int converted = atoi(argv[1]);
        converted = converted*8;
        if(converted < minPageSize || converted > maxPageSize) {
            printf("\nPlease provide a page size between 256 and 8192 as the first argument.");
            return 0;
        } else {
            pageSize = converted;  
        }
    } else {
        printf("\nPlease provide a page size between 256 and 8192 as the first argument.");
        return 0;
    }
    
    if(argv[2] != NULL) {
        int converted2 = atoi(argv[2]);
        memSize = converted2*1000000*8;
    } else {
        printf("\nPlease provide a memory size from this list: 4, 16, 32, 64 MB as the second argument.");
        return 0;
    }
    
    if(argv[3] != NULL) {
//        if(argv[3] == 'Random') {
//            
//        } else if(argv[3] == 'FIFO') {
//            
//        } else if(argv[3] == 'LRU') {
//            
//        } else {
//            printf("\nAlgorithm argument unknown, please choose Random, FIFO or LRU.");
//        }
    } else {
        printf("\nAlgorithm not specified, using the Random algorithm.");
    }
    
    numPages = memSize/pageSize;
    PageTableEntry pageTable[numPages];
    list freeFrameList;
    
    printf("\nJohn Yates and Joseph Colarossi\nCS433 MWF 10:30-11:20\nHomework Program #5\n\n");
    printf("\nMemory Size: %i bits", memSize);
    printf("\nPage Size: %i bits", pageSize);
    printf("\nNumber of Pages: %i bits", numPages);
    
    return 0;
    
    string read;
    
    ifstream file("references.txt");
    while(getline(file, read)) {
        printf("\n");
        printf(read.c_str());
    }
    
    return 0;
}

void Random() {
    
}

void FIFO() {
    
}

void LRU() {
    
}

int pageTableReference(int memReference) {
    
}
