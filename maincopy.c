#include <stdio.h>
#define TAM 5

int fila[TAM];
int frente = -1, tras = -1;

// Função para verificar se a fila está vazia
int filaVazia()
{
  return (frente == -1 && tras == -1);
}

// Função para verificar se a fila está cheia
int filaCheia()
{
  return ((tras + 1) % TAM == frente);
}

// Função para enfileirar um elemento
void enfileirar(int valor)
{
  if (filaCheia())
  {
    printf("A fila está cheia. Não é possível enfileirar.\n");
    return;
  }
  else if (filaVazia())
  {
    frente = tras = 0;
  }
  else
  {
    tras = (tras + 1) % TAM;
  }

  fila[tras] = valor;
  printf("Elemento %d enfileirado com sucesso.\n", valor);
}

// Função para desenfileirar um elemento
void desenfileirar()
{
  if (filaVazia())
  {
    printf("A fila está vazia. Não é possível desenfileirar.\n");
    return;
  }
  else if (frente == tras)
  {
    printf("Elemento %d desenfileirado com sucesso.\n", fila[frente]);
    frente = tras = -1;
  }
  else
  {
    printf("Elemento %d desenfileirado com sucesso.\n", fila[frente]);
    frente = (frente + 1) % TAM;
  }
}

// Função para exibir o elemento no início da fila
void frenteDaFila()
{
  if (filaVazia())
  {
    printf("A fila está vazia.\n");
    return;
  }

  printf("Elemento na frente da fila: %d\n", fila[frente]);
}

// Função para exibir a fila
void exibirFila()
{
  if (filaVazia())
  {
    printf("A fila está vazia.\n");
    return;
  }

  printf("Elementos da fila: ");
  int i = frente;
  do
  {
    printf("%d ", fila[i]);
    i = (i + 1) % TAM;
  } while (i != (tras + 1) % TAM);
  printf("\n");
}

int main()
{
  // Exemplo de utilização
  enfileirar(1);
  enfileirar(2);
  enfileirar(3);
  exibirFila();
  frenteDaFila();
  desenfileirar();
  exibirFila();

  return 0;
}
