#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nome[30];
    char celular[12];
    char email[36];
    int codigo;
} Lista;

/*
int levenshtein(char[], int, char[], int);
int min(int, int, int);
 
int levenshtein(char a[], int m, char b[], int n) {
        //Se alguma string for vazia, a diferença é a inserção de todos os caracteres da outra
		if (m == 0) {
			return n;
		}
        
		if (n == 0) {
			return m;
		}
        
		//Se as últimas letras são iguais, verifica a diferença para os demais caracteres das strings
        if (a[m - 1] == b[n - 1]) {
            return levenshtein(a, m - 1, b, n - 1);
		}

        int s = levenshtein(a, m - 1, b, n - 1); //Substitui o último caractere a[m] por b[n]
        int r = levenshtein(a, m, b, n - 1); //Remove o último caractere a[m]
        int i = levenshtein(a, m - 1, b, n); //Insere o último caractere b[n] após a[m] 

		//Qualquer operação (substituir, remover ou inserir) implicará em um custo 1
        return min(s, r, i) + 1;
}

int min(int a, int b, int c) {
	int min = a;

	if (min > b) {
		min = b;
	}

	if (min > c) {
		min = c;
	}

	return min;
}*/

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
            printf("Celular: %s\n", contato[i].celular);
            printf("Email: %s\n", contato[i].email);
            printf("-===========-\n");
        }
    }
}

//Função que salva os contatos no arquivo "contato.txt"
int salvar(Lista contato[], int cont){
    char pulalinha[2]="\n";
    FILE *arquivo = fopen("contato.txt","w");
    for (int i = 0; i < cont; i++){
        int retorno = fputs(contato[i].nome,arquivo);
        int pula = fputs(pulalinha,arquivo);
        int retorno2 = fputs(contato[i].celular,arquivo);
        int pula2 = fputs(pulalinha,arquivo);
        char temporario[12];
        sprintf(temporario, "%i", contato[i].codigo);
        int retorno3 = fputs(temporario,arquivo);
        int pula3 = fputs(pulalinha,arquivo);
        int retorno4 = fputs(contato[i].email,arquivo);
        int pula4 = fputs(pulalinha,arquivo);

    }
    fclose(arquivo);
}
//Criar uma variavel de validação de contato, assim só podera excluir, alterar ou procurar algum contato caso essa
//variavel for 1. No inicio do codigo a variavel é 0 e só é setada para 1 na criação de um contato
//Possivel problema, uma variavel a mais a se guardar no arquivo
int main()
{
    Lista contato[1000];
    int x = 1, opcao, cont = 0;

    FILE *arquivo = fopen("contato.txt","r"); //Le o arquivo "contato.txt"
    if(arquivo!=NULL){   //le o arquivo se não estiver em branco
        /*
        char texto[36];
        char *retorno = fgets(contato[cont].nome,'\n',arquivo);
        printf("Lido:%i\n", cont+1);
        cont++;*/
    }
    fclose(arquivo);
    while (x >= 1)
    {
        printf("!AGENDA DE CONTATOS!\n");
        printf("Escolha uma opcao:\n1--Registrar novo contato\n2--Excluir contato existente\n");
        printf("3--Alterar contator existente\n4--Listar contatos existentes\n5--Localizar Contato\n6--Fechar Programa\n");
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
            scanf("%s", &contato[cont].celular);
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
                    printf("OK! Nome do contato %d alterado para %s\n",alterar,contato[alterar-1].nome);
                    break;

                case 2:
                    printf("Digite o novo email: ");
                    scanf("%s", contato[alterar - 1].email);
                    //validar novo email
                    printf("OK! Email do contato %d alterado para %s\n",alterar,contato[alterar-1].email);
                    break;

                case 3:
                    printf("Digite o novo celular: ");
                    scanf("%s", contato[alterar - 1].celular);
                    printf("OK! Celular do contato %d alterado para %s\n",alterar,contato[alterar-1].celular);
                    break;

                case 4:
                    printf("Digite o nome: ");
                    scanf("%s", &contato[alterar - 1].nome);
                    fflush(stdin);
                    printf("Digite o numero: ");
                    scanf("%s", &contato[alterar - 1].celular);
                    printf("Digite o email: ");
                    scanf("%s", &contato[alterar - 1].email);
                    fflush(stdin);
                    printf("OK! Informações do contato alteradas\n");
                    break;

                default:
                    printf("Ocorreu um erro, tente novamente.\n");
            }
            break;

        case 4: //Listar contatos
            printf(" -=!LISTAR CONTATOS!=- \n");
            listar(contato, cont);
            break;

        case 5:    
            printf(" -=!LOCALIZAR CONTATOS!=- \n");
            char resultadoDaBusca[100];
            char pesquisa;
            printf("Digite o nome do contato: \n");
            scanf("%s",&pesquisa);
            /*
            for(int i=0; i<cont; i++){

                char a[36];

                strcpy(a,contato[i].nome);
                printf("%s",a);
                int semelhanca = levenshtein(a, strlen(a), pesquisa, strlen(pesquisa));
                printf("%d\n", semelhanca);
                if(semelhanca > 0 || (strcmp (pesquisa, a) == 0) ){
                    strcpy(resultadoDaBusca[semelhanca],a);
                    printf("%c\n",resultadoDaBusca[semelhanca]);
                }    
            }

            for(int i = 0; i <= 100; i++){
                printf("%c \n", resultadoDaBusca[i]);
            }
            */
            break;

        case 6: //Salva os contatos e então fecha o Programa
            printf("SALVANDO PROGRAMA...\n");
            salvar(contato, cont); //salva os contatos
            x = 0; //sai do while, fechando o programa 
            break;

        default: //Não escolheu um numero entre 1 a 5
            printf("Opcao invalida, tente novamente!\n");
            break;
        }
    }
    return 0;
}
