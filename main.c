#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10

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
  }

  // ADICIONAR PAI E MAE
  pessoa->Pai = criarNoPessoa();
  Pessoa *paiPtr = pessoa->Pai;

  printf("\nDigite o nome do pai: ");
  scanf(" %s", paiPtr->nome);

  pessoa->Mae = criarNoPessoa();
  Pessoa *maePtr = pessoa->Mae;

  printf("\nDigite o nome da mae: ");
  scanf(" %s", maePtr->nome);

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

  return raiz->nome;
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

  return raiz->nome;
}

void imprimirArvore(Pessoa *Pessoa)
{
  if (Pessoa == NULL)
  {
    return;
  }

  // IMPRIMIR FILHOS E IRMAOS

  printf("\n(%s", Pessoa->nome);

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
    if (cadastrouPrimeira)
    {
      printf("\n\n-- Recomendações --");
      printf("\n8 - Acrescentar antecedentes de (%s)", encontrarUltimoNomePai(raiz));
      printf("\n9 - Acrescentar antecedentes de (%s)", encontrarUltimoNomeMae(raiz));
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
    case 8:
      adicionarPessoa(encontrarUltimoNomePai(raiz), cadastrouPrimeira);
      break;
    case 9:
      adicionarPessoa(encontrarUltimoNomeMae(raiz), cadastrouPrimeira);
      break;
    default:
      printf("Opcao invalida\n");
      break;
    };
  }
}