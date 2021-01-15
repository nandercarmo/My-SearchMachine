#ifndef MAQUINABUSCA_H_INCLUDED
#define  MAQUINABUSCA_H_INCLUDED

#define TAMANHO 55001

//definição dos TAD's

//--------------------------------------------------------------------------------------
//Definição do Hash
typedef char TipoChave[100];
typedef unsigned long TipoIndice;
typedef struct Item_str TipoItem;
typedef struct Celula_str *Apontador;
typedef struct Celula_str TipoCelula;
typedef struct Lista_str TipoLista;
typedef struct Hash_str Hash;

     typedef struct Item_str {
          TipoChave chave;
          int frequencia[TAMANHO];
          char arquivo[TAMANHO][10];
     } TipoItem;

    struct Celula_str {
        Apontador prox;
        TipoItem item;
     };

    struct Lista_str {
        Apontador primeiro;
        Apontador ultimo;
     };

    struct Hash_str {
         TipoLista *vetor;
         unsigned long colisoes;
         int tamanho;
     };
//--------------------------------------------------------------------------------------
//Funções de Manipulação de Arquivo
void TrataArquivo(char*);
int TamanhoArquivo(FILE*);
char** LeArquivo(FILE*, char[][40], int*);
void IndexaArquivo(FILE*, char[][40], Hash*, int, int);
//--------------------------------------------------------------------------------------
//Funções de Manipulação de Listas
void FazListaVazia(TipoLista*);
void InsereLista(int, int, TipoChave, Hash*, TipoIndice);
//--------------------------------------------------------------------------------------
//Funções de Manipulação do Hash
void CriaHash(Hash*);
void InsereHash(TipoChave, TipoIndice, int, Hash*);
void ImprimeHash(FILE*, Hash*);
void OrdenaHash(int*, int*, int);
void PesquisaHash(Hash*, char*);


#endif
