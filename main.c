#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 10
#define MAXOPR 20

// FUNCAO PARA PROCESSAR STRINGS
void processarString(char *string)
{
  // Remover espacos em branco no comeco e final
  int inicio = 0, fim;
  while (isspace(string[inicio]))
  {
    inicio++;
  };

  fim = strlen(string) - 1;
  while (isspace(string[fim]))
  {
    fim--;
  }
  int j = 0;
  for (int i = inicio; i <= fim; i++)
  {
    string[j++] = string[i];
  }
  string[j] = '\0';

  // Palavra em minusculo
  for (int i = 0; string[i] != '\0'; i++)
  {
    string[i] = tolower(string[i]);
  }

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

typedef struct Operacao
{
  Pessoa *copiaOldDados;
  Pessoa *pessoaQueEra;
  int tipoOperacao;
} Operacao;

typedef struct PilhaOperacoes
{
  Operacao *operacao[MAXOPR];
  int topo;
} PilhaOperacoes;
PilhaOperacoes *raizPilhaOp;
PilhaOperacoes *raizPilhaDesfeita;

Pessoa *criarNoPessoa()
{
  Pessoa *pessoaPtr = malloc(sizeof(Pessoa));
  if (pessoaPtr != NULL)
  {
    pessoaPtr->nome[0] = '\0';
    pessoaPtr->Pai = NULL;
    pessoaPtr->Mae = NULL;
    pessoaPtr->irmaos = NULL;
  }
  return pessoaPtr;
}

void criarAcao(Pessoa *pessoa, int tipoOp)
{

  if (raizPilhaOp->topo >= MAXOPR - 1)
  {
    printf("\nPilha de operacoes lotou");
    return;
  }

  raizPilhaOp->topo++;
  int topo = raizPilhaOp->topo;

  raizPilhaOp->operacao[topo] = malloc(sizeof(Operacao));

  raizPilhaOp->operacao[topo]->tipoOperacao = tipoOp;

  raizPilhaOp->operacao[topo]->copiaOldDados = criarNoPessoa();
  memcpy(raizPilhaOp->operacao[topo]->copiaOldDados, pessoa, sizeof(Pessoa));

  raizPilhaOp->operacao[topo]->pessoaQueEra = pessoa;
}
void desfazerAcao()
{
  if (raizPilhaOp->topo == -1)
  {
    printf("\nNao tem operacao pra ser desfeita");
    return;
  }
  int tipoOp = raizPilhaOp->operacao[raizPilhaOp->topo]->tipoOperacao;
  int topo = raizPilhaOp->topo;
  switch (tipoOp)
  {
  case 1:
    printf("\nPessoa ' %s ' retornada para ' %s '", raizPilhaOp->operacao[topo]->pessoaQueEra->nome, raizPilhaOp->operacao[topo]->copiaOldDados->nome);
    memcpy(raizPilhaOp->operacao[topo]->pessoaQueEra, raizPilhaOp->operacao[topo]->copiaOldDados, sizeof(Pessoa));

    if (raizPilhaOp->operacao[topo]->pessoaQueEra->Pai != NULL)
    {
      strcpy(raizPilhaOp->operacao[topo]->pessoaQueEra->Pai->nome, raizPilhaOp->operacao[topo]->copiaOldDados->Pai->nome);
    }

    if (raizPilhaOp->operacao[topo]->pessoaQueEra->Mae != NULL)
    {
      strcpy(raizPilhaOp->operacao[topo]->pessoaQueEra->Mae->nome, raizPilhaOp->operacao[topo]->copiaOldDados->Mae->nome);
    }

    break;

  default:
    break;
  }
  raizPilhaOp->topo--;
}

Pessoa *buscarPessoaEspecifica(Pessoa *raiz, char nomeBusca[49], int mostrarDados)
{
  if (raiz == NULL)
  {
    return NULL;
  }
  Pessoa *raizPtr = raiz;

  if (!strcmp(raizPtr->nome, nomeBusca))
  {
    if (mostrarDados)
    {
      printf("\n\nPessoa: %s", raizPtr->nome);
      printf("\nPai-> %s", (raizPtr->Pai != NULL) ? raizPtr->Pai->nome : "//Sem dados");
      printf("\nMae-> %s", (raizPtr->Mae != NULL) ? raizPtr->Mae->nome : "//Sem dados");

      if (raizPtr->irmaos != NULL && raizPtr->irmaos->front != -1)
      {
        printf("\nIrmaos-> ");
        for (int i = 0; i <= raizPtr->irmaos->rear; i++)
        {
          printf("%s, ", raizPtr->irmaos->nomeIrmao[i]);
        }
      }
    }
    return raizPtr;
  }

  // Busca especifica pelas listas de irmaos tambem
  if (raizPtr->irmaos != NULL && raizPtr->irmaos->front != -1)
  {
    for (int i = 0; i <= raizPtr->irmaos->rear; i++)
    {
      if (!strcmp(raizPtr->irmaos->nomeIrmao[i], nomeBusca))
      {
        if (mostrarDados)
        {
          printf("\n\nPessoa: %s", raizPtr->irmaos->nomeIrmao[i]);
          printf("\nPai-> %s", (raizPtr->Pai != NULL) ? raizPtr->Pai->nome : "//Sem dados");
          printf("\nMae-> %s", (raizPtr->Mae != NULL) ? raizPtr->Mae->nome : "//Sem dados");
          printf("\nIrmaos-> ");
          printf("%s", raizPtr->nome);

          for (int j = 0; j <= raizPtr->irmaos->rear; j++)
          {
            if (i != j)
            {
              printf(", %s", raizPtr->irmaos->nomeIrmao[j]);
            }
          }
        }
        return raizPtr;
      }
    }
  }

  Pessoa *resultadoPai = NULL;
  Pessoa *resultadoMae = NULL;

  if (raiz->Pai != NULL)
  {
    resultadoPai = buscarPessoaEspecifica(raizPtr->Pai, nomeBusca, mostrarDados);
  }
  if (raiz->Mae != NULL)
  {
    resultadoMae = buscarPessoaEspecifica(raizPtr->Mae, nomeBusca, mostrarDados);
  }

  // Retorna a pessoa certa
  if (resultadoPai != NULL)
  {
    return resultadoPai;
  }
  else if (resultadoMae != NULL)
  {
    return resultadoMae;
  }
  else
  {
    return NULL;
  }
}

void adicionarPessoa(Pessoa *pessoa, int cadastrouPrimeira)
{
  criarAcao(pessoa, 1);
  if (!cadastrouPrimeira)
  {
    printf("\nDigite o nome da pessoa: ");
    fgets(pessoa->nome, 50, stdin);
    processarString(pessoa->nome);
  }

  // ADICIONAR PAI E MAE
  if (pessoa->Pai == NULL)
  {
    pessoa->Pai = criarNoPessoa();
    printf("\nDigite o nome do pai: ");
    fgets(pessoa->Pai->nome, 50, stdin);
    processarString(pessoa->Pai->nome);
  }
  if (pessoa->Mae == NULL)
  {
    pessoa->Mae = criarNoPessoa();
    printf("\nDigite o nome da mae: ");
    fgets(pessoa->Mae->nome, 50, stdin);
    processarString(pessoa->Mae->nome);
  }

  // ADICIONAR IRMAOS (FILA)
  if (pessoa->irmaos == NULL)
  {
    pessoa->irmaos = malloc(sizeof(filaIrmaos));
    filaIrmaos *IrmaoPtr = pessoa->irmaos;
    IrmaoPtr->front = -1;
    IrmaoPtr->rear = -1;
    int saida = 1;
    for (int i = 0; i < TAM; i++)
    {
      printf("\n0 - Pular\n1 - Adicionar irmao: ");
      scanf("%d", &saida);
      getchar();
      if (saida == 0)
      {
        break;
      }

      printf("\nNome do %d° irmao: ", i + 1);
      fgets(IrmaoPtr->nomeIrmao[i], 50, stdin);
      processarString(IrmaoPtr->nomeIrmao[i]);

      IrmaoPtr->front = 0;
      IrmaoPtr->rear = i;
    }
  }
}
void editarPessoa(Pessoa *pessoa)
{
  criarAcao(pessoa, 1);
  if (pessoa == NULL)
  {
    printf("\n<-- Pessoa nao encontrada -->");
    return;
  }
  criarAcao(pessoa, 1);
  int escolha = 0;
  Pessoa *pessoaPtr = pessoa;

  printf("\nEditar o atual nome de ' %s ' ? (1- Sim / 0- Pular): ", pessoaPtr->nome);
  scanf("%d", &escolha);
  if (escolha)
  {
    getchar();
    printf("\nNovo nome: ");
    fgets(pessoaPtr->nome, 50, stdin);
    processarString(pessoaPtr->nome);
  }

  if (pessoaPtr->Pai != NULL)
  {
    printf("\nEditar o atual nome ' %s ' do pai? (1- Sim / 0- Pular): ", pessoaPtr->Pai->nome);
    scanf("%d", &escolha);
    if (escolha)
    {
      getchar();
      printf("\nNovo nome: ");
      fgets(pessoaPtr->Pai->nome, 50, stdin);
      processarString(pessoaPtr->Pai->nome);
    }
  }

  if (pessoaPtr->Mae != NULL)
  {
    printf("\nEditar o atual nome ' %s ' da mae? (1- Sim / 0- Pular): ", pessoaPtr->Mae->nome);
    scanf("%d", &escolha);
    if (escolha)
    {
      getchar();
      printf("\nNovo nome: ");
      fgets(pessoaPtr->Mae->nome, 50, stdin);
      processarString(pessoaPtr->Mae->nome);
    }
  }

  if (pessoaPtr->irmaos != NULL && pessoaPtr->irmaos->front != -1)
  {
    if (pessoaPtr->irmaos != NULL && pessoaPtr->irmaos->front != -1)
    {
      for (int i = 0; i <= pessoaPtr->irmaos->rear; i++)
      {
        printf("\n%d- %s", i + 1, pessoaPtr->irmaos->nomeIrmao[i]);
      }
      printf("\nEditar o nome de algum irmao? ([1...10]- Escolher o Irmao / 0- Pular): ");
      scanf("%d", &escolha);
      escolha--;
      if (escolha > 0 && escolha <= 10)
      {
        getchar();
        printf("\nNovo nome: ");
        fgets(pessoaPtr->irmaos->nomeIrmao[escolha], 50, stdin);
        processarString(pessoaPtr->irmaos->nomeIrmao[escolha]);
      }
    }
  }
}
void excluirPessoa(Pessoa *pessoa)
{
  if (raizPilhaOp->topo >= MAXOPR - 1)
  {
    printf("\n<-- Limite de Historico de operacoes atingifo -->");
    return;
  }
  if (pessoa == NULL)
  {
    printf("\n<-- Pessoa nao encontrada -->");
    return;
  }

  pessoa->Pai = NULL;
  pessoa->Mae = NULL;
  pessoa->irmaos = NULL;
  pessoa->nome[0] = '\0';
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

void imprimirArvore(Pessoa *raiz)
{
  if (raiz == NULL)
  {
    return;
  }

  Pessoa *pessoaAtual;
  filaIrmaos *fila = NULL;

  while (raiz != NULL || fila != NULL)
  {
    while (raiz != NULL)
    {
      printf("\n\n(%s", raiz->nome);

      fila = raiz->irmaos;
      if (fila != NULL && fila->front != -1)
      {
        for (int i = 0; i <= fila->rear; i++)
        {
          printf(", %s", fila->nomeIrmao[i]);
        }
      }
      printf(")");

      if (raiz->Pai != NULL)
      {
        printf("\nPai-> %s", raiz->Pai->nome);
      }
      if (raiz->Mae != NULL)
      {
        printf("\nMae-> %s", raiz->Mae->nome);
      }

      if (raiz->Pai != NULL)
      {
        imprimirArvore(raiz->Pai);
      }

      raiz = raiz->Mae;
    }

    if (fila != NULL)
    {
      if (fila->front != -1)
      {
        raiz = raiz;
      }
      else
      {
        raiz = NULL;
      }
      fila = NULL;
    }
  }
}
void miniImprimirArvore(Pessoa *Pessoa)
{
  if (Pessoa == NULL)
  {
    return;
  }

  // MINI IMPRIMIR FILHOS E IRMAOS
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

  // MINIIMPRIMIR PAI E MAE
  if (Pessoa->Pai != NULL)
  {
    printf("-> Pai: %s;", Pessoa->Pai->nome);
  }
  if (Pessoa->Mae != NULL)
  {
    printf(" Mae: %s", Pessoa->Mae->nome);
  }
  imprimirArvore(Pessoa->Pai);
  imprimirArvore(Pessoa->Mae);
}

int main()
{
  int menu = 0;
  int cadastrouPrimeira = 0;
  char nomeBusca[50];
  Pessoa *raiz = criarNoPessoa();
  raizPilhaOp = malloc(sizeof(PilhaOperacoes));
  raizPilhaOp->topo = -1;
  raizPilhaDesfeita = malloc(sizeof(PilhaOperacoes));
  raizPilhaDesfeita->topo = -1;

  while (menu != 1)
  {

    printf("\n\n_________MENU_________");
    printf("\n1 - Sair");
    printf("\n2 - Adicionar Pessoa");
    printf("\n3 - Imprimir Arvore Genealogica");
    printf("\n4 - BUSCAR Dados Pessoa Especifica");
    printf("\n5 - EDITAR Dados/Parentes Pessoa Especifica");
    printf("\n6 - EXCLUIR Dados Pessoa Especifica");
    if (cadastrouPrimeira && raiz->nome[0] != '\0')
    {
      printf("\n\n8 - Desfazer Acao <-");
      printf("\n9 - Refazer Acao  ->");
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
      getchar();
      if (!cadastrouPrimeira)
      {
        adicionarPessoa(raiz, cadastrouPrimeira);
      }
      else
      {
        printf("\nInsira o nome da pessoa para buscar e adicionar parentes: ");
        fgets(nomeBusca, 50, stdin);
        processarString(nomeBusca);
        adicionarPessoa(buscarPessoaEspecifica(raiz, nomeBusca, 0), cadastrouPrimeira);
      }
      cadastrouPrimeira = 1;
      break;
    case 3:
      imprimirArvore(raiz);
      break;
    case 4:
      getchar();
      printf("\nInsira o nome da pessoa para busca: ");
      fgets(nomeBusca, 50, stdin);
      processarString(nomeBusca);
      buscarPessoaEspecifica(raiz, nomeBusca, 1);
      break;
    case 5:
      getchar();
      printf("\nInsira o nome da pessoa para editar: ");
      fgets(nomeBusca, 50, stdin);
      processarString(nomeBusca);
      editarPessoa(buscarPessoaEspecifica(raiz, nomeBusca, 0));
      break;
    case 6:
      getchar();
      printf("\nInsira o nome da pessoa para excluir: ");
      fgets(nomeBusca, 50, stdin);
      processarString(nomeBusca);
      excluirPessoa(buscarPessoaEspecifica(raiz, nomeBusca, 0));
      break;
    case 8:
      desfazerAcao();
      break;
    case 9:
      // refazerAcao();
      miniImprimirArvore(raiz);
      break;
    case 10:
      getchar();
      adicionarPessoa(encontrarUltimoNomePai(raiz), cadastrouPrimeira);
      break;
    case 11:
      getchar();
      adicionarPessoa(encontrarUltimoNomeMae(raiz), cadastrouPrimeira);
      break;
    case 12:
      strcpy(raiz->nome, "Alison Pereira");
      processarString(raiz->nome);
      raiz->Pai = criarNoPessoa();
      strcpy(raiz->Pai->nome, "Antonio Silva");
      processarString(raiz->Pai->nome);
      raiz->Mae = criarNoPessoa();
      strcpy(raiz->Mae->nome, "Maria Silva");
      processarString(raiz->Mae->nome);
      cadastrouPrimeira = 1;
      break;
    default:
      printf("Opcao invalida\n");
      break;
    };
  }
}