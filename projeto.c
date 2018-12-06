#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define SENHAG "06122018" 

#define ENTER 13
#define ESQUERDA 75
#define CIMA 72
#define BAIXO 80
#define DIREITA 77
#define ESC 27

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define GREENBLUE
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define GREENWATER 11
#define LIGHTRED 12
#define LILAC 13
#define LIGHTTELLOW 14
#define BRIGHTWHITE 15

struct tm *periodo; //Struct composta para hora, minuto, segundo, dia mes e ano 
                    //em determinadas etapas do programa
typedef struct {                   //Struct para guardar hora, minuto, segundo, dia mes e ano 
	    int dia, mes, ano;         //em determinadas etapas do programa    
	    int hora, minuto, segundo;    
}Momento;

typedef struct {    //Struct principal, com a função de guardar os dados dos rotistas
	char numConta[10];
	char nome[100];
	char cpf[13];
	char rg[15];
	char tel[12];
	int qntdRota;
    Momento mRotista;    //varivel do tipo struct Local
}Rotista;

typedef struct{
	char numPonto[6];
	char numConta[10];
	char bairro[100];
	char address[100];
	char dono[100];
	char cep[10];
	Momento mRota;    //varivel do tipo struct Local
}Ponto;

typedef struct{
	char nome[100];
	char senha[20];
	char check[20];
	char loguin[12];
	char senhag[11];
}Gerente;

void textcolor (int i){
	HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x00F0;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= i);
}

void textbackground (int i){
	
    HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x000F;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= i << 4);
    
}

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

//Cadastro Gerente
void cadGerente();


//Verificação de cadastro existentes
int numRcad(char [], int);
int cpfRcad(char [], char [], int);
int rgRcad(char [], char [], int);
int telRcad(char [], char [], int);
int numPcad(char [], char [], int);
int cepCad(char [], char [], int);

//Funções de Leitura Ponto de venda
int lerNumP(Ponto *, int);
int lerCep(Ponto *, int);
int lerBairro(Ponto *);
int lerAddress(Ponto *);
int lerDono(Ponto *);

//Funções de Leitura Rotista
int lerTelR(Rotista *, int);
int lerNumR(Rotista *, int);
int lerRgR(Rotista *, int);
int lerCpfR(Rotista *, int);
int lerNomeR(Rotista *);

//Entradas para rotista e gerente
void cgEntrada();
void crEntrada(Rotista *);
void crRotista();

//Funções relacionadas ao rotista
void conRotista();
void altRotista(Rotista *);
void demRotista(Rotista *);
void proRotista(Rotista *);
void lisRotista(Rotista *);

//Entrada do Gerente No Programa
void cEntradaG(Gerente *);
int lerSenhaG(Gerente *);

//Leitura para cadastro do Gerente
int lerLogin(Gerente *);
int lerSenha(Gerente *);
int lerSenhaDois(Gerente *);

//Funções Úteis
int isaccent(char );
int ischaracter(char );
void buscaH(Rotista *, Ponto *, int);
void buscaD(Rotista *, Ponto *,int);
int veriCpf(char []);

//				Entrada de dados
//Entrada de dados Gerente
int lerNomeG(Gerente *);


//						Funções de Interface
void caixona();
void cGerente();
void cPriEntrada();
void cLogin();
int cLoginG(Gerente *);
int cLoginR(Rotista *);
int cLoginP(Rotista *, Ponto *);
void cRotista(int, int, int);
void cgPonto();

//Contorna qualquer coisa com duas barras
void cLADOP(int , int , int , int);
void cCANTOP(int , int , int);
void bCANTOP(int , int , int);
void cBAIXOP(int , int , int);
void cCIMAP(int , int , int);

//Contorna qualquer coisa com uma barra
void cLADOS(int , int , int , int);
void cCANTOS(int , int , int);
void bCANTOS(int , int , int);
void cBAIXOS(int , int , int);
void cCIMAS(int , int , int);

// Cadastro para Pontos
void proPonto(Rotista *, Ponto *);
void adcPonto(Rotista *);
void delPonto(Rotista *, Ponto *);
void altPonto(Rotista *, Ponto*);
void lisPonto(Rotista *);

//Interface de Listagem
void cLisPonto(int, int, int );
void cLisRotista(int, int, int );

int main(){
	system("mode con:cols=65 lines=50"); 
	SetConsoleTitle("Sistem de Gerenciamento NS");
	remove("gerente.c");	
	Gerente *gerente = (Gerente *) malloc(sizeof(Gerente));
	int check = 0;
	
	FILE *ptrLG = fopen("gerente.c","rb");
	rewind(ptrLG);
	while(fread(gerente, sizeof(Gerente), 1, ptrLG) == 1){
		check = 1;
	}
	if(check == 0){
		textcolor(LIGHTBLUE);
		textbackground(WHITE);
		
		caixona();
		cadGerente();
	}
	
	textcolor(LIGHTBLUE);
	textbackground(WHITE);
	cPriEntrada();

	fclose(ptrLG);
	
	return 0;
}

//Funções de Cadastro
void cadGerente(){
	int x;
	int max;
	int  check = 1;
	
	FILE *ptrWG = fopen("gerente.c","wb");
	if(ptrWG != NULL){
		Gerente *gerente = (Gerente *) malloc(sizeof(Gerente));
		if(gerente != NULL){
			cEntradaG(gerente);
			cGerente();
			
			gotoxy(15, 20);
			if(!lerNomeG(gerente)){
				do{
					gotoxy(15, 20);
					printf("                          ");
					gotoxy(15, 20);
					printf("Entrada inv%clida!", 160);
					sleep(1);
					
					gotoxy(15, 20);
					printf("                          ");
					gotoxy(15, 20);
				}while(!lerNomeG(gerente));
			}	
			
			gotoxy(16, 22);
			if(!lerLogin(gerente)){
				do{
					gotoxy(16, 22);
					printf("                         ");
					gotoxy(16, 22);
					printf("Apenas letras e n%cmeros!", 163);
					sleep(1);
					
					gotoxy(16, 22);
					printf("                         ");
					gotoxy(16, 22);
				}while(!lerLogin(gerente));
			}
			
			do{
				gotoxy(16, 24);
				if(!lerSenha(gerente)){
					do{
						gotoxy(16, 24);
						printf("                         ");
						gotoxy(16, 24);
						printf("Entrada inv%clida!", 160);
						sleep(1);
						
						gotoxy(16, 24);
						printf("                         ");
						gotoxy(16, 24);
					}while(!lerSenha(gerente));
				}
				//Esconde a senha
				gotoxy(16, 24);
				for(max = 16, x = 16; x < max + strlen(gerente->senha); x++)
					printf("*");
				
				gotoxy(31, 26);
				if(!lerSenhaDois(gerente)){
						//Joa mensagem de aviso
						gotoxy(31, 26);
						printf("                        ");
						gotoxy(31, 26);
						printf("As senhas n%co coincidem!", 198);
						
						gotoxy(16, 24);
						printf("                         ");
						gotoxy(16, 24);
						printf("As senhas n%co coincidem!", 198);
						sleep(1);
						
						//Limpa os espaços
						gotoxy(31, 26);
						printf("                         ");
						gotoxy(31, 26);
						
						gotoxy(16, 24);
						printf("                         ");
						gotoxy(16, 24);
						check = 0;
				}else{
					//Esconde a senha
					gotoxy(31, 26);
					for(max = 31, x = 31; x < max + strlen(gerente->check); x++)
						printf("*");
						
					check = 1;	
				}
			}while(!check);
			
			fwrite(gerente, sizeof(Gerente), 1, ptrWG);
				
			gotoxy(20, 29);
			printf("PROGRAMA PRONTO PARA USO!");
				
			gotoxy(10, 40);
			printf("Pressione qualquer ENTER para continuar...");
		}else{
			printf("Erro! Sem memoria");
		}
	}else{
		printf("Erro! Sem memoria");
	}
	fclose(ptrWG);
	
	getch();
}

//						Funções de Leitura
//		Leitura Nome Gerente
int lerNomeG(Gerente *gerente){
	int i;
	int check = 0;
	
    fflush(stdin);
    fgets(gerente->nome,100,stdin);
    fflush(stdin);
    gerente->nome[strlen(gerente->nome) - 1] = '\0';
	
	if(strlen(gerente->nome) == 0)
		return 0;
	
	for(i = 0; i < strlen(gerente->nome); i++){
		if(isalpha(gerente->nome[i]) ){
			check = 1;
		}else
			if(isaccent(gerente->nome[i])){
				check = 1;
			}else
				if(gerente->nome[i] == 32){
					check = 1;
				}
			
		if(check != 1)
			return 0;
		check = 0;
	}
	
	return 1;
}

//	 	Leitura Senha Gerente e Verificação
int lerSenha(Gerente *gerente){
	int i;
	
	fflush(stdin);
	fgets(gerente->senha, 20, stdin);
	fflush(stdin);
	gerente->senha[strlen(gerente->senha) - 1] = '\0';
	
	if(strlen(gerente->senha) == 0)
		return 0;
	
	for(i = 0; i < strlen(gerente->senha); i++){
		if( !isdigit(gerente->senha[i]) )
			return 0;
	}
	
	return 1;
}

//	 	Leitura Senha Gerente e Verificação
int lerSenhaDois(Gerente *gerente){	
	fflush(stdin);
	fgets(gerente->check, 20, stdin);
	fflush(stdin);
	gerente->check[strlen(gerente->check) - 1] = '\0';
	
	if(strcmp(gerente->senha, gerente->check) == 0){
		return 1;
	}
	return 0;
}

//		Leitura loguin e Verificação
int lerLogin(Gerente *gerente){
	int i;
	int check = 0;
	
    fflush(stdin);
    fgets(gerente->loguin, 100, stdin);
    fflush(stdin);
    gerente->loguin[strlen(gerente->loguin) - 1] = '\0';
	
	if(strlen(gerente->nome) == 0)
		return 0;
	
	for(i = 0; i < strlen(gerente->loguin); i++){
		if(isalnum(gerente->loguin[i]) ){
			check = 1;
		}else
			if(isaccent(gerente->loguin[i])){
				check = 1;
			}
			
		if(check != 1)
			return 0;
			
		check = 0;
	}
	
	return 1;
}

//Boas VIndas e Pedido de acesso Incicial
void cEntradaG(Gerente *gerente){
	gotoxy(27, 6);
	printf(" BEM-VINDO! ");
	cCANTOP(27, 6, 12);
	cCIMAP(27, 6, 12);
	cBAIXOP(27, 6, 12);
	bCANTOP(27, 6, 12);
	cLADOP(27, 6, 7, 12);
	
	gotoxy(14, 10);
	printf("Entre com o codigo de acesso inicial");
	cCANTOP(14, 10, 36);
	cCIMAP(14, 10, 36);
	cBAIXOP(14, 12, 36);
	bCANTOP(14, 12, 36);
	cLADOP(14, 10, 13, 36);
	
	gotoxy(13, 11);
	printf("%c",-52);
	gotoxy(50, 11);
	printf("%c",-71);
	cCIMAP(14, 12, 36);
	gotoxy(14,12);
	printf("CODIGO: ");
	
	if(!lerSenhaG(gerente)){
		do{
			gotoxy(22, 12);
			printf("                      ");
			
			gotoxy(22, 12);
			printf("Senha inv%clida!", 160);
			sleep(1);
			
			gotoxy(21, 12);
			printf("                      ");
			gotoxy(22, 12);
		}while(!lerSenhaG(gerente));
	}
	gotoxy(22, 12);
	printf("********");
	
	cGerente();
}

int lerSenhaG(Gerente *gerente){
	fflush(stdin);
	fgets(gerente->senhag, 11, stdin);
	fflush(stdin);
	gerente->senhag[strlen(gerente->senhag) - 1] = '\0';
	
	if(strlen(gerente->senhag) == 0)
		return 0;
	
	if(strcmp(gerente->senhag, SENHAG) != 0){
		return 0;
	}
	
	return 1;
}

//					Funções de Interface
//Primera Janela
void cPriEntrada(){
	char key;
	int x;
	int y;
	
	caixona();
	
	gotoxy(19,6);
	printf("SISTEMA DE GERENCIAMENTO NS");
	cCANTOP(10, 5, 46);
	cCIMAP(10, 5, 46);
	cBAIXOP(10, 7, 46);
	bCANTOP(10, 7, 46);
	cLADOP(10, 5, 8, 46);
	
	gotoxy(30,14);
	printf("LOGIN");
	cCANTOP(24, 14, 18);
	cCIMAP(24, 14, 18);
	cBAIXOP(24, 14, 18);
	bCANTOP(24, 14, 18);
	cLADOP(24, 14, 15, 18);
	
	gotoxy(31,17);
	printf("SAIR");
	cCANTOP(24, 17, 18);
	cCIMAP(24, 17, 18);
	cBAIXOP(24, 17, 18);
	bCANTOP(24, 17, 18);
	cLADOP(24, 17, 18, 18);
	
	gotoxy(22, 14);
	printf("%c", -81);
	gotoxy(22, 14);
	
	x = 22;
	y = 14;
	
	do{
		getch();
		key = getch();
		switch(key){
			case CIMA:
				if(y >= 15){
					gotoxy(x, y);
					printf(" ");
					
					y -= 3;
					gotoxy(x, y);
					printf("%c", -81);
					gotoxy(x, y);
				}
				break;
			
			case BAIXO:
				if(y <= 16){
					gotoxy(x, y);
					printf(" ");
					
					y += 3;
					gotoxy(x, y);
					printf("%c", -81);
					gotoxy(x, y);
				}
				break;
			default:
				gotoxy(x, y);
				printf("%c", -81);
				gotoxy(x, y);
		}
	}while(key != ENTER);
	
	if(y == 14){
		cLogin();
		getch();
	}else
		if(y == 17){
			exit(1);
		}
}
//Interface para Rotistas e Pontos de vendas
void cRotista(int x, int y, int tam){
	int w ;
	
	cCANTOS(x, y - 1, tam);
	
	cCIMAS(x , y - 1, tam);
	
	cLADOS(x, y - 1, (y + 13), tam);
	cLADOS(x + 12, y + 2, (y + 12), tam - 12);
	
	
	cBAIXOS(x, y + 1, tam);
	
	cBAIXOS(x, y + 3, tam);
	
	cBAIXOS(x, y + 5, tam);
	
	cBAIXOS(x, y + 7, tam);
	
	cBAIXOS(x, y + 9, tam);
	
	cBAIXOS(x, y + 11, tam);
	
	for(w = (y + 2); w <= (y + 12); w += 2){
		gotoxy(x - 1, w);
		printf("%c", -61);
		
		if(w == (y + 2)){
			gotoxy(x + 11, w);
			printf("%c", -62);
		}
		if(w == (y +12)){
			gotoxy(x + 11, w);
			printf("%c", -63);	
		}
		if(w != (y + 2) && w != (y +12)){
			gotoxy(x + 11, w);
			printf("%c", -59);
		}
		
		gotoxy(x + tam, w);
		printf("%c", -76);
	}
	bCANTOS(x, y + 11, tam);
	
	cCANTOS(x, (y + 15), tam);
	cCIMAS(x, (y + 15), tam);
	cLADOS(x, (y + 15), (y + 16), tam);
	cBAIXOS(x, (y + 15), tam);
	bCANTOS(x, (y + 15), tam);
}

void cPonto(int x, int y, int tam){
	int w ;
	
	cCANTOS(x, y - 1, tam);
	
	cCIMAS(x , y - 1, tam);
	
	cLADOS(x, y - 1, (y + 13), tam);
	cLADOS(x + 12, y + 2, (y + 12), tam - 12);
	
	
	cBAIXOS(x, y + 1, tam);
	
	cBAIXOS(x, y + 3, tam);
	
	cBAIXOS(x, y + 5, tam);
	
	cBAIXOS(x, y + 7, tam);
	
	cBAIXOS(x, y + 9, tam);
	
	cBAIXOS(x, y + 11, tam);
	
	for(w = (y + 2); w <= (y + 12); w += 2){
		gotoxy(x - 1, w);
		printf("%c", -61);
		
		if(w == (y + 2)){
			gotoxy(x + 11, w);
			printf("%c", -62);
		}
		if(w == (y +12)){
			gotoxy(x + 11, w);
			printf("%c", -63);	
		}
		if(w != (y + 2) && w != (y +12)){
			gotoxy(x + 11, w);
			printf("%c", -59);
		}
		
		gotoxy(x + tam, w);
		printf("%c", -76);
	}
	bCANTOS(x, y + 11, tam);
	
	cCANTOS(x, (y + 15), tam);
	cCIMAS(x, (y + 15), tam);
	cLADOS(x, (y + 15), (y + 16), tam);
	cBAIXOS(x, (y + 15), tam);
	bCANTOS(x, (y + 15), tam);
}

//Interface do cadastro Gerente
void cGerente(){
	
	gotoxy(25,18);
	printf("CADASTRO GERENTE");
	cCANTOP(9, 18, 49);
	cCIMAP(9, 18, 49);
	
	cBAIXOP(9, 18, 49);
	cBAIXOP(9, 30, 49);
	
	bCANTOP(9, 30, 49);
	cLADOP(9, 18, 31, 49);
	
	gotoxy(8 ,19);
	printf("%c", -52);
	gotoxy(58, 19);
	printf("%c", -71);
	
	//Fazer contorno Nome
	gotoxy(9, 20   );
	printf("Nome: ");
	cBAIXOP(9, 20, 49);
	gotoxy(8 ,21);
	printf("%c", -52);
	gotoxy(58, 21);
	printf("%c", -71);
	
	gotoxy(9, 22);
	printf("login");
	cBAIXOP(9, 22, 49);
	gotoxy(8 ,23);
	printf("%c", -52);
	gotoxy(58, 23);
	printf("%c", -71);
	
	gotoxy(9, 24);
	printf("senha: ");
	cBAIXOP(9, 24, 49);
	gotoxy(8 ,25);
	printf("%c", -52);
	gotoxy(58, 25);
	printf("%c", -71);
	
	gotoxy(9, 26);
	printf("Verifica%c%co de senha: ", -121, -58);
	cBAIXOP(9, 26, 49);
	gotoxy(8 ,27);
	printf("%c", -52);
	gotoxy(58, 27);
	printf("%c", -71);
}

//Caixa Loguin
int cLoginG(Gerente *gerente){
	int col, x, max;
	char senha[20], user[100];
	
	gotoxy(26, 32);
	printf("LOGIN GERENTE");
	gotoxy(15, 34);
	printf("Usu%crio:", -96);
	
	for(col = 15; col <= 49; col += 2){
		gotoxy(col, 35);
		printf("-");
	}	
	
	gotoxy(15, 36);
	printf("Senha:");
	
	cCIMAS(15, 32, 36);
	cCANTOS(15, 32, 36);
	cLADOS(15, 32, 37, 36);
	
	cBAIXOS(15, 32, 36);
	cBAIXOS(15, 36, 36);
	
	bCANTOS(15, 36, 36);
	
	gotoxy(24, 34);
	if(!lerLogin(gerente)){
		do{
			gotoxy(24, 34);
			printf("                     ");		
			gotoxy(24, 34);
			printf("Entrada Inv%clida!", -96);
			sleep(1);
			gotoxy(24, 34);
			printf("                     ");		
			gotoxy(24, 34);
		}while(!lerLogin(gerente));
	}
	
	gotoxy(22, 36);
	if(!lerSenha(gerente)){
		do{
			gotoxy(22, 36);
			printf("                             ");		
			gotoxy(22, 36);
			printf("Entrada Inv%clida!", -96);
			sleep(1);
			gotoxy(22, 36);
			printf("                             ");		
			gotoxy(22, 36);
		}while(!lerSenha(gerente));
	}
	gotoxy(22, 36);
	for(max = 22, x = 22; x < max + strlen(gerente->senha); x++)
	printf("*");
	
	strcpy(senha, gerente->senha);
	strcpy(user, gerente->loguin);
	
	FILE *ptrLG = fopen("gerente.c","rb");
	rewind(ptrLG);
	while(fread(gerente, sizeof(Gerente), 1, ptrLG) == 1){
		if(strcmp(gerente->loguin, user) == 0 && strcmp(gerente->senha, senha) == 0){
			fclose(ptrLG);
			return 1;
		}
	}

	fclose(ptrLG);
	
	gotoxy(15, 38);
	printf("Erro ao encontrar Gerente!");	
	cCIMAS(15, 38, 36);
	cCANTOS(15, 38, 36);
	cLADOS(15, 38, 39, 36);
	cBAIXOS(15, 38, 36);
	bCANTOS(15, 38, 36);
	
	gotoxy(14,37);
	printf("%c", -61);
	gotoxy(51, 37);
	printf("%c", -76);
	
	gotoxy(17, 45);
	printf("Pressione ENTER para continuar...");
	getch();
	
	return 0;
}

int cLoginR(Rotista *rotista){
	int col;
	char nc[8], cpf[12];
	
	gotoxy(26, 32);
	printf("LOGIN ROTISTA");
	gotoxy(15, 34);
	printf("N%c de Conta:", -89);
	
	for(col = 15; col <= 49; col += 2){
		gotoxy(col, 35);
		printf("-");
	}	
	
	gotoxy(15, 36);
	printf("CPF:");
	
	cCIMAS(15, 32, 36);
	cCANTOS(15, 32, 36);
	cLADOS(15, 32, 37, 36);
	
	cBAIXOS(15, 32, 36);
	cBAIXOS(15, 36, 36);
	
	bCANTOS(15, 36, 36);
	
	gotoxy(28, 34);
	if(!lerNumR(rotista, 0)){
		do{
			gotoxy(28, 34);
			printf("                     ");		
			gotoxy(28, 34);
			printf("Entrada Invalida!");
			sleep(1);
			gotoxy(28, 34);
			printf("                     ");		
			gotoxy(28, 34);
		}while(!lerNumR(rotista, 0));
	}
	
	gotoxy(20, 36);
	if(!lerCpfR(rotista, 0)){
		do{
			gotoxy(20, 36);
			printf("                             ");		
			gotoxy(20, 36);
			printf("Entrada Invalida!");
			sleep(1);
			gotoxy(20, 36);
			printf("                             ");		
			gotoxy(20, 36);
		}while(!lerCpfR(rotista, 0));
	}
	
	strcpy(nc, rotista->numConta);
	strcpy(cpf, rotista->cpf);
	
	FILE *ptrLR = fopen("rotista.c","rb");
	rewind(ptrLR);
	while(fread(rotista, sizeof(Rotista), 1, ptrLR) == 1){
		if(strcmp(rotista->numConta, nc) == 0 && strcmp(rotista->cpf, cpf) == 0){
			fclose(ptrLR);
			return 1;
		}
	}
	fclose(ptrLR);
	
	gotoxy(15, 38);
	printf("Erro ao procurar Rotista!");	
	cCIMAS(15, 38, 36);
	cCANTOS(15, 38, 36);
	cLADOS(15, 38, 39, 36);
	cBAIXOS(15, 38, 36);
	bCANTOS(15, 38, 36);
	
	gotoxy(14,37);
	printf("%c", -61);
	gotoxy(51, 37);
	printf("%c", -76);
	
	gotoxy(17, 45);
	printf("Pressione ENTER para continuar...");
	getch();
	
	return 0;
}

int cLoginP(Rotista *rotista, Ponto *ponto){
	int col;
	char nc[8], np[6];
	char check = 0;
	
	gotoxy(24, 32);
	printf("LOGIN DE PONTO");
	gotoxy(15, 34);
	printf("N%c de Conta:", -89);
	
	for(col = 15; col <= 49; col += 2){
		gotoxy(col, 35);
		printf("-");
	}	
	
	gotoxy(15, 36);
	printf("N%c de Ponto:", -89);
	
	cCIMAS(15, 32, 36);
	cCANTOS(15, 32, 36);
	cLADOS(15, 32, 37, 36);
	
	cBAIXOS(15, 32, 36);
	cBAIXOS(15, 36, 36);
	
	bCANTOS(15, 36, 36);
	
	gotoxy(28, 34);
	if(!lerNumR(rotista, 0)){
		do{
			gotoxy(28, 34);
			printf("                     ");		
			gotoxy(28, 34);
			printf("Entrada Inv%clida!", -96);
			sleep(1);
			gotoxy(28, 34);
			printf("                     ");		
			gotoxy(28, 34);
		}while(!lerNumP(ponto, 0));
	}
	
	gotoxy(28, 36);
	if(!lerNumP(ponto, 0)){
		do{
			gotoxy(28, 36);
			printf("                             ");		
			gotoxy(28, 36);
			printf("Entrada Inv%clida!", -96);
			sleep(1);
			gotoxy(28, 36);
			printf("                             ");		
			gotoxy(28, 36);
		}while(!lerNumP(ponto, 0));
	}
	
	strcpy(nc, rotista->numConta);
	strcpy(np, ponto->numPonto);
	
	FILE *ptrLR = fopen("rotista.c","rb");
	rewind(ptrLR);
	while(fread(rotista, sizeof(Rotista), 1, ptrLR) == 1){
		if(strcmp(rotista->numConta, nc) == 0){
			fclose(ptrLR);
			check = 1;
		}
	}
	fclose(ptrLR);
	
	if(check == 1){
		FILE *ptrLP = fopen("ponto.c","rb");
		rewind(ptrLP);
		while(fread(ponto, sizeof(Ponto), 1, ptrLP) == 1){
			if(strcmp(ponto->numPonto, np) == 0 && strcmp(ponto->numConta, nc) == 0)
				return 1;	
		}
	}
	
	
	gotoxy(15, 38);
	printf("Erro ao procurar Rotista!");	
	cCIMAS(15, 38, 36);
	cCANTOS(15, 38, 36);
	cLADOS(15, 38, 39, 36);
	cBAIXOS(15, 38, 36);
	bCANTOS(15, 38, 36);
	
	gotoxy(14,37);
	printf("%c", -61);
	gotoxy(51, 37);
	printf("%c", -76);
	
	gotoxy(17, 45);
	printf("Pressione ENTER para continuar...");
	getch();
	
	return 0;
}

void cLogin(){
	Rotista *rotista = (Rotista *) malloc(sizeof(Rotista));
	Gerente *gerente = (Gerente *) malloc(sizeof(Gerente));
	
	int col, key, lin;
	
	gotoxy(30,25);
	printf("LOGIN");
	//Contorna a Palvra LOGIN
	cCANTOS(20, 25, 26);
	
	cCIMAS(20, 25, 26);
	cBAIXOS(20, 25, 26);
	
	bCANTOS(20, 27, 26);
	cLADOS(20, 25, 29, 26);
	
	cBAIXOS(20, 27, 26);
	
	bCANTOS(20, 27, 26);
	
	//Posicona caracter espacial em LOGIN
	gotoxy(19, 26);
	printf("%c", -61);
	
	gotoxy(46, 26);
	printf("%c", -76);
	
	gotoxy(29, 27);
	printf("GERENTE");
		
	
	lin = 27;
	col = 27;
	
	gotoxy(col, lin);
	printf("%c", -81);
	do{
		getch();
		key = getch();
		
		switch(key){
			default:
				gotoxy(col, lin);
				printf(" ");
				gotoxy(col, lin);
				printf("%c", -81);	
		}
	}while(key != ENTER);

	gotoxy(col, lin);
	printf(" ");
	
	if(col == 27){
		if(cLoginG(gerente)){
			cgEntrada();
		}else{
			cPriEntrada();
		}
	}
	
	
}

//Entrada de Rotista e Gerente
void cgRotista(){
	Gerente *gerente = (Gerente *) malloc(sizeof(Gerente));
	FILE *ptrRG = fopen("gerente.c","rb");
	rewind(ptrRG);
	fread(gerente, sizeof(Gerente), 1, ptrRG);
	
	caixona();
	
	gotoxy(26, 8);
	printf("%s", "ACESSO GERENTE");
	cCIMAS(20, 8, 27);
	cCANTOS(20, 8, 27);
	cLADOS(20, 8, 9, 27);
	bCANTOS(20, 8, 27);
	cBAIXOS(20, 8, 27);
	
	gotoxy(20, 10);
	printf("%s", gerente->nome);
	cCIMAS(10,10, 47);
	cCANTOS(10, 10, 47);
	cLADOS(10, 10, 11, 47);
	bCANTOS(10, 10, 47);
	cBAIXOS(10, 10, 47);
	gotoxy(19, 9);
	printf("%c", -63);
	gotoxy(47, 9);
	printf("%c", -63);
	
	gotoxy(25, 16);
	printf("Contratar Rotista");
	
	gotoxy(25, 20);
	printf("Demitir Rotista");
	
	gotoxy(18, 24);
	printf("Alterar Dados Pessoais - Rotista");
	
	gotoxy(25, 28);
	printf("Procurar Rotista");
	
	gotoxy(25, 32);
	printf("Lista Rotistas");
	
	gotoxy(4,47);
	printf("%s","ESC -Voltar");
	cCIMAS(4,47, 3);
	cCANTOS(4, 47, 3);
	cLADOS(4, 47, 48, 3);
	bCANTOS(4, 47, 3);
	cBAIXOS(4, 47, 3);
}

void cgEntrada(){
	int x = 17, y = 16;
	char key;
	
	Rotista *rotista = (Rotista *) malloc(sizeof(Rotista));
	if(rotista == NULL){
		printf("Erro! Sem Memória!");
		getch();
	}
	
	cgRotista();
	
	x = 17;  y = 16;
	gotoxy(x, y);
	printf("%c", -81);
	
	do{
		getch();
		key = getch();
		
		switch(key){
			case CIMA:
				if(y >= 17){
					gotoxy(x, y);
					printf(" ");
					
					y -= 4;
					gotoxy(x, y);
					printf("%c", -81);
					gotoxy(x, y);
				}
				break;
			case BAIXO:
				if(y <= 31){
					gotoxy(x, y);
					printf(" ");
					
					y += 4;
					gotoxy(x, y);
					printf("%c", -81);
					gotoxy(x, y);
				}
				break;
			case ESC:
				cPriEntrada();
				
			default:
				gotoxy(x, y);
				printf("%c", -81);
				gotoxy(x,y);
		}
	}while(key != ENTER);
	
	if(y == 16){	
		conRotista();
	}else
		if(y == 20){
			
			if(cLoginR(rotista))
				demRotista(rotista);
			
		}else
			if(y == 24){
				
				if(cLoginR(rotista))
					altRotista(rotista);

			}else
				if(y == 28){
					
					if(cLoginR(rotista))
						proRotista(rotista);
					
				}else
					if(y == 32){
							lisRotista(rotista);
					}
	
	cgEntrada();
}

void cgPonto(){
	gotoxy(20, 21);
	printf("%s", "ACESSO AOS PONTOS DE ROTA");
	
	gotoxy(24, 25);
	printf("Adicionar Ponto");
	
	gotoxy(24, 29);
	printf("Excluir Ponto");
	
	gotoxy(24, 33);
	printf("Alterar Ponto");
	
	gotoxy(24, 37);
	printf("Localizar Ponto");
	
	gotoxy(24, 41);
	printf("Listar Pontos");
	
	gotoxy(4,47);
	printf("%s","ESC -Voltar");
	cCIMAS(4,47, 3);
	cCANTOS(4, 47, 3);
	cLADOS(4, 47, 48, 3);
	bCANTOS(4, 47, 3);
	cBAIXOS(4, 47, 3);
	
}

//Interface de Listagem
void cLisPonto(int x, int y, int tam){
	int w ;
	
	cCANTOS(x, y - 1, tam);
	
	cCIMAS(x , y - 1, tam);
	
	cLADOS(x, y - 1, (y + 6), tam);
	cLADOS(x + 12, y + 2, (y + 6), tam - 12);
	
	
	cBAIXOS(x, y + 1, tam);
	
	cBAIXOS(x, y + 3, tam);
	
	cBAIXOS(x, y + 5, tam);
	
	
	for(w = (y + 2); w <= (y + 7); w += 2){
		gotoxy(x - 1, w);
		printf("%c", -61);
		
		if(w == (y + 2)){
			gotoxy(x + 11, w);
			printf("%c", -62);
		}
		if(w == (y +12)){
			gotoxy(x + 11, w);
			printf("%c", -63);	
		}
		if(w != (y + 2) && w != (y +12)){
			gotoxy(x + 11, w);
			printf("%c", -59);
		}
		
		gotoxy(x + tam, w);
		printf("%c", -76);
	}
	bCANTOS(x, y + 5, tam);
	
	gotoxy(x + 11 , y + 6);
	printf("%c", -63);
	
	gotoxy(x , y + 3);
	printf("CPF");
	
	gotoxy(x , y + 5);
	printf("N%c da Conta", -89);
}

void cLisRotista(int x, int y, int tam){
	int w ;
	
	cCANTOS(x, y - 1, tam);
	
	cCIMAS(x , y - 1, tam);
	
	cLADOS(x, y - 1, (y + 6), tam);
	cLADOS(x + 12, y + 2, (y + 6), tam - 12);
	
	
	cBAIXOS(x, y + 1, tam);
	
	cBAIXOS(x, y + 3, tam);
	
	cBAIXOS(x, y + 5, tam);
	
	
	for(w = (y + 2); w <= (y + 7); w += 2){
		gotoxy(x - 1, w);
		printf("%c", -61);
		
		if(w == (y + 2)){
			gotoxy(x + 11, w);
			printf("%c", -62);
		}
		if(w == (y +12)){
			gotoxy(x + 11, w);
			printf("%c", -63);	
		}
		if(w != (y + 2) && w != (y +12)){
			gotoxy(x + 11, w);
			printf("%c", -59);
		}
		
		gotoxy(x + tam, w);
		printf("%c", -76);
	}
	bCANTOS(x, y + 5, tam);
	
	gotoxy(x + 11 , y + 6);
	printf("%c", -63);
	
	gotoxy(x , y + 3);
	printf("N%c de Conta",-89);
	
	gotoxy(x , y + 5);
	printf("CPF", -89);
}

//Função de Contorno  principal
void caixona(){
	int colEC, colEB;
	int colDC, colDB;
	int linEB, linEC;
	int linDB, linDC;
	
	gotoxy(1, 49);
	printf("%c", -56);	

	gotoxy(65, 2);
	printf("%c", -69);
	
	gotoxy(1, 2);
	printf("%c", -55);
	
	gotoxy(65, 49);
	printf("%c",-68);
	
	for(linEC = 25, linEB = 25, linDC = 25, linDB = 25; linEB <= 49; linEC--, linEB++, linDC--, linDB++){
		for(colEC = 33, colEB =33, colDC = 33, colDB = 33; colDC <= 65; colEC--, colEB--, colDC++, colDB++){
			if(colEC == 1 && colEB == 1){
				gotoxy(colEC, linEC);
				printf("%c", -70);
				
				gotoxy(colEB, linEB);
				printf("%c", -70);
			}
			
			if(colDC == 65 && colDB == 65){
				gotoxy(colDC, linDC);
				printf("%c", -70);
				
				gotoxy(colDB, linDB);
				printf("%c", -70);
			}
			
			if(colDC < 65 && colEC > 1){
				gotoxy(colEC, linEC);
				printf(" ");
				
				gotoxy(colEB, linEB);
				printf(" ");
				
				gotoxy(colDC, linDC);
				printf(" ");
				
				gotoxy(colDB, linDB);
				printf(" ");
			}
			
			if(linEC == 2 && linDC == 2){
				gotoxy(colEC, linEC);
				printf("%c", -51);
				
				gotoxy(colDC, linDC);
				printf("%c", -51);
			}else
				if(colEC > 1 && colDC < 65){
					gotoxy(colEC, linEC);
					printf(" ");
				
					gotoxy(colDC, linDC);
					printf(" ");
				}
			
			if(linEB == 49 && linDB == 49){
				gotoxy(colEB, linEB);
				printf("%c", -51);
				
				gotoxy(colDB, linDB);
				printf("%c", -51);
			}else
				if(colEB > 1 && colDB > 65){
					gotoxy(colEB, linEB);
					printf(" ");
				
					gotoxy(colDB, linDB);
					printf(" ");
				}
		}
	}
	
	gotoxy(1, 49);
	printf("%c", -56);	

	gotoxy(65, 2);
	printf("%c", -69);
	
	gotoxy(1, 2);
	printf("%c", -55);
	
	gotoxy(65, 49);
	printf("%c",-68);
	
	gotoxy(1, 1);
	printf(" ");
	
	gotoxy(65, 1);
	printf(" ");
}

//Funções de contornar palavras com duas barras
void cCIMAP(int col, int lin, int word){
	int maxC;
	for(maxC = col; maxC < (col + word); maxC++){
		gotoxy(maxC, lin - 1);
		printf("%c", -51);
	}
}

void cBAIXOP(int col, int lin, int word){
	int maxC;
	for(maxC = col; maxC < (col + word); maxC++){
		gotoxy(maxC, lin + 1);
		printf("%c", -51);
	}
}

void cCANTOP(int col, int lin, int word){
	gotoxy(col - 1, lin - 1);
	printf("%c",-55);
	
	gotoxy(col + word, lin - 1);
	printf("%c",-69);
}

void bCANTOP(int col, int lin, int word){
	gotoxy(col - 1, lin + 1);
	printf("%c",-56);
	
	gotoxy(col + word, lin + 1);
	printf("%c",-68);
}

void cLADOP(int col, int lin, int maxL, int word){
	for(; lin < maxL; lin++){
		gotoxy(col - 1, lin);
		printf("%c", -70);
		
		gotoxy(col + word, lin);
		printf("%c", -70);
	}
}

//Funções de contornar palavras com um barra
void cCIMAS(int col, int lin, int word){
	int maxC;
	for(maxC = col; maxC < (col + word); maxC++){
		gotoxy(maxC, lin - 1);
		printf("%c", -60);
	}
}

void cBAIXOS(int col, int lin, int word){
	int maxC;
	for(maxC = col; maxC < (col + word); maxC++){
		gotoxy(maxC, lin + 1);
		printf("%c", -60);
	}
}

void cCANTOS(int col, int lin, int word){
	gotoxy(col - 1, lin - 1);
	printf("%c",-38);
	
	gotoxy(col + word, lin - 1);
	printf("%c",-65);
}

void bCANTOS(int col, int lin, int word){
	gotoxy(col - 1, lin + 1);
	printf("%c",-64);
	
	gotoxy(col + word, lin + 1);
	printf("%c",-39);
}

void cLADOS(int col, int lin, int maxL, int word){
	for(; lin < maxL; lin++){
		gotoxy(col - 1, lin);
		printf("%c", -77);
		
		gotoxy(col + word, lin);
		printf("%c", -77);
	}
}

//Funções úteis
int isaccent(char letter){
	
	switch(letter){
		case -29: break;//Ô
		case -31: break;//Ó
		case -41: break;//Í
		case -45: break;//Ê
		case -56: break;//Ã
		case -57: break;//ã
		case -73: break;//Â
		case -74: break;//Á
		case -93: break;//ú
		case -95: break;//ó
		case -96: break;//í
		case -108: break;//ô
		case -111: break;//É
		case -119: break;//ê
		case -121: break;//ç
        case -126: break;//é
		default: return 0;
	}
	
	return 1;
}

int ischaracter(char letter){
	switch(letter){
		case 40: break;// (
		case 41: break;// )
		case 42: break;// *
		case 44: break;// ,
		case 45: break;// -
		case 46: break;// .
		case 47: break;// /
		case 48: break;// &
		case 58: break;// :
		case 59: break;// ;
		case 91: break;// [
		case 93: break;// ]
		case 92: break;// \ /
		case 95: break; // _
		case 123: break;// {
		case 124: break;// |
		case 125: break;// }
        case 32: break;//space
		default: return 0;
	}
	
	return 1;    
}

void buscaH(Rotista *rotista, Ponto *ponto, int tipo){
    //Salvando a hora em que o cadastro do rotista foi criado
    
    if(tipo == 1){
	    rotista->mRotista.segundo = periodo->tm_sec;
        rotista->mRotista.minuto = periodo->tm_min;
        rotista->mRotista.hora = periodo->tm_hour;
    }else
        if(tipo == 2){
            ponto->mRota.segundo = periodo->tm_sec;
            ponto->mRota.minuto = periodo->tm_min;
            ponto->mRota.hora = periodo->tm_hour;
        }
}

void buscaD(Rotista *rotista, Ponto *ponto, int tipo){
    //Salvando o dia em que o cadastro do rotista foi Rotista foi criado
    if(tipo == 1){
	    rotista->mRotista.dia  = periodo->tm_mday;
        rotista->mRotista.mes = periodo->tm_mon + 1;
        rotista->mRotista.ano = periodo->tm_year + 1900;
    }else
        if(tipo == 2){
            ponto->mRota.dia  = periodo->tm_mday;
            ponto->mRota.mes = periodo->tm_mon + 1;
            ponto->mRota.ano = periodo->tm_year + 1900;
        }
}

//Funções de leitura para Rotista
int lerNomeR(Rotista *rotista){
	int k;
	int check = 0;
	
	fflush(stdin);
	fgets(rotista->nome, 100, stdin);
	fflush(stdin);
	rotista->nome[strlen(rotista->nome) - 1] = '\0';
	
	if(strlen(rotista->nome) == 0)
		return 0;
		
	for(k = 0; k < strlen(rotista->nome); k++){
		if(isalpha(rotista->nome[k])){
			check = 1;
		}else
			if(isaccent(rotista->nome[k])){
				check = 1;
			}else
				if(rotista->nome[k] == 32){
					check = 1;
				}
		
		if(check == 0)
			return 0;
			
		check = 0;
	}
	
	return 1;
}

int lerCpfR(Rotista *rotista, int tipo){
	int k;
	
	fflush(stdin);
	fgets(rotista->cpf, 13, stdin);
	fflush(stdin);
	rotista->cpf[strlen(rotista->cpf) - 1] = '\0';
	
	if(strlen(rotista->cpf) != 11)
		return 0;
		
	for(k = 0; k < strlen(rotista->cpf); k++){
		if(!isdigit(rotista->cpf[k])){
			return 0;
		}
	}
	
	if(!veriCpf(rotista->cpf))
		return 0;
	
	if(tipo == 1 || tipo == 2){
		if(!cpfRcad(rotista->cpf, rotista->numConta, tipo))
			return 0;
	}
	
	return 1;
}

int veriCpf(char cpf[]){
	char aux[1]; //String de 1 porque atoi nao converte caracter unico
    int a,b;
    int soma=0;

    for (a=0;a<11;a++){
        if (!isdigit(cpf[a])) //verifica se todos os caracteres inseridos são um digito
            return 0;
    }

    for (a = 0,b = 10;a < 9;a++,b--){
        aux[0] = cpf[a];
        soma += b * atoi(aux);  
    }
    aux[0] = cpf[9];  
    if(soma % 11 >= 2 ){
        if(atoi(aux) != 11 - (soma % 11)){
            return 0;
        }   
    }else{
        if(atoi(aux) != 0){
            return 0;
        }
    }

    soma = 0;
    for(a = 0,b = 11;a < 10;a++,b--){
        aux[0] = cpf[a];
        soma += b * atoi(aux);
    }
    
    aux[0] = cpf[10];
    if(soma % 11 >= 2){
        if(atoi(aux) != 11 - (soma % 11))
            return 0;
    }else{
        if(atoi(aux) != 0)
            return 0;
    }
    
    return 1;
}

int lerRgR(Rotista *rotista, int tipo){
	int k;
	
	fflush(stdin);
	fgets(rotista->rg, 15, stdin);
	fflush(stdin);
	rotista->rg[strlen(rotista->rg) - 1] = '\0';
	
	if(strlen(rotista->rg) < 8 && strlen(rotista->rg) > 13)
		return 0;
		
	for(k = 0; k < strlen(rotista->rg); k++){
		if(!isdigit(rotista->rg[k])){
			return 0;
		}
	}
	
	if(tipo == 1 || tipo == 2){
		if(!rgRcad(rotista->rg, rotista->numConta, tipo))
			return 0;
	}
	return 1;
}

int lerNumR(Rotista *rotista, int tipo){
	int k;
	
	fflush(stdin);
	fgets(rotista->numConta, 9, stdin);
	fflush(stdin);
	rotista->numConta[strlen(rotista->numConta) - 1] = '\0';
	
	if(strlen(rotista->numConta) != 7 || strncmp(rotista->numConta, "2018", 4) != 0)
		return 0;
	
	for(k = 0; k < strlen(rotista->numConta); k++){
		if(!isdigit(rotista->numConta[k]))
			return 0;
	}
	
	if(tipo == 1 || tipo == 2){
		if(!numRcad(rotista->numConta, tipo))
			return 0;
	}
	
	return 1;
}

int lerTelR(Rotista *rotista, int tipo){
	int k;
	
	fflush(stdin);
	fgets(rotista->tel, 12, stdin);
	fflush(stdin);
	rotista->tel[strlen(rotista->tel) - 1] = '\0';
	
	if(strlen(rotista->tel) != 9)
		return 0;
	
	for(k = 0; k < strlen(rotista->tel); k++){
		if(!isdigit(rotista->tel[k]))
			return 0;
	}
		
	if(tipo == 1 || tipo == 2){	
		if(!telRcad(rotista->tel, rotista->numConta, tipo))
			return 0;
	}
	
	return 1;
}

//Funções de Leitura para Pontos de Vendas
int lerNumP(Ponto *ponto, int tipo){
	int k;
	
	fflush(stdin);
	fgets(ponto->numPonto, 6, stdin);
	fflush(stdin);
	ponto->numPonto[strlen(ponto->numPonto) - 1] = '\0';
	
	if(strlen(ponto->numPonto) != 3){
		return 0;
	}
	for(k = 0; k < strlen(ponto->numPonto); k++){
		if(!isdigit(ponto->numPonto[k])){
			return 0;	
		}
	}
		
	if(tipo == 1 || tipo == 2){
		if(!numPcad(ponto->numPonto, ponto->numConta, tipo)){
			getch();
			return 0;
		}
	}
	
	return 1;
}

int lerCep(Ponto *ponto, int tipo){
	int k;
	
	fflush(stdin);
	fgets(ponto->cep, 10, stdin);
	fflush(stdin);
	ponto->cep[strlen(ponto->cep) - 1] = '\0';
	
	if(strlen(ponto->cep) != 8)
		return 0;
		
	for(k = 0; k < strlen(ponto->cep); k++){
		if(!isdigit(ponto->cep[k]))
			return 0;	
	}
		
	if(tipo == 1 || tipo == 2){
		if(!cepCad(ponto->cep, ponto->numConta, tipo))
			return 0;
	}
	
	return 1;
}

int lerBairro(Ponto *ponto){
	int k;
	int check = 0;
	
	fflush(stdin);
	fgets(ponto->bairro, 100, stdin);
	fflush(stdin);
	ponto->bairro[strlen(ponto->bairro) - 1] = '\0';
	
	if(strlen(ponto->bairro) == 0)
		return 0;
		
	for(k = 0; k > strlen(ponto->bairro); k++){
		if(isalnum(ponto->bairro[k])){
			check = 1;
		}else
			if(isaccent(ponto->bairro[k]) ){
				check = 1;
			}else
				if(ischaracter(ponto->bairro[k])){
					check = 1;
				}
		
		if(check == 0)
			return 0;
			
		check = 0;
	}
	
	return 1;
}

int lerAddress(Ponto *ponto){
	int k;
	int check = 0;
	
	fflush(stdin);
	fgets(ponto->address, 100, stdin);
	fflush(stdin);
	ponto->address[strlen(ponto->address) - 1] = '\0';
	
	if(strlen(ponto->address) == 0)
		return 0;
		
	for(k = 0; k > strlen(ponto->address); k++){
		if(isalnum(ponto->address[k])){
			check = 1;
		}else
			if(isaccent(ponto->address[k])){
				check = 1;
			}else
				if(ischaracter(ponto->address[k])){
					check = 1;
				}
		
		if(check == 0)
			return 0;
			
		check = 0;
	}
	
	return 1;
}

int lerDono(Ponto *ponto){
	int k;
	int check = 0;
	
	fflush(stdin);
	fgets(ponto->dono, 100, stdin);
	fflush(stdin);
	ponto->dono[strlen(ponto->dono) - 1] = '\0';
	
	if(strlen(ponto->dono) == 0)
		return 0;
		
	for(k = 0; k < strlen(ponto->dono); k++){
		if(isalpha(ponto->dono[k])){
			check = 1;
		}else
			if(isaccent(ponto->dono[k])){
				check = 1;
			}else
				if(ponto->dono[k] == 32){
					check = 1;
				}
		
		if(check == 0)
			return 0;
			
		check = 0;
	}
	
	return 1;
}

//Funções de existencia de cadastro para rotista

int numRcad(char nc1[], int tipo){
	FILE *ler = fopen("rotista.c","rb");
	if(ler != NULL){
		Rotista *auxR = (Rotista *) malloc(sizeof(Rotista));
		FILE *ler2 = fopen("rotista.c","rb");
		Rotista *auxR2 = (Rotista *) malloc(sizeof(Rotista));
		
		if(auxR != NULL){
			rewind(ler);
			while(fread(auxR, sizeof(Rotista), 1, ler) == 1){
				if(tipo == 1){
					if(strcmp(auxR->numConta, nc1) == 0){
						auxR = NULL;
						free(auxR);
						
						auxR2 = NULL;
						free(auxR2);
						
						fclose(ler2);	
						fclose(ler);
						return 0;
					}	
				}else
					if(tipo == 2){				
						rewind(ler2);
						while(fread(auxR2, sizeof(Rotista), 1, ler2) == 1){
							if(strcmp(auxR->numConta, nc1) != 0 && strcmp(auxR2->numConta, nc1) == 0){
								auxR = NULL;
								free(auxR);
								
								auxR2 = NULL;
								free(auxR2);
								
								fclose(ler);
								fclose(ler2);
								return 0;
							}
						}
					}
			}
		}
		auxR2 = NULL;
		free(auxR2);
	
		auxR = NULL;
		free(auxR);
		
		fclose(ler2);	
	}
	fclose(ler);
	
	return 1;
}

int cpfRcad(char cpf[], char nc[], int tipo){
	FILE *ler = fopen("rotista.c","rb");
	if(ler != NULL){
		Rotista *auxR = (Rotista *) malloc(sizeof(Rotista));
		if(auxR != NULL){
			rewind(ler);
			while(fread(auxR, sizeof(Rotista), 1, ler) == 1){
				if(tipo == 1){
					if(strcmp(auxR->cpf, cpf) == 0){
						auxR = NULL;
						free(auxR);
						fclose(ler);
						return 0;
					}
				}else
					if(tipo == 2){
						if(strcmp(auxR->numConta, nc) == 0 && strcmp(auxR->cpf, cpf) == 0){
							auxR = NULL;
							free(auxR);
							fclose(ler);
							return 0;
						}
					}
			}
		}
		auxR = NULL;
		free(auxR);
	}
	fclose(ler);
	
	return 1;
}

int rgRcad(char rg[], char nc[], int tipo){
	
	FILE *ler = fopen("rotista.c","rb");
	if(ler != NULL){
		Rotista *auxR = (Rotista *) malloc(sizeof(Rotista));
		if(auxR != NULL){
			rewind(ler);
			while(fread(auxR, sizeof(Rotista), 1, ler) == 1){
				if(tipo == 1){
					if(strcmp(auxR->rg, rg) == 0){
						auxR = NULL;
						free(auxR);
						
						fclose(ler);
						return 0;
					}
				}else
					if(tipo == 2){
						if(strcmp(auxR->rg, rg) == 0 && strcmp(auxR->numConta, nc) == 0){
							auxR = NULL;
							free(auxR);
							fclose(ler);
							return 0;
						}
					}
			}
		}
		auxR = NULL;
		free(auxR);
	}
	fclose(ler);
	
	return 1;
}	

int telRcad(char tel[], char nc[], int tipo){
	
	FILE *ler = fopen("rotista.c","rb");
	if(ler != NULL){
		Rotista *auxR = (Rotista *) malloc(sizeof(Rotista));
		if(auxR != NULL){
			rewind(ler);
			while(fread(auxR, sizeof(Rotista), 1, ler) == 1){
				if(tipo == 1){
					if(strcmp(auxR->tel, tel) == 0){
						auxR = NULL;
						free(auxR);
						fclose(ler);
						return 0;
					}
				}else
					if(tipo == 2){
						if(strcmp(auxR->tel, tel) == 0 && strcmp(auxR->numConta, nc) == 0){
							auxR = NULL;
							free(auxR);
							fclose(ler);
							return 0;
						}
					}
			}
		}
		auxR = NULL;
		free(auxR);
	}
	fclose(ler);
	
	return 1;
}	

//Funções de existencia de cadastro para Pontos de venda
int cepCad(char cep[], char nc[], int tipo){
	FILE *lerLP = fopen("ponto.c","rb");
	if(lerLP != NULL){
		Ponto *auxP = (Ponto *) malloc(sizeof(Ponto));
		if(auxP != NULL){
			rewind(lerLP);
			while(fread(auxP, sizeof(Ponto), 1, lerLP) == 1){
				if(tipo == 2){
					if(strcmp(auxP->cep, cep) == 0 && strcmp(auxP->numConta, nc) != 0){
						fclose(lerLP);
						auxP = NULL;
						free(auxP);
						return 0;
					}
				}else
					if(tipo == 1){
						if(strcmp(auxP->cep, cep) == 0){
							fclose(lerLP);
							auxP = NULL;
							free(auxP);
							return 0;
						}
					}
			}
		}
		auxP = NULL;
		free(auxP);
	}
	fclose(lerLP);
	
	return 1;
}

int numPcad(char nc[], char np[], int tipo){
	
	FILE *lerP = fopen("ponto.c","rb");
	if(lerP != NULL){
		Ponto *auxP = (Ponto *) malloc(sizeof(Ponto));
		if(auxP != NULL){
			rewind(lerP);
			while(fread(auxP, sizeof(Ponto), 1, lerP) == 1){
				if(tipo == 2){
					if(strcmp(auxP->numConta, nc) != 0 && strcmp(auxP->numPonto, np) == 0){
						auxP = NULL;
						free(auxP);
						fclose(lerP);
						return 0;
					}
				}else
					if(tipo == 1){
						if( strcmp(auxP->numPonto, np) == 0 && strcmp(auxP->numConta, nc) == 0 ){
							printf("AAA");
							auxP = NULL;
							free(auxP);
							fclose(lerP);
							return 0;
						}
					}
			}	
		}
		auxP = NULL;
		free(auxP);
	}
	fclose(lerP);
	
	return 1;
}

//Funções do CRUD dos rotistas
void adcPonto(Rotista *rotista){
	caixona();
	cPonto(6, 6, 54);
	gotoxy(25, 6);
	printf("CONTRATO DE ROTISTA");

	gotoxy(6, 9);
	printf("N%c do Ponto", -89);
	
	gotoxy(6, 11);
	printf("Endere%co", -121);
	
	gotoxy(6, 13);
	printf("Bairro");
	
	gotoxy(6, 15);
	printf("CEP");
	
	gotoxy(6, 17);
	printf("Dono");	
	
	FILE *ptrWP = fopen("ponto.c","ab");
	if(ptrWP != NULL){
		FILE *ptrWR = fopen("rotistaDois.c","ab");
		FILE *ptrLR = fopen("rotista.c","rb");
		Rotista * rot = (Rotista *) malloc(sizeof(Rotista));
		Ponto *ponto = (Ponto *) malloc(sizeof(Ponto));
	
		if(ponto != NULL){
			strcpy(ponto->numConta, rotista->numConta);
			
			gotoxy(19, 9);
			if(!lerNumP(ponto, 1)){
				do{
					gotoxy(19, 9);
					printf("                        ");
					gotoxy(19, 9);
					printf("N%cmero de Ponto Inv%clido", -93, -96);
					sleep(1);
					gotoxy(19, 9);
					printf("                        ");
					gotoxy(19, 9);
				}while(!lerNumP(ponto, 1));
			}
			
			gotoxy(19, 11);
			if(!lerAddress(ponto)){
				do{
					gotoxy(19, 11);
					printf("                    ");
					gotoxy(19, 11);
					printf("Endere%co inv%clido", -121, -96);
					sleep(1);
					gotoxy(19, 11);
					printf("                  ");
					gotoxy(19, 11);
				}while(!lerAddress(ponto));
			}
			
			gotoxy(19, 13);
			if(!lerBairro(ponto)){
				do{
					gotoxy(19, 13);
					printf("                    ");
					gotoxy(19, 13);
					printf("Entrada de Bairro inv%clido", -96);
					sleep(1);
					gotoxy(19, 13);
					printf("                          ");
					gotoxy(19, 13);
				}while(!lerBairro(ponto));
			}
			
			gotoxy(19, 15);
			if(!lerCep(ponto, 1)){
				do{
					gotoxy(19, 15);
					printf("                    ");
					gotoxy(19, 15);
					printf("CEP inv%clido", -96);
					sleep(1);
					gotoxy(19, 15);
					printf("            ");
					gotoxy(19, 15);
				}while(!lerCep(ponto , 1));
			}
			
			gotoxy(19, 17);
			if(!lerDono(ponto)){
				do{
					gotoxy(19, 17);
					printf("                    ");
					gotoxy(19, 17);
					printf("Nome inv%clido", -96);
					sleep(1);
					gotoxy(19, 17);
					printf("                          ");
					gotoxy(19, 17);
				}while(!lerDono(ponto));
			}
			
			fwrite(ponto, sizeof(Ponto), 1, ptrWP);
			fclose(ptrWP);
			
			rotista->qntdRota += 1;
			rewind(ptrLR);
			rewind(ptrWR);
			while(fread(rot, sizeof(Rotista), 1, ptrLR) == 1){
				if(strcmp(rot->numConta, rotista->numConta) == 0){
					gotoxy(20, 21);
					printf("Novo Ponto de Rota Salvo!");
					fwrite(rotista, sizeof(Rotista), 1, ptrWR);
				}else{
					fwrite(rot, sizeof(Rotista), 1, ptrWR);
				}
			}
			ponto = NULL;
			free(ponto);
			
			fclose(ptrWR);
			fclose(ptrLR);
			remove("rotista.c");
			rename("rotistaDois.c","rotista.c");
			
			gotoxy(17, 45);
			printf("Pressione ENTER para continuar...");
			getch();
			
			proRotista(rotista);
		}else{
			gotoxy(25, 40);
			printf("Erro! Sem espa%co!", -121);	
		}
		rot = NULL;
		free(rot);
		ponto = NULL;
		free(ponto);
		fclose(ptrLR);
		fclose(ptrWR);
	}else{
		gotoxy(25, 40);
		printf("Erro! Sem espa%co!", -121);
	}
	fclose(ptrWP);
	
	gotoxy(17, 45);
	printf("Pressione ENTER para continuar...");
	getch();
	
	proRotista(rotista);
}

void delPonto(Rotista *rotista, Ponto *ponto){
	caixona();
	char np[4], nc[8];
	strcpy(np, ponto->numPonto);
	strcpy(nc, rotista->numConta);
		
	cPonto(6, 6, 54);
	gotoxy(15, 6);
	printf("Rotista - %s", rotista->nome);
	
	gotoxy(6, 9);
	printf("Endere%co", -121);
	gotoxy(19, 9);
	printf("%s",ponto->address);
	
	gotoxy(6, 11);
	printf("Bairro");
	gotoxy(19, 11);
	printf("%s", ponto->bairro);
	
	gotoxy(6, 13);
	printf("CEP");
	gotoxy(19, 13);
	printf("%s", ponto->cep);
	
	gotoxy(6, 15);
	printf("Dono");
	gotoxy(19, 15);
	printf("%s", ponto->dono);
	
	gotoxy(6, 17);
	printf("N%c do Ponto", -89);
	gotoxy(19, 17);
	printf("%s", ponto->numPonto);
	
	
	FILE *ptrWP = fopen("pontoDois.c","ab");
	FILE *ptrLP = fopen("ponto.c","rb");
	
	FILE *ptrLR = fopen("rotista.c","rb");
	FILE *ptrWR = fopen("rotistaDois.c","ab");
	if(ptrWR != NULL){
		Rotista *auxR = (Rotista *) malloc(sizeof(Rotista));
		Ponto *auxP = (Ponto *) malloc(sizeof(Ponto));
		if(ponto != NULL){
			
			rewind(ptrLP);
			rewind(ptrWP);
			while(fread(auxP, sizeof(Ponto), 1, ptrLP) == 1){
				if(strcmp(auxP->numConta, nc) == 0 && strcmp(auxP->numPonto, np) == 0){
					gotoxy(12, 21);
					printf("Ponto de Rota Deletado!");
				}else{
					fwrite(auxP, sizeof(Ponto), 1, ptrWP);
				}
			}
			ponto = NULL;
			free(ponto);
			
			fclose(ptrLP);
			fclose(ptrWP);
			remove("ponto.c");
			rename("pontoDois.c","ponto.c");
			
			rotista->qntdRota -= 1;
			rewind(ptrLR);
			rewind(ptrWR);
			while(fread(auxR, sizeof(Rotista), 1, ptrLR) == 1){
				if(strcmp(rotista->numConta, auxR->numConta) == 0){
					fwrite(rotista, sizeof(Rotista), 1, ptrWR);
				}else{
					fwrite(auxR, sizeof(Rotista), 1, ptrWR);
				}
			}
			fclose(ptrLR);
			fclose(ptrWR);
			remove("rotista.c");
			rename("rotistaDois.c","rotista.c");
			
			gotoxy(17, 45);
			printf("Pressione ENTER para continuar...");
			getch();
			
			proRotista(rotista);	
		}
		auxR = NULL;
		free(auxR);
	}
	
	fclose(ptrLR);
	fclose(ptrLP);
	fclose(ptrWP);
	fclose(ptrWR);
	
	ponto = NULL;
	free(ponto);
	
	gotoxy(25, 40);
	printf("Erro! Sem memória!");
	
	gotoxy(17, 45);
	printf("Pressione ENTER para continuar...");
	getch();
	
	proRotista(rotista);
}

void altPonto(Rotista *rotista, Ponto *ponto){
	caixona();
	cPonto(6, 6, 54);
	gotoxy(15, 6);
	printf("Rotista - %s", rotista->nome);
	
	gotoxy(6, 9);
	printf("Endere%co", -121);
	gotoxy(19, 9);
	printf("%s",ponto->address);
	
	gotoxy(6, 11);
	printf("Bairro");
	gotoxy(19, 11);
	printf("%s", ponto->bairro);
	
	gotoxy(6, 13);
	printf("CEP");
	gotoxy(19, 13);
	printf("%s", ponto->cep);
	
	gotoxy(6, 15);
	printf("Dono");
	gotoxy(19, 15);
	printf("%s", ponto->dono);
	
	gotoxy(6, 17);
	printf("N%c do Ponto", -89);
	gotoxy(19, 17);
	printf("%s", ponto->numPonto);
	
	cRotista(6, 26, 54);
	gotoxy(20, 26);
	//Tabela de Alteração
	printf("ALTERA%c%cO DO PONTO DE ROTA", -128, -57);
	
	gotoxy(6, 29);
	printf("N%c da Conta", -89);
	
	gotoxy(6, 31);
	printf("Endere%co", -121);
	
	gotoxy(6, 33);
	printf("Bairro");
	
	gotoxy(6,35);
	printf("CEP");
	
	gotoxy(6, 37);
	printf("Dono");
	
	FILE *ptrLP = fopen("ponto.c","rb");
	FILE *ptrWP = fopen("pontoDois.c","ab");
	if(ptrWP != NULL){
		Ponto *auxP = (Ponto *) malloc(sizeof(Ponto));
		if(ponto != NULL){
			
			gotoxy(19, 29);
			if(!lerNumP(auxP, 1)){
				do{
					gotoxy(19, 29);
					printf("                        ");
					gotoxy(19, 29);
					printf("N%cmero de Ponto Inv%clido", -93, -96);
					sleep(1);
					gotoxy(19, 29);
					printf("                        ");
					gotoxy(19, 29);
				}while(!lerNumP(auxP, 1));
			}
			
			gotoxy(19, 31);
			if(!lerAddress(auxP)){
				do{
					gotoxy(19, 31);
					printf("                    ");
					gotoxy(19, 31);
					printf("Endere%co inv%clido", -121, -96);
					sleep(1);
					gotoxy(19, 31);
					printf("                   ");
					gotoxy(19, 31);
				}while(!lerAddress(auxP));
			}
			
			gotoxy(19, 33);
			if(!lerBairro(auxP)){
				do{
					gotoxy(19, 33);
					printf("                    ");
					gotoxy(19, 33);
					printf("Entrada de Bairro inv%clido", -96);
					sleep(1);
					gotoxy(19, 33);
					printf("                          ");
					gotoxy(19, 33);
				}while(!lerBairro(auxP));
			}
			
			gotoxy(19, 35);
			if(!lerCep(auxP, 1)){
				do{
					gotoxy(19, 35);
					printf("                    ");
					gotoxy(19, 35);
					printf("CEP inv%clido", -96);
					sleep(1);
					gotoxy(19, 35);
					printf("              ");
					gotoxy(19, 35);
				}while(!lerCep(auxP , 1));
			}
			
			gotoxy(19, 37);
			if(!lerDono(auxP)){
				do{
					gotoxy(19, 37);
					printf("                    ");
					gotoxy(19, 37);
					printf("Nome inv%clido", -96);
					sleep(1);
					gotoxy(19, 37);
					printf("                          ");
					gotoxy(19, 37);
				}while(!lerDono(auxP));
			}
			strcpy(ponto->numConta, rotista->numConta);
			
			rewind(ptrLP);
			rewind(ptrWP);
			while(fread(ponto, sizeof(Ponto), 1, ptrLP) == 1){
				if(strcmp(auxP->numPonto, ponto->numPonto) == 0 && strcmp(auxP->numConta, ponto->numConta) == 0){
					gotoxy(12, 41);
					printf("ALTERA%c%cO CONCLUÍDA!", -128, -57, -42);
					fwrite(auxP, sizeof(Ponto), 1, ptrWP);
				}else{
					fwrite(ponto, sizeof(Ponto), 1, ptrWP);
				}
			}
			fclose(ptrLP);
			fclose(ptrWP);
			auxP = NULL;
			ponto = NULL;
			free(auxP);
			free(ponto);
			
			gotoxy(17, 45);
			printf("Pressione ENTER para continuar...");
			getch();
			
			proRotista(rotista);
		}else{
			gotoxy(25, 41);
			printf("Erro! Sem espa%co!", -121);	
		}
		auxP = NULL;
		free(auxP);
	}else{
		gotoxy(25, 41);
		printf("Erro! Sem espa%co!", -121);
	}
	ponto = NULL;
	free(ponto);
	
	fclose(ptrLP);
	fclose(ptrWP);
	
	gotoxy(17, 45);
	printf("Pressione ENTER para continuar...");
	getch();
	
	proRotista(rotista);
}

void proPonto(Rotista *rotista, Ponto *ponto){
	caixona();
	cPonto(6, 6, 54);
	gotoxy(15, 6);
	printf("Rotista - %s", rotista->nome);
	
	gotoxy(6, 9);
	printf("Endere%co", -121);
	gotoxy(19, 9);
	printf("%s",ponto->address);
	
	gotoxy(6, 11);
	printf("Bairro");
	gotoxy(19, 11);
	printf("%s", ponto->bairro);
	
	gotoxy(6, 13);
	printf("CEP");
	gotoxy(19, 13);
	printf("%s", ponto->cep);
	
	gotoxy(6, 15);
	printf("Dono");
	gotoxy(19, 15);
	printf("%s", ponto->dono);
	
	gotoxy(6, 17);
	printf("N%c da Conta", -89);
	gotoxy(19, 17);
	printf("%s", ponto->numPonto);
	
	gotoxy(12, 21);
	printf("Ponto de Rota Encontrado!");
	
	gotoxy(17, 45);
	printf("Pressione ENTER para continuar...");
	getch();
	
	ponto = NULL;
	free(ponto);
			
	proRotista(rotista);	
}

void lisPonto(Rotista *rotista){
	int k = 0, key;
	int col1 = 6, col2 = 19;
	int check = 0;
	
	caixona();
	
	FILE *ptrLP = fopen("ponto.c","rb");
	if(ptrLP != NULL){
		Ponto *ponto = (Ponto *) malloc(sizeof(Ponto));
		
		rewind(ptrLP);
		while(fread(ponto, sizeof(Ponto), 1, ptrLP) == 1){
			if(strcmp(ponto->numConta, rotista->numConta) == 0){
				check = 1;
				k++;
				
				if(k == 1){
					cLisPonto(col1, 6, 54);
					gotoxy(col1, 6);
					printf("%s", ponto->dono);
				
					gotoxy(col2, 9);
					printf("%s", ponto->numPonto);
					
					gotoxy(col2, 11);
					printf("%s", ponto->numConta);
				}
				
				if(k == 2){
					cLisPonto(6, 18, 54);
					gotoxy(col1, 18);
					printf("%s", ponto->dono);
					
					gotoxy(col2, 21);
					printf("%s", ponto->numPonto);
					
					gotoxy(col2, 23);
					printf("%s", ponto->numConta);
				}
			
				if(k == 3){
					cLisPonto(6, 29, 54);
					gotoxy(col1, 29);
					printf("%s", ponto->dono);
				
					gotoxy(col2, 32);
					printf("%s", ponto->numPonto);
					
					gotoxy(col2, 34);
					printf("%s", ponto->numConta);
				
					k = 0;

				}
				gotoxy(40, 47);
				printf("ENTER - Prox. Ponto");
				
				do{
					getch();
					key = getch();
				
					switch(key){
						case ENTER:
							break;
						default:
							gotoxy(40, 47);
							printf("ENTER - Prox. Ponto");		
						}
				}while(key != ENTER);	
			}
		}
	}else{
		cLisPonto(6, 6, 54);
		gotoxy(10, 6);
		printf("Ainda n%co h%c pontos de cadastrados", 198, 160);
	}
	
	if(check == 0){
		cLisPonto(6, 6, 54);
		gotoxy(10, 6);
		printf("Ainda n%co h%c pontos de cadastrados", 198, 160);
	}
	fclose(ptrLP);
	cgRotista();
}

//Funções do CRUD dos rotistas
void conRotista(){
	caixona();
	cRotista(6, 6, 54);
	gotoxy(25, 6);
	printf("CONTRATO DE ROTISTA");
	
	gotoxy(6, 9);
	printf("N%c da Conta", -89);
	
	gotoxy(6, 11);
	printf("Nome");
	
	gotoxy(6, 13);
	printf("Telefone");
	
	gotoxy(6, 15);
	printf("CPF");
	
	gotoxy(6, 17);
	printf("RG");
	
	gotoxy(19, 9);
	
	Rotista *rotista = (Rotista *) malloc(sizeof(Rotista));
	Ponto *ponto = (Ponto *) malloc(sizeof(Ponto));
	FILE *ptrWR = fopen("rotista.c","ab");
	if(ptrWR != NULL){
		if(rotista != NULL){
			time_t t;
    		t = time(NULL);
    		periodo = localtime(&t);
			
			if(!lerNumR(rotista, 1)){
				do{
					gotoxy(19, 9);
					printf("                                        ");
					gotoxy(19, 9);
					printf("Numero de conta invalido");
					sleep(1);
					gotoxy(19, 9);
					printf("                                        ");
					gotoxy(19, 9);
				}while(!lerNumR(rotista, 1));
			}
			
			gotoxy(19, 11);
			if(!lerNomeR(rotista)){
				do{
					gotoxy(19, 11);
					printf("                                        ");
					gotoxy(19, 11);
					printf("Nome invalido");
					sleep(1);
					gotoxy(19, 11);
					printf("                                        ");
					gotoxy(19, 11);
				}while(!lerNomeR(rotista));
			}
			
			gotoxy(19, 13);
			if(!lerTelR(rotista, 1)){
				do{
					gotoxy(19, 13);
					printf("                                        ");
					gotoxy(19, 13);
					printf("Telefone invalido!");
					sleep(1);
					gotoxy(19, 13);
					printf("                                        ");
					gotoxy(19, 13);
				}while(!lerTelR(rotista, 1));
			}
			
			gotoxy(19, 15);
			if(!lerCpfR(rotista, 1)){
				do{
					gotoxy(19, 15);
					printf("                                        ");
					gotoxy(19, 15);
					printf("CPF invalido!");
					sleep(1);
					gotoxy(19, 15);
					printf("                                        ");
					gotoxy(19, 15);
				}while(!lerCpfR(rotista, 1));
			}
			
			gotoxy(19, 17);
			if(!lerRgR(rotista, 1)){
				do{
					gotoxy(19, 17);
					printf("                                        ");
					gotoxy(19, 17);
					printf("RG invalido!");
					sleep(1);
					gotoxy(19, 17);
					printf("                                        ");
					gotoxy(19, 17);
				}while(!lerRgR(rotista, 1));
			}
			
			buscaH(rotista, ponto, 1);
			buscaD(rotista, ponto, 1);
			
			rotista->qntdRota = 0;
			
			fwrite(rotista, sizeof(Rotista), 1, ptrWR);
			
			fclose(ptrWR);
			
			gotoxy(12, 21);
			printf("%s -  contratado!", rotista->nome);
		}else{
			gotoxy(25, 21);
			printf("Erro! Sem memória!");
		}
	}else{
		gotoxy(25, 21);
		printf("Erro! Sem memória!");
	}
	rotista = NULL;
	free(rotista);
	ponto = NULL;
	free(ponto);
	
	fclose(ptrWR);
	
	gotoxy(17, 45);
	printf("Pressione ENTER para continuar...");
	getch();
}

void altRotista(Rotista *rotista){
	char nc[8];
	strcpy(nc, rotista->numConta);
	
	caixona();
	cRotista(6, 6, 54);
	gotoxy(15, 6);
	printf("%s - %s", rotista->nome, rotista->numConta);
	
	gotoxy(6, 9);
	printf("CPF");
	gotoxy(19, 9);
	printf("%s",rotista->cpf);
	
	gotoxy(6, 11);
	printf("RG");
	gotoxy(19, 11);
	printf("%s",rotista->rg);
	
	gotoxy(6, 13);
	printf("Telefone");
	gotoxy(19, 13);
	printf("%s", rotista->tel);
	
		gotoxy(6, 15);
	printf("Contratado");
	gotoxy(19, 15);
	printf("Em: %d/%d/%d", rotista->mRotista.dia, rotista->mRotista.mes, rotista->mRotista.ano);

	gotoxy(31, 15);
	printf("%cs: %d:%d:%d", -75, rotista->mRotista.hora, rotista->mRotista.minuto, rotista->mRotista.segundo);
	
	gotoxy(6, 17);
	printf("Rotas");
	gotoxy(19, 17);
	printf("%d", rotista->qntdRota);
	
	gotoxy(12, 21);
	printf("Rotista %s Encontrado!", rotista->nome);
	
	cRotista(6, 26, 54);
	gotoxy(22, 26);
	//Tabela de Alteração
	printf("ALTERA%c%cO DE DADOS PESSOAIS", -128, -57);
	
	gotoxy(6, 29);
	printf("Nome");
	
	gotoxy(6, 31);
	printf("Telefone");
	
	gotoxy(6, 33);
	printf("CPF");
	
	gotoxy(6,35);
	printf("RG");
	
	gotoxy(6, 37);
	printf("N%c de Conta", -89);
	
	gotoxy(19, 29);
	FILE *lerRot = fopen("rotista.c","rb");
	if(lerRot != NULL){
		Rotista *rot = (Rotista *) malloc(sizeof(Rotista));
		if(rot != NULL){
			if(!lerNomeR(rot)){
				do{
					gotoxy(19, 29);
					printf("                                        ");
					gotoxy(19, 29);
					printf("Nome inv%clido", -96);
					sleep(1);
					gotoxy(19, 29);
					printf("                                        ");
					gotoxy(19, 29);
				}while(!lerNomeR(rot));
			}
			
			gotoxy(19, 31);
			if(!lerTelR(rot, 2)){
				do{
					gotoxy(19, 31);
					printf("                                        ");
					gotoxy(19, 31);
					printf("N%cmero inv%clido", -89, -96);
					sleep(1);
					gotoxy(19, 31);
					printf("                                        ");
					gotoxy(19, 31);
				}while(!lerTelR(rot, 2));
			}
			
			gotoxy(19, 33);
			if(!lerCpfR(rot, 2)){
				do{
					gotoxy(19, 33);
					printf("                                        ");
					gotoxy(19, 33);
					printf("CPF inv%clido", -96);
					sleep(1);
					gotoxy(19, 33);
					printf("                                        ");
					gotoxy(19, 33);
				}while(!lerCpfR(rot, 2));
			}
			
			gotoxy(19, 35);
			if(!lerRgR(rot, 2)){
				do{
					gotoxy(19, 35);
					printf("                                        ");
					gotoxy(19, 35);
					printf("RG inv%clido", -96);
					sleep(1);
					gotoxy(19, 35);
					printf("                                        ");
					gotoxy(19, 35);
				}while(!lerRgR(rot, 2));
			}
	
			gotoxy(19, 37);
			if(!lerNumR(rot, 2)){
				do{
					gotoxy(19, 37);
					printf("                                        ");
					gotoxy(19, 37);
					printf("N%cmero inv%clido", -89, -96);
					sleep(1);
					gotoxy(19, 37);
					printf("                                        ");
					gotoxy(19, 37);
				}while(!lerNumR(rot, 2));
			}
			
			FILE *ptrWR = fopen("rotistaDois.c","ab");
			if(ptrWR == NULL){
				printf("ERRO!");
				getch();
			}
			Rotista *rot2 = (Rotista *) malloc(sizeof(Rotista));
			
			rewind(lerRot);
			rewind(ptrWR);
			while(fread(rot2, sizeof(Rotista), 1, lerRot) == 1){
				
				if( strcmp(rot2->numConta, rotista->numConta) == 0){
					gotoxy(12, 41);
					printf("ALTERAÇÕES SALVAS!");
					fwrite(rot, sizeof(Rotista), 1, ptrWR);
				}else{
					fwrite(rot2, sizeof(Rotista), 1, ptrWR);
				}
			}
			fclose(lerRot);
			fclose(ptrWR);
			
			remove("rotista.c");
			rename("rotistaDois.c","rotista.c");	
			
			rot = NULL;
			free(rot);	
			rot2 = NULL;
			free(rot2);
			
		}else{
			gotoxy(25, 41);
			printf("Erro! Sem memória!");
		}
		rot = NULL;
		free(rot);	
	}else{
		gotoxy(25, 41);
		printf("Erro! Sem memória!");
	}
	fclose(lerRot);
	
	gotoxy(17, 45);
	printf("Pressione ENTER para continuar...");
	getch();
}

void demRotista(Rotista *rotista){
	char nc[9];
	strcpy(nc, rotista->numConta);
	
	caixona();
	cRotista(6, 6, 54);
	gotoxy(15, 6);
	printf("%s - %s", rotista->nome, rotista->numConta);
	
	gotoxy(6, 9);
	printf("CPF");
	gotoxy(19, 9);
	printf("%s",rotista->cpf);
	
	gotoxy(6, 11);
	printf("RG");
	gotoxy(19, 11);
	printf("%s",rotista->rg);
	
	gotoxy(6, 13);
	printf("Telefone");
	gotoxy(19, 13);
	printf("%s", rotista->tel);
	
		gotoxy(6, 15);
	printf("Contratado");
	gotoxy(19, 15);
	printf("Em: %d/%d/%d", rotista->mRotista.dia, rotista->mRotista.mes, rotista->mRotista.ano);

	gotoxy(31, 15);
	printf("%cs: %d:%d:%d", -75, rotista->mRotista.hora, rotista->mRotista.minuto, rotista->mRotista.segundo);
	
	gotoxy(6, 17);
	printf("Rotas");
	gotoxy(19, 17);
	printf("%d", rotista->qntdRota);
	//Tabela de Alteração
	
	FILE *lerPonto = fopen("ponto.c","rb");
	if(lerPonto != NULL){
		Ponto *ponto = (Ponto *) malloc(sizeof(Ponto));
		FILE *ptrWP = fopen("pontoDois.c","ab");
		if(ponto != NULL && ptrWP != NULL){
			rewind(lerPonto);
			while(fread(ponto, sizeof(Ponto), 1, lerPonto) == 1){
				if(strcmp(ponto->numConta, rotista->numConta) == 0){
					
				}else{
					fwrite(ponto, sizeof(Ponto), 1, ptrWP);
				}
			}
		}else{
			gotoxy(12, 21);
			printf("Erro! Sem memória");
			getch();
		}
		ponto = NULL;
		free(ponto);
		fclose(ptrWP);
		fclose(lerPonto);
		remove("ponto.c");
		rename("pontoDois.c","ponto.c");
	}
	
	fclose(lerPonto);
	
	FILE *ptrWR = fopen("rotistaDois.c","ab");
	FILE *lerRot = fopen("rotista.c","rb");
	rewind(lerRot);
	rewind(ptrWR);
	while(fread(rotista, sizeof(Rotista), 1, lerRot) == 1){
		if(strcmp(nc, rotista->numConta) == 0){
			gotoxy(20, 21);
			printf("Rotista Demitido!  ");
		}else{
			fwrite(rotista, sizeof(Rotista), 1, ptrWR);
		}
	}
	fclose(lerRot);
	fclose(ptrWR);
	remove("rotista.c");
	rename("rotistaDois.c","rotista.c");
	
	gotoxy(17, 45);
	printf("Pressione ENTER para continuar...");
	getch();
}

void proRotista(Rotista *rotista){
	int x, y, key;
	Ponto *ponto = (Ponto *) malloc(sizeof(Ponto));
 	
	caixona();
	cRotista(6, 6, 54);
	gotoxy(15, 6);
	printf("%s - %s", rotista->nome, rotista->numConta);
	
	gotoxy(6, 9);
	printf("CPF");
	gotoxy(19, 9);
	printf("%s",rotista->cpf);
	
	gotoxy(6, 11);
	printf("RG");
	gotoxy(19, 11);
	printf("%s",rotista->rg);
	
	gotoxy(6, 13);
	printf("Telefone");
	gotoxy(19, 13);
	printf("%s", rotista->tel);
	
	gotoxy(6, 15);
	printf("Contratado");
	gotoxy(19, 15);
	printf("Em: %d/%d/%d", rotista->mRotista.dia, rotista->mRotista.mes, rotista->mRotista.ano);

	gotoxy(31, 15);
	printf("%cs: %d:%d:%d", -75, rotista->mRotista.hora, rotista->mRotista.minuto, rotista->mRotista.segundo);
	
	gotoxy(6, 17);
	printf("Rotas");
	gotoxy(19, 17);
	printf("%d", rotista->qntdRota);
	
	cgPonto();
	//Colocar a interface para entrar na opções de Pontos
	x = 22;  y = 25;
	gotoxy(x, y);
	printf("%c", -81);
	
	do{
		getch();
		key = getch();
		
		switch(key){
			case CIMA:
				if(y >= 26){
					gotoxy(x, y);
					printf(" ");
					
					y -= 4;
					gotoxy(x, y);
					printf("%c", -81);
					gotoxy(x, y);
				}
				break;
			case BAIXO:
				if(y <= 40){
					gotoxy(x, y);
					printf(" ");
					
					y += 4;
					gotoxy(x, y);
					printf("%c", -81);
					gotoxy(x, y);
				}
				break;
			case ESC:
				cPriEntrada();
				
			default:
				gotoxy(x, y);
				printf("%c", -81);
				gotoxy(x,y);
		}
	}while(key != ENTER);
	
	if(y == 25){
		adcPonto(rotista);	
	}else
		if(y == 29){
			if(cLoginP(rotista, ponto))
				delPonto(rotista, ponto);
		}else
			if(y == 33){
				if(cLoginP(rotista, ponto))
					altPonto(rotista, ponto);	
			}else
				if(y == 37){
					if(cLoginP(rotista, ponto))
						proPonto(rotista, ponto);
				}else
					if(y == 41){
						lisPonto(rotista);
					}
				
				
	proRotista(rotista);
}


void lisRotista(Rotista *rotista){
	int k = 0, key;
	int col1 = 6, col2 = 19;
	int check = 0;
	
	caixona();
	
	FILE *ptrLR = fopen("rotista.c","rb");
	if(ptrLR != NULL){
		Rotista *rot = (Rotista *) malloc(sizeof(Rotista));
		
		rewind(ptrLR);
		while(fread(rot, sizeof(rot), 1, ptrLR) == 1){
				check = 1;
				k++;
				
				if(k == 1){
					cLisPonto(col1, 6, 54);
					gotoxy(col1, 6);
					printf("%s", rot->nome);
				
					gotoxy(col2, 9);
					printf("%s", rot->numConta);
					
					gotoxy(col2, 11);
					printf("%s", rot->cpf);
				}
				
				if(k == 2){
					cLisPonto(6, 18, 54);
					gotoxy(col1, 18);
					printf("%s", rot->nome);
					
					gotoxy(col2, 21);
					printf("%s", rot->numConta);
					
					gotoxy(col2, 23);
					printf("%s", rot->cpf);
				}
			
				if(k == 3){
					cLisPonto(6, 29, 54);
					gotoxy(col1, 29);
					printf("%s", rot->nome);
				
					gotoxy(col2, 32);
					printf("%s", rot->numConta);
					
					gotoxy(col2, 34);
					printf("%s", rot->cpf);
				
					k = 0;

				}

				gotoxy(40, 47);
				printf("ENTER - Prox. Rotista");
				
				do{
					getch();
					key = getch();
				
					switch(key){
						case ENTER:
							break;
						default:
							gotoxy(40, 47);
							printf("ENTER - Prox. Rotista");		
						}
				}while(key != ENTER);	

		}
		free(rot);
	}else{
		cLisPonto(6, 6, 54);
		gotoxy(10, 6);
		printf("Ainda n%co h%c rotistas contratados", 198, 160);
	}
	
	if(check == 0){
		cLisPonto(6, 6, 54);
		gotoxy(10, 6);
		printf("Ainda n%co h%c rotistas contratados", 198, 160);
	}
	

	fclose(ptrLR);	
	cgRotista();
}
