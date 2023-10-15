#include <stdio.h>
#include <string.h>
#include "tratamento.h"
#include "bruxo.h"
#include "paciente.h"
#include "pocoes.h"
#include "get_input.h"


#define MAX_TRATAMENTOS 100

void listarTratamentos(char** nomesBruxos, char** nomesPacientes, char** nomesPocoes, int* diasTratamentos, int* dosagensDiarias, int numTratamentos) {
    if (numTratamentos == 0) {
        printf("Nenhum tratamento cadastrado.\n");
        return;
    }

    printf("Tratamentos cadastrados:\n");
    for (int i = 0; i < numTratamentos; i++) {
        printf("Tratamento %d:\n", i);
        printf("Bruxo: %s\n", nomesBruxos[i]);
        printf("Paciente: %s\n", nomesPacientes[i]);
        printf("Poção: %s\n", nomesPocoes[i]);
        printf("Dias de tratamento: %d\n", diasTratamentos[i]);
        printf("Dosagens diárias: %d\n", dosagensDiarias[i]);
        printf("====================\n");
    }
}

void iniciarTratamento(char** nomesBruxos, char** nomesPacientes, char** nomesPocoes, int* diasTratamentos, int* dosagensDiarias, int* numTratamentos, int numBruxos, int numPacientes, int numPocoes) {
    if (numBruxos == 0 || numPacientes == 0 || numPocoes == 0) {
        printf("Não é possível iniciar um tratamento. Verifique se há bruxos, pacientes e poções cadastrados.\n");
        return;
    }

    printf("Iniciando tratamento:\n");

    int bruxoIndex = get_int_input("Digite o código do bruxo: ");
    if (bruxoIndex < 0 || bruxoIndex >= numBruxos) {
        printf("Código de bruxo inválido.\n");
        return;
    }

    int pacienteIndex = get_int_input("Digite o código do paciente: ");
    if (pacienteIndex < 0 || pacienteIndex >= numPacientes) {
        printf("Código de paciente inválido.\n");
        return;
    }

    int pocaoIndex = get_int_input("Digite o código da poção: ");
    if (pocaoIndex < 0 || pocaoIndex >= numPocoes) {
        printf("Código de poção inválido.\n");
        return;
    }

    int dias = get_int_input("Digite o número de dias de tratamento: ");
    if (dias <= 0) {
        printf("Número de dias inválido.\n");
        return;
    }

    int dosagens = get_int_input("Digite o número de dosagens diárias: ");
    if (dosagens <= 0) {
        printf("Número de dosagens inválido.\n");
        return;
    }

    nomesBruxos[*numTratamentos] = nomesBruxos[bruxoIndex];
    nomesPacientes[*numTratamentos] = nomesPacientes[pacienteIndex];
    nomesPocoes[*numTratamentos] = nomesPocoes[pocaoIndex];
    diasTratamentos[*numTratamentos] = dias;
    dosagensDiarias[*numTratamentos] = dosagens;

    (*numTratamentos)++;

    printf("Tratamento iniciado com sucesso!\n");
}

void apagarTratamento(char** nomesBruxos, char** nomesPacientes, char** nomesPocoes, int* diasTratamentos, int* dosagensDiarias, int* numTratamentos) {
    if (*numTratamentos == 0) {
        printf("Nenhum tratamento cadastrado para apagar.\n");
        return;
    }

    int index = get_int_input("Digite o código do tratamento a ser apagado: ");

    if (index < 0 || index >= *numTratamentos) {
        printf("Código de tratamento inválido.\n");
        return;
    }

    for (int i = index; i < *numTratamentos - 1; i++) {
        nomesBruxos[i] = nomesBruxos[i + 1];
        nomesPacientes[i] = nomesPacientes[i + 1];
        nomesPocoes[i] = nomesPocoes[i + 1];
        diasTratamentos[i] = diasTratamentos[i + 1];
        dosagensDiarias[i] = dosagensDiarias[i + 1];
    }

    (*numTratamentos)--;

    printf("Tratamento apagado com sucesso!\n");
}

void ampliarTratamento(char** nomesBruxos, char** nomesPacientes, char** nomesPocoes, int* diasTratamentos, int* dosagensDiarias, int* numTratamentos) {
    if (*numTratamentos == 0) {
        printf("Nenhum tratamento cadastrado.\n");
        return;
    }

    int index = get_int_input("Digite o código do tratamento a ser ampliado: ");

    if (index < 0 || index >= *numTratamentos) {
        printf("Código de tratamento inválido.\n");
        return;
    }

    int dosagens = get_int_input("Digite o número de dosagens adicionais: ");
    if (dosagens <= 0) {
        printf("Número de dosagens inválido.\n");
        return;
    }

    dosagensDiarias[index] += dosagens;

    printf("Tratamento ampliado com sucesso!\n");
}

