
#include "../inc/processManager.h"

// storage a information of a process
typedef struct sheet_ {
   int prior;
   TIME* start;
   char description[MAX_DESCR];
} SHEET;

// storage processes sheets
typedef struct process_ {
   SHEET* processes[MAX_PROCESSES];
   int size;
} PROCESS;

// create a time function that returns a pointer to a TIME struct
TIME* createTime(int hour, int minute, int second) {
   TIME* time = (TIME*)malloc(sizeof(TIME));
   time->hh = hour;
   time->mm = minute;
   time->ss = second;
   return time;
}

// create a process function that returns a pointer to a PROCESS struct
PROCESS* createProcess() {
   PROCESS* list = (PROCESS*)malloc(sizeof(PROCESS));
   list->size = 0;
   return list;
}

// add process to queue process to be executed
bool add_process(PROCESS * list, int priority, TIME* time, char* description){
   if (list->size < MAX_PROCESSES) {
      SHEET* sheet = (SHEET*)malloc(sizeof(SHEET));
      sheet->prior = priority;
      sheet->start = time;
      strcpy(sheet->description, description);
      list->processes[list->size] = sheet;
      list->size++;
      return true;
   }
   return false;

}

// execute a process with highest priority
void executeHighPriority_process(PROCESS * list) {

}

// execute a process with lowest time
void executeLowTime_process(PROCESS * list) {}

// shows all information about the highest priority process
void infoHighPriority_process(PROCESS * list) {

}

// shows all information about the lowest time process
void infoLowTime_process(PROCESS * list) {}

// change the priority of a process
bool changePriority_process(PROCESS * list, int oldPriority, int newPriority) {}

// change the time of a process
bool changeTime_process(PROCESS * list, TIME* oldTime, TIME* newTime) {}

// print all processes in descending order of priority
void printDescPriority_process(PROCESS * list) {}

// print all processes in ascending order of time
void printAscTime_process(PROCESS * list) {}
