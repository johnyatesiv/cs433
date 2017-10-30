/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Event.h
 * Author: johnyates
 *
 * Created on October 11, 2017, 10:08 AM
 */

#ifndef EVENT_H
#define EVENT_H

#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include "randomLib.h"

class Event {
public:
    Event();
    Event(int type);
    Event(Event* orig);
    virtual ~Event();
    void print();
    int processId;
    int scheduled; // Index for Priority Event Queue
    /* 
     * Event Types
     * 1 Process Arrival
     * 2 CPU Completion
     * 3 IO Completion
     * 4 Timer Expiration
     */
    int type;
    int arrived;
    bool burstComplete;
    bool ioComplete;
    int timer;
private:

};

#endif /* EVENT_H */

