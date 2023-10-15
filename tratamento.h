#ifndef TRATAMENTO_H
#define TRATAMENTO_H

#include "bruxo.h"
#include "pocoes.h"
#include "paciente.h"

#define MAX_TRATAMENTOS 100

void listarTratamentos(char** nomesBruxos, char** nomesPacientes, char** nomesPocoes, int* diasTratamentos, int* dosagensDiarias, int numTratamentos);
void iniciarTratamento(char** nomesBruxos, char** nomesPacientes, char** nomesPocoes, int* diasTratamentos, int* dosagensDiarias, int* numTratamentos, int numBruxos, int numPacientes, int numPocoes);
void ampliarTratamento(char** nomesBruxos, char** nomesPacientes, char** nomesPocoes, int* diasTratamentos, int* dosagensDiarias, int* numTratamentos);
void apagarTratamento(char** nomesBruxos, char** nomesPacientes, char** nomesPocoes, int* diasTratamentos, int* dosagensDiarias, int* numTratamentos);

#endif

