#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Hash.h"
/*
-> Comentários:

     -> main: A função recebe como parâmetro o arquivo de consulta e um contendo as palavras que devem ser desconsideradas na construção do hash. Em seguida ela chama a funsão TamanhoArquivo para descobrir quantas palavras tem no arquivo de stopwords e inclui as palavras contidas nesse arquivo em uma matriz. Na sequência é criada uma variável Hash, que é passada como referência para a função Indexador, que irá realizar a confecção do Hash e do arquivo de índice invertido. Após a criação do Hash é impresso na tela o número de colisões que ocorreram na criação do Hash. Por fim a função realiza a leitura do arquivo de consulta através da função LeArquivo, que retorna um vetor de strings contendo as palavras que serão pesquisadas. Na sequência a função Processador  é chamada para fazer a pesquisa no Hash das palavras de consulta e a impressão da saída. O tempo de execução dessa função é medido e impresso na tela. Essa função não retorna nada.

     -> Indexador: Essa função recebe como parâmetro um arquivo, um hash e uma matriz. A função realiza a leitura de todos os arquivos cujo nome sejam apenas algoritmos presentes na pasta corpus um a um. Para cada palavra lida de cada um desses arquivos a função chama a IndexaArquivo que irá adicionar a palavra caso seja necessário e possível no hash. Isso é feito para todos os arquivos da pasta. Por fim a função ImprimeHash é chamda para imprimir no arquivo inverted_list.txt, também presente na pasta corpus.

     -> Processador: Essa função recebe como parâmetro o hash, um vetor de strings e um inteiro que representa o número de palavras que serão pesquisadas. Dentro de um loop então, a função chama para cada palavra de consulta a função PesquisaHash. Essa função não retorna nada.
*/

//Declaração das Funções
void main(int argc, char const*[]);
void Indexador(FILE*, Hash*, char[][40], int);
void Processador(Hash*, char**, int);
//-------------------------------------------------------------------------------------

void main(int argc, char const *argv[]) {

     int tmh_stopword, num_pesquisa;
     FILE *stopwords;
     FILE *consulta;
     FILE *inverted_list;

     stopwords = fopen (argv[2],"r");
     if (stopwords!=NULL)
     {
          tmh_stopword = TamanhoArquivo(stopwords);
          char stpwds[tmh_stopword][40];
          int i = 0;

          fseek(stopwords, 0, SEEK_SET);
          while (!feof(stopwords)) {

               fscanf(stopwords,"%s ", stpwds[i]);
               i++;
          }
          fclose (stopwords);

          Hash hash;
          Indexador(inverted_list, &hash, stpwds, tmh_stopword);
          printf("Colisões: %lu\n", hash.colisoes);

          consulta = fopen (argv[1],"r");
          if (consulta!=NULL)
          {
               num_pesquisa = tmh_stopword;
               char **pesquisa;
               pesquisa = LeArquivo(consulta, stpwds, &num_pesquisa);

               clock_t tempo;
               tempo = clock();

               Processador(&hash, pesquisa, num_pesquisa);

               tempo = clock() - tempo;
               double time_taken = ((double) tempo) / CLOCKS_PER_SEC;
               printf("Pesquisa demorou %f segundos para execução\n", time_taken);

               fclose (consulta);

          }else printf("ERRO AO ABRIR ARQUIVO DE CONSULTA\n");
     } else printf("ERRO AO ABRIR ARQUIVO DE STOPWORDS\n");

     return ;
}


void Indexador(FILE *inverted_list, Hash *hash, char stpwds[][40], int tmh_stopword){

     inverted_list = fopen("corpus/inverted_list.txt", "w");
     CriaHash(hash);

     int aux=0;

     for (int i = 1; aux == 0; i++) {

          char string[15] = "corpus/";
          char c[5];
          sprintf(c, "%i", i);
          strcat(string, c);

          FILE *arquivo;
          arquivo = fopen (string,"r");

          if (arquivo!=NULL)
          {
               IndexaArquivo(arquivo, stpwds, hash, i, tmh_stopword);
               fclose (arquivo);
          } else aux = 1;
     }

     ImprimeHash(inverted_list, hash);

     fclose(inverted_list);
     return ;
}


void Processador(Hash *hash, char **consulta, int num_pesquisa){

     for (int i = 0; i < num_pesquisa; i++) {
          PesquisaHash(hash, consulta[i]);
     }
     return ;
}
