#include "../inc/processManager.h"

int main() {
   char operation[15];
   char option[2];
   bool flag;

   // get the operation from the user and store it in the variable operation
   while (strcmp(operation, "quit") != 0) {
      scanf("%s", operation);

      // if the operation is add
      if (strcmp(operation, "add") == 0) {
         int priority, hour, minute, second;
         char description[50];

         // get the priority, hour, minute, second, and description from the
         scanf("%d %d:%d:%d %s", &priority, &hour, &minute, &second,
               description);

         // storage time information in the time struct
         TIME* time = createTime(hour, minute, second);

         flag = add_process(priority, time, description);

         // verify if the process was added
         if (!flag) {
            printf("Process not added :(\n");
         }
      }

      // if the operation is exec
      else if (strcmp(operation, "exec") == 0) {
         // capturing the option flag
         scanf("%s", option);

         // if the option is -p, call the execute highest priority function
         if (strcmp(option, "-p") == 0) {
            executeHighPriority_process();
         }

         // if the option is -t, call the execute execute low time function
         else if (strcmp(option, "-t") == 0) {
            executeLowTime_process();
         }

         // otherwise, invalid option
         else {
            printf("Invalid option\n");
         }
      }

      // if operation is next
      else if (strcmp(operation, "next") == 0) {
         // capturing the option flag
         scanf("%s", option);

         // if the option is -p, call the next highest priority function
         if (strcmp(option, "-p") == 0) {
            infoHighPriority_process();
         }
         // if the option is -t, call the next low time function
         else if (strcmp(option, "-t") == 0) {
            infoLowTime_process();
         }

         // otherwise, invalid option
         else {
            printf("Invalid option\n");
         }
      }

      // if operation is change
      else if (strcmp(operation, "change") == 0) {
         // capturing the option flag
         scanf("%s", option);

         // if the option is -p
         if (strcmp(option, "-p") == 0) {
            int oldPriority, newPriority;
            scanf("%d|%d", &oldPriority, &newPriority);

            flag = changePriority_process(oldPriority, newPriority);

            // verify if the priority was changed
            if (!flag) {
               printf("Priority not changed :(\n");
            }
         }

         // if the option is -t
         else if (strcmp(option, "-t") == 0) {
            int oldHour, oldMinute, oldSecond, newHour, newMinute, newSecond;
            scanf("%d:%d:%d|%d:%d:%d", &oldHour, &oldMinute, &oldSecond,
                  &newHour, &newMinute, &newSecond);

            // storage time information in the time struct
            TIME* oldTime = createTime(oldHour, oldMinute, oldSecond);
            TIME* newTime = createTime(newHour, newMinute, newSecond);

            flag = changeTime_process(oldTime, newTime);

            // verify if the time was changed
            if (!flag) {
               printf("Time not changed :(\n");
            }
         }
      }

      // if operation is print
      else if (strcmp(operation, "print") == 0) {
         // capturing the option flag
         scanf("%s", option);

         // if the option is -p
         if (strcmp(option, "-p") == 0) {
            printDescPriority_process();
         }

         // if the option is -t
         else if (strcmp(option, "-t") == 0) {
            printAscTime_process();
         }

         // otherwise, invalid option
         else {
            printf("Invalid option\n");
         }
      }
   }

   return 0;
}
