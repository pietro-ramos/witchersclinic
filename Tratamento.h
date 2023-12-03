#ifndef TRATAMENTO_H
#define TRATAMENTO_H

typedef struct {
	int codigoTratamento;
    int codigoPaciente;
    int codigoBruxo;
    int codigoPocao;
    int duracao;
    int dosagem;
} Tratamento;

extern Tratamento* tratamentos;

int InicializarTratamentos();
int EncerrarTratamentos();
int QuantidadeTratamentos();
int CodigoPacienteValido(int codigo);
int CodigoBruxoValido(int codigo);
int CodigoPocaoValido(int codigo);
int SalvarTratamento(Tratamento t);
Tratamento* ObterTratamentoPeloIndice(int indice);
void LiberarCopiaTratamento(Tratamento* copiaTratamento);
Tratamento* ObterTratamentoPeloCodigo(int codigo);
int ObterNomeBruxo(int codigo, char *nomeBruxo);
int ObterNomePocao(int codigo, char *nomePocao);
int ObterNomePaciente(int codigo, char *nomePaciente);
int ListarTratamentosPaciente(int codigoPaciente, int** tratamentosPaciente);
int ListarTratamentosBruxo(int codigoBruxo, int** tratamentosBruxo);
int AmpliarTratamento(int codigoTratamento, int duracaoAdicional, int dosagemAdicional);
int VerificarTratamentosVinculadosAoBruxo(int codigoBruxo);
int VerificarTratamentosVinculadosAoPaciente(int codigoPaciente);
int VerificarTratamentosVinculadosAPocao(int codigoPocao);
int ExcluirTratamento(int codigoTratamento);

#endif
