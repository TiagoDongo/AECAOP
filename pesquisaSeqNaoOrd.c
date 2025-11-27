//Pesquisa Sequencial-Nao Ordenada

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STR 50

// Imprime um array de strings
void print_array(char* v[], int n)
{
  for (int i=0; i<n ; i++)
    printf("%2d: %s\n", i+1, v[i]);
}

// Algoritmo Pesquisa Sequencial numa lista nao ordenada aplicado a um array de n strings
int pesquisaSequencial(char* v[],int n,char* procurado){
    for(int i=0;i<n;i++){
        if(strcmp(v[i],procurado)==0){
            return i;
        }
    }
    return -1;
}

// Aloca memória para um vetor de n_strings ponteiros para char,
// e para cada ponteiro aloca espaço para MAX_STR caracteres
char **criar_array_nomes(int n_strings)
{
  char ** arr = (char**) malloc(sizeof(char*) * n_strings);
  if (arr==NULL) return NULL;

  for (int i=0; i<n_strings; i++)
  {
    arr[i] = (char*) malloc(MAX_STR);
    if (arr[i]==NULL) return NULL;
  }

  return arr;
}

int main()
{
  FILE *fp;

  clock_t ini, fim;
  char **nomes; // Futuro array de nomes

  const char * ficheiro = "words.txt";

  // Tenta abrir o ficheiro
   if ((fp = fopen("words.txt", "rt")) == NULL)
  {
    fprintf(stderr, "Impossível abrir o ficheiro: %s\n", ficheiro);
    return 1;
  }

  int n_nomes;
  char aux[MAX_STR];

  // Lê a primeira linha do ficheiro, converte em inteiro e guarda em 'n_nomes'.
  // Se não for um número válido (resultado 0), mostra erro e termina.
  if ((n_nomes = atoi(fgets(aux, MAX_STR, fp)))==0)
  {
    fprintf(stderr, "A primeira linha do ficheiro não contém o número de linhas que o ficheiro contém.\n");
    return 2;
  }

  // Criar o array com referências para futuras strings
  if ((nomes = criar_array_nomes(n_nomes))==NULL)
  {
    fprintf(stderr, "Impossível criar a memória necessária.\n");
    return 3;
  }

  // Lê cada linha do ficheiro para 'nomes[i]' e remove o '\n' final,
  // mantendo o terminador '\0'
  for (int i=0; i<n_nomes; i++)
    if (fgets(nomes[i], MAX_STR, fp)!=NULL)
      if (nomes[i][strlen(nomes[i])-1]<' ')
        nomes[i][strlen(nomes[i])-1]='\0';

  // Regista o tempo antes e depois da pesquisa para medir a duração da ordenação
  ini = clock();
  char procurado[100];
  printf("Digite um nome para procurar: ");
  scanf("%s",procurado);

  puts("Searching: start . . .");
  int resPesq = pesquisaSequencial(nomes,n_nomes,procurado);
  puts("Searching: done!");
  fim = clock();

  if(resPesq == -1){
    printf("A palavra nao foi encontrada!\n");
    // Calcula e imprime o tempo total gasto na pesquisa em segundos
    printf("%d procura da string foi feita em %.2lf segundos\n", n_nomes, ((double)fim-ini)/CLOCKS_PER_SEC);

    return 0;
  }

  printf("A palavra foi encontrada!\n");
  // Calcula e imprime o tempo total gasto na ordenação em segundos
  printf("%d procura da string foi feita em %.2lf segundos\n", n_nomes, ((double)fim-ini)/CLOCKS_PER_SEC);

  return 0;
}


