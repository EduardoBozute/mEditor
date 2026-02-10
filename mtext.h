#ifndef MTEXT_H
#define MTEXT_H

//interface
void interface();

//prompt interativo
void prompt(char* entrada, Lista* texto, FILE** arq, char* arquivo, Pilha* pundo, Pilha* predo);

//abrir
void open(char* arquivo, Lista* texto, FILE** arq);

//salvar
void save(Lista* texto, FILE** arq, char* arquivo);

//insercao
void i(int pos, Lista* texto, char* newlinha);

//remocao
void d(int pos, Lista* texto);

//substituicao
void r(int pos, char* newlinha, Lista* texto);

//edicao
void a(int pos, char* suf, Lista* texto);

//operacoes de linha
void split(int pos, int idx, Lista* texto);

void join(int pos, Lista* texto);

//desfazer
void undo(Pilha* pundo, Pilha* predo, Lista* texto);

//refazer
void redo(Pilha* pundo, Pilha* predo, Lista* texto);

//amostragem
void print(Lista* texto, node* noat, int at);

//encerramento
void quit(FILE** arq, Lista* texto, Pilha* pundo, Pilha* predo);

//ajuda de sintaxe
void help();

#endif