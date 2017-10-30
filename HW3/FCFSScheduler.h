/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FCFSScheduler.h
 * Author: johnyates
 *
 * Created on October 24, 2017, 10:11 AM
 */

#include "Scheduler.h"

#ifndef FCFSSCHEDULER_H
#define FCFSSCHEDULER_H

class FCFSScheduler: public Scheduler {
public:
    FCFSScheduler();
    FCFSScheduler(const FCFSScheduler& orig);
    virtual ~FCFSScheduler();
private:

};

#endif /* FCFSSCHEDULER_H */

