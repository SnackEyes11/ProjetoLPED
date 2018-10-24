#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

typedef struct {
	int numConta;
	char nome[10];
	char sobrenome[10];
	float saldo;
	char cpf[13];
	/*struct {
	    char
	};*/
} Rotista;

int menu();
void listaRotistas();
void procuraRotista();
void cadastraRotista();
void alteraRotista();
void deletaRotista();
void opcao();

//Verificações de entrada de dados
int verifica_CPF(char[]);

/*void adicionaRota();
void excluiRota();
void alteraRota();
*/
void main() {
	setlocale(LC_ALL, "Portuguese"); //Aceita acentos
	opcao();//Chama o controlador do menu
}

int menu() { // MONTA O MENU E RETORNA A OPÇÃO ESCOLHIDA

	system("cls");
	printf("\t\tMENU\n");
	printf("(0) - Sair\n");
	printf("(1) - Cadastro\n");
	printf("(2) - Listar\n");
	printf("(3) - Procurar\n");
	printf("(4) - Alterar\n");
	printf("(5) - Deletar\n");
	int opcao;
	scanf("%d", &opcao);
	return opcao; // retorna a opção escolhida
}

void listaRotistas() { //lista todos os rotistas cadastros

	FILE *parq;
	system("cls");//LIMPA A TELA
	//Abre o arquivo em modo de leitura binária.
	parq = fopen("rotista.c", "rb");
	Rotista *rotista = (Rotista *) malloc(sizeof(Rotista)); // Cria um rotista

	if(parq == NULL) {
		printf("Erro ao abrir arquivo!");
	} else {
		rewind(parq); //Ler o arquivo desde o começo
		while(fread(rotista, sizeof(Rotista), 1, parq) == 1) { //LER um rotista por cada vez e imprimi as informaçoes
			printf("%-15s%d\n", "Identificação:", rotista->numConta);
			printf("%-15s%s %s\n", "Nome:", rotista->nome, rotista->sobrenome);
			printf("%-15s%s\n", "CPF:", rotista->cpf);
			printf("%-15s%.2f\n\n", "Saldo:", rotista->saldo);
		}
	}

	fclose(parq);
	printf("Pressione qualquer tecla para continuar...");

	getch(); //Espera o usuário clicar uma botão

}
void procuraRotista() { //Procura um rotista especifico
	system("cls");
	printf("Digite o numero da conta: ");
	int numConta;
	scanf("%d", &numConta);

	Rotista *rotista = (Rotista *) malloc(sizeof(Rotista));
	FILE *parq;

	//Abre o arquivo em modo de leitura binária.
	parq = fopen("rotista.c", "rb");

	if(parq == NULL) {
		printf("Erro ao abrir arquivo!");
	} else {
		rewind(parq);
		while(fread(rotista, sizeof(Rotista), 1, parq) == 1) {
			if(rotista->numConta == numConta) {	//Compara o numConta do rotista que está sendo lido no arquivo  pelo numConta digitado
				printf("%d\n", rotista->numConta);
				printf("%s %s\n\n", rotista->nome, rotista->sobrenome);
				printf("%.2f\n", rotista->saldo);
				break; //Sai do while
			}
		}
	}

	fclose(parq);
	printf("Pressione qualquer tecla para continuar...");

	getch();
}

void cadastroRotista() {
	Rotista *rotista = (Rotista *) malloc(sizeof(Rotista));

	system("cls");
	printf("Digite o numero de sua conta: ");
	scanf("%d", &rotista->numConta);
	fflush(stdin);

	printf("Digite seu nome: ");
	gets(rotista->nome);
	fflush(stdin);

	printf("Digite seu sobrenome: ");
	gets(rotista->sobrenome);
	fflush(stdin);

	printf("Digite seu CPF: ");
inicio:
	fgets(rotista->cpf,13,stdin);
	fflush(stdin);
	if(verifica_CPF(rotista->cpf) == -1)
		goto inicio;

	printf("Entre com seu saldo: ");
	scanf("%f", &rotista->saldo);
	fflush(stdin);
	//Aqui pode fazer viriCAÇÕES de invalidade de dados

	FILE *parq;
	parq = fopen("rotista.c", "ab");

	if(parq == NULL) {
		printf("Erro ao abrir arquivo!");
	} else {

		printf("Salvando...");
		fwrite(rotista, sizeof(Rotista), 1, parq); //Salva 1 registro de rotista no arquivo de forma binaria
		printf("Salvo!");
	}
	fclose(parq);

	free(rotista);//Libera a memoria
	rotista = NULL;
}

void alteraRotista() {
	int entrou = 0;
	int numConta;

	system("cls");

	printf("Digite o numero da conta: ");
	scanf("%d", &numConta);
	fflush(stdin);

	Rotista *rotista = (Rotista *) malloc(sizeof(Rotista));
	FILE *parq;

	//Abre o arquivo em modo de leitura binária.
	parq = fopen("rotista.c", "rb");

	if(parq == NULL) {
		printf("Erro ao abrir arquivo!");
	} else {
		rewind(parq);
		while(fread(rotista, sizeof(Rotista), 1, parq) == 1) {
			if(rotista->numConta == numConta) {
				entrou = 1;
				printf("%d\n", rotista->numConta);
				printf("%s %s\n", rotista->nome, rotista->sobrenome);
				printf("%s\n",rotista->cpf);
				printf("%f\n", rotista->saldo);
				break;
			}
		}
	}

	fclose(parq);
	if(entrou == 1) { // Se o rotista foi encontrado
		printf("ALTERAÇÕES: \n\n");

		char nomeAux[10];
		char sobrenomeAux[10];
		char saldoAux[50];
		char cpfAux[13];

		printf("Digite seu nome: ");
		gets(rotista->nome);
		fflush(stdin);


		printf("Digite seu sobrenome: ");
		gets(rotista->sobrenome);
		fflush(stdin);

		printf("Digite seu CPF: ");
		gets(rotista->cpf);
		fflush(stdin);

		printf("Digite seu saldo: ");
		scanf("%f", &rotista->saldo);
		fflush(stdin);
		//Aqui pode fazer viriCAÇÕES de invalidade de dados


		FILE *parqAux;
		parq = fopen("rotista.c", "rb");
		parqAux = fopen("rotistaAux.c", "ab");

		//Temos dois arquivos abertos
		//O original e o que auxiliar que terá os novos dados
		Rotista *rotistaAux = (Rotista *) malloc(sizeof(Rotista));


		//rotista = possui o rotista alterado
		//rotistaAux são os rotistas já salvo no arquivo

		if(parq == NULL || parqAux == NULL) {
			printf("Erro ao abrir arquivo!");
		} else {
			rewind(parq);
			while(fread(rotistaAux, sizeof(Rotista), 1, parq) == 1) {
				if(rotistaAux->numConta == numConta) { //Se for o rotista alterado, salve o novo rotista
					fwrite(rotista, sizeof(Rotista), 1, parqAux);
				} else {
					//SE NÃO, salve o rotista normal
					fwrite(rotistaAux, sizeof(Rotista), 1, parqAux);
				}
			}
		}


		fclose(parq);
		fclose(parqAux);
		free(rotista);
		free(rotistaAux);
		rotista = NULL;
		rotistaAux = NULL;


		remove("rotista.c"); //Remove o arquivo original
		rename("rotistaAux.c", "rotista.c"); //Renomeia o arquivo auxiliar com os novos dados
	}

	printf("Pressione qualquer tecla para continuar...");

	getch();


}

void deletaRotista() {
	int entrou = 0;
	system("cls");
	printf("Digite o numero da conta: ");
	int numConta;
	scanf("%d", &numConta);

	Rotista *rotista = (Rotista *) malloc(sizeof(Rotista));
	FILE *parq;

	//Abre o arquivo em modo de leitura binária.
	parq = fopen("rotista.c", "rb");

	if(parq == NULL) {
		printf("Erro ao abrir arquivo!");
	} else {
		rewind(parq);
		while(fread(rotista, sizeof(Rotista), 1, parq) == 1) {
			if(rotista->numConta == numConta) {
				entrou = 1;
				printf("%d\n", rotista->numConta);
				printf("%s %s\n\n", rotista->nome, rotista->sobrenome);
				printf("%s\n",rotista->cpf);
				printf("%.2f\n", rotista->saldo);
				break;
			}
		}
	}

	fclose(parq);

	if(entrou == 1) {
		FILE *parqAux;
		parq = fopen("rotista.c", "rb");
		parqAux = fopen("rotistaAux.c", "ab");
		Rotista *rotistaAux = (Rotista *) malloc(sizeof(Rotista));


		if(parq == NULL || parqAux == NULL) {
			printf("Erro ao abrir arquivo!");
		} else {
			rewind(parq);
			while(fread(rotistaAux, sizeof(Rotista), 1, parq) == 1) {
				if(rotistaAux->numConta == numConta) {	//Se for o rotista deletado,não fazer nada
					//DELETADO
				} else {
					//salvar os outros rotistas
					fwrite(rotistaAux, sizeof(Rotista), 1, parqAux);
				}
			}
		}


		fclose(parq);
		fclose(parqAux);
		free(rotista);
		free(rotistaAux);
		rotista = NULL;
		rotistaAux = NULL;


		remove("rotista.c");
		rename("rotistaAux.c", "rotista.c");
	}
	printf("Pressione qualquer tecla para continuar...");

	getch();
}

void opcao() {

	//Verifica a opção escolhida e manda para a função necessária
	system("cls");
	int escolha = menu();

	switch(escolha) {
		case 0:
			exit(0);
		case 1:
			cadastroRotista();
			opcao();
		case 2:
			listaRotistas();
			opcao();
		case 3:
			procuraRotista();
			opcao();
		case 4:
			alteraRotista();
			opcao();
		case 5:
			deletaRotista();
			opcao();
		default:
			opcao();

	}

}

int verifica_CPF(char cpf[]) {
	char aux[1]; //String de 1 porque atoi nao converte caracter unico
	int a,b;
	int soma=0;
	int check;


	if (strlen(cpf) -1 != 11) //verifica se o valor inserido tem 11 caracteres
		return -1;

	for (a=0; a<11; a++) {
		if (!isdigit(cpf[a]))
			return -1;
	}

	for (a = 0,b = 10; a < 9; a++,b--) {
		aux[0] = cpf[a];
		soma += b * atoi(aux);
	}
	aux[0] = cpf[9];
	if(soma % 11 >= 2) {
		if(atoi(aux) != 11 - (soma % 11)) {
			return -1;
		}
	} else {
		if(cpf[9] != 0) {
			return -1;
		}
	}

	soma = 0;
	for(a = 0,b = 11; a < 10; a++,b--) {
		aux[0] = cpf[a];
		soma += b * atoi(aux);
	}
	aux[0] = cpf[10];
	if(soma % 11 >= 2) {
		if(atoi(aux) != 11 - (soma % 11)) {
			return -1;
		}
	} else {
		if(cpf[10] != 0) {
			return -1;
		}
	}

	return 0;
}
