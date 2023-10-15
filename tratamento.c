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
        printf("Po��o: %s\n", nomesPocoes[i]);
        printf("Dias de tratamento: %d\n", diasTratamentos[i]);
        printf("Dosagens di�rias: %d\n", dosagensDiarias[i]);
        printf("====================\n");
    }
}

void iniciarTratamento(char** nomesBruxos, char** nomesPacientes, char** nomesPocoes, int* diasTratamentos, int* dosagensDiarias, int* numTratamentos, int numBruxos, int numPacientes, int numPocoes) {
    if (numBruxos == 0 || numPacientes == 0 || numPocoes == 0) {
        printf("N�o � poss�vel iniciar um tratamento. Verifique se h� bruxos, pacientes e po��es cadastrados.\n");
        return;
    }

    printf("Iniciando tratamento:\n");

    int bruxoIndex = get_int_input("Digite o c�digo do bruxo: ");
    if (bruxoIndex < 0 || bruxoIndex >= numBruxos) {
        printf("C�digo de bruxo inv�lido.\n");
        return;
    }

    int pacienteIndex = get_int_input("Digite o c�digo do paciente: ");
    if (pacienteIndex < 0 || pacienteIndex >= numPacientes) {
        printf("C�digo de paciente inv�lido.\n");
        return;
    }

    int pocaoIndex = get_int_input("Digite o c�digo da po��o: ");
    if (pocaoIndex < 0 || pocaoIndex >= numPocoes) {
        printf("C�digo de po��o inv�lido.\n");
        return;
    }

    int dias = get_int_input("Digite o n�mero de dias de tratamento: ");
    if (dias <= 0) {
        printf("N�mero de dias inv�lido.\n");
        return;
    }

    int dosagens = get_int_input("Digite o n�mero de dosagens di�rias: ");
    if (dosagens <= 0) {
        printf("N�mero de dosagens inv�lido.\n");
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

    int index = get_int_input("Digite o c�digo do tratamento a ser apagado: ");

    if (index < 0 || index >= *numTratamentos) {
        printf("C�digo de tratamento inv�lido.\n");
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

    int index = get_int_input("Digite o c�digo do tratamento a ser ampliado: ");

    if (index < 0 || index >= *numTratamentos) {
        printf("C�digo de tratamento inv�lido.\n");
        return;
    }

    int dosagens = get_int_input("Digite o n�mero de dosagens adicionais: ");
    if (dosagens <= 0) {
        printf("N�mero de dosagens inv�lido.\n");
        return;
    }

    dosagensDiarias[index] += dosagens;

    printf("Tratamento ampliado com sucesso!\n");
}

