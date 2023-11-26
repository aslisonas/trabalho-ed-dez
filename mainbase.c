#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pessoa
{
  char nome[50];
  struct Pessoa *pai;
  struct Pessoa *mae;
  struct Pessoa *prox_irmao;
} Pessoa;

typedef struct FilaIrmaos
{
  Pessoa *primeiro;
  Pessoa *ultimo;
} FilaIrmaos;

typedef struct PilhaOperacoes
{
  int tipo; // 1 para inserção, 2 para remoção
  Pessoa *pessoa;
  struct PilhaOperacoes *anterior;
} PilhaOperacoes;

Pessoa *criar_pessoa(char *nome, Pessoa *pai, Pessoa *mae)
{
  Pessoa *nova_pessoa = (Pessoa *)malloc(sizeof(Pessoa));
  strcpy(nova_pessoa->nome, nome);
  nova_pessoa->pai = pai;
  nova_pessoa->mae = mae;
  nova_pessoa->prox_irmao = NULL;
  return nova_pessoa;
}

void inserir_na_fila(FilaIrmaos *fila, Pessoa *pessoa)
{
  if (fila->primeiro == NULL)
  {
    fila->primeiro = pessoa;
  }
  else
  {
    fila->ultimo->prox_irmao = pessoa;
  }
  fila->ultimo = pessoa;
}

Pessoa *buscar(Pessoa *raiz, char *nome)
{
  if (raiz == NULL)
  {
    return NULL;
  }
  if (strcmp(raiz->nome, nome) == 0)
  {
    return raiz;
  }
  Pessoa *encontrado = buscar(raiz->pai, nome);
  if (encontrado)
  {
    return encontrado;
  }
  encontrado = buscar(raiz->mae, nome);
  if (encontrado)
  {
    return encontrado;
  }
  Pessoa *irmao_atual = raiz->prox_irmao;
  while (irmao_atual)
  {
    encontrado = buscar(irmao_atual, nome);
    if (encontrado)
    {
      return encontrado;
    }
    irmao_atual = irmao_atual->prox_irmao;
  }
  return NULL;
}

PilhaOperacoes *empilhar_operacao(PilhaOperacoes **pilha, int tipo, Pessoa *pessoa)
{
  PilhaOperacoes *nova_operacao = (PilhaOperacoes *)malloc(sizeof(PilhaOperacoes));
  nova_operacao->tipo = tipo;
  nova_operacao->pessoa = pessoa;
  nova_operacao->anterior = *pilha;
  *pilha = nova_operacao;
  return nova_operacao;
}

void imprimir_arvore(Pessoa *raiz, int nivel)
{
  if (raiz == NULL)
    return;

  for (int i = 0; i < nivel; ++i)
    printf("  ");
  printf("%s\n", raiz->nome);

  imprimir_arvore(raiz->pai, nivel + 1);
  imprimir_arvore(raiz->mae, nivel + 1);

  // Print siblings
  Pessoa *irmao_atual = raiz->prox_irmao;
  while (irmao_atual)
  {
    imprimir_arvore(irmao_atual, nivel + 1); // Increased the level for siblings
    irmao_atual = irmao_atual->prox_irmao;
  }
}

void menu()
{
  printf("Menu:\n");
  printf("1 - Inserir Pessoa\n");
  printf("2 - Remover Pessoa\n");
  printf("3 - Imprimir Árvore Genealógica\n");
  printf("4 - Buscar Pessoa\n");
  printf("5 - Desfazer Operação\n");
  printf("6 - Refazer Operação\n");
  printf("7 - Sair\n");
  printf("Escolha uma opção: ");
}

int main()
{
  Pessoa *raiz = NULL;
  FilaIrmaos *fila_irmaos = (FilaIrmaos *)malloc(sizeof(FilaIrmaos));
  fila_irmaos->primeiro = fila_irmaos->ultimo = NULL;
  PilhaOperacoes *pilha_operacoes = NULL;
  char nome[50];
  int opcao;

  while (1)
  {
    menu();
    scanf("%d", &opcao);

    switch (opcao)
    {
      // Inside the main switch cases

    case 1:
    {
      // Logic to insert a person
      char nome[50];
      char nome_pai[50];
      char nome_mae[50];

      printf("Nome da pessoa: ");
      scanf("%s", nome);

      printf("Nome do pai (ou 'NULL' se não tiver): ");
      scanf("%s", nome_pai);

      printf("Nome da mãe (ou 'NULL' se não tiver): ");
      scanf("%s", nome_mae);

      Pessoa *pai = buscar(raiz, nome_pai);
      Pessoa *mae = buscar(raiz, nome_mae);

      Pessoa *nova_pessoa = criar_pessoa(nome, pai, mae);
      inserir_na_fila(fila_irmaos, nova_pessoa);

      PilhaOperacoes *operacao = empilhar_operacao(&pilha_operacoes, 1, nova_pessoa);
      break;
    }

    case 2:
    {
      // Logic to remove a person
      char nome[50];
      printf("Nome da pessoa a ser removida: ");
      scanf("%s", nome);

      Pessoa *pessoa_removida = buscar(raiz, nome);
      if (pessoa_removida)
      {
        // Remove pessoa da fila de irmãos
        if (pessoa_removida->pai)
        {
          if (pessoa_removida->pai->prox_irmao == pessoa_removida)
            pessoa_removida->pai->prox_irmao = pessoa_removida->prox_irmao;
          else
          {
            Pessoa *irmao_atual = pessoa_removida->pai->prox_irmao;
            while (irmao_atual->prox_irmao != pessoa_removida)
              irmao_atual = irmao_atual->prox_irmao;
            irmao_atual->prox_irmao = pessoa_removida->prox_irmao;
          }
        }
        else
        {
          // If person is at the root
          fila_irmaos->primeiro = pessoa_removida->prox_irmao;
        }

        // Free the memory of the removed person
        free(pessoa_removida);
      }
      else
      {
        printf("Pessoa não encontrada.\n");
      }

      PilhaOperacoes *operacao = empilhar_operacao(&pilha_operacoes, 2, pessoa_removida);
      break;
    }
    case 3:
      imprimir_arvore(raiz, 0);
      break;
    case 4:
    {
      // Logic to search for a person
      char nome[50];
      printf("Nome da pessoa a ser buscada: ");
      scanf("%s", nome);

      Pessoa *pessoa_encontrada = buscar(raiz, nome);
      if (pessoa_encontrada)
      {
        printf("Pessoa encontrada: %s\n", pessoa_encontrada->nome);
      }
      else
      {
        printf("Pessoa não encontrada.\n");
      }
      break;
    }

    case 5:
    {
      // Logic to undo an operation
      if (pilha_operacoes != NULL)
      {
        PilhaOperacoes *operacao_desfeita = pilha_operacoes;
        pilha_operacoes = operacao_desfeita->anterior;

        if (operacao_desfeita->tipo == 1) // Undo insert operation
        {
          // Remove person from siblings queue
          if (operacao_desfeita->pessoa->pai)
          {
            Pessoa *irmao_atual = operacao_desfeita->pessoa->pai->prox_irmao;
            if (irmao_atual == operacao_desfeita->pessoa)
              operacao_desfeita->pessoa->pai->prox_irmao = NULL;
            else
            {
              while (irmao_atual->prox_irmao != operacao_desfeita->pessoa)
                irmao_atual = irmao_atual->prox_irmao;
              irmao_atual->prox_irmao = NULL;
            }
          }
          else
          {
            // If person is at the root
            fila_irmaos->ultimo = NULL;
          }

          // Free the memory of the person
          free(operacao_desfeita->pessoa);
        }
        else if (operacao_desfeita->tipo == 2) // Undo remove operation
        {
          // Restore person to siblings queue
          inserir_na_fila(fila_irmaos, operacao_desfeita->pessoa);
        }

        free(operacao_desfeita);
      }
      else
      {
        printf("Nenhuma operação para desfazer.\n");
      }
      break;
    }

    case 6:
    {
      // Logic to redo an operation
      // Note: Implementing redo functionality would require additional tracking of undone operations,
      //       which is not provided in the current code. You would need to extend the data structures
      //       and logic to support redo operations.
      printf("Função de refazer ainda não implementada.\n");
      break;
    }
    }
  }

  return 0;
}