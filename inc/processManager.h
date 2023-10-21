#define PROCESSMANAGER_H
#ifndef PROCESSMANAGER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct process_ PROCESS;

typedef struct time_ {
   int hour;
   int minute;
   int second;
} TIME;

// add process to queue process to be executed
bool add_process(int priority, TIME* time, char description[50]);

// execute a process with highest priority
void executeHighPriority_process();

// execute a process with lowest time
void executeLowTime_process();

// shows all information about the highest priority process
void infoHighPriority_process();

// shows all information about the lowest time process
void infoLowTime_process();

// change the priority of a process
bool changePriority_process(int oldPriority, int newPriority);

// change the time of a process
bool changeTime_process(TIME* oldTime, TIME* newTime);

// print all processes in descending order of priority
void printDescPriority_process();

// print all processes in ascending order of time
void printAscTime_process();

#endif