//Leitura de arquivo
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
  char nome[30];
  printf("Digite nome: ");
  fgets(nome, 30, stdin);
  printf("\n%s", nome);

  return(0);
}