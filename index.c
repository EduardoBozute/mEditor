#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tads.h"
#include "mtext.h"

int main(){
    //declaracao de variaveis e inicializacao de tads
    char entrada[256], arquivo[256];
    FILE* arq=NULL;
    Lista* texto=newList();
    Pilha* pundo=newP();// pilha undo
    Pilha* predo=newP();// pilha redo
    if(texto==NULL){//se o texto nao foi inicializado
        printf("\nErro de inicialização");
        return 1;
    }
    //execucao do programa
    do{
        prompt(entrada, texto, &arq, arquivo, pundo, predo);
    }while(strcmp(entrada, "quit")!=0);
    //fim do programa
    return 0;
}