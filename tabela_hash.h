#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#define TAMANHO_TABELA 100  // Definindo o tamanho da tabela hash

// Estrutura que representa um livro
typedef struct {
    int id;             // Identificador único do livro
    char titulo[50];    // Título do livro
    char autor[50];     // Nome do autor do livro
    int ano;            // Ano de publicação do livro
} Livro;

// Estrutura de um nó para listas encadeadas (usado no encadeamento fechado)
typedef struct No {
    Livro livro;           // Dados do livro armazenado no nó
    struct No* prox;       // Ponteiro para o próximo nó na lista encadeada
} No;

// Funções comuns para manipulação da tabela hash
void inicializarTabelas();  // Inicializa as tabelas hash
int hash(int id);           // Função de hash para gerar um índice com base no id do livro

// Funções de encadeamento fechado (usando listas encadeadas para resolver colisões)
int inserirEncadeamentoFechado(Livro livro);   // Insere um livro na tabela usando encadeamento fechado
Livro* buscarEncadeamentoFechado(int id);      // Busca um livro na tabela usando encadeamento fechado
int removerEncadeamentoFechado(int id);        // Remove um livro da tabela usando encadeamento fechado

// Funções de encadeamento aberto (endereçamento aberto para resolver colisões)
int inserirEncadeamentoAberto(Livro livro);   // Insere um livro na tabela usando encadeamento aberto
Livro* buscarEncadeamentoAberto(int id);      // Busca um livro na tabela usando encadeamento aberto
int removerEncadeamentoAberto(int id);        // Remove um livro da tabela usando encadeamento aberto

#endif
