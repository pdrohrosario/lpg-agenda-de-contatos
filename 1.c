#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nome[30];
    int celular;
    char email[36];
    int codigo;
} Lista;

//Função que válida se o código de usuário
int validaCodigo(int cont)
{
    int codigo;
    printf("Escolha o codigo do contato que deseja alterar:");
    scanf("%i", &codigo);

    while (codigo < 1 || codigo >= cont + 1)
    { //valida se o codigo existe
        printf("Codigo inexistente, tente novamente: ");
        scanf("%i", &codigo);
    }
    return codigo;
}


//Função que lista os contatos
int listar(Lista contato[], int cont)
{
    printf(" -=!CONTATOS!=- \n");
    for (int i = 0; i < cont; i++)
    {
        if (contato[i].codigo > 0)
        {
            printf("Codigo de Identificacao: %d\n", contato[i].codigo);
            printf("Nome: %s\n", contato[i].nome);
            printf("Celular: %i\n", contato[i].celular);
            printf("Email: %s\n", contato[i].email);
            printf("-===========-\n");
        }
    }
}
//Criar uma variavel de validação de contato, assim só podera excluir, alterar ou procurar algum contato caso essa
//variavel for 1. No inicio do codigo a variavel é 0 e só é setada para 1 na criação de um contato
//Possivel problema, uma variavel a mais a se guardar no arquivo
int main()
{
    Lista contato[1000];
    int x = 1, opcao, cont = 0;
    while (x >= 1)
    {
        printf("!AGENDA DE CONTATOS!\n");
        printf("Escolha uma opcao:\n1--Registrar novo contato\n2--Excluir contato existente\n");
        printf("3--Alterar contator existente\n4--Listar contatos existentes\n5--Fechar Programa\n");
        scanf("%i", &opcao);
        printf("-==================-\n");
        switch (opcao)
        {
        case 1: //Criar novos Contatos
            printf(" -=!REGISTRAR CONTATO!=- \n");
            printf("Digite o nome: ");
            scanf("%s", &contato[cont].nome);
            fflush(stdin);
            printf("Digite o numero: ");
            scanf("%i", &contato[cont].celular);
            printf("Digite o email: ");
            scanf("%s", &contato[cont].email);
            fflush(stdin);
            //Precisa validar o email
            contato[cont].codigo = cont + 1;
            cont++;
            break;

        case 2: //Excluir Contatos
            printf(" -=!EXCLUIR CONTATO!=- \n");
            listar(contato, cont);
            int excluir = validaCodigo(cont);
            contato[excluir - 1].codigo = contato[excluir - 1].codigo * -1;
            break;

        case 3: //Alterar Contatos
            printf(" -=!ALTERAR CONTATO EXISTENTE!=- \n");
            listar(contato, cont); //printa os contatos com numero na frente
            int alterar = validaCodigo(cont);
            printf("Digite: 1 para alterar nome. \n");
            printf("Digite: 2 para alterar email. \n");
            printf("Digite: 3 para alterar celular. \n");
            printf("Digite: 4 para alterar todas as informações acima. \n");
            int selecione;
            scanf("%d",&selecione);

            switch(selecione){
                case 1: 
                    printf("Digite o novo nome: ");
                    scanf("%s", contato[alterar - 1].nome);
                    printf("OK! Nome do contato %d alterado para %s",alterar,contato[alterar].nome);
                    break;

                case 2:
                    printf("Digite o novo email: ");
                    scanf("%s", contato[alterar - 1].email);
                    //validar novo email
                    printf("OK! Email do contato %d alterado para %s",alterar,contato[alterar].email);
                    break;

                case 3:
                    printf("Digite o novo celular: ");
                    scanf("%i", contato[alterar - 1].celular);
                    printf("OK! Celular do contato %d alterado para %i",alterar,contato[alterar].celular);
                    break;

                case 4:
                    printf("Digite o nome: ");
                    scanf("%s", &contato[alterar - 1].nome);
                    fflush(stdin);
                    printf("Digite o numero: ");
                    scanf("%i", &contato[alterar - 1].celular);
                    printf("Digite o email: ");
                    scanf("%s", &contato[alterar - 1].email);
                    fflush(stdin);
                    printf("OK! Informações do contato alteradas");
                    break;

                default:
                    printf("Ocorreu um erro, tente novamente.\n");
            }
            break;

        case 4: //Listar contatos
            printf(" -=!LISTAR CONTATOS!=- \n");
            listar(contato, cont);
            break;

        case 5: //Fecha o Programa
            printf("FECHANDO PROGRAMA...\n");
            //Salvar Dados e entao fecha
            x = 0;
            break;

        default: //Não escolheu um numero entre 1 a 5
            printf("Opcao invalida, tente novamente!\n");
            break;
        }
    }
    return 0;
}
