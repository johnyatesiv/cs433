/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SRTFScheduler.h
 * Author: johnyates
 *
 * Created on October 24, 2017, 10:15 AM
 */

#include "Scheduler.h"

#ifndef SRTFSCHEDULER_H
#define SRTFSCHEDULER_H

class SRTFScheduler {
public:
    SRTFScheduler();
    SRTFScheduler(const SRTFScheduler& orig);
    virtual ~SRTFScheduler();
    
    /* Comparison for remaining burst time */
    struct LowerRemainingTime {
        bool operator()(Process* left, Process* right) const {
            return left->cpuTime < right->cpuTime;
        }
    };
    
    priority_queue<Process*, vector<Process*>, LowerRemainingTime> processQueue;
private:

};

#endif /* SRTFSCHEDULER_H */

