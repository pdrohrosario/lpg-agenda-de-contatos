#include <stdio.h>
#include <stdlib.h>
//testando novamente

typedef struct {
		char nome[30];
		int celular;
		char email[36];
		int codigo;
} Lista;

int listar(Lista contato[], int cont){
    printf(" -=!CONTATOS!=- \n");
    for (int i = 0; i < cont; i++){
        printf("Codigo de Identificacao: %d\n", contato[i].codigo);
        printf("Nome: %s\n", contato[i].nome);
        printf("Celular: %i\n", contato[i].celular);
        printf("Email: %s\n", contato[i].email);
        printf("-===========-\n");
    }
}

int main() {
	Lista contato[1000];
    int x=1, opcao, cont=0;
    while(x>=1){
		printf("!AGENDA DE CONTATOS!\n");
		printf("Escolha uma opcao:\n1--Registrar novo contato\n2--Excluir contato existente\n");
        printf("3--Alterar contator existente\n4--Listar contatos existentes\n5--Fechar Programa\n");
		scanf("%i", &opcao);
		printf("-==================-\n");
		switch (opcao){
		    case 1:   //Criar novos Contatos
                printf(" -=!REGISTRAR CONTATO!=- \n");
                printf("Digite o nome: ");
                scanf("%s", &contato[cont].nome);
                fflush(stdin);
                printf("Digite o numero: ");
                scanf("%i", &contato[cont].celular);
                printf("Digite o email: ");
                scanf("%s", &contato[cont].email);
                fflush(stdin);
                contato[cont].codigo = cont + 1;
                cont++;
                break;
            case 2:   //Excluir Contatos
                printf(" -=!EXCLUIR CONTATO!=- \n");
                listar(contato, cont);
                break;
            case 3:  //Alterar Contatos
                printf(" -=!ALTERAR CONTATO EXISTENTE!=- \n");
                listar(contato, cont); //printa os contatos com numero na frente
                break;
            case 4:   //Listar contatos
                printf(" -=!LISTAR CONTATOS!=- \n");
                listar(contato, cont);
                break;
            case 5:    //Fecha o Programa
                printf("FECHANDO PROGRAMA...\n");
                x=0;
                break;
            default:   //Não escolheu um numero entre 1 a 5
                printf("Opcao invalida, tente novamente!\n");
                break;
            }
	}
	return 0;
}
