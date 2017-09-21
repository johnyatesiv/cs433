/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   shell.cpp
 * Author: johnyates
 *
 * Created on September 21, 2017, 2:54 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
using namespace std;

#define MAX_LINE 80

/*
 *
 */

int main(void) {
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    
    while(should_run) {
        printf("osh>");
        fflush(stdout);
        
        /*
         * 1. Read user input
         * 2. Determine whether to exit
         * 3. If not exiting, fork a child process with fork();
         * 4. Child process invokes execvp()
         * 5. Parent process invokes wait() if the command included &
         * 
         * 
         */
    }
    
    return 0;
}

