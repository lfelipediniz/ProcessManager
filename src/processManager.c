
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
PROCESS* createList_process() {
   PROCESS* list = (PROCESS*)malloc(sizeof(PROCESS));
   list->size = 0;
   return list;
}

void shellSort(SHEET* arr[], int n) {
    // Start with a large gap
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            SHEET* temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap]->prior > temp->prior; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}
// add a process
bool add_process(PROCESS* list, int priority, TIME* time, char* description) {
   if (list == NULL || list->size == MAX_PROCESSES) return false;

   SHEET* sheet = (SHEET*)malloc(sizeof(SHEET));
   sheet->prior = priority;
   sheet->start = time;
   strcpy(sheet->description, description);

   list->processesOrgPrior[list->size] = sheet;
   list->processesOrgTime[list->size] = sheet;

   shellSort(list->processesOrgPrior, list->size + 1);

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
bool changePriority_process(PROCESS* list, int oldPriority, int newPriority) {
   return true;
}

// change the time of a process
bool changeTime_process(PROCESS* list, TIME* oldTime, TIME* newTime) {
   return true;
}

// print all processes in descending order of priority
void printDescPriority_process(PROCESS* list) {
   if (list == NULL || list->size == 0) {
      printf("No processes to print.\n");
      return;
   }

   printf("Processes in descending order of priority:\n");
   for (int i = list->size - 1; i >= 0; i--) {
      SHEET* sheet = list->processesOrgPrior[i];
      printf("Priority: %d, Time: %02d:%02d:%02d, Description: %s\n",
             sheet->prior, sheet->start->hh, sheet->start->mm, sheet->start->ss,
             sheet->description);
   }
}

// print all processes in ascending order of time
void printAscTime_process(PROCESS* list) {
   if (list == NULL || list->size == 0) {
      printf("No processes to print.\n");
      return;
   }

   printf("Processes in ascending order of time:\n");
   for (int i = 0; i < list->size; i++) {
      SHEET* sheet = list->processesOrgTime[i];
      printf("Priority: %d, Time: %02d:%02d:%02d, Description: %s\n",
             sheet->prior, sheet->start->hh, sheet->start->mm, sheet->start->ss,
             sheet->description);
   }
}

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
