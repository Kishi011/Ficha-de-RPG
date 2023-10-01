#define ARQLOGIN "login.txt"

#ifndef ARQFICHA
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
#endif

typedef struct {
    char usuario[25];
    char senha[16];
} Login;

int checaConta(FILE*);
int criaConta(FILE*);
int validaConta(FILE*, Login, short int*);

int checaConta(FILE* arq) {
    arq = fopen(ARQLOGIN, "r");
    Login conta;
    if(fread(&conta, sizeof(Login), 1, arq)) {
        short int tentativas = 3;
        printf("validando login...\n");
        return validaConta(arq, conta, &tentativas);
    }
    fclose(arq);
    return criaConta(arq);
}

int validaConta(FILE* arq, Login conta, short int* tentativas) {
    if(*tentativas > 0) {
        
        Login input;
        memset(&input, 0, sizeof(Login));
        printf("usuario: ");
        scanf("%25s", input.usuario);
        fflush(stdin);
        printf("senha: ");
        scanf("%16s", input.senha);
        fflush(stdin);
        
        if(!strcmp(conta.usuario, input.usuario) && !strcmp(conta.senha, input.senha)) {
            // system("clear");
            printf("\e[1;1H\e[2J"); // regex em C que limpa a tela do console
            printf("logado com sucesso!\n");
        } else {
            // system("clear");
            printf("\e[1;1H\e[2J"); // regex em C que limpa a tela do console
            printf("usuario ou senha invalido\n");
            (*tentativas)--;
            printf("tentativas restantes: %d\n", *tentativas);
            return validaConta(arq, conta, tentativas);
        }
    } else {
        printf("acesso negado\n");
        return 0;
    }
    printf("PRESSIONE QUALQUER TECLA PARA CONTINUAR\n");
    getchar();
    printf("\e[1;1H\e[2J"); // regex em C que limpa a tela do console
    return 1;
}

int criaConta(FILE* arq) {
    arq = fopen(ARQLOGIN, "w");
    printf("criando conta...\n");
    Login conta;
    memset(&conta, 0, sizeof(Login));
    printf("usuario: ");
    scanf("%s", conta.usuario);
    fflush(stdin);
    printf("senha: ");
    scanf("%s", conta.senha);
    fflush(stdin);
    if(fwrite(&conta, sizeof(Login), 1, arq)) {
        // system("clear");
        printf("\e[1;1H\e[2J"); // regex em C que limpa a tela do console
        printf("conta criada com sucesso\n");
    } else {
        // system("clear");
        printf("\e[1;1H\e[2J"); // regex em C que limpa a tela do console
        printf("erro: ");
        ferror(arq);
        printf("tente novamente\n");
        fclose(arq);
        criaConta(arq);
    }
    printf("PRESSIONE QUALQUER TECLA PARA CONTINUAR\n");
    getchar();
    printf("\e[1;1H\e[2J"); // regex em C que limpa a tela do console
    fclose(arq);
    return 1;
}