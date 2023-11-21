#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct {
    int codigo;
    char* nome;
    int idade;
    float altura;
} Paciente;

extern Paciente* pacientes;

int InicializarPacientes();
int EncerrarPacientes();
int VerificarCodigoPaciente(int codigo);
int SalvarPaciente(Paciente p);
int QuantidadePacientes();
Paciente* ObterPacientePeloIndice(int indice);
void LiberarCopiaPaciente(Paciente* copiaPaciente);
Paciente* ObterPacientePeloCodigo(int codigo);
int AtualizarPaciente(Paciente p);
int ModificarPacientePeloCodigo(int codigo, const char* novoNome, int novaIdade, float novaAltura);
int ApagarPacientePeloCodigo(int codigo);

#endif

