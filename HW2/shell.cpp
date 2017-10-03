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
#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
using namespace std;

#define MAX_LINE 80 // max line length
#define EXIT "exit" // exit command
#define NOWAIT "&" // signal to not wait and run the next command
#define BUF_SIZE 50

/*
 *
 */

char history[10][BUF_SIZE]; //history array to store history commands
int historyCount = 0;

void adjustHistory(char command[]) {
    int i; 

    for(i = 9;i>0; i--) { /* Shift the history up */
        strcpy(history[i], history[i-1]);
    }

    strcpy(history[0], command); /* Update the history with the last command */
    historyCount++; /* Increment history counter */

    if(historyCount > 10) { 
        /* Discard older history entries */
        historyCount = 10;
    }
}

void showHistory() {
    
    printf("Command History:\n");
    
    int i, j = 0;
    int count = historyCount;
    
    /* Loop through stored commands */
    for(i=0; i<10; i++) {
        printf("%d.  ", count);
        while(history[i][j] != '\n' && history[i][j] != '\0') {
            printf("%c", history[i][j]); /* Print command */
            j++;
        }
        
        printf("\n");
        j = 0;
        count--;
        
        if(count < 1) {
            break;   
        }
    }
    
    printf("\n");
}

int formatCommand(char command[], char *args[], int *flag) {
    /* length is number of characters in command 
     * i is a looping index
     * start is the index of the next command
     */
    
    int length, i, start;
    int argCounter = 0; // index of where to place the next parameter into args[]
    
    /* Get input and check for History Commands */

    length = read(STDIN_FILENO, command, MAX_LINE);
    start = -1;
    
    if(length == 0) {
        exit(0);   //end of command
    }

    if(length < 0) {
        printf("Command not read\n");
        exit(-1);  //terminate
    }
    
   //examine each character
    for(i=0;i<length;i++) {
        if(command[i] == ' ' || command[i] == '\t') {
            if(start != -1) {
                args[argCounter] = &command[start];    
                argCounter++;
            }
            
            command[i] = '\0'; // add a null char at the end
            start = -1;
        } else if(command[i] == '\n') {
            if(start != -1) {
                args[argCounter] = &command[start];
                argCounter++;
            }
            
            command[i] = '\0';
            args[argCounter] = NULL; // no more args
        } else {
            if(start == -1) {
                start = i;   
            }
            
            if(command[i] == '&') {
                *flag  = 1; //this flag is the differentiate whether the child process is invoked in background
                command[i] = '\0';
            }
        }
    }
    
    args[argCounter] = NULL; //if the input line was > 80

    if(strcmp(args[0], EXIT) == 0) {
        printf("Exiting. Goodbye!\n");
        exit(0);
    } else if(strcmp(args[0], "history") == 0) {
            showHistory();
            return -1;
    } else if (args[0][0]-'!' ==0) {
            int x = args[0][1]- '0'; 
            int y = args[0][2]- '0'; 

            if(x > historyCount) {//second letter check
                printf("%i", historyCount);
                printf("Index outside of history bound.\n");
                return -1;
            } else if(y != -48) { //third letter check
                printf("Command not found in history.\n");
                return -1;
            } else {
                if(x == -15) { /*Check for '!!' */
                    strcpy(command, history[0]);  /* Most recent command */
                } else if(x == 0) { //Checking for '!0'
                    printf("Invalid command.\n");
                    return -1;
                } else if(x >= 1) { /* Checking for !n where 9 >= n >=1 */
                    strcpy(command, history[(historyCount-x)]);
                    return 0;
                }
            }
    }
    
    adjustHistory(command);
    
    return 0;
}

int main(void) {
    char command[MAX_LINE]; /* buffer to hold the input command */
    int flag; // equals 1 if a command is followed by "&"
    char *args[MAX_LINE/2 + 1];/* max arguments */
    int shouldRun = 1;
    
    pid_t pid;
   
    
    while(shouldRun) { /* Loop prompt forever */
        flag = 0; /* Wait flag */
        
        printf("osh>"); /* Print shell prompt */
        fflush(stdout); /* Flush stream */
        
        if(formatCommand(command, args, &flag) > -1) {
		pid = fork();
        
        	if(pid < 0) {
                    /* PID less than zero indicates failed fork */
                    printf("Failed to fork.\n");
                    exit(1);
        	} else if(pid == 0) {
                    //command not executed
                    if(execvp(args[0], args) < 0) {	
                        /* Error while executing! */
                        printf("ERROR: Command Failed.\n");
                    }
       		} else {
                    /* If the wait flag is 0, wait. */
                    if(flag == 0) {
                        wait(NULL);
                    }
        	}
   	 } else {
            printf("ERROR: Unable to process command.\n");
         }
     }
}
