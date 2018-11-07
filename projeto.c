#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>

struct tm * periodo; // Composição composta para hora, minuto, segundo, dia mes e ano
                    // em vez de etapas do programa
                    
typedef struct {// estrutura para guardar hora, minuto, segundo, dia mes e ano 
	    int dia, mes, ano; // em vez de etapas do programa    
	    int hora, minuto, segundo;    
}Local;
    

typedef struct {// Estruturar principal, com uma função de armazenamento de dados dos rotistas
	char numConta [5];
	char nome [10];
	char sobrenome [10];
	char cpf [14];
	flutuar saldo;
    Local local; // varivel do tipo struct Local
} Rotista;

/ * typedef struct {
    char numRua [10];
    char nomeRua [100]
    char casa [10];
    
}; * /

int menu (); // Contém como opções de entrada para o usuário
void opcao (); // retorna a opção do usuário em função ao menu
void listaRotistas (); // Lista todos os rotários na ativa
void procuraRotista (); // Procura um rotista cadastrado
void cadastroRotista (); // Cadastra um rotista ao programa
void alteraRotista (); // Altera um rotista cadastro
void deletaRotista (); // Deleta um rotista que foi cadastrado
void sair ();

// Verificações de entrada de dados
int folhasCPF (char []); // Verifica CPF no cadastro ou alteração de um rotista
int verificaNumConta (char []); // Verifica Numero da conta sem cadastro de um rotista

// Verificação de experiência de dados
int cpfCadastrado (char [], char [], int); // Verifica o CPF do rotista já cadastrado   
int numContaCadastro (char []); // Verifica se um numero de conta do rotador já foi Cadastrado

// Entradas de dados dos usuários
void lerNumConta (Rotista *);
void lerNome (Rotista *);
void lerSobrenome (Rotista *);
void lerCPF (Rotista *, char [], int);
void lerSaldo (Rotista *);
voara declaraTempo (Rotista *);
void declaraData (Rotista *);

// Digita na tela informações de um rotista
int escreveRotista (Rotista *, char []);

void main () {// Inserir principal
	setlocale (LC_ALL, "Português"); // Aceita acentos
	opcao (); // Chama o controlador do menu
}

int menu () {// MONTA O MENU E RETORNA À OPÇÃO ESCOLHIDA

	sistema ("cls");
	printf ("\ t \ tMENU \ n");
	printf ("(0) - Sair \ n");
	printf ("(1) - Cadastro \ n");
	printf ("(2) - Listar \ n");
	printf ("(3) - procura \ n");
	printf ("(4) - Alterar \ n");
	printf ("(5) - Deletar \ n");
	
	int escolha;
	scanf ("% d", & escolha);
	
	return escolha; // retorna uma opção escolhida
}

void opcao () {
	// Verifica uma opção escolhida e obrigatória para uma função necessária
	sistema ("cls");
	void (* retorno [6]) (vazio) = {sair, cadastroRotista, listaRotistas, procuraRotista, alteraRotista, deletaRotista};
    int escolha = menu ();

    if (escolha <= 5 && escolha> = 0) {
        (* retorno [escolha]) ();
        opcao ();
    }    
    opcao ();
}

void cadastroRotista () {
	Rotista * rotista = (Rotista *) malloc (sizeof (Rotista));
    sistema ("cls");
    
    time_t t;
    t = tempo (NULL);
    periodo = hora local (& t);
    
    lerNumConta (rotista);
    lerNome (rotista);
    lerSobrenome (rotista);
    lerCPF (rotista, rotista-> numConta, 0);
    lerSaldo (rotista);
    declaraTempo (rotista);
    declaraData (rotista);

	ARQUIVO * ptr;
	ptr = fopen ("rotista.c", "ab");

	if (ptr == NULL) {
		printf ("Erro ao abrir arquivo!");
	} outro {
		fwrite (rotista, tamanho de (Rotista), 1, ptr); // Salva 1 registro de roteador no arquivo de forma binaria
		printf ("Salvo! \ n");
	}
	fclose (ptr);
	grátis (rotista); // Libera a memoria
	
	printf ("\ nPressione qualquer botão para continuar ...");
	getch ();
}

void procuraRotista () {// Procura um rotista especifico
    sistema ("cls");
    char numConta [11];
    int entrou = 0;
	Rotista * rotista = (Rotista *) malloc (sizeof (Rotista));
	
    printf ("Digite o numero da conta:");
    fflush (stdin);
	fgets (numConta, 11, stdin);
	fflush (stdin);
    
    sistema ("cls");
	entrou = escreveRotista (rotista, numConta);
	
	se (entrou == 0)
	    printf ("Erro ao encontrar número de conta \ n \ n");
    
	
	printf ("qualquer outro evento para continuar ...");
    livre (rotista);
    
	getch ();
}

void listaRotistas () {// lista todos os rotistas cadastros
	ARQUIVO * ptr;
	sistema ("cls"); // LIMPA A TELA
	// Abre o arquivo em modo de leitura binária.
	ptr = fopen ("rotista.c", "rb");
	Rotista * rotista = (Rotista *) malloc (sizeof (Rotista)); // Cria um rotista

	if (ptr == NULL) {
		printf ("Erro ao abrir arquivo!");
	} outro {
		rebobinar (ptr); // Ler o arquivo desde o começo
		enquanto (frito (rotista, tamanho de (Rotista), 1, ptr) == 1) {// LER um roteiro por cada vez e imprimi como informaçoes
			printf ("% - 15s% s", "Identificação:", rotista-> numConta);
			printf ("% - 15s% s% s \ n", "Nome:", rotista -> nome, rotista -> sobrenome);
			printf ("% - 15s% s", "CPF:", rotista-> cpf);
			printf ("% - 15s% .2f \ n \ n", "Saldo:", rotista-> saldo);
			printf ("% s", "Periodo do cadastro: \ n");
			printf ("% d /% d /% d \ n", rotista-> local.dia, rotista-> local.mes, rotista-> local.ano);
			printf ("% d:% d:% d \ n \ n", rotista-> local.hora, rotista-> local.minuto, rotista-> local.segundo);
		}
	}

	fclose (ptr);
	livre (rotista);
	printf ("qualquer outro evento para continuar ...");

	getch (); // Espera o usuário ao clicar em uma tecla
}

void alteraRotista () {
    setlocale (LC_ALL, "Português");
    Rotista * rotista = (Rotista *) malloc (sizeof (Rotista));
	int entrou = 0;
    char numConta [11];
    
	sistema ("cls");
	printf ("Digite o numero da conta:");
	fflush (stdin);
	fgets (numConta, 11, stdin);
	fflush (stdin);
    
    sistema ("cls");
    entrou = escreveRotista (rotista, numConta);
	
	se (entrou == 1) {// Se o rotista foi encontrado
        time_t t;
        t = tempo (NULL); 
        periodo = hora local (& t);
        
        printf ("\ t \ tALTERALÇÕES: \ n");
        lerNome (rotista);
        lerSobrenome (rotista);
        lerCPF (rotista, numConta, 1);
        lerSaldo (rotista);
        declaraTempo (rotista);
        declaraData (rotista);

        ARQUIVO * ptr;
		ARQUIVO * ptrAux;
		ptr = fopen ("rotista.c", "rb");
		ptrAux = fopen ("rotistaAux.c", "ab");

		Há dois arquivos abertos
		// O original e o que auxiliar que os novos dados
		Rotista * rotistaAux = (Rotista *) malloc (sizeof (Rotista));
		
		// rotista = possui o rotista alterado
		// rotistaAux são os roteiros já salvo no arquivo

		if (ptr == NULL || ptrAux == NULL) {
			printf ("Erro ao abrir arquivo!");
		} outro {
			rebobinar (ptr);
			while (frade (rotistaAux, sizeof (Rotista), 1, ptr) == 1) {
				if (strcmp (rotador-> numConta, numConta) == 0) {// Para o rotador alterado, salve o novo rotista
					fwrite (rotista, sizeof (Rotista), 1, ptrAux);
				} outro {
					// SE NÃO, salve o rotista normal
					fwrite (rotistaAux, sizeof (Rotista), 1, ptrAux);
				}
			}
		}
		fclose (ptr);
		fclose (ptrAux);
		livre (rotista);
		grátis (rotistaAux);
		
		remove ("rotista.c"); // Remove o arquivo original
		renomear ("rotistaAux.c", "rotista.c"); // Renomeia o arquivo auxiliar com os novos dados
	}

	printf ("qualquer outro evento para continuar ...");
	getch ();
}

void deletaRotista () {
    Rotista * rotista = (Rotista *) malloc (sizeof (Rotista));
	int entrou = 0;
	char numConta [5];
    
    sistema ("cls");
    printf ("Digite o numero da conta:");
	fflush (stdin);
    fgets (numConta, 11, stdin);
    fflush (stdin);
    
    sistema ("cls");    
    entrou = escreveRotista (rotista, numConta);
	
	se (entrou == 1) {
		ARQUIVO * ptrAux;
		ARQUIVO * ptr;
		ptr = fopen ("rotista.c", "rb");
		ptrAux = fopen ("rotistaAux.c", "ab");
		Rotista * rotista = (Rotista *) malloc (sizeof (Rotista));
        Rotista * rotistaAux = (Rotista *) malloc (sizeof (Rotista));
        
		if (ptr == NULL || ptrAux == NULL) {
			printf ("Erro ao abrir arquivo!");
		} outro {
			rebobinar (ptr);
			rebobinar (ptrAux);
			enquanto (fread (rotista, sizeof (Rotista), 1, ptr) == 1) {
				if (strcmp (rotador-> numConta, numConta) == 0) {// Para o rotista deletado, não fazer nada
				    // DELETADO
				} outro {
					// salvar os outros rotistas
					fwrite (rotistaAux, sizeof (Rotista), 1, ptrAux);
				}
			}
		}
		fclose (ptr);
		fclose (ptrAux);
		
		livre (rotista);
		grátis (rotistaAux);
		rotista = NULL;
		rotistaAux = NULL;

		remove ("rotista.c");
		renomear ("rotistaAux.c", "rotista.c");
	}
	printf ("qualquer outro evento para continuar ...");

	getchar ();
}

void sair () {
    saída (1);
}

// Verificações da validação do cpf
int cpfCadastrado (char cpf [], char numConta [], int check) {
    ARQUIVO * ptrAux;
    
    ptrAux = fopen ("rotista.c", "rb");
    Rotista * rotistaAux = (Rotista *) malloc (sizeof (Rotista));
       
    if (ptrAux == NULL) {
          
    }outro{
        rebobinar (ptrAux);
        while (frade (rotistaAux, sizeof (Rotista), 1, ptrAux) == 1) {
            if (check == 0) {
                if (strcmp (rotistaAux-> cpf, cpf) == 0) {
                    printf ("Entre com um CPF ainda não cadastrado:");
                    fclose (ptrAux);
                    grátis (rotistaAux);
                    return 0;
                }
            }outro
                if (check == 1) {
                    if (strcmp (rotistaAux-> cpf, cpf) == 0 && strcmp (rotistaAux-> numConta, numConta)! = 0) {
                        printf ("Entre com um CPF ainda não cadastrado:");
                        fclose (ptrAux);
                        grátis (rotistaAux);
                        return 0;
                    }
                }
        }   
        if (verificaCPF (cpf) == 0) {
            printf ("Entre com um CPF válido:");
            fclose (ptrAux);
            grátis (rotistaAux);
            return 0;
        }outro{
            fclose (ptrAux);
            grátis (rotistaAux);
            return 1;
        }
    }
}

int folhasCPF (char cpf []) {
	char aux [1]; // Cadeia de 1 porque atoi nao desloca caracter unico
    int a, b;
    int soma = 0;
     
    if (strlen (cpf) - 1! = 11) // verifica se o valor é inserido tem 11 caracteres
        return 0;

    para (a = 0; a <11; a ++) {
        if (! isdigit (cpf [a])) // verifica se todos os caracteres inseridos são um digito
            return 0;
    }

    para (a = 0, b = 10; a <9; a ++, b -) {
        aux [0] = cpf [a];
        soma + = b * atoi (aux);  
    }
    aux [0] = cpf [9];  
    se (soma% 11> = 2) {
        se (atoi (aux)! = 11 - (soma% 11)) {
            return 0;
        }   
    }outro{
        se (atoi (aux)! = 0) {
            return 0;
        }
    }

    soma = 0;
    para (a = 0, b = 11; a <10; a ++, b -) {
        aux [0] = cpf [a];
        soma + = b * atoi (aux);
    }
    
    aux [0] = cpf [10];
    se (soma% 11> = 2) {
        se (atoi (aux)! = 11 - (soma% 11))
            return 0;
    }outro{
        se (atoi (aux)! = 0)
            return 0;
    }
    
    return 1;
}
////////////////////////////////////////////////// ///////
// Verificações da validação do NumConta //
int numContaCadastrado (char dado []) {
    setlocale (LC_ALL, "Português");
    ARQUIVO * ptr;
    
    ptr = fopen ("rotista.c", "rb");
    Rotista * rotista = (Rotista *) malloc (sizeof (Rotista));
       
    if (ptr == NULL) {
       
    }outro{
        rebobinar (ptr);
        while (fread (rotista, sizeof (Rotista), 1, ptr) == 1) {
            if (strcmp (rotista-> numConta, dado) == 0) {
                printf ("Entre com um número de conta não cadastrado:");
                fclose (ptr);
                livre (rotista);
                return 0;       
            }
        }
        if (verificaNumConta (dado) == 0) {
            printf ("Entre com um número de conta válido");
            fclose (ptr);
            livre (rotista);
            return 0;
        }
    }
    fclose (ptr);
    livre (rotista);
    return 1;
}

int verificaNumConta (char numConta []) {
    int i;
        
    if (strlen (numConta) - 1! = 3)
        return 0;
    
    para (i = 0; i <strlen (numConta) - 1; i ++) {
        if (! isdigit (numConta [i]))
            return 0;
    }
    
    return 1;
}
////////////////////////////////////////////////// //////////////////
void lerNumConta (Rotista * rotista) {
    // Entra com o numero da conta
	printf ("Digite o número da sua conta:");
	inicio:
        fflush (stdin);
	    fgets (rotista-> numConta, 11, stdin);
	    fflush (stdin);
	    if (numContaCadastrado (rotista-> numConta) == 0)  
                    goto inicio;
}

void lerNome (Rotista * rotista) {
    // Entrada do Nome do Usuário
    printf ("Digite seu nome:");
	fflush (stdin);
    Obtém (rotista-> nome);
    fflush (stdin);
}

void lerSobrenome (Rotista * rotista) {
    // Entrada do Sobrenome no Usuário
	printf ("Digite seu sobrenome:");
	fflush (stdin);
	Obtém (rotista-> sobrenome);
	fflush (stdin);
}

void lerCPF (Rotista * rotista, char numConta [], int check) {
    // Entrada do CPF do usuário
	printf ("Digite seu CPF:");
    inicio:
        fflush (stdin);
        fgets (rotista-> cpf, 14, stdin);               
        fflush (stdin);
        if (cpfCadastrado (rotista-> cpf, numConta, check) == 0)
            goto inicio; 
        
}

void lerSaldo (Rotista * rotista) {
    // Entrada do saldo do rotista
	printf ("Entre com seu saldo:");
	fflush (stdin);
	scanf ("% f", & rotista-> saldo);
	fflush (stdin);
}

voara declaraTempo (Rotista * rotista) {
    // Salvando o dia em que o cadastro do roteiro foi
	rotista-> local.dia = periodo-> tm_mday;
    rotista-> local.mes = periodo-> tm_mon + 1;
    rotista-> local.ano = periodo-> tm_ano + 1900;
}

void declaraData (Rotista * rotista) {
    // Salvando a hora em que o cadastro do roteiro foi criado
    rotista-> local.segundo = periodo-> tm_sec;
    rotista-> local.minuto = periodo-> tm_min;
    rotista-> local.hora = periodo-> tm_hour;
}
////////////////////////////////////////////////// //////////////////////
int escreveRistista (Rotista * rotista, char numeroConta []) {
    FILE * ptr = fopen ("rotista.c", "rb");
    
    if (ptr == NULL) {
        printf ("Erro ao abrir o arquivo!");
    }outro{
        rebobinar (ptr);
        enquanto (fread (rotista, sizeof (Rotista), 1, ptr)) {
            if (strcmp (rotista-> numConta, numeroConta) == 0) {
				printf ("% - 15s% s", "Identificação:", rotista-> numConta);
	            printf ("% - 15s% s% s \ n", "Nome:", rotista -> nome, rotista -> sobrenome);
			    printf ("% - 15s% s", "CPF:", rotista-> cpf);
			    printf ("% - 15s% .2f \ n \ n", "Saldo:", rotista-> saldo);
			    printf ("% s", "Periodo do cadastro: \ n");
			    printf ("% d /% d /% d \ n", rotista-> local.dia, rotista-> local.mes, rotista-> local.ano);
			    printf ("% d:% d:% d \ n \ n", rotista-> local.hora, rotista-> local.minuto, rotista-> local.segundo);
				fclose (ptr);
                return 1;
            }
        }
    }
    fclose (ptr);
    return 0;
}
