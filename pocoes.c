#include <stdio.h>
#include <string.h>
#include "pocoes.h"
#include "get_input.h"

#define MAX_POCOES 100

void listarPocoes(char* nomesPocoes[], int numPocoes) {
    if (numPocoes == 0) {
        printf("Nenhuma po��o cadastrada.\n");
        return;
    }

    printf("Pocoes cadastradas:\n");
    for (int i = 0; i < numPocoes; i++) {
        printf("%d. %s\n", i, nomesPocoes[i]);
    }
}

void cadastrarPocao(char* nomesPocoes[], int* numPocoes) {
    char nome[50];
    printf("Digite o nome da po��o: ");
    scanf("%s", nome);

    if (*numPocoes >= MAX_POCOES) {
        printf("Limite de po��es cadastradas atingido.\n");
        return;
    }

    nomesPocoes[*numPocoes] = strdup(nome);
    (*numPocoes)++;

    printf("Po��o cadastrada com sucesso!\n");
}
void excluirPocao(char* nomesPocoes[], int* numPocoes) {
    if (*numPocoes == 0) {
        printf("Nenhuma po��o cadastrada para exclus�o.\n");
        return;
    }

    int index = get_int_input("Digite o c�digo da po��o a ser exclu�da: ");

    if (index < 0 || index >= *numPocoes) {
        printf("C�digo de po��o inv�lido.\n");
        return;
    }

    free(nomesPocoes[index]);

    for (int i = index; i < *numPocoes - 1; i++) {
        nomesPocoes[i] = nomesPocoes[i + 1];
    }

    (*numPocoes)--;

    printf("Po��o exclu�da com sucesso!\n");
}

