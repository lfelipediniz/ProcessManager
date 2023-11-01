
#include "../inc/processManager.h"

// storage a information of a process
typedef struct sheet_ {
   int prior;
   TIME* start;
   char description[MAX_DESCR];
} SHEET;

// storage processes sheets
struct process_ {
   SHEET* processesOrgPrior[MAX_PROCESSES];
   SHEET* processesOrgTime[MAX_PROCESSES];
   int size;
};

// create a process function that returns a pointer to a PROCESS struct
PROCESS* createList_process() {
   PROCESS* list = (PROCESS*)malloc(sizeof(PROCESS));

   if(list != NULL)
      list->size = 0;
   return list;
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

   if(sheet == NULL)
      return false;
   sheet->prior = priority;
   sheet->start = time;
   strcpy(sheet->description, description);

   list->processesOrgPrior[list->size] = sheet;
   list->processesOrgTime[list->size] = sheet;

   // sort each list
   shellSort(list->processesOrgPrior, list->size + 1, 'p');
   shellSort(list->processesOrgTime, list->size + 1, 't');

   list->size++;

   return true;
}

// execute a process with highest priority
void executeHighPriority_process(PROCESS* list) {
   if(list == NULL || list->size == 0) {
      printf("No processes to execute\n");
      return;
   }

   SHEET* aux = list->processesOrgPrior[list->size-1];

   int prior = list->processesOrgPrior[list->size-1]->prior;
   list->processesOrgPrior[list->size-1] = NULL;

   int i = 0;

   for(; i<list->size; i++) {
      if(prior == list->processesOrgTime[i]->prior) {
         list->processesOrgTime[i] = NULL;
         break;
      }
   }

   for(; i<list->size-1; i++) {
      list->processesOrgTime[i] = list->processesOrgTime[i+1];
   }

   freeTime(&(aux->start));
   free(aux);

   list->size--;
}

// execute a process with lowest time
void executeLowTime_process(PROCESS* list) {
   if (list == NULL || list->size == 0) {
      printf("No processes to execute\n");
      return;
   }

   SHEET* aux = list->processesOrgTime[0];

   // Pointer of the item with the low time points to NULL
   TIME* t = ((list->processesOrgTime)[0])->start;
   (list->processesOrgTime)[0] = NULL;

   int i = 0;
   // search for the time in the prior list
   for(; i < list->size; ++i) {
      if(compareTime(t, ((list->processesOrgPrior)[i])->start) == 0) {
         (list->processesOrgPrior)[i] = NULL;
         break;
      }
   }

   // shift the lists to the left
   for(; i < list->size - 1; ++i) {
      (list->processesOrgPrior)[i] = (list->processesOrgPrior)[i+1];
   }

   for(i = 0; i < list->size - 1; ++i) {
      (list->processesOrgTime)[i] = (list->processesOrgTime)[i+1];
   }

   freeTime(&(aux->start));
   free(aux);

   list->size--;
}

// shows all information about the highest priority process
void infoHighPriority_process(PROCESS* list) {
   if(list != NULL) {
      printf("%02d ", list->processesOrgPrior[list->size-1]->prior);
      printTime(list->processesOrgPrior[list->size-1]->start);
      printf(" %s\n", list->processesOrgPrior[list->size-1]->description);
   }
}

// shows all information about the lowest time process
void infoLowTime_process(PROCESS* list) {
   if(list != NULL) {
      printf("%02d ", list->processesOrgTime[0]->prior);
      printTime(list->processesOrgTime[0]->start);
      printf(" %s\n", list->processesOrgTime[0]->description);
   }
}

// change the priority of a process
bool changePriority_process(PROCESS* list, int oldPriority, int newPriority) {
   if(list != NULL) {
      int start, middle, final;

      start = 0;
      final = list->size - 1;
      middle = (start + final)/2;

      // Binary search to find the sheet with the old prior
      while((start < final) && (list->processesOrgPrior[middle]->prior != oldPriority)) {
         if(list->processesOrgPrior[middle]->prior < oldPriority)
            start = middle + 1;
         else
            final = middle - 1;
         middle = (start + final)/2;
      }

      // if it was founded, change the prior and sort the list
      if((start <= final) && (list->processesOrgPrior[middle]->prior == oldPriority)) {
         list->processesOrgPrior[middle]->prior = newPriority;
         shellSort(list->processesOrgPrior, list->size, 'p');
         return true;
      }
   }

   return false;
}

// change the time of a process
bool changeTime_process(PROCESS* list, TIME* oldTime, TIME* newTime) {
   if(list != NULL) {
      int start, middle, final;

      start = 0;
      final = list->size-1;
      middle = (start + final)/2;

      // binary search with the function compareTime
      while((start < final) && (compareTime(list->processesOrgTime[middle]->start, oldTime) != 0)) {
         if(compareTime(list->processesOrgTime[middle]->start, oldTime) == -1)
            start = middle + 1;
         else
            final = middle - 1;
         middle = (start + final)/2;
      }

      // change the info and sort the list
      if((start <= final) && (compareTime(list->processesOrgTime[middle]->start, oldTime) == 0)) {
         if(changeInfo(list->processesOrgTime[middle]->start, newTime));
            shellSort(list->processesOrgTime, list->size, 't');
         return true;
      }
   }

   return false;
}

// print all processes in descending order of priority
void printDescPriority_process(PROCESS* list) {
   if (list == NULL || list->size == 0) {
      printf("No processes to print\n");
      return;
   }

   int i;
   for (int i = list->size - 1; i >= 0; i--) {
      SHEET* sheet = list->processesOrgPrior[i];
      printf("%02d ", sheet->prior);
      printTime(sheet->start);
      printf(" %s\n", sheet->description);
   }
}

// print all processes in ascending order of time
void printAscTime_process(PROCESS* list) {
   if (list == NULL || list->size == 0) {
      printf("No processes to print\n");
      return;
   }

   int i;
   for (i = 0; i < list->size; i++) {
      SHEET* sheet = list->processesOrgTime[i];
      printf("%02d ", sheet->prior);
      printTime(sheet->start);
      printf(" %s\n", sheet->description);
   }
}

//free the process list
bool freeProcessList(PROCESS** list) {
   if (*list == NULL) 
      return false;

   for (int i = 0; i < (*list)->size; i++) {
      freeTime(&((*list)->processesOrgPrior[i]->start));
      free((*list)->processesOrgPrior[i]);
   }

   free(*list);
   return true;
}
