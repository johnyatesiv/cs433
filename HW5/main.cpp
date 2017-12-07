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
#include <sys/mman.h>
#include <list>
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <vector>
#include <unordered_map>

#define minPageSize 256*8
#define maxPageSize 8192*8
#define maxVirtualMemory 134217728*8

using namespace std;

int memoryReferences = 0;
int pageFaults = 0;
int flushes = 0;
int cycles = 0;

class PageTableEntry {
    public:
        PageTableEntry() {
            this->valid = 1;
            this->frameNumber = -1;
            //check if address is odd, if so it is a write and mark it dirty
            //this->bits = std::bitset<64>(address).to_string();
        }
        
        string bits;
        int frameNumber;
        int valid;
        int dirty; 
        timeval loaded;
        timeval accessed;
        timeval lastAccess;
        
        int LSB() {
            return this->bits[this->bits.length()-1];
        }
    private:
};

//int Random(int pageSize, int memSize, int numPages) {
//    printf("\nUsing Random algorithm...\n");
//}
//
//void FIFO(int pageSize, int memSize, int numPages) {
//    
//}
//
//void LRU(int pageSize, int memSize, int numPages) {
//    
//}

//int pageTableReference(int memReference) {
//    
//}

int main(int argc, char **argv) {
    /* Determine if Random, FIFO or LRU replacement, initialize memory sizes */
    int pageSize;
    int memSize;
    int algorithm;
    
    if(argv[1] != NULL) {
        /* Convert the value to bits and store the page size */
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
        /* Convert the argument to bits and store memory size */
        int converted2 = atoi(argv[2]);
        memSize = converted2*1000000*8;
    } else {
        printf("\nPlease provide a memory size from this list: 4, 16, 32, 64 MB as the second argument.");
        return 0;
    }
    
    int numPages = memSize/pageSize;
    
    printf("\nJohn Yates and Joseph Colarossi\nCS433 MWF 10:30-11:20\nHomework Program #5\n\n");
    printf("\nMemory Size: %i bits", memSize);
    printf("\nPage Size: %i bits", pageSize);
    printf("\nNumber of Pages: %i", numPages);
    
    if(argv[3] != NULL) {
        if(strcmp(argv[3], "Random") == 0) {
            algorithm = 3;
        } else if(strcmp(argv[3], "FIFO") == 0) {
            algorithm = 1;
        } else if(strcmp(argv[3], "LRU") == 0) {
            algorithm = 2;
        } else {
            printf("\nAlgorithm argument unknown, please choose Random, FIFO or LRU.");
        }
    } else {
        printf("\nAlgorithm not specified, using the Random algorithm.");
        //Random(pageSize, memSize, numPages);
    }
    
    //PageTableEntry pageTable[numPages];
    unordered_map<int, PageTableEntry> PageTable;
    unordered_map<int, PageTableEntry> FreeFrameList;
    
    string read; //String for holding memory references
    int address; //for memory ref address
    int pageAddress; //for calculated page #
    int pageOffset; //for calculated page offset
    int write; //to determine if page should be marked dirty or not
    
    srand(time(NULL)); //seed random
    
    vector<string> input;
    
    /* Read the references into memory for quicker access? */
    ifstream file("references.txt");
    while(getline(file, read)) {
        input.push_back(read);
    }
    
    /* Start the benchmark */
    struct timeval timeStart, timeEnd, currentTime;
    gettimeofday(&timeStart, NULL);
    
    PageTableEntry currentPage;
    int frameNumber;
    
    for(vector<string>::iterator it = input.begin() ; it != input.end(); ++it) {
        memoryReferences++;
        
        /* 1. Find location of desired page on disk */
        
        address = atoi(it->c_str());
        pageAddress = address/pageSize;
        pageOffset = address%pageSize;
        write = address%2;
        
        currentPage = PageTable[pageAddress];
        frameNumber = currentPage.frameNumber;
        //printf("\nAddress: %i, Page: %i, Frame: %i", address, pageAddress, frameNumber);
        
        if(FreeFrameList[frameNumber].frameNumber < 0) {
                currentPage = PageTableEntry();
                PageTable[pageAddress] = currentPage;
                /* miss, select victim frame */   
                pageFaults++; // Increment page faults
                /* 2. Find a free frame: */
                //printf("\nFrameList size: %i", FreeFrameList.size());
                
                if(FreeFrameList.size() < numPages) {
                    //printf("\nFound free Frame, adding Page... %i < %i", FreeFrameList.size(), numPages);
                    /* - If there is a free frame, use it */
                    FreeFrameList[PageTable.size()] = PageTableEntry();
                    FreeFrameList[PageTable.size()].frameNumber = PageTable.size();
                    PageTable[pageAddress].frameNumber = FreeFrameList[PageTable.size()].frameNumber;
                } else {
                    //printf("\nNo free frame, replacing using ");
                    /* - If not, use the page replacement algorithm to select a victim frame */
                    if(algorithm == 1) {
                        //printf("FIFO algorithm.");
                        /* FIFO Algorithm */
                        int recent = 0;
                        unordered_map<int, PageTableEntry>::iterator it = FreeFrameList.begin();
                        while(it != FreeFrameList.end()) {
                            if(it->second.loaded.tv_usec > recent) {
                                currentPage = it->second;
                                recent = it->second.loaded.tv_usec;
                            }
                            
                            it++;
                        }
                        
                        if(FreeFrameList[currentPage.frameNumber].dirty) {
                            flushes++;
                        }
                        
                        FreeFrameList[currentPage.frameNumber] = PageTableEntry();
                        FreeFrameList[currentPage.frameNumber].frameNumber = currentPage.frameNumber;
                        PageTable[pageAddress].frameNumber = FreeFrameList[currentPage.frameNumber].frameNumber;
                    } else if(algorithm == 2) {
                        //printf("LRU algorithm.");
                        /* LRU Algorithm */
                        int accessed = 0;
                        unordered_map<int, PageTableEntry>::iterator it = FreeFrameList.begin();
                        while(it != FreeFrameList.end()) {
                            if(it->second.accessed.tv_usec < accessed) {
                                currentPage = it->second;
                                accessed = it->second.accessed.tv_usec;
                            }
                            
                            it++;
                        }
                        
                        if(FreeFrameList[currentPage.frameNumber].dirty) {
                            flushes++;
                        }
                        
                        FreeFrameList[currentPage.frameNumber] = PageTableEntry();
                        FreeFrameList[currentPage.frameNumber].frameNumber = currentPage.frameNumber;
                        PageTable[pageAddress].frameNumber = FreeFrameList[currentPage.frameNumber].frameNumber;
                    } else {
                        //printf("Random algorithm.");
                        /* Random ALgorithm */
                        int t = rand()%(numPages - 1 + 1) + 1;
                        if(FreeFrameList[t].dirty) {
                            flushes++;
                        }
                        
                        FreeFrameList[t] = PageTableEntry();
                        FreeFrameList[t].frameNumber = t;
                        PageTable[pageAddress].frameNumber = t;
                    }
                }

                /* 3. Put the desired page into the free frame, update page and frame tables */

                /* 4. Restart process */
        } else {
            /* Hit */
            //printf("\nHit!");
        }
        
        gettimeofday(&currentTime, NULL);
        FreeFrameList[frameNumber].lastAccess = currentTime;
        FreeFrameList[frameNumber].loaded = currentTime;
        
        if(write) {
            FreeFrameList[frameNumber].dirty = 1;
        }
        
//        if(pageAddress < numPages) {
//            printf("%i mapped to %i / %i + %i", address, pageAddress, numPages, pageOffset);   
//        } else {
//            printf("\nBAD PAGE NUMBER!");
//        }
        
        cycles++;
    }
    
    /* End the benchmark */
    gettimeofday(&timeEnd, NULL);
    
    printf("\nMemory References: %i", memoryReferences);
    printf("\nPage Faults: %i", pageFaults);
    printf("\nFlushes: %i", flushes);
    double taken = (timeEnd.tv_usec - timeStart.tv_usec);
    printf("\nTime taken: %f microseconds\n", taken);
     
    return 0;
}
