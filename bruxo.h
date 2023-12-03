#ifndef BRUXO_H
#define BRUXO_H

typedef struct {
    int codigo;
    char* nome;
    char* especialidade;
} Bruxo;

extern Bruxo* bruxos;

int InicializarBruxos();
int EncerrarBruxos();
int VerificarCodigoBruxo(int codigo);
int SalvarBruxo(Bruxo b);
int QuantidadeBruxos();
Bruxo* ObterBruxoPeloIndice(int indice);
void LiberarCopiaBruxo(Bruxo* copiaBruxo);
Bruxo* ObterBruxoPeloCodigo(int codigo);
int ModificarBruxoPeloCodigo(int codigo, const char* novoNome, const char* novaEspecialidade);
int AtualizarBruxo(Bruxo b);
int ApagarBruxoPeloCodigo(int codigo);

#endif

