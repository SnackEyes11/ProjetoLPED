#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int verifica(char []);

int main(){
    char cpf[13];
    int check;
    
    fgets(cpf,13,stdin);
    fflush(stdin);
    
    check = verifica(cpf);
    
    printf("Check : %d",check);
    return 0;
}

int verifica(char cpf[]){
    char aux[1]; //String de 1 porque atoi nao converte caracter unico
    int a,b;
    int soma=0;
    int check;
        
     
    if (strlen(cpf) -1 != 11) //verifica se o valor inserido tem 11 caracteres
        exit(1);

    for (a=0;a<11;a++){
        if (!isdigit(cpf[a])){
            exit(1);
        }
    }

    for (a = 0,b = 10;a < 9;a++,b--){
        aux[0] = cpf[a];
        soma += b * atoi(aux);
    }
    aux[0] = cpf[9];  
    if(soma % 11 >= 2){
        if(atoi(aux) != 11 - (soma % 11)){
            printf("Ola");
            exit(1);
        }   
    }else{
        if(cpf[9] != 0){
            printf("Hello");
            exit(1);
        }
    }

    soma = 0;
    for(a = 0,b = 11;a < 10;a++,b--){
        aux[0] = cpf[a];
        soma += b * atoi(aux);
    }
    aux[0] = cpf[10];
    if(soma % 11 >= 2){
        if(atoi(aux) != 11 - (soma % 11)){
            exit(1);
        }   
    }else{
        if(cpf[10] != 0){
            exit(1);
        }
    }
    
    printf("Mano, teu cpf ta certo!");
    return 0;
}
