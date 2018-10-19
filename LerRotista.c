/*Fazer a verificação do nome do rotista adicionado ao pacote de rotista da empresa*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int Corrige(char []); //prottipo da função Corrige - irá verificar se o nome do rotista é válido
void Ler(char []); //prótotipo da função que Ler - irá ler o nome do rotista

int main(){
    char nome[11];

    Ler(nome); //Chama a função Ler
    
    return 0;
}

void Ler(char str[]){
    int check;
    
    inicio:
    system("cls");
    printf("Informe o nome do rotista: ");
    fgets(str,10,stdin);
    
    check = Corrige(str);
    if(check == 0){
        printf("\nNome inválido!!!!!!!!");
        system("pause");
        goto inicio;
    }
    printf("Nome %s e valido!\n",str);
}

int Corrige(char str[]){
        
    if(str[(strlen(str)) - 1] == '\n')
        str[(strlen(str)) - 1] = '\0';
    
    for(int i = 0;i < strlen(str);i++){
        if(isalpha(str[i]) == 0 && str[i] != '\0')
            return 0; //A função Corrige retorna '0' caso a mesma encontre um erro na string 'str'
    } 
    
    return 1;   //A função Corrige retorna '1' caso a mesma não encontre nenhum erro na string 'str'
}
