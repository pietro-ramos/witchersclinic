#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "get_input.h"
#include "Bruxo.h"
#include "Pocao.h"
#include "Paciente.h"
	
int codigo;
int indice;
int resultadoCadastro;
char* nome;
char* especialidade;
char* tipo;
int idade;
float altura;
Bruxo novoBruxo;
void InicializarTudo();
void EncerrarTudo();
void menuBruxo();
void menuPaciente();
void menuPocao();
void menuTratamento();


int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Portuguese");
    InicializarTudo(); // Inicializa as estruturas
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

// INICIALIZA��O E ENCERRAMENTO

void InicializarTudo()
{
	InicializarBruxos();
	InicializarPocoes();
	InicializarPacientes();
}

void EncerrarTudo()
{
	EncerrarBruxos();
	EncerrarPocoes();
	EncerrarPacientes();
}

// FUN��ES DOS SUBMENUS

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
					            printf("C�digo: %d\n", copia->codigo);
					            printf("Nome: %s\n", copia->nome);
					            printf("Especialidade: %s\n\n", copia->especialidade);
					            LiberarCopiaBruxo(copia);
					        } else {
					            printf("Erro ao acessar informa��es do bruxo.\n");
					        }
					    }
            			break;
					case 2:
						indice = get_int_input("Digite o �ndice do bruxo:");
		                Bruxo* copia = ObterBruxoPeloIndice(indice);
		
		                if (copia != NULL)
						{
		                    // Imprimir dados do Bruxo
		                    printf("Bruxo %d: %s, %s\n", copia->codigo, copia->nome, copia->especialidade);
		
		                    // Liberar mem�ria alocada para a c�pia do Bruxo
		                    LiberarCopiaBruxo(copia);
		                } else {
		                    printf("�ndice inv�lido ou bruxo n�o encontrado.\n");
		                }
		                break;
		    	}
                /////////////////////////////////////////////////////////////////////////////////
            case 2: // Cadastrar bruxo
    			codigo = get_int_input("Digite o codigo do Bruxo: ");
                nome = get_string_input("Digite o nome do Bruxo: ");
                especialidade = get_string_input("Digite a especialidade do Bruxo: ");
                novoBruxo.codigo = codigo;
                novoBruxo.nome = nome;
                novoBruxo.especialidade = especialidade;
                
				resultadoCadastro = SalvarBruxo(novoBruxo);
                if (resultadoCadastro == 0)
				{
                    printf("C�digo j� existente. Por favor, insira um c�digo diferente.\n");
                }
                break;
            case 3:
			    codigo = get_int_input("Digite o c�digo do Bruxo que deseja atualizar: ");
			    Bruxo* bruxoParaAtualizar = ObterBruxoPeloCodigo(codigo);
			
			    if (bruxoParaAtualizar != NULL)
				{
					char* novoNome;
			        novoNome = get_string_input("Digite o novo nome do Bruxo: ");
			        char* novaEspecialidade;
			        novaEspecialidade = get_string_input("Digite a nova especialidade do Bruxo: ");
			        Bruxo novoBruxo;
			   		novoBruxo.codigo = codigo;
                	novoBruxo.nome = novoNome;
               		novoBruxo.especialidade = novaEspecialidade;
               		
			        if (AtualizarBruxo(novoBruxo))
					{
			            printf("Bruxo atualizado com sucesso!\n");
			        } else {
			            printf("Falha ao atualizar o Bruxo.\n");
			        }
			    } else {
			        printf("Bruxo n�o encontrado.\n");
			    }
			    break;

            case 4: // Excluir bruxo
    			codigo = get_int_input("Digite o c�digo do Bruxo que deseja apagar: ");

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
                opcao = get_int_input("1. Listar todos os pacientes.\n2. Listar paciente pelo �ndice\n");
                switch (opcao)
                {
                    case 1:
                        printf("Lista de Pacientes:\n");
                        for (int i = 0; i < QuantidadePacientes(); i++)
                        {
                            Paciente* copia = ObterPacientePeloIndice(i);
                            if (copia != NULL)
                            {
                                printf("C�digo: %d\n", copia->codigo);
                                printf("Nome: %s\n", copia->nome);
                                printf("Idade: %d\n", copia->idade);
                                printf("Altura: %.2f\n\n", copia->altura);
                                LiberarCopiaPaciente(copia);
                            } else {
                                printf("Erro ao acessar informa��es do paciente.\n");
                            }
                        }
                        break;
                    case 2:
                        indice = get_int_input("Digite o �ndice do paciente:");
                        Paciente* copia = ObterPacientePeloIndice(indice);

                        if (copia != NULL)
                        {
                            // Imprimir dados do Paciente
                            printf("Paciente %d: %s, %d anos, %.2f de altura\n", copia->codigo, copia->nome, copia->idade, copia->altura);

                            // Liberar mem�ria alocada para a c�pia do Paciente
                            LiberarCopiaPaciente(copia);
                        } else {
                            printf("�ndice inv�lido ou paciente n�o encontrado.\n");
                        }
                        break;
                }
                /////////////////////////////////////////////////////////////////////////////////
                break;
            case 2: // Cadastrar paciente
                codigo = get_int_input("Digite o c�digo do Paciente: ");
                nome = get_string_input("Digite o nome do Paciente: ");
                idade = get_int_input("Digite a idade do Paciente: ");
                altura = get_float_input("Digite a altura do Paciente: ");
                Paciente novoPaciente;
                novoPaciente.codigo = codigo;
                novoPaciente.nome = nome;
                novoPaciente.idade = idade;
                novoPaciente.altura = altura;

                int resultadoCadastro = SalvarPaciente(novoPaciente);
                if (resultadoCadastro == 0)
                {
                    printf("C�digo j� existente. Por favor, insira um c�digo diferente.\n");
                }
                break;
            case 3:
                codigo = get_int_input("Digite o c�digo do Paciente que deseja atualizar: ");
                Paciente* pacienteParaAtualizar = ObterPacientePeloCodigo(codigo);

                if (pacienteParaAtualizar != NULL)
                {
                    char* novoNome;
                    novoNome = get_string_input("Digite o novo nome do Paciente: ");
                    int novaIdade = get_int_input("Digite a nova idade do Paciente: ");
                    float novaAltura = get_float_input("Digite a nova altura do Paciente: ");
                    Paciente novoPaciente;
                    novoPaciente.codigo = codigo;
                    novoPaciente.nome = novoNome;
                    novoPaciente.idade = novaIdade;
                    novoPaciente.altura = novaAltura;

                    if (AtualizarPaciente(novoPaciente))
                    {
                        printf("Paciente atualizado com sucesso!\n");
                    } else {
                        printf("Falha ao atualizar o Paciente.\n");
                    }
                } else {
                    printf("Paciente n�o encontrado.\n");
                }
                break;
            case 4: // Excluir paciente
                codigo = get_int_input("Digite o c�digo do Paciente que deseja apagar: ");

                if (ApagarPacientePeloCodigo(codigo))
                {
                    printf("Paciente removido com sucesso!\n");
                } else {
                    printf("Falha ao remover o Paciente.\n");
                }
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
                break;
        }
    }
}

void menuPocao()
{
    int opcao = -1;
    while (opcao != 0)
    {
        printf("\n--- Menu Po��o ---\n");
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
            case 1:// Listar po��es
                if (QuantidadePocoes() == 0)
                {
                    printf("Nenhuma po��o cadastrada.\n");
                    break;
                }
                /////////////////////////////////////////////////////////////////////////////////
                opcao = get_int_input("1. Listar todas as po��es.\n2. Listar po��o pelo �ndice\n");
                switch (opcao)
                {
                    case 1:
                        printf("Lista de Po��es:\n");
                        for (int i = 0; i < QuantidadePocoes(); i++)
                        {
                            Pocao* copia = ObterPocaoPeloIndice(i);
                            if (copia != NULL)
                            {
                                printf("C�digo: %d\n", copia->codigo);
                                printf("Nome: %s\n", copia->nome);
                                printf("Tipo: %s\n\n", copia->tipo);
                                LiberarCopiaPocao(copia);
                            } else {
                                printf("Erro ao acessar informa��es da po��o.\n");
                            }
                        }
                        break;
                    case 2:
                        indice = get_int_input("Digite o �ndice da po��o:");
                        Pocao* copia = ObterPocaoPeloIndice(indice);

                        if (copia != NULL)
                        {
                            // Imprimir dados da Po��o
                            printf("Po��o %d: %s, %s\n", copia->codigo, copia->nome, copia->tipo);

                            // Liberar mem�ria alocada para a c�pia da Po��o
                            LiberarCopiaPocao(copia);
                        } else {
                            printf("�ndice inv�lido ou po��o n�o encontrada.\n");
                        }
                        break;
                }
                /////////////////////////////////////////////////////////////////////////////////
                break;
            case 2: // Cadastrar po��o
                codigo = get_int_input("Digite o c�digo da Po��o: ");
                nome = get_string_input("Digite o nome da Po��o: ");
                tipo = get_string_input("Digite o tipo da Po��o: ");
                Pocao novaPocao;
                novaPocao.codigo = codigo;
                novaPocao.nome = nome;
                novaPocao.tipo = tipo;

                resultadoCadastro = SalvarPocao(novaPocao);
                if (resultadoCadastro == 0)
                {
                    printf("C�digo j� existente. Por favor, insira um c�digo diferente.\n");
                }
                break;
            case 3:
                codigo = get_int_input("Digite o c�digo da Po��o que deseja atualizar: ");
                Pocao* pocaoParaAtualizar = ObterPocaoPeloCodigo(codigo);

                if (pocaoParaAtualizar != NULL)
                {
                    char* novoNome;
                    novoNome = get_string_input("Digite o novo nome da Po��o: ");
                    char* novoTipo;
                    novoTipo = get_string_input("Digite o novo tipo da Po��o: ");
                    Pocao novaPocao;
                    novaPocao.codigo = codigo;
                    novaPocao.nome = novoNome;
                    novaPocao.tipo = novoTipo;

                    if (AtualizarPocao(novaPocao))
                    {
                        printf("Po��o atualizada com sucesso!\n");
                    } else {
                        printf("Falha ao atualizar a Po��o.\n");
                    }
                } else {
                    printf("Po��o n�o encontrada.\n");
                }
                break;
            case 4: // Excluir po��o
                codigo = get_int_input("Digite o c�digo da Po��o que deseja apagar: ");

                if (ApagarPocaoPeloCodigo(codigo))
                {
                    printf("Po��o removida com sucesso!\n");
                } else {
                    printf("Falha ao remover a Po��o.\n");
                }
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
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

        switch (opcao) {
            case 0:
                // Retorna ao menu anterior
                break;
            case 1:
                // Listar tratamentos do paciente
                break;
            case 2:
                // Listar tratamentos do bruxo
                break;
            case 3:
                // Iniciar tratamento
                break;
            case 4:
                // Ampliar tratamento
                break;
            case 5:
                // Excluir tratamento
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }
}
