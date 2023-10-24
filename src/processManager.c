
#include "../inc/processManager.h"

// storage a information of a process
typedef struct sheet_ {
   int prior;
   TIME* start;
   char description[MAX_DESCR];
} SHEET;

// storage processes sheets
typedef struct process_ {
   SHEET* processesOrgPrior[MAX_PROCESSES];
   SHEET* processesOrgTime[MAX_PROCESSES];

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

int binarySearchProcess(PROCESS* list, char criteria, SHEET* sheet) {
   int left = 0;
   int right = list->size - 1;
   int insertIndex = -1;

   while (left <= right) {
      int mid = (left + right) / 2;
      int compare;

      if (criteria == 'p')
         // compare by priority (from high to low)
         compare = list->processesOrgPrior[mid]->prior - sheet->prior;
      else if (criteria == 't')
         // compare by time (from low to high)
         compare =
             compareTimes(sheet->start, list->processesOrgTime[mid]->start);
      else
         // invalid criteria
         return -1;

      if (compare < 0) {
         // sheet should be inserted before mid
         right = mid - 1;
         insertIndex = mid;
      } else if (compare > 0) {
         // sheet should be inserted after mid
         left = mid + 1;
      } else {
         // if there is a tie in the comparison, insert after mid
         left = mid + 1;
         insertIndex = mid + 1;
      }
   }

   if (insertIndex == -1) {
      // the list is empty, or the sheet should be inserted at the beginning
      insertIndex = 0;
   }

   return insertIndex;
}

// compare two time structs for the binary search function
int compareTimes(TIME* time1, TIME* time2) {
   if (time1->hh != time2->hh)
      return time1->hh - time2->hh;
   else if (time1->mm != time2->mm)
      return time1->mm - time2->mm;
   else
      return time1->ss - time2->ss;
}

// add a process to the list based on the specified criteria
bool addProcess(PROCESS* list, int priority, TIME* time, char* description,
                char criteria) {
   // list is full
   if (list->size >= MAX_PROCESSES) return false;

   SHEET* sheet = (SHEET*)malloc(sizeof(SHEET));
   sheet->prior = priority;
   sheet->start = time;
   strcpy(sheet->description, description);

   int insertIndex;
   int i;

   if (criteria == 'p') {
      insertIndex = binarySearchProcess(list, 'p', sheet);

      // shift elements to make space for the new element
      for (i = list->size; i > insertIndex; i--)
         list->processesOrgPrior[i] = list->processesOrgPrior[i - 1];

      list->processesOrgPrior[insertIndex] = sheet;

   } else if (criteria == 't') {
      insertIndex = binarySearchProcess(list, 't', sheet);
      // shift elements to make space for the new element

      for (i = list->size; i > insertIndex; i--)
         list->processesOrgTime[i] = list->processesOrgTime[i - 1];

      list->processesOrgTime[insertIndex] = sheet;

   } else
      return false;  // invalid criteria

   list->size++;
   return true;
}

// execute a process with highest priority
void executeHighPriority_process(PROCESS* list) {}

// execute a process with lowest time
void executeLowTime_process(PROCESS* list) {}

// shows all information about the highest priority process
void infoHighPriority_process(PROCESS* list) {}

// shows all information about the lowest time process
void infoLowTime_process(PROCESS* list) {}

// change the priority of a process
bool changePriority_process(PROCESS* list, int oldPriority, int newPriority) {}

// change the time of a process
bool changeTime_process(PROCESS* list, TIME* oldTime, TIME* newTime) {}

// print all processes in descending order of priority
void printDescPriority_process(PROCESS* list) {}

// print all processes in ascending order of time
void printAscTime_process(PROCESS* list) {}

// free the process list
bool freeProcessList(PROCESS* list) {
   if (!list) return false;

   int i;
   for (i = 0; i < list->size; i++) {
      free(list->processesOrgPrior[i]->start);
      free(list->processesOrgPrior[i]);
      free(list->processesOrgTime[i]->start);
      free(list->processesOrgTime[i]);
   }

   free(list);
   return true;
}
