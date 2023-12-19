#include "Bruxo.h"
#include "Tratamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Bruxo* bruxos = NULL;
int MAX_BRUXOS = 5;
int qtdBruxos = 0;

int InicializarBruxos()
{
    bruxos = (Bruxo*)calloc(MAX_BRUXOS, sizeof(Bruxo));
    if (bruxos == NULL)
	{
        return 0;
    }
    return 1;
}

int EncerrarBruxos()
{
    if (bruxos != NULL)
	{
		for(int i = 0; i < qtdBruxos;i++)
		{
			free(bruxos[i].nome);
			free(bruxos[i].especialidade);
		}
		
        free(bruxos);
        bruxos = NULL;
        MAX_BRUXOS = 0;
        qtdBruxos = 0;
        return 1;
    }
    return 0;
}

int VerificarCodigoBruxo(int codigo)
{
    for (int i = 0; i < qtdBruxos; i++)
	{
        if (bruxos[i].codigo == codigo)
		{
            return 1; // Código já existe na lista de bruxos
        }
    }
    return 0; // Código não encontrado na lista de bruxos
}

int SalvarBruxo(Bruxo b)
{
    if (bruxos == NULL)
	{
        return 0;
    }
    
    if (VerificarCodigoBruxo(b.codigo))
	{
    	return 0; 
	}

    if (qtdBruxos == MAX_BRUXOS)
	{
        // Amplia o array usando realloc
        MAX_BRUXOS += 5;
        Bruxo* temp = (Bruxo*)realloc(bruxos, MAX_BRUXOS * sizeof(Bruxo));
        if (temp == NULL)
		{
			MAX_BRUXOS -=5;
            return 0; // Não foi possível ampliar o array
        }
        bruxos = temp;
    }

    bruxos[qtdBruxos] = b;
    qtdBruxos++;
    return 1;
}

int QuantidadeBruxos()
{
    return qtdBruxos;
}

Bruxo* ObterBruxoPeloIndice(int indice)
{
    if (indice >= 0 && indice < qtdBruxos) {
        Bruxo* copiaBruxo = (Bruxo*)malloc(sizeof(Bruxo));

        if (copiaBruxo == NULL) {
            return NULL;
        }
        copiaBruxo->codigo = bruxos[indice].codigo;
        copiaBruxo->nome = strdup(bruxos[indice].nome);
        copiaBruxo->especialidade = strdup(bruxos[indice].especialidade);

        return copiaBruxo;
    }
    return NULL;
}

void LiberarCopiaBruxo(Bruxo* copiaBruxo)
{
    if (copiaBruxo != NULL) {
        free(copiaBruxo->nome);
        free(copiaBruxo->especialidade);
        free(copiaBruxo);
    }
}


Bruxo* ObterBruxoPeloCodigo(int codigo)
{
    for (int i = 0; i < qtdBruxos; i++)
	{
        if (bruxos[i].codigo == codigo)
		{
            return &bruxos[i];
        }
    }
    return NULL;
}

int AtualizarBruxo(Bruxo b)
{
    Bruxo* bruxoExistente = ObterBruxoPeloCodigo(b.codigo);

    if (bruxoExistente != NULL) {
        free(bruxoExistente->nome); // Libera a memória do nome existente
        free(bruxoExistente->especialidade); // Libera a memória da especialidade existente

        bruxoExistente->nome = strdup(b.nome);
        bruxoExistente->especialidade = strdup(b.especialidade);

        return 1;
    }
    return 0; // Bruxo com o código especificado não encontrado
}

int ModificarBruxoPeloCodigo(int codigo, const char* novoNome, const char* novaEspecialidade)
{
    Bruxo* bruxoParaAtualizar = ObterBruxoPeloCodigo(codigo);

    if (bruxoParaAtualizar != NULL) {
        free(bruxoParaAtualizar->nome); // Libera a memória do nome existente
        free(bruxoParaAtualizar->especialidade); // Libera a memória da especialidade existente

        bruxoParaAtualizar->nome = strdup(novoNome);
        bruxoParaAtualizar->especialidade = strdup(novaEspecialidade);

        return AtualizarBruxo(*bruxoParaAtualizar);
    }
    return 0; // Bruxo com o código especificado não encontrado
}

int ApagarBruxoPeloCodigo(int codigo)
{
    int indiceParaRemover = -1;
    for (int i = 0; i < qtdBruxos; i++)
	{
        if (bruxos[i].codigo == codigo)
		{
            indiceParaRemover = i;
            break;
        }
    }

    if (indiceParaRemover != -1)
	{
        if (VerificarTratamentosVinculadosAoBruxo(codigo))
		{
			printf("Não é possível excluir o bruxo, pois ha tratamentos vinculados.\n");
		    return 0;
		}
		
        free(bruxos[indiceParaRemover].nome);
        free(bruxos[indiceParaRemover].especialidade);

        // Movendo os bruxos à direita do índice para preencher a lacuna
        for (int i = indiceParaRemover; i < qtdBruxos - 1; i++)
		{
            bruxos[i] = bruxos[i + 1];
        }

        qtdBruxos--;

        // Verificar a ocupação e reduzir o array se necessário
        if (qtdBruxos < MAX_BRUXOS / 2.5)
		{
			int temp_MAX_BRUXOS = MAX_BRUXOS;
            MAX_BRUXOS /= 2.5;
            Bruxo* temp = (Bruxo*)realloc(bruxos, MAX_BRUXOS * sizeof(Bruxo));
            if (temp != NULL) {
                bruxos = temp;
            } else {
            	MAX_BRUXOS = temp_MAX_BRUXOS;
			}
        }
        return 1;
    }
    return 0; // Bruxo com o código especificado não encontrado
}

