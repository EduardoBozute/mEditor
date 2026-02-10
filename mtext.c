#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tads.h"
#include "mtext.h"

//funções do programa

//interface
void interface(){
    printf("mtext> ");
}

//prompt interativo
void prompt(char* entrada, Lista* texto, FILE** arq, char* arquivo, Pilha* pundo, Pilha* predo){
    interface();
    scanf("%s", entrada);
    if(strcmp(entrada, "open")==0){
        if(*arq!=NULL){//se o arquivo esta aberto
            interface();
            printf("Já existe um arquivo aberto\n");
            return;
        }//senão, abre o arquivo
        scanf("%s", arquivo);
        open(arquivo, texto, arq);
        return;
    }
    if(strcmp(entrada, "save")==0){
        save(texto, arq, arquivo);//salva e fecha o arquivo
        return;
    }
    if(strcmp(entrada, "i")==0){
        int pos=texto->tamanho+1;//padrao de insercao apos a ultima linha
        char newlinha[256];
        scanf("%d%*c", &pos);//não inclui o espaço da entrada na linha
        fgets(newlinha, 256, stdin);
        if(*arq==NULL){//se nenhum arquivo foi aberto
            interface();
            printf("Abra um arquivo primeiro!\n");
            return;
        }
        if(pos<1){//impossivel inserir, indice invalido
        interface();
        printf("Posição inválida\n");
        return;
        }//inserir na linha pos
        push(pundo, "", "d", pos, texto->tamanho);
        i(pos, texto, newlinha);
        interface();
        printf("Linha inserida!\n");
        return;
    }
    if(strcmp(entrada, "d")==0){
        int pos;
        scanf("%d", &pos);
        if(*arq==NULL){//se o arquivo nao foi aberto
            interface();
            printf("Abra um arquivo primeiro!\n");
            return;
        }
        if(pos>texto->tamanho || pos<1){//se o numero da linha é invalido
            interface();
            printf("Posição inválida\n");
            return;
        }//deletar a linha de numero pos
        node* aux=texto->head;
        for(int i=1; i<pos; i++)
            aux=aux->next;
        push(pundo, aux->data, "i", pos, 0);
        d(pos, texto);
        interface();
        printf("Linha removida!\n");
        return;
    }
    if(strcmp(entrada, "r")==0){
        int pos;
        char newlinha[256];
        scanf("%d%*c", &pos);//não inclui o espaço de entrada na linha
        fgets(newlinha, 256, stdin);
        if(*arq==NULL){//se nenhum arquivo foi aberto;
            interface();
            printf("Abra um arquivo primeiro!\n");
            return;
        }
        if(pos<1 || pos>texto->tamanho){//se a posicao é invalida
            interface();
            printf("Posição inválida\n");
            return;
        }//substituir o conteudo da linha pos por newlinha
        node* aux=texto->head;
        for(int i=1; i<pos; i++)
            aux=aux->next;
        push(pundo, aux->data, "r", pos, 0);
        r(pos, newlinha, texto);
        interface();
        printf("Linha substituída com sucesso!\n");
        return;
    }
    if(strcmp(entrada, "a")==0){
        int pos;
        char suf[256];
        scanf("%d%*c", &pos);//não inclui o espaço de entrada na linha
        fgets(suf, 256, stdin);
        if(*arq==NULL){//se nenhum arquivo foi aberto;
            interface();
            printf("Abra um arquivo primeiro");
            return;
        }
        if(pos<1 || pos>texto->tamanho){//se a posicao é invalida
            interface();
            printf("Posição inválida\n");
            return;
        }//concatena um sufixo no conteudo da linha pos
        node* aux=texto->head;
        for(int i=1; i<pos; i++)
            aux=aux->next;
        push(pundo, aux->data, "r", pos, 0);
        a(pos, suf, texto);
        interface();
        printf("Sufixo concatenado!\n");
        return;
    }
    if(strcmp(entrada, "split")==0){
        int pos, idx;
        scanf("%d %d", &pos, &idx);
        if(*arq==NULL){//se nenhum arquivo foi aberto;
            interface();
            printf("Abra um arquivo primeiro!\n");
        }
        if(pos<1 || pos>texto->tamanho){// se a posicao é invalida
            interface();
            printf("Posição inválida\n");
            return;
        }
        //verificacao do indice
        node* aux=texto->head;
        for(int i=1; i<pos; i++)
            aux=aux->next;
        int tlinha=strlen(aux->data);//tamanho da linha sem \0 e com \n;
        int barran=(tlinha-1==strcspn(aux->data, "\n"));//tem \n no final;
        if(idx<1 || idx>tlinha-1-barran){
            interface();
            printf("Índice inválido\n");
            return;
        }//divisao do conteudo da linha no indice
        push(pundo, " ", "join", pos, idx);
        split(pos, idx, texto);
        interface();
        printf("Linha dividida!\n");
        return;
    }
    if(strcmp(entrada, "join")==0){
        int pos;
        scanf("%d", &pos);
        if(*arq==NULL){//se nenhum arquivo foi aberto;
            interface();
            printf("Abra um arquivo primeiro!\n");
        }
        if(pos<1 || pos>texto->tamanho-1){//verificacao da posicao, ultima linha nao une com ninguem
            interface();
            printf("Posição inválida\n");
            return;
        }//uniao das linhas
        node* aux=texto->head;
        for(int i=1; i<pos; i++)
            aux=aux->next;
        push(pundo, "", "split", pos, strlen(aux->data));
        join(pos, texto);
        interface();
        printf("Linhas unidas!\n");
        return;
    }
    if(strcmp(entrada, "undo")==0){
        if(pundo->top==NULL){//nenhuma operacao de edicao foi realizada até agora
            interface();
            printf("Não há operações para desfazer\n");
            return;
        }//desfazer
        undo(pundo, predo, texto);
        interface();
        printf("Operação desfeita\n");
        return;
    }
    if(strcmp(entrada, "redo")==0){
        if(predo->top==NULL){//nenhuma operacao de edicao foi desfeita até agora
            interface();
            printf("Não há operações para refazer\n");
            return;
        }//refazer
        redo(pundo, predo, texto);
        interface();
        printf("Operação refeita\n");
        return;
    }
    if(strcmp(entrada, "print")==0){
        print(texto, texto->head, 1);//amostragem
        printf("\n");
        return;
    }
    if(strcmp(entrada, "quit")==0){
        quit(arq, texto, pundo, predo);//liberacao de memoria
        interface();
        printf("Encerrando o programa...\n");
        return;
    }
    if(strcmp(entrada, "help")==0){
        help();
        return;
    }
    else{
        interface();
        printf("Comando invalido! Digite 'help' para visualizar os comandos\n");
    }
}

//abrir
void open(char* arquivo, Lista* texto, FILE** arq){
    *arq=fopen(arquivo, "r+");//novo arquivo
    if(*arq==NULL){//arquivo nao existe
        interface();
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    //arquivo existe, carregar conteudo
    if(fgetc(*arq)==EOF){//arquivo vazio, criar 1 nó vazio
        insertTail(texto, "\0");
        printf("Arquivo aberto com sucesso\n");
        return;
    }
    rewind(*arq);
    char str[256];
    while(fgets(str, 256, *arq)!=NULL){//ponteiro nao chegou em EOF
        insertTail(texto, str);
    }
    interface();
    printf("Arquivo aberto com sucesso\n");
}

//salvar
void save(Lista* texto, FILE** arq, char* arquivo){
    if (*arq==NULL){//nenhum arquivo foi aberto
        interface();
        printf("O arquivo não está aberto\n");
        return;
    }//limpar conteudo anigo
    fclose(*arq);
    *arq=fopen(arquivo, "w+");
    if(*arq==NULL){//erro de abertura, aviso de possivel perca de dados
        interface();
        printf("Erro no editor, arquivo perdido\n");
        return;
    }//coloca os novos dados no arquivo
    node* aux=texto->head;
    while(aux!=NULL){
        fputs(aux->data, *arq);
        aux=aux->next;
        deleteHead(texto);//liberar nós
    }//fecha e salva o arquivo
    fclose(*arq);
    *arq=NULL;
    interface();
    printf("Arquivo salvo e fechado com sucesso\n");
}

//insercao
void i(int pos, Lista* texto, char* newlinha){
    if(pos>texto->tamanho){//novo EOF, substituir \0 por \n
        int subs=strlen(texto->tail->data);
        texto->tail->data[subs]='\n';
        while(pos>texto->tamanho+1){
            insertTail(texto, "\n");//inserção de linhas até a anterior da linha desejada
        }
        insertTail(texto, newlinha);
        //substituir \n por \0
        subs=strlen(texto->tail->data);
        if(texto->tail->data[subs-1]=='\n')//tratamento para ultima liha
            texto->tail->data[subs-1]='\0';//\n faz parte como ultimo caractere da string
        return;
    }
    //linha 1<= e <=n
    insertMid(texto, pos-1, newlinha);//lista começa contando do 0, não do 1
}

//remocao
void d(int pos, Lista* texto){
    if(texto->tamanho>1){
        int sub=strlen(texto->tail->prev->data);
        if(pos==texto->tamanho && texto->tail->prev->data[sub-1]=='\n')
            texto->tail->prev->data[sub-1]='\0';//substitui \n por \0 no novo final
    }
    deleteMid(texto, pos-1);
    if(texto->tamanho==0)//se o texto tinha 1 linha
        insertTail(texto, "\0");//arquivo vazio
}

//substituicao
void r(int pos, char* newlinha, Lista* texto){
    node* aux=texto->head;
    for(int i=1; i<pos; i++){//encontrar no
        aux=aux->next;
    }
    strcpy(aux->data, newlinha);//substituir conteudo
    if(pos==texto->tamanho){//substituir \n por \0
        int subs=strlen(texto->tail->data);
        texto->tail->data[subs-1]='\0';
    }
}

//edicao
void a(int pos, char* suf, Lista* texto){
    int subs;
    if(pos<texto->tamanho){//substituir \n por \0
        node* aux=texto->head;
        for(int i=1; i<pos; i++)
            aux=aux->next;
        if(aux->data[0]=='\n'){//linha vazia
            strcpy(aux->data, suf);
        }
        else{//linha com conteudo
        aux->data[strcspn(aux->data, "\n")]='\0';//\n se torna \0
        strcspn(aux->data, "\0");//\0 se torna \n
        strcat(aux->data, suf);
        }
        return;
    }
    //pos==tamanho, ultima linha, tratamento do terminador de cadeia \0
    strcspn(texto->tail->data, "\0");
    strcat(texto->tail->data, suf);
    subs=strlen(texto->tail->data);//substituir \n por \0
    texto->tail->data[subs-1]='\0';
}

//operacoes de linha
void split(int pos, int idx, Lista* texto){
    node* aux=texto->head;
    for(int i=1; i<pos; i++)
        aux=aux->next;
    int tlinha=strlen(aux->data);//tamanho da linha sem \0 e com \n;
    int barran=(tlinha-1==strcspn(aux->data, "\n"));//tem \n no final;
    //indice ja foi verificado, nao é preciso repetir
    if(!barran){//ultima linha
        char newlinha[256];
        strncpy(newlinha, aux->data+idx, tlinha-idx);//le até antes do \0
        if(newlinha[tlinha-idx]=='\n');
        newlinha[tlinha-idx]='\0';//termina a cadeia
        i(pos+1, texto, newlinha);//cria a proxima linha
        strncpy(newlinha, aux->data, idx);//le até antes do \n
        newlinha[idx]='\n';//completa
        newlinha[idx+1]='\0';//garante que não haverá leitura de lixo de memória
        r(pos, newlinha, texto);//substitui a mesma linha até o indice
        return;
    }
    //não é a ultima linha;
    //terminar a linha pos com novo \n e criar a próxima com os caracteres seguintes, incluindo o \n
    char newlinha[256];
    strncpy(newlinha, aux->data+idx, tlinha-idx);//a copia do \n é incluida
    newlinha[tlinha-idx]='\0';
    i(pos+1, texto, newlinha);
    strncpy(newlinha, aux->data, idx);
    newlinha[idx]='\n';
    newlinha[idx+1]='\0';
    r(pos, newlinha, texto);
}

void join(int pos, Lista* texto){
    node* aux=texto->head;
    for(int i=1; i<pos; i++){//localiza a linha
        aux=aux->next;
    }
    aux->data[strcspn(aux->data, "\n")]='\0';//\n se torna \0
    strcat(aux->data, aux->next->data);//uniao
    d(pos+1, texto);//delecao da linha seguinte
}

//desfazer
void undo(Pilha* pundo, Pilha* predo, Lista* texto){//empilha em redo a operacao contraria e desempilha em undo
    if(strcmp(pundo->top->op, "i")==0){
        push(predo, " ", "d", pundo->top->pos, 0);
        i(pundo->top->pos, texto, pundo->top->data);
        pop(pundo);
        return;
    }
    if(strcmp(pundo->top->op, "d")==0){
        node* aux=texto->head;
        for(int i=1; i<pundo->top->pos; i++)
            aux=aux->next;
        push(predo, aux->data, "i", pundo->top->pos, pundo->top->idx);
        if(pundo->top->idx<texto->tamanho-1){//insercao em linha > tamanho+1
            while(pundo->top->idx<texto->tamanho)
                d(texto->tamanho, texto);//eliminacao de todas as linhas criadas
            pop(pundo);
            return;
        }
        d(pundo->top->pos, texto);
        pop(pundo);
        return;
    }
    if(strcmp(pundo->top->op, "r")==0){
        node* aux=texto->head;
        for(int i=1; i<pundo->top->pos; i++)
            aux=aux->next;
        push(predo, aux->data, "r", pundo->top->pos, 0);
        r(pundo->top->pos, pundo->top->data, texto);
        pop(pundo);
        return;
    }
    //caso "a" não existe, pois é convertido em "r" para undo
    if(strcmp(pundo->top->op, "split")==0){
        push(predo, "", "join", pundo->top->pos, pundo->top->idx);
        split(pundo->top->pos, pundo->top->idx-1, texto);
        pop(pundo);
        return;
    }
    if(strcmp(pundo->top->op, "join")==0){
        push(predo, "", "split", pundo->top->pos, pundo->top->idx);
        join(pundo->top->pos, texto);
        pop(pundo);
        return;
    }
}
//refazer
void redo(Pilha* pundo, Pilha* predo, Lista* texto){//empilha em redo a operacao contraria e desempilha em undo
    if(strcmp(predo->top->op, "i")==0){
        push(pundo, "", "d", predo->top->pos, predo->top->idx);//indice para caso de insercao em linha > tamanho+1
        i(predo->top->pos, texto, predo->top->data);
        pop(predo);
        return;
    }
    if(strcmp(predo->top->op, "d")==0){
        node* aux=texto->head;
        for(int i=1; i<predo->top->pos; i++)
            aux=aux->next;
        push(pundo, aux->data, "i", predo->top->pos, 0);
        d(predo->top->pos, texto);
        pop(predo);
        return;
    }
    if(strcmp(predo->top->op, "r")==0){
        node* aux=texto->head;
        for(int i=1; i<predo->top->pos; i++)
            aux=aux->next;
        push(pundo, aux->data, "r", predo->top->pos, 0);
        r(predo->top->pos, predo->top->data, texto);
        pop(predo);
        return;
    }
    //caso "a" não existe, pois é convertido em "r" para undo, logo é traado como "r" em redo tambem
    if(strcmp(predo->top->op, "split")==0){
        push(pundo, "", "join", predo->top->pos, predo->top->idx);
        split(predo->top->pos, predo->top->idx, texto);
        pop(predo);
        return;
    }
    if(strcmp(predo->top->op, "join")==0){
        push(pundo, "", "split", predo->top->pos, predo->top->idx);
        join(predo->top->pos, texto);
        pop(predo);
        return;
    }
}

//amostragem
void print(Lista* texto, node* noat, int at){
    if(texto->head==NULL){
        interface();
        printf("Sem conteudo carregado no editor!");
        return;
    }
    printf("    %d\t| ", at);
    printf("%s", noat->data);
    if(noat->next!=NULL)//enquanto nao for o final da lista
        print(texto, noat->next, at+1);//recursao da amostragem
}

//encerramento
void quit(FILE** arq, Lista* texto, Pilha* pundo, Pilha* predo){
    if(*arq!=NULL){//se o arquivo nao foi fechado
        fclose(*arq);//feche
        while(texto->head!=NULL){//há conteudo se o arquivo não foi salvo
            deleteHead(texto);//liberar nós
        }
    }
    while(pundo->top!=NULL)//liberar elementos
        pop(pundo);
    while(predo->top!=NULL)
        pop(predo);
    free(texto);//liberar lista
    free(pundo);//liberar pilhas
    free(predo);
}

//ajuda
void help(){
    interface();
    printf("\t| open <arquivo> – abre um arquivo de texto e carrega o conteúdo no editor\n");
    printf("\t| save <arquivo> – salva o documento atual em um arquivo texto\n");
    printf("\t| i <pos> <texto> – insere uma nova linha antes da posição <pos>\n");
    printf("\t| d <pos> – remove a linha na posição <pos>\n");
    printf("\t| r <pos> <novo texto> – substitui a linha da posição indicada\n");
    printf("\t| a <pos> <sufixo> – concatena um sufixo ao final da linha da posição indicada\n");
    printf("\t| split <pos> <idx> – divide a linha em duas, no índice indicado\n");
    printf("\t| join <pos> – une a linha <pos> com a seguinte\n");
    printf("\t| undo – desfaz a última operação de edição\n");
    printf("\t| redo – refaz a última operação desfeita\n");
    printf("\t| print – imprime todas as linhas numeradas, usando recursão\n");
    printf("\t| quit – encerra o programa, liberando toda a memória alocada dinamicamente\n");
}