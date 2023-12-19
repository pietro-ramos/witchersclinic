#include "Pocao.h"
#include "Tratamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* pocoes = NULL;

int InicializarPocoes()
{
    pocoes = fopen("pocoes.bin", "rb+");
    if (!pocoes)
    {
        pocoes = fopen("pocoes.bin", "wb+");
        return 0;
    }
    return 1;
}

int EncerrarPocoes()
{
    if (pocoes != NULL)
    {
        fclose(pocoes);
        pocoes = NULL;
        return 1;
    }
    return 0;
}

int VerificarCodigoPocao(int codigo)
{
    Pocao verificaPocao;
    fseek(pocoes, 0, SEEK_SET); // Move para início do arquivo
    while (fread(&verificaPocao, sizeof(Pocao), 1, pocoes) == 1)
    {
        if (verificaPocao.codigo == codigo)
        {
            return 1; // Código já existe na lista de pocoes
        }
    }
    return 0; // Código não encontrado na lista de pocoes
}

int SalvarPocao(Pocao p)
{
    if (!pocoes)
    {
        return 0;
    }

    if (VerificarCodigoPocao(p.codigo))
    {
        return 0;
    }

    // Aloca memória dinâmica para as strings da estrutura Pocao
    p.nome = strdup(p.nome);
    p.tipo = strdup(p.tipo);

    fseek(pocoes, 0, SEEK_END);  // Move para o final do arquivo
    fwrite(&p, sizeof(Pocao), 1, pocoes);

    return 1;
}

int QuantidadePocoes()
{
    if (!pocoes)
    {
        return 0;
    }

    Pocao countPocoes;
    fseek(pocoes, 0, SEEK_SET); // Move para início do arquivo
    int quantidade = 0;

    while (fread(&countPocoes, sizeof(Pocao), 1, pocoes) == 1)
    {
        quantidade++;
    }

    return quantidade;
}

Pocao* ObterPocaoPeloIndice(int indice)
{
    if (indice >= 0 && indice < QuantidadePocoes())
    {
        Pocao* copiaPocao = (Pocao*)malloc(sizeof(Pocao));
        fseek(pocoes, indice * sizeof(Pocao), SEEK_SET);  // Move para a posição do registro

        if (!copiaPocao)
        {
            return NULL;
        }

        fread(copiaPocao, sizeof(Pocao), 1, pocoes);

        // Alocação de memória para as strings
        copiaPocao->nome = strdup(copiaPocao->nome);
        copiaPocao->tipo = strdup(copiaPocao->tipo);

        return copiaPocao;
    }
    return NULL;
}

void LiberarCopiaPocao(Pocao* copiaPocao)
{
    if (copiaPocao != NULL)
    {
        free(copiaPocao->nome);
        free(copiaPocao->tipo);
        free(copiaPocao);
    }
}

Pocao* ObterPocaoPeloCodigo(int codigo)
{
    Pocao obterPocao;
    fseek(pocoes, 0, SEEK_SET); // Move para início do arquivo.

    while (fread(&obterPocao, sizeof(Pocao), 1, pocoes) == 1)
    {
        if (obterPocao.codigo == codigo)
        {
            Pocao* copiaPocao = (Pocao*)malloc(sizeof(Pocao));
            if (!copiaPocao)
            {
                return NULL;
            }

            *copiaPocao = obterPocao;
            return copiaPocao;
        }
    }

    return NULL;
}

int AtualizarPocao(Pocao p)
{
    if (!pocoes)
    {
        return 0;
    }

    Pocao pocaoExistente;

    FILE* temp = fopen("temp.bin", "wb+");
    if (!temp)
    {
        return 0;
    }

    int verificacao = 0;

    fseek(pocoes, 0, SEEK_SET); // Move para início do arquivo

    while (fread(&pocaoExistente, sizeof(Pocao), 1, pocoes) == 1)
    {
        if (pocaoExistente.codigo != p.codigo)
        {
            fwrite(&pocaoExistente, sizeof(Pocao), 1, temp);
        }
        else
        {
            // Atualiza o pocaoExistente com os novos dados
            pocaoExistente = p;
            fwrite(&pocaoExistente, sizeof(Pocao), 1, temp);

            verificacao = 1; // Pocao com o código especificado encontrado
        }
    }

    fclose(pocoes);
    fclose(temp);

    remove("pocoes.bin");
    rename("temp.bin", "pocoes.bin");

    pocoes = fopen("pocoes.bin", "rb+");

    return verificacao;
}

int ModificarPocaoPeloCodigo(int codigo, const char* novoNome, const char* novoTipo)
{
    Pocao* pocaoParaAtualizar = ObterPocaoPeloCodigo(codigo);

    if (pocaoParaAtualizar != NULL)
    {
        free(pocaoParaAtualizar->nome); // Libera a memória do nome existente
        free(pocaoParaAtualizar->tipo); // Libera a memória do tipo existente

        pocaoParaAtualizar->nome = strdup(novoNome);
        pocaoParaAtualizar->tipo = strdup(novoTipo);

        return AtualizarPocao(*pocaoParaAtualizar);
    }
    return 0; // Pocao com o código especificado não encontrado
}

int ApagarPocaoPeloCodigo(int codigo)
{
    if (!pocoes)
    {
        return 0;
    }

    Pocao apagadaPocao;

    FILE* temp = fopen("temp.bin", "wb+");
    if (!temp)
    {
        return 0;
    }

    int verificacao = 0;

    fseek(pocoes, 0, SEEK_SET); // Move para início do arquivo

    while (fread(&apagadaPocao, sizeof(Pocao), 1, pocoes) == 1)
    {
        if (apagadaPocao.codigo != codigo)
        {
            fwrite(&apagadaPocao, sizeof(Pocao), 1, temp);
        }
        else
        {
            verificacao = 1; // Pocao com o código especificado encontrado
        }
    }

    fclose(pocoes);
    fclose(temp);

    if (remove("pocoes.bin") != 0 || rename("temp.bin", "pocoes.bin") != 0)
    {
        return 0;
    }

    pocoes = fopen("pocoes.bin", "rb+");

    return verificacao;
}

