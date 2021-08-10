#include <stdio.h>
#include <stdlib.h>
//testeeee

typedef struct {
		char nome[30];
		int celular;
		char email[36];
		int codigo;
} Contato;

int listar(Contato c[], int cont){
    printf(" -=!CONTATOS!=- \n");
    for (int i = 0; i < cont; i++){
        printf("Codigo de Identificacao: %d\n", c[i].codigo);
        printf("Nome: %s\n", c[i].nome);
        printf("Celular: %i\n", c[i].celular);
        printf("Email: %s\n", c[i].email);
        printf("-===========-\n");
    }
}

int main() {
	Contato c[1000];
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
                scanf("%s", &c[cont].nome);
                fflush(stdin);
                printf("Digite o numero: ");
                scanf("%i", &c[cont].celular);
                printf("Digite o email: ");
                scanf("%s", &c[cont].email);
                fflush(stdin);
                c[cont].codigo = cont + 1;
                cont++;
                break;
            case 2:   //Excluir Contatos
                printf(" -=!EXCLUIR CONTATO!=- \n");
                listar(c, cont);
                break;
            case 3:  //Alterar Contatos
                printf(" -=!ALTERAR CONTATO EXISTENTE!=- \n");
                listar(c, cont); //printa os contatos com numero na frente
                break;
            case 4:   //Listar contatos
                printf(" -=!LISTAR CONTATOS!=- \n");
                listar(c, cont);
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