#include <stdio.h>
#include <stdlib.h>

#define TAM 10

typedef struct Pessoa
{
  char nome[50];
  struct Pessoa *Pai;
  struct Pessoa *Mae;
  struct filaIrmaos *irmaos;
} Pessoa;

typedef struct filaIrmaos
{
  char nomeIrmao[TAM][50];
  int front;
  int rear;
} filaIrmaos;

Pessoa *criarNoPessoa()
{
  Pessoa *pessoaPtr = malloc(sizeof(Pessoa));
  pessoaPtr->Pai = NULL;
  pessoaPtr->Mae = NULL;
  pessoaPtr->irmaos = NULL;
}

Pessoa *adicionarPessoa(Pessoa *Pessoa)
{

  printf("\nDigite o nome da pessoa: ");
  scanf(" %s", Pessoa->nome);

  // ADICIONAR FILA IRMAOS
  Pessoa->irmaos = malloc(sizeof(filaIrmaos));
  filaIrmaos *IrmaoPtr = Pessoa->irmaos;
  IrmaoPtr->front = -1;
  IrmaoPtr->rear = -1;
  int saida = 1;
  for (int i = 0; i < TAM; i++)
  {
    printf("\n0 - Pular\n1 - Adicionar irmão: ");
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
  return Pessoa;
}

void imprimirArvore(Pessoa *Pessoa)
{
  if (Pessoa == NULL)
  {
    printf("\n<vazio>");
    return;
  }

  // IMPRIMIR FILHOS E IRMAOS
  printf("\nFilho(s): (%s", Pessoa->nome);

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
  printf("\nPai-> %s", Pessoa->Pai);
  imprimirArvore(Pessoa->Pai);
  printf("\nMae-> %s", Pessoa->Mae);
  imprimirArvore(Pessoa->Mae);
}

int main()
{
  int menu = 0;
  Pessoa *raiz = criarNoPessoa();
  while (menu != 1)
  {
    printf("\n1 - Sair");
    printf("\n2 - Adicionar Pessoa");
    printf("\n3 - Imprimir Arvore Genealógica");
    printf("\n4 - Associar");
    printf("\nDigite a opcao: ");
    scanf("%d", &menu);
    switch (menu)
    {
    case 1:
      menu = 1;
      break;
    case 2:
      adicionarPessoa(raiz);
      break;
    case 3:
      imprimirArvore(raiz);
      break;
    default:
      printf("Opcao invalida\n");
      break;
    };
  }
}