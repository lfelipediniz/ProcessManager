#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 300
#define MAX_DESCR 50

typedef struct process_ PROCESS;

typedef struct time_ {
   int hh;
   int mm;
   int ss;
} TIME;

// create a Time
TIME* createTime(int hour, int minute, int second);

// create a Process
PROCESS* createList_process();

// add process to queue process to be executed
bool add_process(PROCESS* list, int priority, TIME* time, char* description);

// execute a process with highest priority
void executeHighPriority_process(PROCESS* list);

// execute a process with lowest time
void executeLowTime_process(PROCESS* list);

// shows all information about the highest priority process
void infoHighPriority_process(PROCESS* list);

// shows all information about the lowest time process
void infoLowTime_process(PROCESS* list);

// change the priority of a process
bool changePriority_process(PROCESS* list, int oldPriority, int newPriority);

// change the time of a process
bool changeTime_process(PROCESS* list, TIME* oldTime, TIME* newTime);

// print all processes in descending order of priority
void printDescPriority_process(PROCESS* list);

// print all processes in ascending order of time
void printAscTime_process(PROCESS* list);

// free the process list
bool freeProcessList(PROCESS* list);

#endif