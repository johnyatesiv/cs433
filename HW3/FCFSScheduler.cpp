/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FCFSScheduler.cpp
 * Author: johnyates
 * 
 * Created on October 18, 2017, 10:52 AM
 */

#include "FCFSScheduler.h"

FCFSScheduler::FCFSScheduler() {
    this->preemptive = 0;
    this->CPUState = 0;
}

FCFSScheduler::FCFSScheduler(const FCFSScheduler& orig) {
    
}

FCFSScheduler::~FCFSScheduler() {
    
}
