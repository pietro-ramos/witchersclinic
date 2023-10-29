#include "Tratamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Tratamento* tratamentos = NULL;
int MAX_TRATAMENTOS = 5;
int qtdTratamentos = 0;

int InicializarTratamentos()
{
    tratamentos = (Tratamento*)malloc(MAX_TRATAMENTOS * sizeof(Tratamento));
    if (tratamentos == NULL)
	{
        return 0;
    }
    return 1;
}

int EncerrarTratamentos()
{
    if (tratamentos != NULL)
	{
        free(tratamentos);
        tratamentos = NULL;
        MAX_TRATAMENTOS = 0;
        qtdTratamentos = 0;
        return 1;
    }
    return 0;
}

int SalvarTratamento(Tratamento t)
{
    if (tratamentos == NULL)
	{
        return 0;
    }

    if (qtdTratamentos == MAX_TRATAMENTOS)
	{
        // Amplia o array usando realloc
        MAX_TRATAMENTOS += 5;
        Tratamento* temp = (Tratamento*)realloc(tratamentos, MAX_TRATAMENTOS * sizeof(Tratamento));
        if (temp == NULL)
		{
            return 0; // Não foi possível ampliar o array
        }
        tratamentos = temp;
    }

    tratamentos[qtdTratamentos] = t;
    qtdTratamentos++;
    return 1;
}

int ListarTratamentosPaciente(int codigoPaciente, int** tratamentosPaciente) {
    int count = 0;
    *tratamentosPaciente = (int*)malloc(qtdTratamentos * sizeof(int)); // Aloca memória para armazenar os índices dos tratamentos

    if (*tratamentosPaciente == NULL) {
        return 0; // Falha na alocação de memória
    }

    for (int i = 0; i < qtdTratamentos; i++) {
        if (tratamentos[i].codigoPaciente == codigoPaciente) {
            (*tratamentosPaciente)[count] = i;
            count++;
        }
    }

    return count;
}

int ListarTratamentosBruxo(int codigoBruxo, int** tratamentosBruxo) {
    int count = 0;
    *tratamentosBruxo = (int*)malloc(qtdTratamentos * sizeof(int)); // Aloca memória para armazenar os índices dos tratamentos

    if (*tratamentosBruxo == NULL) {
        return 0; // Falha na alocação de memória
    }

    for (int i = 0; i < qtdTratamentos; i++) {
        if (tratamentos[i].codigoBruxo == codigoBruxo) {
            (*tratamentosBruxo)[count] = i;
            count++;
        }
    }

    return count;
}

int IniciarTratamento(int codigoTratamento, int codigoPaciente, int codigoBruxo, const char* descricao, int duracao) {
    Tratamento novoTratamento;
    novoTratamento.codigoTratamento = codigoTratamento;
    novoTratamento.codigoPaciente = codigoPaciente;
    novoTratamento.codigoBruxo = codigoBruxo;
    novoTratamento.descricao = strdup(descricao);
    novoTratamento.duracao = duracao;

    return SalvarTratamento(novoTratamento);
}

int AmpliarTratamento(int codigoTratamento, int duracaoAdicional)
{
    for (int i = 0; i < qtdTratamentos; i++)
	{
        if (tratamentos[i].codigoTratamento == codigoTratamento)
		{
            tratamentos[i].duracao += duracaoAdicional;
            return 1;
        }
    }
    return 0; // Tratamento não encontrado
}

int ExcluirTratamento(int codigoTratamento)
{
    int indiceParaRemover = -1;
    for (int i = 0; i < qtdTratamentos; i++)
	{
        if (tratamentos[i].codigoTratamento == codigoTratamento)
		{
            indiceParaRemover = i;
            break;
        }
    }

    if (indiceParaRemover != -1)
	{
        free(tratamentos[indiceParaRemover].descricao);

        // Movendo os tratamentos à direita do índice para preencher a lacuna
        for (int i = indiceParaRemover; i < qtdTratamentos - 1; i++)
		{
            tratamentos[i] = tratamentos[i + 1];
        }

        qtdTratamentos--;

        // Verificar a ocupação e reduzir o array se necessário
        if (qtdTratamentos < MAX_TRATAMENTOS / 2.5)
		{
            MAX_TRATAMENTOS /= 2.5;
            Tratamento* temp = (Tratamento*)realloc(tratamentos, MAX_TRATAMENTOS * sizeof(Tratamento));
            if (temp != NULL)
			{
                tratamentos = temp;
            }
        }
        return 1;
    }
    return 0; // Tratamento com o código especificado não encontrado
}

