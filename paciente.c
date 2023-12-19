#include "Paciente.h"
#include "Tratamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* pacientes = NULL;

int InicializarPacientes()
{
    pacientes = fopen("pacientes.bin", "rb+");
    if (!pacientes)
    {
        pacientes = fopen("pacientes.bin", "wb+");
        return 0;
    }
    return 1;
}

int EncerrarPacientes()
{
    if (pacientes != NULL)
    {
        fclose(pacientes);
        pacientes = NULL;
        return 1;
    }
    return 0;
}

int VerificarCodigoPaciente(int codigo)
{
    Paciente* verificaPaciente;
    fseek(pacientes, 0, SEEK_SET); // Move para início do arquivo
    while (fread(&verificaPaciente, sizeof(Paciente), 1, pacientes) == 1)
    {
        if (verificaPaciente->codigo == codigo)
        {
            return 1; // Código já existe na lista de pacientes
        }
    }
    return 0; // Código não encontrado na lista de pacientes
}

int SalvarPaciente(Paciente p)
{
    if (!pacientes)
    {
        return 0;
    }

    if (VerificarCodigoPaciente(p.codigo))
    {
        return 0;
    }
    
    // Aloca memória dinâmica para as strings da estrutura Paciente
    p.nome = strdup(p.nome);

    fseek(pacientes, 0, SEEK_END);  // Move para o final do arquivo
    fwrite(&p, sizeof(Paciente), 1, pacientes);

    return 1;
}

int QuantidadePacientes()
{
    if (!pacientes)
    {
        return 0;
    }

    Paciente countPacientes;
    fseek(pacientes, 0, SEEK_SET); // Move para início do arquivo
    int quantidade = 0;

    while (fread(&countPacientes, sizeof(Paciente), 1, pacientes) == 1)
    {
        quantidade++;
    }

    return quantidade;
}

Paciente* ObterPacientePeloIndice(int indice)
{
    if (indice >= 0 && indice < QuantidadePacientes())
    {
        Paciente* copiaPaciente = (Paciente*)malloc(sizeof(Paciente));
        fseek(pacientes, indice * sizeof(Paciente), SEEK_SET);  // Move para a posição do registro

        if (!copiaPaciente)
        {
            return NULL;
        }
        
        fread(copiaPaciente, sizeof(Paciente), 1, pacientes);
        
        // Aloca memória dinâmica para as strings da estrutura Paciente
    	copiaPaciente->nome = strdup(copiaPaciente->nome);

        return copiaPaciente;
    }
    return NULL;
}

void LiberarCopiaPaciente(Paciente* copiaPaciente)
{
    if (copiaPaciente != NULL)
    {
        free(copiaPaciente->nome);
        free(copiaPaciente);
    }
}

Paciente* ObterPacientePeloCodigo(int codigo)
{
    Paciente obterPaciente;
    fseek(pacientes, 0, SEEK_SET); // Move para início do arquivo.

    while (fread(&obterPaciente, sizeof(Paciente), 1, pacientes) == 1)
    {
        if (obterPaciente.codigo == codigo)
        {
            Paciente* copiaPaciente = (Paciente*)malloc(sizeof(Paciente));
            if (!copiaPaciente)
            {
                return NULL;
            }

            *copiaPaciente = obterPaciente;
            return copiaPaciente;
        }
    }

    return NULL;
}

int AtualizarPaciente(Paciente p)
{
    if (!pacientes)
    {
        return 0;
    }

    Paciente pacienteExistente;

    FILE* temp = fopen("temp.bin", "wb+");
    if (!temp)
    {
        return 0;
    }

    int verificacao = 0;

    fseek(pacientes, 0, SEEK_SET); // Move para início do arquivo

    while (fread(&pacienteExistente, sizeof(Paciente), 1, pacientes) == 1)
    {
        if (pacienteExistente.codigo != p.codigo)
        {
            fwrite(&pacienteExistente, sizeof(Paciente), 1, temp);
        }
        else
        {
        	// Atualiza o pacienteExistente com os novos dados
        	pacienteExistente = p;
        	fwrite(&pacienteExistente, sizeof(Paciente), 1, temp);

            verificacao = 1; // Paciente com o código especificado encontrado
        }
    }

    fclose(pacientes);
    fclose(temp);

    remove("pacientes.bin");
    rename("temp.bin", "pacientes.bin");

    pacientes = fopen("pacientes.bin", "rb+");

    return verificacao;
}

int ModificarPacientePeloCodigo(int codigo, const char* novoNome, int novaIdade, float novaAltura)
{
    Paciente* pacienteParaAtualizar = ObterPacientePeloCodigo(codigo);

    if (pacienteParaAtualizar != NULL)
    {
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
    if (!pacientes)
    {
        return 0;
    }

    Paciente apagadoPaciente;

    FILE* temp = fopen("temp.bin", "wb+");
    if (!temp)
    {
        return 0;
    }

    int verificacao = 0;

    fseek(pacientes, 0, SEEK_SET); // Move para início do arquivo

    while (fread(&apagadoPaciente, sizeof(Paciente), 1, pacientes) == 1)
    {
        if (apagadoPaciente.codigo != codigo)
        {
            fwrite(&apagadoPaciente, sizeof(Paciente), 1, temp);
        }
        else
        {
            verificacao = 1; // Paciente com o código especificado encontrado
        }
    }

    fclose(pacientes);
    fclose(temp);

    if (remove("pacientes.bin") != 0 || rename("temp.bin", "pacientes.bin") != 0)
	{
        return 0;
    }

    pacientes = fopen("pacientes.bin", "rb+");

    return verificacao;
}

