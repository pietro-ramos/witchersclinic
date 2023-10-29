#include "Pocao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Pocao* pocoes = NULL;
int MAX_POCOES = 5;
int qtdPocoes = 0;

int InicializarPocoes()
{
    pocoes = (Pocao*)malloc(MAX_POCOES * sizeof(Pocao));
    if (pocoes == NULL)
    {
        return 0;
    }
    return 1;
}

int EncerrarPocoes()
{
    if (pocoes != NULL)
    {
        free(pocoes);
        pocoes = NULL;
        MAX_POCOES = 0;
        qtdPocoes = 0;
        return 1;
    }
    return 0;
}

int VerificarCodigoPocao(int codigo)
{
    for (int i = 0; i < qtdPocoes; i++)
    {
        if (pocoes[i].codigo == codigo)
        {
            return 1; // C�digo j� existe na lista de po��es
        }
    }
    return 0; // C�digo n�o encontrado na lista de po��es
}

int SalvarPocao(Pocao p)
{
    if (pocoes == NULL)
    {
        return 0;
    }

    if (VerificarCodigoPocao(p.codigo))
    {
        return 0;
    }

    if (qtdPocoes == MAX_POCOES)
    {
        // Amplia o array usando realloc
        MAX_POCOES += 5;
        Pocao* temp = (Pocao*)realloc(pocoes, MAX_POCOES * sizeof(Pocao));
        if (temp == NULL)
        {
            return 0; // N�o foi poss�vel ampliar o array
        }
        pocoes = temp;
    }

    pocoes[qtdPocoes] = p;
    qtdPocoes++;
    return 1;
}

int QuantidadePocoes()
{
    return qtdPocoes;
}

Pocao* ObterPocaoPeloIndice(int indice)
{
    if (indice >= 0 && indice < qtdPocoes) {
        Pocao* copiaPocao = (Pocao*)malloc(sizeof(Pocao));

        if (copiaPocao == NULL) {
            return NULL;
        }

        copiaPocao->codigo = pocoes[indice].codigo;
        copiaPocao->nome = strdup(pocoes[indice].nome);
        copiaPocao->tipo = strdup(pocoes[indice].tipo);

        return copiaPocao;
    }
    return NULL;
}

void LiberarCopiaPocao(Pocao* copiaPocao)
{
    if (copiaPocao != NULL) {
        free(copiaPocao->nome);
        free(copiaPocao->tipo);
        free(copiaPocao);
    }
}

Pocao* ObterPocaoPeloCodigo(int codigo)
{
    for (int i = 0; i < qtdPocoes; i++)
    {
        if (pocoes[i].codigo == codigo)
        {
            return &pocoes[i];
        }
    }
    return NULL;
}

int AtualizarPocao(Pocao p)
{
    Pocao* pocaoExistente = ObterPocaoPeloCodigo(p.codigo);

    if (pocaoExistente != NULL) {
        free(pocaoExistente->nome); // Libera a mem�ria do nome existente
        free(pocaoExistente->tipo); // Libera a mem�ria do tipo existente

        pocaoExistente->nome = strdup(p.nome);
        pocaoExistente->tipo = strdup(p.tipo);

        return 1;
    }
    return 0; // Po��o com o c�digo especificado n�o encontrado
}

int ApagarPocaoPeloCodigo(int codigo)
{
    int indiceParaRemover = -1;
    for (int i = 0; i < qtdPocoes; i++)
    {
        if (pocoes[i].codigo == codigo)
        {
            indiceParaRemover = i;
            break;
        }
    }

    if (indiceParaRemover != -1)
    {
        free(pocoes[indiceParaRemover].nome);
        free(pocoes[indiceParaRemover].tipo);

        // Movendo as po��es � direita do �ndice para preencher a lacuna
        for (int i = indiceParaRemover; i < qtdPocoes - 1; i++)
        {
            pocoes[i] = pocoes[i + 1];
        }

        qtdPocoes--;

        // Verificar a ocupa��o e reduzir o array se necess�rio
        if (qtdPocoes < MAX_POCOES / 2.5)
        {
            MAX_POCOES /= 2.5;
            Pocao* temp = (Pocao*)realloc(pocoes, MAX_POCOES * sizeof(Pocao));
            if (temp != NULL) {
                pocoes = temp;
            }
        }
        return 1;
    }
    return 0; // Po��o com o c�digo especificado n�o encontrado
}

