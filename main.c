#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "get_input.h"
#include "Bruxo.h"
#include "Pocao.h"
#include "Paciente.h"
#include "Tratamento.h"

int codigo;
int indice;
int resultadoCadastro;
char* nome;
char* especialidade;
char* tipo;
int idade;
float altura;
int dosagem;
int duracao;
Bruxo novoBruxo;
Pocao novaPocao;
Paciente novoPaciente;
Tratamento novoTratamento;
int codigoTratamento;
int codPaciente;
int codBruxo;
int codPocao;
int InicializarTudo();
void EncerrarTudo();
void menuBruxo();
void menuPaciente();
void menuPocao();
void menuTratamento();


int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Portuguese");
    int resultado = InicializarTudo();

    if (resultado == 0)
	{
        printf("Os arquivos ainda nao existentes foram criados!\n"); // Encerra o programa
    } else {
        printf("Todas os arquivos foram inicializadas com sucesso.\n"); // Continua o programa
    }
    
	int opcao = -1;
	
    while (opcao != 0) {
        printf("\n--- Menu Principal ---\n");
        printf("1. Bruxo\n");
        printf("2. Paciente\n");
        printf("3. Pocao\n");
        printf("4. Tratamento\n");
        printf("0. Sair\n");

		opcao = get_int_input("");

        switch (opcao) {
            case 0:
                printf("Saindo do programa...\n");
                free(nome);
                free(especialidade);
                free(tipo);
                EncerrarTudo(); // Encerra as estruturas
                break;
            case 1:
                menuBruxo();
                break;
            case 2:
                menuPaciente();
                break;
            case 3:
                menuPocao();
                break;
            case 4:
                menuTratamento();
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////

// INICIALIZAÇÃO E ENCERRAMENTO

int InicializarTudo()
{
    if (!InicializarBruxos() || !InicializarPocoes() || !InicializarPacientes() || !InicializarTratamentos())
	{
        return 0; // Retorna 0 se qualquer inicializacao falhar
    }

    return 1; // Retorna 1 se todas as inicializacoes forem bem-sucedidas
}

void EncerrarTudo()
{
	EncerrarBruxos();
	EncerrarPocoes();
	EncerrarPacientes();
	EncerrarTratamentos();
}

// FUNÇÕES DOS SUBMENUS

void menuBruxo()
{
    int opcao = -1;
    while (opcao != 0)
	{
        printf("\n--- Menu Bruxo ---\n");
        printf("1. Listar\n");
        printf("2. Cadastrar\n");
        printf("3. Alterar\n");
        printf("4. Excluir\n");
        printf("0. Sair\n");

		opcao = get_int_input("");


        switch (opcao)
		{
            case 0:
                // Retorna ao menu anterior
                break;
            case 1:// Listar bruxos
                if (QuantidadeBruxos() == 0)
				{
                    printf("Nenhum bruxo cadastrado.\n");
                    break;
                }
                /////////////////////////////////////////////////////////////////////////////////
            	opcao = get_int_input("1. Listar todos os bruxos.\n2. Listar bruxo pelo indice\n");
            	switch(opcao)
            	{
            		case 1:
						printf("Lista de Bruxos:\n");
					    for (int i = 0; i < QuantidadeBruxos(); i++)
						{
					        Bruxo* copia = ObterBruxoPeloIndice(i);
					        if (copia != NULL)
							{
					            printf("Código: %d\n", copia->codigo);
					            printf("Nome: %s\n", copia->nome);
					            printf("Especialidade: %s\n\n", copia->especialidade);
					            LiberarCopiaBruxo(copia);
					        } else {
					            printf("Erro ao acessar informações do bruxo.\n");
					        }
					    }
            			break;
					case 2:
						indice = get_int_input("Digite o índice do bruxo:");
		                Bruxo* copia = ObterBruxoPeloIndice(indice);
		
		                if (copia != NULL)
						{
		                    // Imprimir dados do Bruxo
		                    printf("Bruxo %d: %s, %s\n", copia->codigo, copia->nome, copia->especialidade);
		
		                    // Liberar memória alocada para a cópia do Bruxo
		                    LiberarCopiaBruxo(copia);
		                } else {
		                    printf("Índice inválido ou bruxo não encontrado.\n");
		                }
		                break;
		    	}
		    	break;
                /////////////////////////////////////////////////////////////////////////////////
            case 2: // Cadastrar bruxo
				novoBruxo.codigo = get_int_input("Digite o codigo do Bruxo: ");
				novoBruxo.nome = get_string_input("Digite o nome do Bruxo: ");
				novoBruxo.especialidade = get_string_input("Digite a especialidade do Bruxo: ");
				
				resultadoCadastro = SalvarBruxo(novoBruxo);
				
				if (resultadoCadastro == 0)
				{
				    printf("Código já existente. Por favor, insira um código diferente.\n");
				}
				else
				{
					printf("Bruxo cadastrado com sucesso!\n");
				}
                break;
            case 3: // Alterar bruxo
			    codigo = get_int_input("Digite o código do Bruxo que deseja atualizar: ");
			    char* novoNome;
			    novoNome = get_string_input("Digite o novo nome do Bruxo: ");
			    char* novaEspecialidade;
				novaEspecialidade = get_string_input("Digite a nova especialidade do Bruxo: ");
				
			    Bruxo novoBruxo;
			    novoBruxo.codigo = codigo;
			    novoBruxo.nome = novoNome;
			    novoBruxo.especialidade = novaEspecialidade;
				
			    if (ModificarBruxoPeloCodigo(codigo, novoNome, novaEspecialidade)) {
			        printf("Bruxo atualizado com sucesso!\n");
			    } else {
			        printf("Falha ao atualizar o Bruxo ou Bruxo não encontrado.\n");
			    }
			    free(novoNome);
				free(novaEspecialidade);
			    break;
            case 4: // Excluir bruxo
    			codigo = get_int_input("Digite o código do Bruxo que deseja apagar: ");

			    if (ApagarBruxoPeloCodigo(codigo))
				{
			        printf("Bruxo removido com sucesso!\n");
			    } else {
			        printf("Falha ao remover o Bruxo.\n");
			    }
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }
}

void menuPaciente()
{
    int opcao = -1;
    while (opcao != 0)
    {
        printf("\n--- Menu Paciente ---\n");
        printf("1. Listar\n");
        printf("2. Cadastrar\n");
        printf("3. Alterar\n");
        printf("4. Excluir\n");
        printf("0. Sair\n");

        opcao = get_int_input("");

        switch (opcao)
        {
            case 0:
                // Retorna ao menu anterior
                break;
            case 1:// Listar pacientes
                if (QuantidadePacientes() == 0)
                {
                    printf("Nenhum paciente cadastrado.\n");
                    break;
                }
                /////////////////////////////////////////////////////////////////////////////////
                opcao = get_int_input("1. Listar todos os pacientes.\n2. Listar paciente pelo índice\n");
                switch (opcao)
                {
                    case 1:
                        printf("Lista de Pacientes:\n");
                        for (int i = 0; i < QuantidadePacientes(); i++)
                        {
                            Paciente* copia = ObterPacientePeloIndice(i);
                            if (copia != NULL)
                            {
                                printf("Código: %d\n", copia->codigo);
                                printf("Nome: %s\n", copia->nome);
                                printf("Idade: %d\n", copia->idade);
                                printf("Altura: %.2f\n\n", copia->altura);
                                LiberarCopiaPaciente(copia);
                            } else {
                                printf("Erro ao acessar informações do paciente.\n");
                            }
                        }
                        break;
                    case 2:
                        indice = get_int_input("Digite o índice do paciente:");
                        Paciente* copia = ObterPacientePeloIndice(indice);

                        if (copia != NULL)
                        {
                            // Imprimir dados do Paciente
                            printf("Paciente %d: %s, %d anos, %.2f de altura\n", copia->codigo, copia->nome, copia->idade, copia->altura);

                            // Liberar memória alocada para a cópia do Paciente
                            LiberarCopiaPaciente(copia);
                        } else {
                            printf("Índice inválido ou paciente não encontrado.\n");
                        }
                        break;
                }
                /////////////////////////////////////////////////////////////////////////////////
                break;
            case 2: // Cadastrar paciente
                codigo = get_int_input("Digite o código do Paciente: ");
                nome = get_string_input("Digite o nome do Paciente: ");
                idade = get_int_input("Digite a idade do Paciente(em x,xx): ");
                altura = get_float_input("Digite a altura do Paciente: ");
                Paciente novoPaciente;
                novoPaciente.codigo = codigo;
                novoPaciente.nome = nome;
                novoPaciente.idade = idade;
                novoPaciente.altura = altura;

                int resultadoCadastro = SalvarPaciente(novoPaciente);
                if (resultadoCadastro == 0)
                {
                    printf("Código já existente. Por favor, insira um código diferente.\n");
                }
                break;
            case 3: // Alterar paciente
			    codigo = get_int_input("Digite o código do Paciente que deseja atualizar: ");
			    char* novoNome;
			    novoNome = get_string_input("Digite o novo nome do Paciente: ");
			    int novaIdade = 0;
			    novaIdade = get_int_input("Digite a nova idade do Paciente: ");
			    float novaAltura = 0.0;
			    novaAltura = get_float_input("Digite a nova altura do Paciente: ");
			    
			    if (ModificarPacientePeloCodigo(codigo, novoNome, novaIdade, novaAltura)) {
			        printf("Paciente atualizado com sucesso!\n");
			    } else {
			        printf("Falha ao atualizar o Paciente ou Paciente não encontrado.\n");
			    }
			    free(novoNome);
			    break;
            case 4: // Excluir paciente
                codigo = get_int_input("Digite o código do Paciente que deseja apagar: ");

                if (ApagarPacientePeloCodigo(codigo))
                {
                    printf("Paciente removido com sucesso!\n");
                } else {
                    printf("Falha ao remover o Paciente.\n");
                }
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }
}

void menuPocao()
{
    int opcao = -1;
    while (opcao != 0)
    {
        printf("\n--- Menu Poção ---\n");
        printf("1. Listar\n");
        printf("2. Cadastrar\n");
        printf("3. Alterar\n");
        printf("4. Excluir\n");
        printf("0. Sair\n");

        opcao = get_int_input("");

        switch (opcao)
        {
            case 0:
                // Retorna ao menu anterior
                break;
            case 1:// Listar poções
                if (QuantidadePocoes() == 0)
                {
                    printf("Nenhuma poção cadastrada.\n");
                    break;
                }
                /////////////////////////////////////////////////////////////////////////////////
                opcao = get_int_input("1. Listar todas as poções.\n2. Listar poção pelo índice\n");
                switch (opcao)
                {
                    case 1:
                        printf("Lista de Poções:\n");
                        for (int i = 0; i < QuantidadePocoes(); i++)
                        {
                            Pocao* copia = ObterPocaoPeloIndice(i);
                            if (copia != NULL)
                            {
                                printf("Código: %d\n", copia->codigo);
                                printf("Nome: %s\n", copia->nome);
                                printf("Tipo: %s\n\n", copia->tipo);
                                LiberarCopiaPocao(copia);
                            } else {
                                printf("Erro ao acessar informações da poção.\n");
                            }
                        }
                        break;
                    case 2:
                        indice = get_int_input("Digite o índice da poção:");
                        Pocao* copia = ObterPocaoPeloIndice(indice);

                        if (copia != NULL)
                        {
                            // Imprimir dados da Poção
                            printf("Poção %d: %s, %s\n", copia->codigo, copia->nome, copia->tipo);

                            // Liberar memória alocada para a cópia da Poção
                            LiberarCopiaPocao(copia);
                        } else {
                            printf("Índice inválido ou poção não encontrada.\n");
                        }
                        break;
                }
                /////////////////////////////////////////////////////////////////////////////////
                break;
            case 2: // Cadastrar poção
                codigo = get_int_input("Digite o código da Poção: ");
                nome = get_string_input("Digite o nome da Poção: ");
                tipo = get_string_input("Digite o tipo da Poção: ");
                Pocao novaPocao;
                novaPocao.codigo = codigo;
                novaPocao.nome = nome;
                novaPocao.tipo = tipo;

                resultadoCadastro = SalvarPocao(novaPocao);
                if (resultadoCadastro == 0)
                {
                    printf("Código já existente. Por favor, insira um código diferente.\n");
                }
                break;
            case 3: // Alterar poção
			    codigo = get_int_input("Digite o código da Poção que deseja atualizar: ");
			    char* novoNome;
			    novoNome = get_string_input("Digite o novo nome da Poção: ");
			    char* novoTipo;
			    novoTipo = get_string_input("Digite o novo tipo da Poção: ");
			    
			    if (ModificarPocaoPeloCodigo(codigo, novoNome, novoTipo)) {
			        printf("Poção atualizada com sucesso!\n");
			    } else {
			        printf("Falha ao atualizar a Poção ou Poção não encontrada.\n");
			    }
			    break;
            case 4: // Excluir poção
                codigo = get_int_input("Digite o código da Poção que deseja apagar: ");

                if (ApagarPocaoPeloCodigo(codigo))
                {
                    printf("Poção removida com sucesso!\n");
                } else {
                    printf("Falha ao remover a Poção.\n");
                }
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }
}

void menuTratamento()
{
    int opcao = -1;
    while (opcao != 0) {
        printf("\n--- Menu Tratamento ---\n");
        printf("1. Listar tratamentos do paciente\n");
        printf("2. Listar tratamentos do bruxo\n");
        printf("3. Iniciar tratamento\n");
        printf("4. Ampliar tratamento\n");
        printf("5. Excluir tratamento\n");
        printf("0. Sair\n");

		opcao = get_int_input("");

        switch (opcao)
		{
            case 0:
                // Retorna ao menu anterior
                break;
			case 1:
				{
				char nome2[100];
			    codigo = get_int_input("Digite o código do Paciente para listar os tratamentos: ");
			    int* tratamentosPaciente = NULL;
				int totalTratamentosPaciente = ListarTratamentosPaciente(codigo, &tratamentosPaciente);
				if(totalTratamentosPaciente > 0)
				{
			        printf("Tratamentos do Paciente %d:\n", codigo);
			        for (int i = 0; i < totalTratamentosPaciente; i++)
					{
			             Tratamento* tratamento = ObterTratamentoPeloIndice(tratamentosPaciente[i]);
			             if (tratamento != NULL)
			             {
			             	printf("Codigo do Tratamento: %d\n", tratamento->codigoTratamento);
                            printf("Codigo do Paciente: %d\n", tratamento->codigoPaciente);
							if (ObterNomePaciente(tratamento->codigoPaciente, nome2))
							{
							    printf("Nome do Paciente: %s\n", nome2);
							}
                            printf("Codigo do Bruxo: %d\n", tratamento->codigoBruxo);
							if (ObterNomeBruxo(tratamento->codigoBruxo, nome2))
							{
							    printf("Nome do Bruxo: %s\n", nome2);
							}
							printf("Codigo da Pocao: %d\n", tratamento->codigoPocao);
							if (ObterNomePocao(tratamento->codigoPocao, nome2))
							{
							    printf("Nome da Pocao: %s\n", nome2);
							}
							printf("Dosagem: %d\n", tratamento->dosagem);
                            printf("Duracao: %d dias\n\n", tratamento->duracao);
                            LiberarCopiaTratamento(tratamento);
						}
			        }
			    } else {
			        printf("Nenhum tratamento encontrado para o Paciente %d.\n", codigo);
			    }
			    free(tratamentosPaciente);
				tratamentosPaciente = NULL;
			    break;
				}
			case 2:
				{
				char nome2[100];
			    codigo = get_int_input("Digite o código do Bruxo para listar os tratamentos: ");
			    int* tratamentosBruxo = NULL;
				int totalTratamentosBruxo = ListarTratamentosBruxo(codigo, &tratamentosBruxo);
				if(totalTratamentosBruxo > 0)
				{
			        printf("Tratamentos do Bruxo %d:\n", codigo);
			        for (int i = 0; i < totalTratamentosBruxo; i++)
					{
			             Tratamento* tratamento = ObterTratamentoPeloIndice(tratamentosBruxo[i]);
			             if (tratamento != NULL)
			             {
			             	printf("Codigo do Tratamento: %d\n", tratamento->codigoTratamento);
                            printf("Codigo do Paciente: %d\n", tratamento->codigoPaciente);
							if (ObterNomePaciente(tratamento->codigoPaciente, nome2))
							{
							    printf("Nome do Paciente: %s\n", nome2);
							}
                            printf("Codigo do Bruxo: %d\n", tratamento->codigoBruxo);
							if (ObterNomeBruxo(tratamento->codigoBruxo, nome2))
							{
							    printf("Nome do Bruxo: %s\n", nome2);
							}
							printf("Codigo da Pocao: %d\n", tratamento->codigoPocao);
							if (ObterNomePocao(tratamento->codigoPocao, nome2))
							{
							    printf("Nome da Pocao: %s\n", nome2);
							}
							printf("Dosagem: %d\n", tratamento->dosagem);
                            printf("Duracao: %d dias\n\n", tratamento->duracao);
                            LiberarCopiaTratamento(tratamento);	
						 }
			        }
			    } else {
			        printf("Nenhum tratamento encontrado para o bruxo %d.\n", codigo);
			    }
			    free(tratamentosBruxo);
				tratamentosBruxo = NULL;
			    break;
				}
			case 3:
			    {
			    	int codTratamento = 0;
			        codTratamento = get_int_input("Digite o codigo do tratamento: ");
			        int codPaciente = 0;
			        codPaciente = get_int_input("Digite o codigo do paciente: ");
			        if (!CodigoPacienteValido(codPaciente))
					{
				        printf("Codigo de paciente invalido. Tratamento nao iniciado.\n");
				        break;
				    }
			        int codBruxo = 0;
			        codBruxo = get_int_input("Digite o codigo do bruxo: ");
			        if (!CodigoBruxoValido(codBruxo))
					{
				        printf("Codigo de bruxo invalido. Tratamento nao iniciado.\n");
				        break;
				    }
			        int codPocao = 0;
			        codPocao = get_int_input("Digite o codigo da pocao: ");
			        if (!CodigoPocaoValido(codPocao))
					{
				        printf("Codigo de pocao invalido. Tratamento nao iniciado.\n");
				        break;
				    }
			        int duracao = 0;
			        duracao = get_int_input("Digite a duracao do tratamento: ");
			        int dosagem = 0;
			        dosagem = get_int_input("Digite a dosagem: ");
			        
			        Tratamento novoTratamento;
			        novoTratamento.codigoTratamento = codTratamento;
			        novoTratamento.codigoPaciente = codPaciente;
			        novoTratamento.codigoBruxo = codBruxo;
			        novoTratamento.codigoPocao = codPocao;
			        novoTratamento.duracao = duracao;
			        novoTratamento.dosagem = dosagem;
			        
			        if (SalvarTratamento(novoTratamento))
					{
			            printf("Tratamento iniciado com sucesso!\n");
			        } else {
			            printf("Falha ao iniciar o tratamento.\n");
			        }
			    }
			    break;
        	case 4:
                codigo = get_int_input("Digite o codigo do Tratamento para ampliar: ");
                int dosagemAdicional = 0;
                int duracaoAdicional = 0;
                dosagemAdicional = get_int_input("Digite a dosagem adicional para o tratamento: ");
				duracaoAdicional = get_int_input("Digite a duração adicional para o tratamento: ");

                if (AmpliarTratamento(codigo, duracaoAdicional, dosagemAdicional))
				{
                    printf("Tratamento ampliado com sucesso!\n");
                } else {
                    printf("Falha ao ampliar o tratamento ou tratamento nao encontrado.\n");
                }
                break;
            case 5:
            	codigo = get_int_input("Digite o codigo do Tratamento para apagar: ");
                if (ExcluirTratamento(codigo))
				{
                    printf("Tratamento excluido com sucesso!\n");
                } else {
                    printf("Falha ao excluir o tratamento ou tratamento nao encontrado.\n");
                }
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }
}
