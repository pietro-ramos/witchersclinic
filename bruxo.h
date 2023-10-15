#ifndef BRUXO_H
#define BRUXO_H


#define MAX_BRUXOS 100
#define MAX_NOME 50
#define MAX_ESPECIALIDADE 50
#define MAX_POCOES 100
#define MAX_PACIENTES 100
#define MAX_TRATAMENTOS 100

void listarBruxos(char** nomesBruxos, char** especialidadeBruxos, int numBruxos);
void cadastrarBruxo(char** nomesBruxos[MAX_BRUXOS], char** especialidadeBruxos, int* numBruxos);
void excluirBruxo(char** nomesBruxos, int* numBruxos);
void listarPacientesDoBruxo(char** nomesBruxos, int numBruxos, char** nomesPacientes);

#endif
