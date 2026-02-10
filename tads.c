#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tads.h"
#include "mtext.h"

//operacoes com lista

node* createNode(char* data){//inicializa no
    node* nd=(node*)malloc(sizeof(node));
    if(nd==NULL){
        printf("Erro de inicialização de nó\n");
        return NULL;
    }
    strcpy(nd->data, data);
    nd->next=NULL;
    nd->prev=NULL;
    return nd;
}

Lista* newList(){// inicializa lista
    Lista* lista=(Lista*)malloc(sizeof(Lista));
    if(lista==NULL){
        printf("Erro de inicialização de lista\n");
        return NULL;
    }
    lista->tamanho=0;
    lista->head=NULL;
    lista->tail=NULL;
    return lista;
}

void insertHead(Lista* lista, char* data){//insere no inicio
    node* new=createNode(data);
    if(new==NULL)
        return;
    new->next=lista->head;
    if(lista->head==NULL){
        lista->head=new;
        lista->tail=new;
        lista->tamanho++;
        return;
    }
    lista->head->prev=new;
    lista->head=new;
    lista->tamanho++;
}

void insertTail(Lista* lista, char* data){//insere no final
    node* new=createNode(data);
    if(new==NULL)
        return;
    if(lista->head==NULL){
        lista->head=new;
        lista->tail=new;
        lista->tamanho++;
        return;
    }
    lista->tail->next=new;
    new->prev=lista->tail;
    lista->tail=new;
    lista->tamanho++;
}

void insertMid(Lista* lista, int position, char* data){//insere na posicao
    if(position<0 || position>lista->tamanho){
        interface();
        printf("Posicao invalida...\n");
        return;
    }
    if(position==0){
        insertHead(lista, data);
        return;
    }
    if(position==lista->tamanho){
        insertTail(lista, data);
        return;
    }
    node* new=createNode(data);
    if(new==NULL)
        return;
    node* aux=lista->head;
    for(int i=0; i<position-1; i++)
        aux=aux->next;
    new->prev=aux;
    new->next=aux->next;
    aux->next->prev=new;
    aux->next=new;
    lista->tamanho++;
}

void deleteHead(Lista* lista){//remove no inicio
    if(lista->head==NULL){
        interface();
        printf("Vazio...");
        return;
    }
    if(lista->head==lista->tail){
        free(lista->head);
        lista->head=NULL;
        lista->tail=NULL;
        lista->tamanho=0;
        return;
    }
    node* aux=lista->head->next;
    free(lista->head);
    lista->head=aux;
    lista->head->prev=NULL;
    lista->tamanho--;
}

void deleteTail(Lista* lista){//remove no final
    if(lista->head==NULL){
        interface();
        printf("Vazio...");
        return;
    }
    if(lista->head==lista->tail){
        free(lista->head);
        lista->head=NULL;
        lista->tail=NULL;
        lista->tamanho=0;
        return;
    }
    node* aux=lista->tail->prev;
    free(lista->tail);
    lista->tail=aux;
    lista->tail->next=NULL;
    lista->tamanho--;
}

void deleteMid(Lista* lista, int position){//remove na posicao
    if(position<0 || position>lista->tamanho-1){
        interface();
        printf("Vazio...");
        return;
    }
    if(position==0){
        deleteHead(lista);
        return;
    }
    if(position==lista->tamanho-1){
        deleteTail(lista);
        return;
    }
    node* aux=lista->head;
    for(int i=0; i<position; i++)
        aux=aux->next;
    aux->next->prev=aux->prev;
    aux->prev->next=aux->next;
    free(aux);
    lista->tamanho--;
}

//operacoes com pilha

nodep* createnodep(char* data, char* op, int pos, int idx){//inicializa no de pilha
    nodep* new=(nodep*)malloc(sizeof(nodep));
    strcpy(new->data, data);
    new->next=NULL;
    new->prev=NULL;
    strcpy(new->op, op);
    new->pos=pos;
    new->idx=idx;
    return new;
}

Pilha* newP(){//inicializa pilha
    Pilha* new=(Pilha*)malloc(sizeof(Pilha));
    new->tamanho=0;
    new->top=NULL;
    new->bot=NULL;
    new->td=4;
    return new;
}

void push(Pilha* pilha, char* data, char* op, int pos, int idx){//insere no topo, tamanho pilha->td
    nodep* new=createnodep(data, op, pos, idx);
    if(pilha->tamanho==0){
        pilha->top=new;
        pilha->bot=new;
        pilha->tamanho++;
        return;
    }
    if(pilha->tamanho<pilha->td){
        new->next=pilha->top;
        pilha->top->prev=new;
        pilha->top=new;
        pilha->tamanho++;
        return;
    }
    //td=4 padrao, maximo
    new->next=pilha->top;
    pilha->top->prev=new;
    pilha->top=new;
    pilha->bot=pilha->bot->prev;
    free(pilha->bot->next);
    pilha->bot->next=NULL;
}

void pop(Pilha* pilha){//remove no topo
    if(pilha->tamanho==0){
        interface();
        printf("Sem operações armazenadas\n");
        return;
    }
    //se o tamanho for 1, libera top e bot simultaneamente, não precisa ser tratado
    nodep* aux=pilha->top;
    pilha->top=pilha->top->next;
    free(aux);
    pilha->tamanho--;
}

