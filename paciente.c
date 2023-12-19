#include "Paciente.h"
#include "Tratamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Paciente* pacientes = NULL;
int MAX_PACIENTES = 5;
int qtdPacientes = 0;

int InicializarPacientes()
{
    pacientes = (Paciente*)calloc(MAX_PACIENTES, sizeof(Paciente));
    if (pacientes == NULL)
    {
        return 0;
    }
    return 1;
}

int EncerrarPacientes()
{
    if (pacientes != NULL)
    {
    	for(int i = 0; i < qtdPacientes; i++)
    	{
    		free(pacientes[i].nome);
		}
        free(pacientes);
        pacientes = NULL;
        MAX_PACIENTES = 0;
        qtdPacientes = 0;
        return 1;
    }
    return 0;
}

int VerificarCodigoPaciente(int codigo)
{
    for (int i = 0; i < qtdPacientes; i++)
    {
        if (pacientes[i].codigo == codigo)
        {
            return 1; // Código já existe na lista de pacientes
        }
    }
    return 0; // Código não encontrado na lista de pacientes
}

int SalvarPaciente(Paciente p)
{
    if (pacientes == NULL)
    {
        return 0;
    }

    if (VerificarCodigoPaciente(p.codigo))
    {
        return 0;
    }

    if (qtdPacientes == MAX_PACIENTES)
    {
        // Amplia o array usando realloc
        MAX_PACIENTES += 5;
        Paciente* temp = (Paciente*)realloc(pacientes, MAX_PACIENTES * sizeof(Paciente));
        if (temp == NULL)
        {
        	MAX_PACIENTES -= 5;
            return 0; // Não foi possível ampliar o array
        }
        pacientes = temp;
    }

    pacientes[qtdPacientes] = p;
    qtdPacientes++;
    return 1;
}

int QuantidadePacientes()
{
    return qtdPacientes;
}

Paciente* ObterPacientePeloIndice(int indice)
{
    if (indice >= 0 && indice < qtdPacientes) {
        Paciente* copiaPaciente = (Paciente*)malloc(sizeof(Paciente));

        if (copiaPaciente == NULL) {
            return NULL;
        }

        copiaPaciente->codigo = pacientes[indice].codigo;
        copiaPaciente->nome = strdup(pacientes[indice].nome);
        copiaPaciente->idade = pacientes[indice].idade;
        copiaPaciente->altura = pacientes[indice].altura;

        return copiaPaciente;
    }
    return NULL;
}

void LiberarCopiaPaciente(Paciente* copiaPaciente)
{
    if (copiaPaciente != NULL) {
        free(copiaPaciente->nome);
        free(copiaPaciente);
    }
}

Paciente* ObterPacientePeloCodigo(int codigo)
{
    for (int i = 0; i < qtdPacientes; i++)
    {
        if (pacientes[i].codigo == codigo)
        {
            return &pacientes[i];
        }
    }
    return NULL;
}

int AtualizarPaciente(Paciente p)
{
    Paciente* pacienteExistente = ObterPacientePeloCodigo(p.codigo);

    if (pacienteExistente != NULL) {
        free(pacienteExistente->nome); // Libera a memória do nome existente
        pacienteExistente->nome = strdup(p.nome);
        pacienteExistente->idade = p.idade;
        pacienteExistente->altura = p.altura;

        return 1;
    }
    return 0; // Paciente com o código especificado não encontrado
}

int ModificarPacientePeloCodigo(int codigo, const char* novoNome, int novaIdade, float novaAltura)
{
    Paciente* pacienteParaAtualizar = ObterPacientePeloCodigo(codigo);

    if (pacienteParaAtualizar != NULL) {
        free(pacienteParaAtualizar->nome); // Libera a memória do nome existente
        pacienteParaAtualizar->nome = strdup(novoNome);
        pacienteParaAtualizar->idade = novaIdade;
        pacienteParaAtualizar->altura = novaAltura;

        return AtualizarPaciente(*pacienteParaAtualizar);
    }
    return 0; // Paciente com o código especificado não encontrado
}


int ApagarPacientePeloCodigo(int codigo)
{
    int indiceParaRemover = -1;
    for (int i = 0; i < qtdPacientes; i++)
    {
        if (pacientes[i].codigo == codigo)
        {
            indiceParaRemover = i;
            break;
        }
    }

    if (indiceParaRemover != -1)
    {
    	if (VerificarTratamentosVinculadosAoPaciente(codigo))
		{
			printf("Não é possível excluir o paciente, pois ha tratamentos vinculados.\n");
		    return 0;
		}
        free(pacientes[indiceParaRemover].nome);

        // Movendo os pacientes à direita do índice para preencher a lacuna
        for (int i = indiceParaRemover; i < qtdPacientes - 1; i++)
        {
            pacientes[i] = pacientes[i + 1];
        }

        qtdPacientes--;

        // Verificar a ocupação e reduzir o array se necessário
        if (qtdPacientes < MAX_PACIENTES / 2.5)
        {
        	int temp_MAX_PACIENTES = MAX_PACIENTES;
            MAX_PACIENTES /= 2.5;
            Paciente* temp = (Paciente*)realloc(pacientes, MAX_PACIENTES * sizeof(Paciente));
            if (temp != NULL) {
                pacientes = temp;
            } else {
            	MAX_PACIENTES = temp_MAX_PACIENTES;
			}
        }
        return 1;
    }
    return 0; // Paciente com o código especificado não encontrado
}

