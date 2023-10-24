
#include "../inc/processManager.h"


typedef struct node_ {
   int priority;
   TIME* time;
   char description[50];
   struct node_* next;
} NODE;

typedef struct process_ {
   NODE* head;
   int size;
} PROCESS;

// create a time function that returns a pointer to a TIME struct
TIME* createTime(int hour, int minute, int second) {
   TIME* time = (TIME*)malloc(sizeof(TIME));
   time->hour = hour;
   time->minute = minute;
   time->second = second;
   return time;
}

// create a process function that returns a pointer to a PROCESS struct
PROCESS* createProcess() {
   PROCESS* process = (PROCESS*)malloc(sizeof(PROCESS));
   process->head = NULL;
   process->size = 0;
   return process;
}

// add process to queue process to be executed
bool add_process(PROCESS * list, int priority, TIME* time, char description[50]){
   NODE* node = (NODE*)malloc(sizeof(NODE));
   node->priority = priority;
   node->time = time;
   strcpy(node->description, description);
   node->next = NULL;

   if (list->head == NULL) {
      list->head = node;
      list->size++;
      return true;
   }

   NODE* aux = list->head;
   NODE* prev = NULL;

   while (aux != NULL && aux->priority > priority) {
      prev = aux;
      aux = aux->next;
   }

   if (prev == NULL) {
      node->next = list->head;
      list->head = node;
   } else {
      prev->next = node;
      node->next = aux;
   }

   list->size++;
   return true;
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
void infoLowTime_process() {PROCESS * list}

// change the priority of a process
bool changePriority_process(PROCESS * list, int oldPriority, int newPriority) {}

// change the time of a process
bool changeTime_process(PROCESS * list, TIME* oldTime, TIME* newTime) {}

// print all processes in descending order of priority
void printDescPriority_process(PROCESS * list) {}

// print all processes in ascending order of time
void printAscTime_process() {PROCESS * list}
