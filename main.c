#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 10

// FUNCAO PARA PROCESSAR STRINGS
void processarString(char *string)
{
  int i, j = 0;

  // Tirar espaco em branco
  for (i = 0; string[i] != '\0'; i++)
  {
    if (!isspace(string[i]))
    {
      string[j++] = string[i];
    }
  }
  string[j] = '\0';

  // Primeira Letra Maiscula
  string[0] = toupper(string[0]);
}

typedef struct filaIrmaos
{
  char nomeIrmao[TAM][50];
  int front;
  int rear;
} filaIrmaos;
typedef struct Pessoa
{
  char nome[50];
  struct Pessoa *Pai;
  struct Pessoa *Mae;
  struct filaIrmaos *irmaos;
} Pessoa;

Pessoa *criarNoPessoa()
{
  Pessoa *pessoaPtr = malloc(sizeof(Pessoa));
  pessoaPtr->Pai = NULL;
  pessoaPtr->Mae = NULL;
  pessoaPtr->irmaos = NULL;
}

Pessoa *adicionarPessoa(Pessoa *pessoa, int cadastrouPrimeira)
{
  if (!cadastrouPrimeira)
  {
    printf("\nDigite o nome da pessoa: ");
    scanf(" %s", pessoa->nome);
    processarString(pessoa->nome);
  }

  // ADICIONAR PAI E MAE
  pessoa->Pai = criarNoPessoa();
  Pessoa *paiPtr = pessoa->Pai;

  printf("\nDigite o nome do pai: ");
  scanf(" %s", paiPtr->nome);
  processarString(paiPtr->nome);

  pessoa->Mae = criarNoPessoa();
  Pessoa *maePtr = pessoa->Mae;

  printf("\nDigite o nome da mae: ");
  scanf(" %s", maePtr->nome);
  processarString(maePtr->nome);

  // ADICIONAR IRMAOS (FILA)
  pessoa->irmaos = malloc(sizeof(filaIrmaos));
  filaIrmaos *IrmaoPtr = pessoa->irmaos;
  IrmaoPtr->front = -1;
  IrmaoPtr->rear = -1;
  int saida = 1;
  for (int i = 0; i < TAM; i++)
  {
    printf("\n0 - Pular\n1 - Adicionar irmao: ");
    scanf("%d", &saida);
    if (saida == 0)
    {
      break;
    }

    printf("\nNome do %d° irmao: ", i + 1);
    scanf(" %s", IrmaoPtr->nomeIrmao[i]);
    processarString(IrmaoPtr->nomeIrmao[i]);

    IrmaoPtr->front = 0;
    IrmaoPtr->rear = i;
  }
  return pessoa;
}

Pessoa *encontrarUltimoNomePai(Pessoa *raiz)
{
  if (raiz == NULL)
  {
    return NULL;
  }

  while (raiz->Pai != NULL)
  {
    raiz = raiz->Pai;
  }

  return raiz;
}
Pessoa *encontrarUltimoNomeMae(Pessoa *raiz)
{
  if (raiz == NULL)
  {
    return NULL;
  }

  while (raiz->Mae != NULL)
  {
    raiz = raiz->Mae;
  }

  return raiz;
}

void imprimirArvore(Pessoa *Pessoa)
{
  if (Pessoa == NULL)
  {
    return;
  }

  // IMPRIMIR FILHOS E IRMAOS

  printf("\n\n(%s", Pessoa->nome);

  filaIrmaos *irmaos = Pessoa->irmaos;
  if (irmaos != NULL && irmaos->front != -1)
  {
    for (int i = 0; i <= irmaos->rear; i++)
    {
      printf(", %s", irmaos->nomeIrmao[i]);
    }
  }
  printf(")");

  // IMPRIMIR PAI E MAE
  if (Pessoa->Pai != NULL)
  {
    printf("\nPai-> %s", Pessoa->Pai->nome);
  }
  if (Pessoa->Mae != NULL)
  {
    printf("\nMae-> %s", Pessoa->Mae->nome);
  }
  imprimirArvore(Pessoa->Pai);
  imprimirArvore(Pessoa->Mae);
}

int main()
{
  int menu = 0;
  int cadastrouPrimeira = 0;
  Pessoa *raiz = criarNoPessoa();
  while (menu != 1)
  {
    printf("\n\n_________MENU_________");
    printf("\n1 - Sair");
    printf("\n2 - Adicionar Pessoa");
    printf("\n3 - Imprimir Arvore Genealógica");
    printf("\n3 - Buscar Pessoa Especifica");
    if (cadastrouPrimeira)
    {
      printf("\n\n-- Recomendações --");
      printf("\n10 - Acrescentar antecedentes de (%s)", encontrarUltimoNomePai(raiz)->nome);
      printf("\n11 - Acrescentar antecedentes de (%s)", encontrarUltimoNomeMae(raiz)->nome);
    }

    printf("\nDigite a opcao: ");
    scanf("%d", &menu);
    switch (menu)
    {
    case 1:
      menu = 1;
      break;
    case 2:
      adicionarPessoa(raiz, cadastrouPrimeira);
      cadastrouPrimeira = 1;
      break;
    case 3:
      imprimirArvore(raiz);
      break;
    case 4:
      char nomeBusca[50];

      break;
    case 10:
      adicionarPessoa(encontrarUltimoNomePai(raiz), cadastrouPrimeira);
      break;
    case 11:
      adicionarPessoa(encontrarUltimoNomeMae(raiz), cadastrouPrimeira);
      break;

    default:
      printf("Opcao invalida\n");
      break;
    };
  }
}