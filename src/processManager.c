
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

// compare two times
int compareTime(const TIME* time1, const TIME* time2) {
   // -1 time1 < time2
   // 1 time1 > time2
   if (time1->hh < time2->hh) return -1;
   if (time1->hh > time2->hh) return 1;
   if (time1->mm < time2->mm) return -1;
   if (time1->mm > time2->mm) return 1;
   if (time1->ss < time2->ss) return -1;
   if (time1->ss > time2->ss) return 1;
   return 0;  // if time1 == time2
}

void shellSort(SHEET* arr[], int n, char typeCompare) {
   int gap, i, j;

   // start with a big gap, then reduce the gap
   for (gap = n / 2; gap > 0; gap /= 2) {
      for (i = gap; i < n; i++) {
         SHEET* temp = arr[i];

         // depending on the type of comparison ('p' for priority, 't' for time)

         if (typeCompare == 'p') {
            // compare based on the 'prior' field for SHEET
            for (j = i; j >= gap && arr[j - gap]->prior > temp->prior;
                 j -= gap) {
               arr[j] = arr[j - gap];
            }
         } else if (typeCompare == 't') {
            // compare based on the 'start' (TIME) field for SHEET using the
            // compareTime function
            for (j = i;
                 j >= gap && compareTime(arr[j - gap]->start, temp->start) > 0;
                 j -= gap) {
               arr[j] = arr[j - gap];
            }
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

   shellSort(list->processesOrgPrior, list->size + 1, 'p');
   shellSort(list->processesOrgTime, list->size + 1, 't');

   list->size++;

   return true;
}

// execute a process with highest priority
void executeHighPriority_process(PROCESS* list) {}

// execute a process with lowest time
void executeLowTime_process(PROCESS* list) {
   if (list == NULL || list->size == 0) {
      printf("No processes to execute.\n");
      return;
   }

   TIME* t = ((list->processesOrgTime)[0])->start;
   (list->processesOrgTime)[0] = NULL;

   int i = 0;
   for(; i < list->size; ++i) {
      if(compareTime(t, ((list->processesOrgPrior)[i])->start) == 0) {
         (list->processesOrgPrior)[i] = NULL;
         break;
      }
   }

   for(; i < list->size - 1; ++i) {
      (list->processesOrgPrior)[i] = (list->processesOrgPrior)[i+1];
   }

   for(int i = 0; i < list->size - 1; ++i) {
      (list->processesOrgTime)[i] = (list->processesOrgTime)[i+1];
   }

   list->size--;
}

// shows all information about the highest priority process
void infoHighPriority_process(PROCESS* list) {}

// shows all information about the lowest time process
void infoLowTime_process(PROCESS* list) {}

// change the priority of a process
bool changePriority_process(PROCESS* list, int oldPriority, int newPriority) {
   int start, middle, final;

   start = 0;
   final = list->size - 1;
   middle = (start + final)/2;

   while((start < final) && (list->processesOrgPrior[middle]->prior != oldPriority)) {
      if(list->processesOrgPrior[middle]->prior < oldPriority)
         start = middle + 1;
      else
         final = middle - 1;
      middle = (start + final)/2;
   }

   if((start <= final) && (list->processesOrgPrior[middle]->prior == oldPriority)) {
      list->processesOrgPrior[middle]->prior = newPriority;
      shellSort(list->processesOrgPrior, list->size, 'p');
      return true;
   }

   return false;
}

// change the time of a process
bool changeTime_process(PROCESS* list, TIME* oldTime, TIME* newTime) {
   int start, middle, final;

   start = 0;
   final = list->size-1;
   middle = (start + final)/2;

   while((start < final) && (list->processesOrgTime[middle]->start->hh != oldTime->hh)) {
      if(list->processesOrgTime[middle]->start->hh < oldTime->hh)
         start = middle + 1;
      else
         final = middle-1;
      middle = (start + final)/2;
   }

   if((start <= final) && (list->processesOrgTime[middle]->start->hh == oldTime->hh)) {
      while((start < final) && (list->processesOrgTime[middle]->start->mm != oldTime->mm)) {
         if(list->processesOrgTime[middle]->start->mm < oldTime->mm)
            start = middle + 1;
         else
            final = middle-1;
         middle = (start + final)/2;
      }
         
      if((start <= final) && (list->processesOrgTime[middle]->start->mm == oldTime->mm)) {
         while((start < final) && (list->processesOrgTime[middle]->start->ss != oldTime->ss)) {
            if(list->processesOrgTime[middle]->start->ss < oldTime->ss)
               start = middle + 1;
            else
               final = middle-1;
            middle = (start + final)/2;
         }

         if((start <= final) && (list->processesOrgTime[middle]->start->ss == oldTime->ss)) {
            list->processesOrgTime[middle]->start->hh = newTime->hh;
            list->processesOrgTime[middle]->start->mm = newTime->mm;
            list->processesOrgTime[middle]->start->ss = newTime->ss;

            shellSort(list->processesOrgTime, list->size, 't');

            return true;
         }
      }
   }

   return false;
}

// print all processes in descending order of priority
void printDescPriority_process(PROCESS* list) {
   if (list == NULL || list->size == 0) {
      printf("No processes to print.\n");
      return;
   }

   int i;
   for (int i = list->size - 1; i >= 0; i--) {
      SHEET* sheet = list->processesOrgPrior[i];
      printf("%d %02d:%02d:%02d %s\n",
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

   int i;
   for (i = 0; i < list->size; i++) {
      SHEET* sheet = list->processesOrgTime[i];
      printf("%d %02d:%02d:%02d %s\n",
             sheet->prior, sheet->start->hh, sheet->start->mm, sheet->start->ss,
             sheet->description);
   }
}

// free the process list
bool freeProcessList(PROCESS** list) {
   if (*list == NULL) 
      return false;

   for (int i = 0; i < (*list)->size; i++) {
      free((*list)->processesOrgPrior[i]->start);
      free((*list)->processesOrgPrior[i]);
   }

   free(*list);
   return true;
}

