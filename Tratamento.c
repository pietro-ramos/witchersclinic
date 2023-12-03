#include "Tratamento.h"
#include "Bruxo.h"
#include "Paciente.h"
#include "Pocao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* tratamentos = NULL;

int InicializarTratamentos()
{
    tratamentos = fopen("tratamentos.bin", "rb+");
    if (!tratamentos)
    {
        tratamentos = fopen("tratamentos.bin", "wb+");
        return 0;
    }
    return 1;
}

int EncerrarTratamentos()
{
    if (tratamentos != NULL)
    {
        fclose(tratamentos);
        tratamentos = NULL;
        return 1;
    }
    return 0;
}

int QuantidadeTratamentos()
{
    if (!tratamentos)
    {
        return 0;
    }

    Tratamento countTratamentos;
    fseek(tratamentos, 0, SEEK_SET); // Move para início do arquivo
    int quantidade = 0;

    while (fread(&countTratamentos, sizeof(Tratamento), 1, tratamentos) == 1)
    {
        quantidade++;
    }

    return quantidade;
}

int VerificarCodigoTratamento(int codigo)
{
    if (!tratamentos)
    {
        return 0;
    }

    fseek(tratamentos, 0, SEEK_SET);

    Tratamento verificaTratamento;
    while (fread(&verificaTratamento, sizeof(Tratamento), 1, tratamentos) == 1)
    {
        if (verificaTratamento.codigoTratamento == codigo)
        {
            return 1; // Código já existe na lista de tratamentos
        }
    }

    return 0; // Código não encontrado na lista de tratamentos
}

int CodigoPacienteValido(int codigo)
{
    return VerificarCodigoPaciente(codigo);
}

int CodigoBruxoValido(int codigo)
{
    return VerificarCodigoBruxo(codigo);
}

int CodigoPocaoValido(int codigo)
{
    return VerificarCodigoPocao(codigo);
}

int SalvarTratamento(Tratamento t)
{
    if (!tratamentos)
    {
        return 0;
    }

    if (VerificarCodigoTratamento(t.codigoTratamento))
    {
        return 0;
    }

    fseek(tratamentos, 0, SEEK_END);
    fwrite(&t, sizeof(Tratamento), 1, tratamentos);

    return 1;
}

Tratamento* ObterTratamentoPeloIndice(int indice)
{
    if (indice >= 0 && indice < QuantidadeTratamentos())
    {
        Tratamento* copiaTratamento = (Tratamento*)malloc(sizeof(Tratamento));
        fseek(tratamentos, indice * sizeof(Tratamento), SEEK_SET);

        if (!copiaTratamento)
        {
            return NULL;
        }

        fread(copiaTratamento, sizeof(Tratamento), 1, tratamentos);
        return copiaTratamento;
    }
    return NULL;
}

void LiberarCopiaTratamento(Tratamento* copiaTratamento)
{
    if (copiaTratamento != NULL)
    {
        free(copiaTratamento);
    }
}

Tratamento* ObterTratamentoPeloCodigo(int codigo)
{
    Tratamento obterTratamento;
    fseek(tratamentos, 0, SEEK_SET);

    while (fread(&obterTratamento, sizeof(Tratamento), 1, tratamentos) == 1)
    {
        if (obterTratamento.codigoTratamento == codigo)
        {
            Tratamento* copiaTratamento = (Tratamento*)malloc(sizeof(Tratamento));
            if (!copiaTratamento)
            {
                return NULL;
            }

            *copiaTratamento = obterTratamento;
            return copiaTratamento;
        }
    }

    return NULL;
}

int ObterNomeBruxo(int codigo, char *nomeBruxo)
{
    Bruxo* bruxo = ObterBruxoPeloCodigo(codigo);
    if (bruxo != NULL)
    {
        strcpy(nomeBruxo, bruxo->nome);
        LiberarCopiaBruxo(bruxo);
        return 1;
    }
    return 0;
}

int ObterNomePocao(int codigo, char *nomePocao)
{
    Pocao* pocao = ObterPocaoPeloCodigo(codigo);
    if (pocao != NULL)
    {
        strcpy(nomePocao, pocao->nome);
        LiberarCopiaPocao(pocao);
        return 1;
    }
    return 0;
}

int ObterNomePaciente(int codigo, char *nomePaciente)
{
    Paciente* paciente = ObterPacientePeloCodigo(codigo);
    if (paciente != NULL)
    {
        strcpy(nomePaciente, paciente->nome);
        LiberarCopiaPaciente(paciente);
        return 1;
    }
    return 0;
}

int ListarTratamentosPaciente(int codigoPaciente, int** tratamentosPaciente)
{
    int count = 0;
    *tratamentosPaciente = (int*)malloc(QuantidadeTratamentos() * sizeof(int));

    if (*tratamentosPaciente == NULL)
    {
        return 0;
    }

    fseek(tratamentos, 0, SEEK_SET);

    Tratamento tr;
    while (fread(&tr, sizeof(Tratamento), 1, tratamentos) == 1)
    {
        if (tr.codigoPaciente == codigoPaciente)
        {
            (*tratamentosPaciente)[count] = tr.codigoTratamento;
            count++;
        }
    }

    return count;
}

int ListarTratamentosBruxo(int codigoBruxo, int** tratamentosBruxo)
{
    int count = 0;
    *tratamentosBruxo = (int*)malloc(QuantidadeTratamentos() * sizeof(int));

    if (*tratamentosBruxo == NULL)
    {
        return 0;
    }

    fseek(tratamentos, 0, SEEK_SET);

    Tratamento listadoTratamento;
    while (fread(&listadoTratamento, sizeof(Tratamento), 1, tratamentos) == 1)
    {
        if (listadoTratamento.codigoBruxo == codigoBruxo)
        {
            (*tratamentosBruxo)[count] = listadoTratamento.codigoTratamento;
            count++;
        }
    }

    return count;
}

int AmpliarTratamento(int codigoTratamento, int duracaoAdicional, int dosagemAdicional)
{
    if (!tratamentos)
    {
        return 0;
    }

    Tratamento ampliadoTratamento;

    fseek(tratamentos, 0, SEEK_SET);

    while (fread(&ampliadoTratamento, sizeof(Tratamento), 1, tratamentos) == 1)
    {
        if (ampliadoTratamento.codigoTratamento == codigoTratamento)
        {
            ampliadoTratamento.dosagem += dosagemAdicional;
            ampliadoTratamento.duracao += duracaoAdicional;

            fseek(tratamentos, sizeof(Tratamento), SEEK_CUR);
            fwrite(&ampliadoTratamento, sizeof(Tratamento), 1, tratamentos);

            return 1;
        }
    }

    return 0;
}

int VerificarTratamentosVinculadosAoBruxo(int codigoBruxo)
{
    if (!tratamentos)
    {
        return 0;
    }

    fseek(tratamentos, 0, SEEK_SET);

    Tratamento verificadoTratamento;
    while (fread(&verificadoTratamento, sizeof(Tratamento), 1, tratamentos) == 1)
    {
        if (verificadoTratamento.codigoBruxo == codigoBruxo)
        {
            return 1;
        }
    }

    return 0;
}

int VerificarTratamentosVinculadosAoPaciente(int codigoPaciente)
{
    if (!tratamentos)
    {
        return 0;
    }

    fseek(tratamentos, 0, SEEK_SET);

    Tratamento verificadoTratamento;
    while (fread(&verificadoTratamento, sizeof(Tratamento), 1, tratamentos) == 1)
    {
        if (verificadoTratamento.codigoPaciente == codigoPaciente)
        {
            return 1;
        }
    }

    return 0;
}

int ExcluirTratamento(int codigoTratamento)
{
    if (!tratamentos)
    {
        return 0;
    }

    Tratamento apagadoTratamento;

    FILE* temp = fopen("temp_tratamentos.bin", "wb+");
    if (!temp)
    {
        return 0;
    }

    int verificacao = 0;

    fseek(tratamentos, 0, SEEK_SET);

    while (fread(&apagadoTratamento, sizeof(Tratamento), 1, tratamentos) == 1)
    {
        if (apagadoTratamento.codigoTratamento != codigoTratamento)
        {
            fwrite(&apagadoTratamento, sizeof(Tratamento), 1, temp);
        }
        else
        {
            verificacao = 1;
        }
    }

    fclose(tratamentos);
    fclose(temp);

    if (remove("tratamentos.bin") != 0 || rename("temp.bin", "tratamentos.bin") != 0)
	{
        return 0;
    }

    tratamentos = fopen("tratamentos.bin", "rb+");

    return verificacao;
}

