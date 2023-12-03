#ifndef POCAO_H
#define POCAO_H

typedef struct {
    int codigo;
    char* nome;
    char* tipo;
} Pocao;

extern Pocao* pocoes;

int InicializarPocoes();
int EncerrarPocoes();
int VerificarCodigoPocao(int codigo);
int SalvarPocao(Pocao p);
int QuantidadePocoes();
Pocao* ObterPocaoPeloIndice(int indice);
void LiberarCopiaPocao(Pocao* copiaPocao);
Pocao* ObterPocaoPeloCodigo(int codigo);
int AtualizarPocao(Pocao p);
int ModificarPocaoPeloCodigo(int codigo, const char* novoNome, const char* novoTipo);
int ApagarPocaoPeloCodigo(int codigo);

#endif

