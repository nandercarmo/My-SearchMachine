#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Hash.h"
/*
-> Comentários:

-> Parte de Manipulação de Arquivos

     -> TrataArquivo: Essa função trata as palavras lidas de um arquivo. Recebe por referência uma string contendo a palavra que se deseja tratar, retirando todos os caracteres não alfa-numéricos, com a exceção do hífen e do apóstrofe que serão mantidos, além de transformar todas as letras em minúsculas, para facilitar a comparação de palavras. Essa função não retorna nada.

     -> TamanhoArquivo: Essa função recebe um ponteiro para um arquivo e retorna o número de palavras contidas nesse arquivo.

     -> LeArquivo: Essa função recebe um ponteiro para um arquivo, uma matriz de caracteres e uma variável do tipo inteiro. A função realiza a leitura das palavras do arquivo e as armazena em um vetor de strings (as quais têm o tamanho variável para economia de espaço, através de alocação dinâmica). Essa função retorna um vetor de strings.

     -> IndexaArquivo: Essa função recebe como referência uma variável do tipo Hash, um arquivo, um vetor de strings e um inteiro. A função realiza a leitura palavra por palavra do arquivo recebido, trada as palavras lidas, compara com as palavras contidas no vetor de strings recebido e, caso, não esteja contida no vetor, essa palavras é então transformada em um índice da tabela Hash e inserida no Hash através da chamada de uma função que será descrita mais adiante. Essa função não retorna nada.


-> Parte de Manipulação de Listas encadeadas

     -> FazListaVazia: Essa função recebe por referência uma lista. A função cria a célula cabeça para a lista através da alocação dinâmica, faz com que o campo primeiro e ultimo da lista apontem para essa célula. Essa função não retorna nada.

     -> InsereLista: Essa função recebe como parâmetro além de um hash como referência, e a posição do vetor do hash no qual se deseja inserir a nova célula, os dados necessários para preencher uma nova célula,  realiza a inserção, após a última célula, de uma nova célula contendo as informações passadas como parâmetro na lista. Essa função não retorna nada.


-> Parte de Manipulação do Hash

     -> CriaHash: Essa função basicamente recebe um hash como referência, define o campo tamanho do hash como sendo o tamanho do vetor do hash, aloca um vetor de listas com o número de posições correto e chama a Função FazListaVazia para criar as listas referentes a cada posição do vetor. Essa função não retorna nada.

     -> InsereHash: Essa função recebe um ponteiro para um hash, a chave que se deseja inserir no hash, o indice gerado para essa chave e o número do arquivo do qual a palavra foi retirada. Primeiro o programa verifica se a lista da posição do vetor indicada pelo indice gerado do hash está vazia, caso esteja ela inicia uma nova lista, com as informações recebidas como parâmetro. Se a lista já estiver preenchida,  o programa verifica se alguma célula nessa lista possui a mesma chave que a que se deseja inserir. Em caso afirmativo o campo frequencia dessa célula é incrementado em 1 unidade. Em caso negativo é inserida uma nova célula no fim dessa lista e o campo colisoes do hash é incrementado em 1 unidade. Essa função não retorna nada.

     -> ImprimeHash: Essa função recebe como parâmetro um arquivo, onde irá realizar a impressão do hash criado, e um hash. A função percorre posição por posição do vetor e dentro dessas posições célula por célula da lista até esta ser completamente percorrida . Para cada célula é criado dois vetores auxiliares contendo em quais arquivos a palavra representada pela célula aparece e qual o peso (frequência) dessa palavra desse arquivo. Depois disso, esses dois arquivos são enviados para serem ordenados e logo depois são impressos ordenadamente no arquivo. Essa função não retorna nada.

     -> OrdenaHash: Essa função recebe por referência dois vetores e, através do método de ordenação por seleção (método escolhido por ser de fácil implementação e principalmente por ser estável) ordena os dois , baseado no vetor que representa a frequência das palavras dos arquivos. Essa função não retorna nada.

     -> PesquisaHash: Essa função recebe por referência um hash e uma string como parâmetro. Primeiro a função transforma a string em um índice. Em seguida, dentro da lista indicada pela posição do vetor refrente ao índice gerado para a string recebida, a função procura pela célula quem contém a mesma chave. Caso encontre a função, assim como a ImprimeHash cria os dois vetores auxiliares, ordena os dados em relação à frequência e imprime a palavra, seguida dos arquivos em que ela aparece, com suas respectivas frequências. Caso não encontre a função imprime uma mensagem informando que a palavra não se encontra em nenhum arquivo. Essa função não retorna nada.
*/
//-----------------------------------------------------------------------------------
//Parte de Manipulação de Arquivos
void TrataArquivo(char *palavra){

     int i;

     for (i = 0; i < 40 && palavra[i] != '\0'; i++) palavra[i] = tolower(palavra[i]);

     if (!isalnum(palavra[0])) {

          for (i = 0; i < 40 && palavra[i] != '\0'; i++) palavra[i] = palavra[i+1];
     }

     for (i = 0; i < 40 && palavra[i] != '\0'; i++) {

          if(!isalnum(palavra[i]) && ((palavra[i] != '\'' && palavra[i] != '-') || palavra[i] == ' ')){

               for (int j = i; j < 40 && palavra[j] != '\'' ; j++) {
                    palavra[j] = palavra[j+1];
               }
               i--;
          }
     }
}

int TamanhoArquivo(FILE *arquivo){


     int tamanho = 0;

     while (!feof(arquivo)) {

          char palavra[40];
          fscanf(arquivo, "%s ", palavra);
          tamanho++;
     }
     return tamanho;
}

char** LeArquivo(FILE *arquivo, char stopwords[][40], int *tamanho){

     int j;
     int aux = *tamanho;
     *tamanho = 0;
     char palavra[40];

     char **palavras = (char**)malloc(sizeof(char*));

     while (!feof(arquivo)) {

          fscanf(arquivo, "%s ", palavra);
          TrataArquivo(palavra);
          for (j = 0; j < aux; j++) {

               if (!strcmp(palavra, stopwords[j])) break;
          }

          if (j == aux) {

               palavras = (char**) realloc(palavras, (*tamanho+1)*sizeof(char*));
               palavras[*tamanho] = (char*)malloc(strlen(palavra)*sizeof(char));
               strcpy(palavras[*tamanho], palavra);
               *tamanho = *tamanho + 1;
          }
     }
     return palavras;
}

void IndexaArquivo(FILE *arquivo, char stopwords[][40], Hash *hash, int num_arquivo, int tmh_stopword){

     int j, aux = 0;
     TipoChave palavra;

     while (!feof(arquivo)) {
          fscanf(arquivo, "%s ", palavra);
          TrataArquivo(palavra);

          for (int i = 0; i < strlen(palavra); i++) if (isalnum(palavra[i])) aux = 1;
          if (aux == 0) return ;

          for (j = 0; j < tmh_stopword; j++) {

               if (!strcmp(palavra, stopwords[j]) || !strcmp(palavra, "") || !strcmp(palavra, "-")) break;
          }

          if (j == tmh_stopword) {

               TipoIndice indice;
               unsigned long soma = 0;
               for (int i = 0; i < strlen(palavra); i++) soma += (unsigned int) palavra[i] * (i+1 + soma);
               indice = (soma % TAMANHO);

               InsereHash(palavra, indice, num_arquivo, hash);
          }
     }
     return ;
}

//-----------------------------------------------------------------------------------
//Parte de Manipulação de Listas encadeadas
void FazListaVazia(TipoLista *lista){

     lista->primeiro = (Apontador) malloc(sizeof(TipoCelula));
     lista->primeiro->prox = NULL;
     lista->ultimo = lista->primeiro;
}

void InsereLista(int arquivo, int frequencia, TipoChave chave, Hash *hash, TipoIndice indice){

     Apontador celula;
     celula = (Apontador)malloc(sizeof(TipoCelula));
     strcpy(celula->item.arquivo[arquivo], "inseriu");
     celula->item.frequencia[arquivo] = 1;
     strcpy(celula->item.chave, chave);

     hash->vetor[indice].ultimo->prox = celula;
     hash->vetor[indice].ultimo = hash->vetor[indice].ultimo->prox;
     hash->vetor[indice].ultimo->prox = NULL;
}

//-----------------------------------------------------------------------------------
//Parte de Manipulação do Hash
void CriaHash(Hash *hash){

     hash->tamanho = TAMANHO;
     hash->colisoes = 0;

     hash->vetor = (TipoLista*) malloc(hash->tamanho*sizeof(TipoLista));

     for (int i = 0; i < hash->tamanho; i++) {
          FazListaVazia(&hash->vetor[i]);
     }
}

void InsereHash(TipoChave chave, TipoIndice indice, int arquivo, Hash *hash){

     if (hash->vetor[indice].primeiro->prox == NULL) {

          InsereLista(arquivo, 1, chave, hash, indice);
          return ;
     }

     Apontador aux;
     aux = hash->vetor[indice].primeiro->prox;

     while (aux != NULL)  {

          if (!strcmp(aux->item.chave, chave)) {

               if (!strcmp(aux->item.arquivo[arquivo], "inseriu")) {

                    aux->item.frequencia[arquivo] = aux->item.frequencia[arquivo] + 1;
                    return ;

               }else {

                    strcpy(aux->item.arquivo[arquivo], "inseriu");
                    aux->item.frequencia[arquivo] = 1;
                    return ;
               }
          } else aux = aux->prox;
     }

     InsereLista(arquivo, 1, chave, hash, indice);

     hash->colisoes++;
     return ;
}

void ImprimeHash(FILE *inverted_list, Hash *hash){

     for (int i = 0; i < hash->tamanho; i++) {

          Apontador aux;
          aux = hash->vetor[i].primeiro->prox;

          while (aux != NULL) {

               fprintf(inverted_list, "[%s] =>", aux->item.chave);

               int tamanho = 0;

               for (int j = 0; j < hash->tamanho; j++) {

                    if (!strcmp(aux->item.arquivo[j], "inseriu")) {

                         tamanho ++;
                    }
               }

               int arquivo[tamanho];
               int frequencia[tamanho];
               int i = 0;

               for (int j = 0; j < hash->tamanho; j++) {

                    if (!strcmp(aux->item.arquivo[j], "inseriu")) {

                         arquivo[i] = j;
                         frequencia[i] = aux->item.frequencia[j];
                         i++;
                    }
               }

               OrdenaHash(frequencia, arquivo, tamanho);

               for (int j = tamanho - 1; j >= 0; j--) {

                    fprintf(inverted_list ," (%i, %i)", arquivo[j], frequencia[j]);
               }

               fprintf(inverted_list, "\n");
          aux = aux->prox;
          }
     }
     return ;
}

void OrdenaHash(int *frequencia, int *arquivo, int tamanho){

     int j;
     int aux_arquivo;
     int aux_frequencia;

     for (int i = 1; i < tamanho; i++) {

          aux_arquivo = arquivo[i];
          aux_frequencia = frequencia[i];

          j = i - 1;

          while ((j >= 0) && aux_frequencia < frequencia[j]) {

               frequencia[j + 1] = frequencia [j];
               arquivo[j + 1] = arquivo[j];
               j--;
          }

          frequencia[j + 1] = aux_frequencia;
          arquivo[j + 1] = aux_arquivo;
     }
}

void PesquisaHash(Hash *hash, char *consulta){

     TipoIndice indice;
     unsigned long soma = 0;
     for (int i = 0; i < strlen(consulta); i++)
          soma += (unsigned int) consulta[i] * (i+1 + soma);
     indice = (soma % TAMANHO);

     Apontador aux;
     aux = hash->vetor[indice].primeiro->prox;

     while (aux != NULL) {

          if (strcpy(aux->item.chave, consulta)) {

               printf("[%s] =>", aux->item.chave);

               int tamanho = 0;
               for (int j = 0; j < hash->tamanho; j++) {

                    if (!strcmp(aux->item.arquivo[j], "inseriu")) {

                         tamanho ++;
                    }
               }

               int arquivo[tamanho];
               int frequencia[tamanho];
               int i = 0;

               for (int j = 0; j < hash->tamanho; j++) {

                    if (!strcmp(aux->item.arquivo[j], "inseriu")) {

                         arquivo[i] = j;
                         frequencia[i] = aux->item.frequencia[j];
                         i++;
                    }
               }

               OrdenaHash(frequencia, arquivo, tamanho);

               for (int j = tamanho - 1; j >= 0; j--) {

                    printf(" (%i, %i)", arquivo[j], frequencia[j]);
               }

               printf("\n");
               return ;
          }
          aux = aux->prox;
     }
     printf("%s -> Palavra não está presente!\n", consulta);
     return ;
}
