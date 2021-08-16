#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/*
teste de validação de email: recebe a string depois verifica a primeira ocorrência do caractere "@" informa no ponteiro
após isso testa se o valor do ponteiro continua nulo ou não
*/
int main(){
    
    char email[36];
    char *verificaEmail;
    
   
	printf("informe email ");
    
    scanf("%s", &email);
    verificaEmail = strchr(email, '@');

    
    if(verificaEmail != NULL){
        printf("\nemail valido\n");
    } else{
        printf("\n email invalido \n");
    }

    
    return 0;
}
