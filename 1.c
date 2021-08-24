#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//Alunos: Thiago Henrique Junkes; Pedro Rosario; Wagner Gomes; Lucas Felipe Pereira; Tiago Graciotto.
//Repositório do GITHUB: https://github.com/pdrohrosario/lpg-agenda-de-contatos - branch:oficial
typedef struct
{
    char nome[30];
    char celular[14];
    char email[36];
    int codigo;
} Lista;


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
}

//Função que válida o código de usuário
int validaCodigo(Lista contato[], int cont)
{
    int codigo;
    printf("Escolha o codigo do contato que deseja alterar:");
    scanf("%i", &codigo);

    while ((codigo < 1 || codigo >= cont) || contato[codigo].codigo != codigo )
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
    for (int i = 1; i <= cont; i++)
    {
        if (contato[i].codigo > 0) //Só mostra os codigos positivos
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
    for (int i = 1; i < cont; i++){
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

//Função que valida se o email possui @
bool validarEmail(char email[36]){

    char *verificaEmail;
    bool t = false;

    verificaEmail = strchr(email, '@');

    if(verificaEmail != NULL){
        t = true;
    } else{
        t = false;
    }

    return t;
}

int main()
{
    Lista contato[1000];
    int x = 1, opcao, cont = 1;
    
    FILE *arquivo = fopen("contato.txt","r"); //Abre o arquivo apenas para leitura
    if(arquivo!=NULL){   //le o arquivo se não estiver em branco
        char texto[36];
        char temporario;
        int linha=1, conttexto = 0;
        do{
            temporario = getc(arquivo);
            if(temporario != '\n'){
                texto[conttexto]=temporario;
                conttexto++;
            } else{
                switch (linha){
                case 1: //salva nome
                    strcpy(contato[cont].nome,texto);
                    break;
                case 2: //salva celular
                    strcpy(contato[cont].celular,texto);
                    break;
                case 3: //salva codigo
                    contato[cont].codigo = strtol(texto, NULL, 10); //transforma char em int
                    break;
                case 4: //salva email
                    strcpy(contato[cont].email,texto);
                    linha=0;
                    cont++;
                    break;
                default:
                    break;
                }
                linha++;
                conttexto=0;
                memset(texto, 0, 36); //limpa a variavel texto
            }

        }while(temporario != EOF); //enquanto não achar o final do arquivo
    }
    fclose(arquivo); //fecha arquivo
    
    while (x >= 1)
    {
        printf("!AGENDA DE CONTATOS!\n");
        printf("Escolha uma opcao:\n1--Registrar novo contato\n2--Excluir contato existente\n");
        printf("3--Alterar contato existente\n4--Listar contatos existentes\n5--Localizar Contato\n6--Fechar Programa\n");
        scanf("%i", &opcao);
        printf("-==================-\n");
        switch (opcao)
        {
        case 1: //Criar novos Contatos
            printf(" -=!REGISTRAR CONTATO!=- \n");
            printf("Digite o nome: ");
            getchar();
            gets(contato[cont].nome);
            printf("Digite o numero: ");
            gets(contato[cont].celular);
            fflush(stdin);
            printf("Digite o email: ");
            scanf("%s", &contato[cont].email);
            fflush(stdin);

            while (validarEmail(contato[cont].email)==false)
            {
                printf("E-mail invalido \nDigite o email: ");
                scanf("%s", &contato[cont].email);
                fflush(stdin);
                validarEmail(contato[cont].email);
            }
            contato[cont].codigo = cont; //Define um codigo para o contato
            cont++;
            printf("Contato criado com sucesso!\n");
            break;

        case 2: //Excluir Contatos
            printf(" -=!EXCLUIR CONTATO!=- \n");
            listar(contato, cont);
            int excluir = validaCodigo(contato, cont);
            contato[excluir].codigo = contato[excluir].codigo * -1;
            printf("Contato %i excluido!\n", excluir);
            break;

        case 3: //Alterar Contatos
            printf(" -=!ALTERAR CONTATO EXISTENTE!=- \n");
            listar(contato, cont); //printa os contatos com numero na frente
            int alterar = validaCodigo(contato, cont);
            printf("Digite: 1 para alterar nome. \n");
            printf("Digite: 2 para alterar email. \n");
            printf("Digite: 3 para alterar celular. \n");
            printf("Digite: 4 para alterar todas as informacoes acima. \n");
            int selecione;
            scanf("%d",&selecione);

            switch(selecione){
                case 1: 
                    printf("Digite o novo nome: ");
                    getchar();
                    gets(contato[alterar].nome);
                    printf("OK! Nome do contato %d alterado para %s\n",alterar,contato[alterar].nome);
                    break;

                case 2:
                    printf("Digite o novo email: ");
                    gets(contato[alterar].email);
                    while (validarEmail(contato[alterar].email)==false)
                    {
                        printf("E-mail invalido \nDigite o email: ");
                        scanf("%s", &contato[alterar].email);
                        fflush(stdin);
                        validarEmail(contato[alterar].email);
                    }
                    printf("OK! Email do contato %d alterado para %s\n",alterar,contato[alterar].email);
                    break;

                case 3:
                    printf("Digite o novo celular: ");
                    getchar();
                    gets(contato[alterar].celular);
                    printf("OK! Celular do contato %d alterado para %s\n",alterar,contato[alterar].celular);
                    break;

                case 4:
                    printf("Digite o nome: ");
                    getchar();
                    gets(contato[alterar].nome);
                    printf("Digite o numero: ");
                    getchar();
                    gets(contato[alterar].celular);
                    printf("Digite o email: ");
                    scanf("%s", &contato[alterar].email);
                    fflush(stdin);
                    while (validarEmail(contato[alterar].email)==false)
                    {
                        printf("E-mail invalido \nDigite o email: ");
                        scanf("%s", &contato[alterar].email);
                        fflush(stdin);
                        validarEmail(contato[alterar].email);
                    }
                    printf("OK! Informacoes do contato alteradas\n");
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
            int resultadoDaBusca[1000];
            int op;
            char pesquisa[50];
            printf("Digite o nome do contato: \n");
            scanf("%s",&pesquisa);
            printf("\n");
            int jaexiste = 0;
            char vazio[]= " ";
            char a[50] = " ";
            char b[50] = " ";

	        memcpy(b, pesquisa, strlen(pesquisa)+1);

            for (int i = 1; i < cont ;i++){
                memcpy(a, contato[i].nome, strlen(contato[i].nome)+1);
                op = levenshtein(a, strlen(a), b, strlen(b));
                if(op>=1 && op <= 5 || (strcmp (a, b) == 0) && contato[i].codigo > 0) {
                   printf("%d i=%d\n",op ,i);
                   if(resultadoDaBusca[op] == NULL){
                     resultadoDaBusca[op] = i;
                   }
                   else  
                   {
                       for (int z = 100; op + 1 <= z; z--){
                         resultadoDaBusca[z] = resultadoDaBusca[z - 1];
                       }
                       resultadoDaBusca[op+1] = i;     
                   }
                }
                memset(a,0,50);
            }
           
            int contzero=0;
            for (int i = 0; i < 100; i++){
                //printf("%d ",i);
                if(resultadoDaBusca[i]!=NULL){
                    int posicao = resultadoDaBusca[i];
                    printf("%s\n", contato[posicao].nome);
                }
            }
            
            memset(resultadoDaBusca,0,100);
            break;

        case 6: //Salva os contatos e então fecha o Programa
            printf("SALVANDO PROGRAMA...\n");
            salvar(contato, cont); //salva os contatos
            x = 0; //sai do while, fechando o programa 
            break;

        default: //Não escolheu um numero entre 1 a 6
            printf("Opcao invalida, tente novamente!\n");
            break;
        }
    }
    return 0;
}
