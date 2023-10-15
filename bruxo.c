#include <stdio.h>
#include <stdlib.h>
#include "get_input.h"
#include "bruxo.h"


#define MAX_BRUXOS 100
#define MAX_NOME 50
#define MAX_ESPECIALIDADE 50
#define MAX_POCOES 100
#define MAX_PACIENTES 100
#define MAX_TRATAMENTOS 100

void limparIndices(char** nomesBruxos, char** especialidadeBruxos, char** nomesPocoes, char** nomesPacientes, char** nomesTratamentos, int numBruxos, int numPocoes, int numPacientes, int numTratamentos) {
    for (int i = 0; i < numBruxos; i++) {
        nomesBruxos[i][0] = '\0';
        especialidadeBruxos[i][0] = '\0';
    }

    for (int i = 0; i < numPocoes; i++) {
        nomesPocoes[i][0] = '\0';
    }

    for (int i = 0; i < numPacientes; i++) {
        nomesPacientes[i][0] = '\0';
    }

    for (int i = 0; i < numTratamentos; i++) {
        nomesTratamentos[i][0] = '\0';
    }
}


void listarBruxos(char** nomesBruxos, char** especialidadeBruxos, int numBruxos) {
    printf("=== Lista de Bruxos ===\n");
    if(numBruxos > 0) {
	    printf("=== Lista de Bruxos ===\n");
	    for (int i = 0; i < MAX_BRUXOS; i++) {
	    	printf("C�digo do bruxo: %d\n", i);
	        printf("Nome: %s\n", nomesBruxos[i]);
	        printf("Especialidade: %s\n", especialidadeBruxos[i]);
	        printf("----------------------\n");
	    }
	}
	else {
		printf("Nenhum bruxo cadastrado!");
	}
}

void cadastrarBruxo(char** nomesBruxos[MAX_BRUXOS], char** especialidadeBruxos, int* numBruxos) {
    if (*numBruxos < MAX_BRUXOS) {
    	int codigo;
    	char* nome;
    	char* especialidade;
    	do {
    		printf("(0 a %d)", MAX_BRUXOS - 1);
	        codigo = get_int_input("�ndice para cadastro: ");
	        if (codigo < 0 || codigo >= MAX_BRUXOS) {
	            printf("�ndice inv�lido, tente novamente.\n");
	        } else if (nomesBruxos[codigo][0] != '\0') {
	            printf("O �ndice escolhido j� est� ocupado. O bruxo n�o pode ser cadastrado.\n");
	        }
    	} while (nomesBruxos[codigo][0] != '\0');
        *nome = get_string_input("Digite o nome do bruxo: ");
        nomesBruxos[codigo] = nome;
        *especialidade = get_string_input("Digite a especialidade do bruxo: ");
        especialidadeBruxos[codigo] = especialidade;
        (*numBruxos)++;
        printf("Bruxo cadastrado com sucesso!\n");
	} else {
        printf("Limite de bruxos atingido!\n");
    }
}

void excluirBruxo(char** nomesBruxos, int* numBruxos) {
    if (*numBruxos > 0) {
        int codigo = get_int_input("Digite o c�digo do bruxo a ser exclu�do: ");
        if (codigo >= 0 && codigo < *numBruxos) {
        	if (nomesBruxos[codigo][0] != '\0') {
            // Verificar se o bruxo possui tratamentos relacionados antes de exclu�-lo
            // ...

            free(nomesBruxos[codigo]);
            for (int i = codigo; i < *numBruxos - 1; i++) {
                nomesBruxos[i] = nomesBruxos[i + 1];
            }
        } else {
        	printf("Bruxo n�o cadastrado no c�digo fornecido.\n");
		}
            (*numBruxos)--;
            printf("Bruxo exclu�do com sucesso!\n");
        } else {
            printf("C�digo de bruxo inv�lido!\n");
        }
    } else {
        printf("N�o h� bruxos cadastrados!\n");
    }
}

void listarPacientesDoBruxo(char** nomesBruxos, int numBruxos, char** nomesPacientes) {
    if (numBruxos > 0) {
        int codigoBruxo = get_int_input("Digite o c�digo do bruxo: ");
        if (codigoBruxo >= 0 && codigoBruxo < numBruxos) {
            printf("=== Pacientes do Bruxo ===\n");
            // Percorrer a lista de pacientes e exibir apenas os que pertencem ao bruxo selecionado
            for (int i = 0; i < MAX_PACIENTES; i++) {
                if (nomesPacientes[i] != NULL && nomesPacientes[i][1] == codigoBruxo) {
                    printf("%d. %s\n", i, nomesPacientes[i]);
                }
            }
        } else {
            printf("C�digo de bruxo inv�lido!\n");
        }
    } else {
        printf("N�o h� bruxos cadastrados!\n");
    }
}

