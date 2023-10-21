#include "../inc/processManager.h"

int main() {
   char operation[15];

   // get the operation from the user and store it in the variable operation
   // while operation != quit
   while (strcmp(operation, "quit") != 0) {
      scanf("%s", operation);

      // If the operation is add
      if (strcmp(operation, "add") == 0) {

         int priority;
         TIME * time = create_time();
         
      }


   }

   return 0;
}
