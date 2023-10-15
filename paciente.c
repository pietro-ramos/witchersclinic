#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"
#include "get_input.h"

#define MAX_PACIENTES 100

void listarPacientes(char* nomesPacientes[], int numPacientes) {
    if (numPacientes == 0) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    printf("Pacientes cadastrados:\n");
    for (int i = 0; i < numPacientes; i++) {
        printf("%d. %s\n", i, nomesPacientes[i]);
    }
}

void cadastrarPaciente(char* nomesPacientes[], int* numPacientes) {
    char nome;
    nome = get_string_input("Digite o nome do paciente: ");

    if (*numPacientes >= MAX_PACIENTES) {
        printf("Limite de pacientes cadastrados atingido.\n");
        return;
    }

    nomesPacientes[*numPacientes] = strdup(nome);
    (*numPacientes)++;

    printf("Paciente cadastrado com sucesso!\n");
}

void excluirPaciente(char* nomesPacientes[], int* numPacientes) {
    if (*numPacientes == 0) {
        printf("Nenhum paciente cadastrado para exclus�o.\n");
        return;
    }

    int index = get_int_input("Digite o c�digo do paciente a ser exclu�do: ");

    if (index < 0 || index >= *numPacientes) {
        printf("C�digo de paciente inv�lido.\n");
        return;
    }

    free(nomesPacientes[index]);

    for (int i = index; i < *numPacientes - 1; i++) {
        nomesPacientes[i] = nomesPacientes[i + 1];
    }

    (*numPacientes)--;

    printf("Paciente exclu�do com sucesso!\n");
}

