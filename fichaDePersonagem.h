#define ARQFICHA "ficha.bin"

#include <conio.h>

#ifndef ARQLOGIN
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
#endif

#include "controleLog.h"

typedef struct {
    short int inteligencia;
    short int forca;
    short int carisma;
    short int destreza;
    short int constituicao;
} Atributos;

typedef struct {
    char nome[50];
    char raca[15];
    char classe[20];
    Atributos attr;
} Personagem;

void listaTodosOsPersonagens(FILE* arq);
int montaNovaFichaDePersonagem(FILE* arq);
int editaPersonagem(FILE* arq);
int excluirPersonagem(FILE* arq);
int buscaPersonagem(FILE* arq);
void mostraPersonagem(Personagem* p);
void alocarAtributos(Personagem* p);
int escolheRaca(Personagem* p);
int escolheClasse(Personagem* p);
void menuAlteracao();
int salvaAlteracoes(FILE*);
int alteraAttr(Personagem*);
void system_wait_for_input();

Personagem p;
int posicao;

void listaTodosOsPersonagens(FILE* arq) {
    arq = fopen(ARQFICHA, "rb");
    if(arq == NULL) {
        printf("erro: ");
        ferror(arq);
        return;
    }

    Personagem temp;
    int i = 1;
    printf("\tFICHAS DE PERSONAGENS\n\n\n");
    while(fread(&temp, sizeof(Personagem), 1, arq)) {
        printf("\t#%d\n\n", i);
        i++;
        mostraPersonagem(&temp);
    }
    FILE* arqLog = fopen(ARQLOG, "a");
    gravaLog(arqLog, "Visualizou as fichas de personagens");
    fclose(arq);
    system_wait_for_input();
}

int buscaPersonagem(FILE* arq) {
    posicao = 0;
    char nomePersonagem[50];
    printf("Digite o nome do personagem: ");
    scanf("%50[^\n]", nomePersonagem);
    fflush(stdin);

    arq = fopen(ARQFICHA, "rb");
    while(fread(&p, sizeof(Personagem), 1, arq)) {
        if(strcmp(p.nome, nomePersonagem) == 0) {
            fclose(arq);
            return 1;
        }
        posicao++;
    }
    printf("Erro: Personagem nao encontrado\n");
    fclose(arq);
    return 0;
}

int editaPersonagem(FILE* arq) {
    if(buscaPersonagem(arq)) {
        printf("Personagem encontrado\n");
        int opt = -1;
        while(1) {
            menuAlteracao();
            scanf("%d", &opt);
            switch(opt) {
                case 0:
                    system("cls");
                    return salvaAlteracoes(arq);
                    break;
                case 1:
                    printf("Novo nome: ");
                    scanf("%*c");
                    scanf("%50[^\n]", p.nome);
                    fflush(stdin);
                    system("cls");
                    printf("Nome alterado, novo nome: %s\n", p.nome);
                    break;
                case 2:
                    escolheRaca(&p);
                    system("cls");
                    printf("Raca alterada, nova raca: %s\n", p.raca);
                    break;
                case 3:
                    escolheClasse(&p);
                    system("cls");
                    printf("Classe alterada, nova classe: %s\n", p.classe);
                    break;
                case 4:
                    alteraAttr(&p);
                    printf("Atributos alterados\n");
                    break;
                default:
                    printf("SELECIONE UMA OPCAO VALIDA\n");
                    system_wait_for_input();
                    break;
            }
        }
    }
    return 0;
}

int alteraAttr(Personagem* p) {
  memset(&p->attr, 0, sizeof(Atributos));
  alocarAtributos(p);
  return 1;
}

void mostraPersonagem(Personagem* p) {
    printf("\tnome: %s\n", p->nome);
    printf("\traca: %s\t\t", p->raca);
    printf("classe: %s\n", p->classe);

    printf("\n\tatributos:\n\n");
    printf("\t\tinteligencia->%hd\t\tforca->%hd\n", p->attr.inteligencia, p->attr.forca);
    printf("\t\tcarisma->%hd\t\tdestreza->%hd\n", p->attr.carisma, p->attr.destreza);
    printf("\t\tconstituicao->%hd\n", p->attr.constituicao);
    printf("\n\t-----------------------------------------------\n");
}

int montaNovaFichaDePersonagem(FILE* arq) {
    arq = fopen(ARQFICHA, "ab");
    Personagem temp;
    // limpa o espaço de memória reservado para a variável
    memset(&temp, 0, sizeof(Personagem));
    printf("Digite o nome do Personagem: ");
    scanf("%50[^\n]", temp.nome);
    fflush(stdin);
    escolheRaca(&temp);
    escolheClasse(&temp);
    alocarAtributos(&temp);
    fwrite(&temp, sizeof(Personagem), 1, arq);
    FILE* arqLog = fopen(ARQLOG, "a");
    gravaLog(arqLog, "Montou uma ficha de personagem");
    fclose(arq);
    printf("FICHA DE PERSONAGEM CRIADA COM SUCESSO\n");
    system_wait_for_input();
    return 1;
}

void alocarAtributos(Personagem* p) {
    system("cls");
    short int pontos = 27;
    short int pontosAlocados = 0;
    short int escolha;
    while(pontos > 0) {
        printf("PONTOS DISPONIVEIS: %hd\n", pontos);
        printf("Escolha o atributo para inserir pontos:\n");
        printf("1 - inteligencia -> %hd\n", p->attr.inteligencia);
        printf("2 - forca -> %hd\n", p->attr.forca);
        printf("3 - carisma -> %hd\n", p->attr.carisma);
        printf("4 - destreza -> %hd\n", p->attr.destreza);
        printf("5 - constituicao -> %hd\n", p->attr.constituicao);
        printf("Escolha: ");
        scanf("%hd", &escolha);
        if(escolha < 1 || escolha > 5) {
            system("cls");
            printf("OPCAO INVALIDA\n");
            continue;
        }
        printf("digite a quantidade de pontos para colocar no atributo: ");
        scanf("%hd", &pontosAlocados);
        if(pontosAlocados > pontos) {
            system("cls");
            printf("OS PONTOS INFORMADOS ULTRAPASSAM A QUANTIDADE DE PONTOS DISPONIVEIS\n");
            continue;
        }
        pontos -= pontosAlocados;
        switch(escolha) {
            case 1:
                p->attr.inteligencia += pontosAlocados;
                break;
            case 2:
                p->attr.forca += pontosAlocados;
                break;
            case 3:
                p->attr.carisma += pontosAlocados;
                break;
            case 4:
                p->attr.destreza += pontosAlocados;
                break;
            case 5:
                p->attr.constituicao += pontosAlocados;
                break;
        }
        pontosAlocados = 0;
        system("cls");
    }
}

int escolheRaca(Personagem* p) {
    system("cls");
    short int escolha;
    printf("Escolha a raca:\n");
    printf("1 - Elfo\n");
    printf("2 - Humano\n");
    printf("3 - Anao\n");
    printf("4 - Tiefling\n");
    printf("5 - Hobbit\n");
    printf("6 - Orc\n");
    printf("7 - Gnomo\n");
    printf("Escolha: ");
    scanf("%hd", &escolha);
    switch(escolha) {
        case 1:
            strcpy(p->raca, "Elfo");
            break;

        case 2:
            strcpy(p->raca, "Humano");
            break;

        case 3:
            strcpy(p->raca, "Anao");
            break;

        case 4:
            strcpy(p->raca, "Tiefling");
            break;

        case 5:
            strcpy(p->raca, "Hobbit");
            break;

        case 6:
            strcpy(p->raca, "Orc");
            break;

        case 7:
            strcpy(p->raca, "Gnomo");
            break;

        default:
            system("cls");
            printf("OPCAO INVALIDA\n");
            escolheRaca(p);
            break;
    }
    return 1;
}

int escolheClasse(Personagem* p) {
    system("cls");
    short int escolha;
    printf("Escolha a classe:\n");
    printf("1 - Barbaro\n");
    printf("2 - Mago\n");
    printf("3 - Arqueiro\n");
    printf("4 - Bardo\n");
    printf("5 - Druida\n");
    printf("6 - Ladino\n");
    printf("7 - Paladino\n");
    printf("Escolha: ");
    scanf("%hd", &escolha);
    switch(escolha) {
        case 1:
            strcpy(p->classe, "Barbaro");
            break;

        case 2:
            strcpy(p->classe, "Mago");
            break;

        case 3:
            strcpy(p->classe, "Arqueiro");
            break;

        case 4:
            strcpy(p->classe, "Bardo");
            break;

        case 5:
            strcpy(p->classe, "Druida");
            break;

        case 6:
            strcpy(p->classe, "Ladino");
            break;

        case 7:
            strcpy(p->classe, "Paladino");
            break;

        default:
            system("clear");
            printf("OPCAO INVALIDA\n");
            escolheRaca(p);
            break;
    }
    return 1;
}

void menuAlteracao() {
    printf("ESCOLHA O QUE QUER QUE SEJA ALTERADO\n");
    printf("1 - NOME DO PERSONAGEM\n");
    printf("2 - RACA\n");
    printf("3 - CLASSE\n");
    printf("4 - ATRIBUTOS\n");
    printf("0 - SAIR\n");
    printf("Escolha: ");
}

/**
 * Essa funcao salva os personagens em um arquivo temporario e depois passa para
 * o arquivo principal.
 */
int salvaAlteracoes(FILE* arq) {
    char nomeArqTemp[50] = "temp____";
    strcat(nomeArqTemp, ARQFICHA);
    FILE* arqTemp = fopen(nomeArqTemp, "wb");
    arq = fopen(ARQFICHA, "rb");
    Personagem tempPersonagem;
    int indexTemp = 0;
    while(fread(&tempPersonagem, sizeof(Personagem), 1, arq)) {
        if(indexTemp == posicao) {
            fwrite(&p, sizeof(Personagem), 1, arqTemp);
            indexTemp++;
            continue;
        }
        fwrite(&tempPersonagem, sizeof(Personagem), 1, arqTemp);
        indexTemp++;
    }
    fclose(arqTemp);
    fclose(arq);
    arqTemp = fopen(nomeArqTemp, "rb");
    arq = fopen(ARQFICHA, "wb");
    while(fread(&tempPersonagem, sizeof(Personagem), 1, arqTemp)) {
        fwrite(&tempPersonagem, sizeof(Personagem), 1, arq);
    }
    fclose(arqTemp);
    fclose(arq);
    FILE* arqLog = fopen(ARQLOG, "a");
    gravaLog(arqLog, "Editou um personagem");
    fclose(arqLog);
    system_wait_for_input();
    return 1;
}

/**
 * Essa funcao funciona quenem a funcao de edicao, porem, para fazer a exclusao,
 * ele nao coloca o registro excluido no arquivo temporario 
 */
int excluirPersonagem(FILE* arq) {
    if(buscaPersonagem(arq)) {
        char nomeArqTemp[50] = "temp____";
        strcat(nomeArqTemp, ARQFICHA);
        FILE* arqTemp = fopen(nomeArqTemp, "wb");
        arq = fopen(ARQFICHA, "rb");
        Personagem tempPersonagem;
        int indexTemp = 0;
        while(fread(&tempPersonagem, sizeof(Personagem), 1, arq)) {
            if(indexTemp == posicao) {
                indexTemp++;
                continue;
            }
            fwrite(&tempPersonagem, sizeof(Personagem), 1, arqTemp);
            indexTemp++;
        }
        fclose(arqTemp);
        fclose(arq);
        arqTemp = fopen(nomeArqTemp, "rb");
        arq = fopen(ARQFICHA, "wb");
        while(fread(&tempPersonagem, sizeof(Personagem), 1, arqTemp)) {
            fwrite(&tempPersonagem, sizeof(Personagem), 1, arq);
        }
        fclose(arqTemp);
        fclose(arq);
        FILE* arqLog = fopen(ARQLOG, "a");
        gravaLog(arqLog, "Excluiu um personagem");
        fclose(arqLog);
        printf("Personagem excluido\n");
        system_wait_for_input();
        return 1;
    }
    return 0;
}

void system_wait_for_input() {
    printf("PRESSIONE QUALQUER TECLA PARA CONTINUAR\n");
    getchar();
    system("cls");
}