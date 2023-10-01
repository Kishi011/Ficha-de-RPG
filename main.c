/**
 *  AUTORES
 *      - Vinicius M. Stuani
 *      - Eduardo Vinicius Bee
 *      - Gustavo Arthur Tedesco
 * 
 */


#include "login.h"
#include "fichaDePersonagem.h"

#ifndef ARQLOGIN
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
#else
    #ifndef ARQFICHA
        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
    #endif
#endif

int inicializaArquivo(FILE*, char[]);
void menu();
void finalizaPrograma();

int main()
{
    FILE *arqLogin, *arqFichaPersonagem, *arqLog;
    inicializaArquivo(arqLogin, ARQLOGIN);
    inicializaArquivo(arqFichaPersonagem, ARQFICHA);
    inicializaArquivo(arqLogin, ARQLOG);
    if(checaConta(arqLogin)) {
        
        int opt = -1;
        while(1) {
            menu();
            scanf("%d", &opt);
            scanf("%*c");
            switch(opt) {
                case 0:
                    finalizaPrograma();
                    break;
                
                case 1:
                    // system("clear");
                    printf("\e[1;1H\e[2J"); // regex em C que limpa a tela do console
                    montaNovaFichaDePersonagem(arqFichaPersonagem);
                    break;
                
                case 2:
                    // system("clear");
                    printf("\e[1;1H\e[2J"); // regex em C que limpa a tela do console
                    editaPersonagem(arqFichaPersonagem);
                    break;
                    
                case 3:
                    // system("clear");
                    printf("\e[1;1H\e[2J"); // regex em C que limpa a tela do console
                    listaTodosOsPersonagens(arqFichaPersonagem);
                    break;
                    
                case 4:
                    // system("clear");
                    printf("\e[1;1H\e[2J"); // regex em C que limpa a tela do console
                    excluirPersonagem(arqFichaPersonagem);
                    break;
                    
                default:
                    printf("SELECIONE UMA OPCAO VALIDA\n");
                    break;
            }
        }
    }

    return 0;
}

int inicializaArquivo(FILE* arq, char caminho[]) {
    arq = fopen(caminho, "r");
    if(arq == NULL) {
        arq = fopen(caminho, "w");
        printf("arquivo %s criado com sucesso\n", caminho);
        fclose(arq);
        return 1;
    }
    fclose(arq);
    return 1;
}

void menu() {
    printf("SELECIONE UMA OPCAO\n");
    printf("1 - CRIAR NOVO PERSONAGEM\n");
    printf("2 - EDITAR PERSONAGEM\n");
    printf("3 - LISTAR TODOS OS PERSONAGENS\n");
    printf("4 - EXCLUIR PERSONAGEM\n");
    printf("0 - SAIR\n");
    printf("Escolha: ");
}

void finalizaPrograma() {
    printf("PROGRAMA FINALIZADO\n");
    exit(0);
}