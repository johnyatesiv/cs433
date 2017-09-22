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

const char *EXIT = "exit";

int main(void) {
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    pid_t pid;
    pid_t childPid;
    int childStatus;
    int shouldRun = 1; /* flag to determine when to exit program */
    
    while(shouldRun) {
        if ((pid = fork()) == -1) { // system functions also set a variable called "errno"
            perror("fork"); // this function automatically checks "errno" and prints the error plus what you give it
            return EXIT_FAILURE;
        }
        
        printf("osh>");
        fflush(stdout);

        /*
         * 1. Read user input
         */

        getline(cin, args);
        
        /* 
         * 2. Determine whether to exit
         */

        if(args == EXIT) {
            shouldRun = 0;
        } else {
            // parseCommand(cmd, argv); should write the command into argv and put a stopping point
            
            /* 
             * 3. If not exiting, fork a child process with fork();
             */
            child_pid = fork();
            if(child_pid == 0) {
                
             /* 
             * 4. Child process invokes execvp()
             */

              execvp(argv[0], argv);

              /* If execvp returns, it must have failed. */

              printf("Could not execute command!\n");
              exit(0);
            }

            else {
              /*
               *  5. Parent process invokes wait() if the command included &
               */

               while(tpid != childPid) {
                    pid_t tpid = wait(&childStatus);
                    if(tpid != childPid) {
                        process_terminated(tpid);
                    }
               }

               return childStatus;
            }

            execvp(args);

            /* Search the char array for & to determine whether to wait() */
            pch=strchr(str,'&');
            while(pch!=NULL) {
                pch=strchr(pch+1,'&');
                wait();
                break;
            }
        }
    }
    
    return 0;
}

