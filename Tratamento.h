#ifndef TRATAMENTO_H
#define TRATAMENTO_H

typedef struct {
	int codigoTratamento;
    int codigoPaciente;
    int codigoBruxo;
    char* descricao;
    int duracao;
} Tratamento;

extern Tratamento* tratamentos;

int InicializarTratamentos();
int EncerrarTratamentos();
int SalvarTratamento(Tratamento t);
int ListarTratamentosPaciente(int codigoPaciente, int** tratamentosPaciente);
int ListarTratamentosBruxo(int codigoBruxo, int** tratamentosBruxo);
int IniciarTratamento(int codigoTratamento, int codigoPaciente, int codigoBruxo, const char* descricao, int duracao);
int AmpliarTratamento(int codigoTratamento, int duracaoAdicional);
int ExcluirTratamento(int codigoTratamento);

#endif
