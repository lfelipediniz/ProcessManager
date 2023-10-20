#include "../inc/dicionario.h"

int main() {
   SKIPLIST *dicionario = criar_sl();

   char operation[15];
   char palavra[MAX_PALAVRA];
   char definicao[MAX_DEFINICAO];
   int flag;
   NODE *resultado;

   // laço que vai capturar as operacoes ate o final do arquivo do runcodes
   while (scanf("%s", operation) != EOF) {
      // Continua até o final da entrada
      if (strcmp(operation, "insercao") == 0) {
         scanf("%s", palavra);
         fgets(definicao, MAX_DEFINICAO, stdin);
         definicao[strcspn(definicao, "\n")] = '\0';

         resultado = buscar_sl(dicionario, palavra);

         if (!resultado)
            inserir_sl(dicionario, palavra, definicao);
         else
            printf("OPERACAO INVALIDA\n");
      } else if (strcmp(operation, "busca") == 0) {
         scanf("%s", palavra);

         resultado = buscar_sl(dicionario, palavra);

         if (resultado)
            printf("%s%s\n", palavra, resultado->definicao);
         else
            printf("OPERACAO INVALIDA\n");
      } else if (strcmp(operation, "remocao") == 0) {
         scanf("%s", palavra);

         flag = deletar_sl(dicionario, palavra);
         if (!flag) printf("OPERACAO INVALIDA\n");
      } else if (strcmp(operation, "alteracao") == 0) {
         scanf("%s", palavra);
         fgets(definicao, MAX_DEFINICAO, stdin);

         definicao[strcspn(definicao, "\n")] = '\0';
         update_sl(dicionario, palavra, definicao);
      } else if (strcmp(operation, "impressao") == 0) {
         char ch1;
         getchar();  
         ch1 = getchar();  // le o char
         flag = printarPalavrasInicial_sl(dicionario, ch1);
         if (!flag) printf("NAO HA PALAVRAS INICIADAS POR %c\n", ch1);
      } else
         printf("OPERACAO INVALIDA\n");
   }

   liberar_sl(dicionario);

   return 0;
}
