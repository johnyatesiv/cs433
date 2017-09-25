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
#include <iostream> //no need to have two IO deps, refactor
#include <unistd.h>
using namespace std;

#define MAX_LINE 80

/*
 *
 */

string EXIT = "exit";

int main(void) {
    string command;
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    pid_t pid; /* this processes PID */
    pid_t childPid; /* the PID of the child process */
    int childStatus; /* the status of the child process */
    char *pch; /* Holder to check arguments */
    int shouldRun = 1; /* flag to determine when to exit program */
    
    while(shouldRun) {
//        if((pid = fork()) == -1) { // system functions also set a variable called "errno"
//           perror("fork"); // this function automatically checks "errno" and prints the error plus what you give it
//           return EXIT_FAILURE;
//        }
        
        printf("osh>");
        fflush(stdout);

        /*
         * 1. Read user input
         */

        getline(cin, command);
        
        
        cout << command << endl;
        
        /* 
         * 2. Determine whether to exit
         */

        if(command == EXIT) {
            shouldRun = 0;
            break;
        } else {
            // parseCommand(cmd, argv); should write the command into argv and put a stopping point
            
            /* 
             * 3. If not exiting, fork a child process with fork();
             */
            childPid = fork();
            if(childPid == 0) {
                
             /* 
             * 4. Child process invokes execvp()
             */

              execvp(args[0], args);

              /* If execvp returns, it must have failed. */

              printf("Could not execute command!\n");
              exit(0);
            }

            else {
                /*
                 *  5. Parent process invokes wait() if the command included &
                 */
                 pid_t tpid;

                 while(tpid != childPid) {
                      pid_t tpid = wait(&childStatus);
                      if(tpid != childPid) {
                          //process_terminated(tpid);
                      }
                 }

                 return childStatus;
            }

            execvp(args[0], args);

            /* Search the char array for & to determine whether to wait() */
//            pch=strchr(str,'&');
//            while(pch!=NULL) {
//                pch=strchr(pch+1,'&');
//            }
        }
    }
    
    return 0;
}

