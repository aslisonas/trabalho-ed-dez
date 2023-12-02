#ifndef headers
#define headers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 10

typedef struct filaIrmaos {
  char nomeIrmao[TAM][50];
  int front;
  int rear;
} filaIrmaos;

typedef struct Pessoa {
  char nome[50];
  struct Pessoa *Pai;
  struct Pessoa *Mae;
  struct filaIrmaos *irmaos;
} Pessoa;

void processarString(char *string);

Pessoa *criarNoPessoa();

Pessoa *buscarPessoaEspecifica(Pessoa *raiz, char nomeBusca[49], int mostrarDados);

void adicionarPessoa(Pessoa *pessoa, int cadastrouPrimeira);

void editarPessoa(Pessoa *pessoa, char nomeBusca[49]);

Pessoa *encontrarUltimoNomePai(Pessoa *raiz);

Pessoa *encontrarUltimoNomeMae(Pessoa *raiz);

void imprimirArvore(Pessoa *Pessoa);

#endif /* headers */