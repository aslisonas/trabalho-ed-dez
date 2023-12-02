#include </home/mikeyas/trabalho-ed-dez/trabalho-ed-dez/headers.h>
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

Pessoa *criarNoPessoa()
{
  Pessoa *pessoaPtr = malloc(sizeof(Pessoa));
  pessoaPtr->Pai = NULL;
  pessoaPtr->Mae = NULL;
  pessoaPtr->irmaos = NULL;
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
      printf("\nPai-> %s", (raizPtr->Pai != NULL) ? raizPtr->Pai->nome : "<-Sem dados->");
      printf("\nMae-> %s", (raizPtr->Mae != NULL) ? raizPtr->Mae->nome : "<-Sem dados->");

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

  // Busca especifica na lista de irmaos tambem
  if (raizPtr->irmaos != NULL && raizPtr->irmaos->front != -1)
  {
    for (int i = 0; i <= raizPtr->irmaos->rear; i++)
    {
      if (!strcmp(raizPtr->irmaos->nomeIrmao[i], nomeBusca))
      {
        if (mostrarDados)
        {
          printf("\n\nPessoa: %s", raizPtr->irmaos->nomeIrmao[i]);
          printf("\nPai-> %s", raizPtr->Pai->nome);
          printf("\nMae-> %s", raizPtr->Mae->nome);
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

  if (raiz->Pai != NULL)
  {
    buscarPessoaEspecifica(raizPtr->Pai, nomeBusca, mostrarDados);
  }
  if (raiz->Mae != NULL)
  {
    buscarPessoaEspecifica(raizPtr->Mae, nomeBusca, mostrarDados);
  }

  return NULL;
}

void adicionarPessoa(Pessoa *pessoa, int cadastrouPrimeira)
{

  if (!cadastrouPrimeira)
  {
    printf("\nDigite o nome da pessoa: ");
    fgets(pessoa->nome, 50, stdin);
    processarString(pessoa->nome);
  }

  // ADICIONAR PAI E MAE
  pessoa->Pai = criarNoPessoa();
  Pessoa *paiPtr = pessoa->Pai;

  printf("\nDigite o nome do pai: ");
  fgets(paiPtr->nome, 50, stdin);
  processarString(paiPtr->nome);

  pessoa->Mae = criarNoPessoa();
  Pessoa *maePtr = pessoa->Mae;

  printf("\nDigite o nome da mae: ");
  fgets(maePtr->nome, 50, stdin);
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
void editarPessoa(Pessoa *pessoa, char nomeBusca[49])
{
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

  printf("\nEditar o atual nome ' %s ' do pai? (1- Sim / 0- Pular): ", pessoaPtr->Pai->nome);
  scanf("%d", &escolha);
  if (escolha)
  {
    getchar();
    printf("\nNovo nome: ");
    fgets(pessoaPtr->Pai->nome, 50, stdin);
    processarString(pessoaPtr->Pai->nome);
  }

  printf("\nEditar o atual nome ' %s ' da mae? (1- Sim / 0- Pular): ", pessoaPtr->Mae->nome);
  scanf("%d", &escolha);
  if (escolha)
  {
    getchar();
    printf("\nNovo nome: ");
    fgets(pessoaPtr->Mae->nome, 50, stdin);
    processarString(pessoaPtr->Mae->nome);
  }

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
  char nomeBusca[50];
  Pessoa *raiz = criarNoPessoa();
  while (menu != 1)
  {
    printf("\n\n_________MENU_________");
    printf("\n1 - Sair");
    printf("\n2 - Adicionar Pessoa");
    printf("\n3 - Imprimir Arvore Genealogica");
    printf("\n4 - BUSCAR Dados Pessoa Especifica");
    printf("\n5 - EDITAR Dados Pessoa Especifica");
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
      getchar();
      adicionarPessoa(raiz, cadastrouPrimeira);
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
      editarPessoa(buscarPessoaEspecifica(raiz, nomeBusca, 0), nomeBusca);
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