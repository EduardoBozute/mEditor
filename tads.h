#ifndef TADS_C
#define TADS_C

//tipos abstratos de dado
typedef struct node{//no de lista
    char data[256];
    struct node* next;
    struct node* prev;
}node;

typedef struct Lista{//lista
    int tamanho;
    node* head;
    node* tail;
}Lista;

typedef struct Pilha{//pilha
    int tamanho;
    struct nodep* top;
    struct nodep* bot;
    int td;//tamanho max
}Pilha;

typedef struct nodep{//no de pilha
    char data[256];
    struct nodep* next;
    struct nodep* prev;
    char op[256];
    int pos;
    int idx;
}nodep;

//operacoes de lista

//inicializa no de lista
node* createNode(char* data);

//inicializa lista
Lista* newList();

//insere no inicio da lista
void insertHead(Lista* lista, char* data);

//insere no final da lista
void insertTail(Lista* lista, char* data);

//insere na posicao da lista
void insertMid(Lista* lista, int position, char* data);

//remove no inicio da lista
void deleteHead(Lista* lista);

//remove no final da lista
void deleteTail(Lista* lista);

//remove na posicao da lista
void deleteMid(Lista* lista, int position);

//operacoes de pilha

//inicializa no de pilha
nodep* createnodep(char* data, char* op, int pos, int idx);

//inicializa pilha
Pilha* newP();

//insere no topo da pilha de tamanho pilha->td
void push(Pilha* pilha, char* data, char* op, int pos, int idx);

//remove no topo da pilha
void pop(Pilha* pilha);

#endif