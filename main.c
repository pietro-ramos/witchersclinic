#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <locale.h>
#include "bruxo.h"
#include "pocoes.h"
#include "paciente.h"
#include "tratamento.h"
#include "get_input.h"

#define MAX_BRUXOS 100
#define MAX_NOME 50
#define MAX_ESPECIALIDADE 50
#define MAX_POCOES 100
#define MAX_PACIENTES 100
#define MAX_TRATAMENTOS 100

char* nomesBruxos[MAX_BRUXOS][MAX_NOME];
char* especialidadeBruxos[MAX_BRUXOS][MAX_ESPECIALIDADE];
int numBruxos = 0;

char* nomesPocoes[MAX_POCOES];
int numPocoes = 0;

char* nomesPacientes[MAX_PACIENTES];
int numPacientes = 0;

char* nomesTratamentos[MAX_TRATAMENTOS][MAX_NOME];
int diasTratamentos[MAX_TRATAMENTOS];
int dosagensDiarias[MAX_TRATAMENTOS];
int numTratamentos = 0;


int main(int argc, char** argv) {
	setlocale(LC_ALL, "Portuguese");
	system("Pause");

	limparIndices(nomesBruxos, especialidadeBruxos, nomesPocoes, nomesPacientes, nomesTratamentos, numBruxos, numPocoes, numPacientes, numTratamentos);
	
    int opcao;
    do
	{
        printf("========== MENU ==========\n");
        printf("1. Listar Bruxos\n");
        printf("2. Cadastrar Bruxo\n");
        printf("3. Excluir Bruxo\n");
        printf("4. Listar Poções\n");
        printf("5. Cadastrar Poção\n");
        printf("6. Excluir Poção\n");
        printf("7. Listar Pacientes\n");
        printf("8. Cadastrar Paciente\n");
        printf("9. Excluir Paciente\n");
        printf("10. Listar Tratamentos\n");
        printf("11. Listar Pacientes do Bruxo\n");
        printf("12. Iniciar Tratamento\n");
        printf("13. Ampliar Tratamento\n");
        printf("14. Apagar Tratamento\n");
        printf("0. Sair\n");
        printf("===========================\n");

        opcao = get_int_input("Digite uma opção: ");

        switch (opcao)
		{
            case 1:
                listarBruxos(nomesBruxos, especialidadeBruxos, numBruxos);
                break;
            case 2:
                cadastrarBruxo(nomesBruxos, especialidadeBruxos, &numBruxos);
                break;
            case 3:
                excluirBruxo(nomesBruxos, &numBruxos);
                break;
            case 4:
                listarPocoes(nomesPocoes, numPocoes);
                break;
            case 5:
                cadastrarPocao(nomesPocoes, &numPocoes);
                break;
            case 6:
                excluirPocao(nomesPocoes, &numPocoes);
                break;
            case 7:
                listarPacientes(nomesPacientes, numPacientes);
                break;
            case 8:
                cadastrarPaciente(nomesPacientes, &numPacientes);
                break;
            case 9:
                excluirPaciente(nomesPacientes, &numPacientes);
                break;
            case 10:
                listarTratamentos(nomesBruxos, nomesPacientes, nomesPocoes, diasTratamentos, dosagensDiarias, numTratamentos);
                break;
            case 11:
			    listarPacientesDoBruxo(nomesBruxos, numBruxos, nomesPacientes);
			    break;
            case 12:
                iniciarTratamento(nomesBruxos, nomesPacientes, nomesPocoes, diasTratamentos, dosagensDiarias, &numTratamentos, numBruxos, numPacientes, numPocoes);
                break;
            case 13:
    			ampliarTratamento(nomesBruxos, nomesPacientes, nomesPocoes, diasTratamentos, dosagensDiarias, &numTratamentos);
    			break;
            case 14:
                apagarTratamento(nomesBruxos, nomesPacientes, nomesPocoes, diasTratamentos, dosagensDiarias, &numTratamentos);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

