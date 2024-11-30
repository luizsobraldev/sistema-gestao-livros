#include "tabela_hash.h" // Inclui o cabeçalho com definições e protótipos das funções
#include <stdio.h>       // Biblioteca para entrada e saída
#include <stdlib.h>      // Biblioteca para manipulação de memória
#include <string.h>      // Biblioteca para manipulação de strings

// Tabelas Hash
No* tabela_encadeamento_fechado[TAMANHO_TABELA]; // Tabela para o encadeamento fechado
Livro tabela_encadeamento_aberto[TAMANHO_TABELA]; // Tabela para o encadeamento aberto
int ocupado[TAMANHO_TABELA]; // Array para indicar se uma posição no encadeamento aberto está ocupada

// Função de hash
int hash(int id) {
    // Calcula o índice baseado no ID e no tamanho da tabela
    return id % TAMANHO_TABELA;
}

// Inicializa as tabelas hash
void inicializarTabelas() {
    // Inicializa a tabela do encadeamento fechado, colocando todas as posições como NULL
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela_encadeamento_fechado[i] = NULL;
    }
    // Inicializa a tabela do encadeamento aberto, marcando todas as posições como livres
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        ocupado[i] = 0;
    }
}

// Funções de encadeamento fechado

// Insere um livro na tabela usando encadeamento fechado
int inserirEncadeamentoFechado(Livro livro) {
    int indice = hash(livro.id); // Calcula o índice da tabela
    // Aloca memória para um novo nó
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) return 0; // Verifica se a alocação foi bem-sucedida

    // Configura os dados do novo nó
    novo->livro = livro;
    novo->prox = tabela_encadeamento_fechado[indice]; // Insere no início da lista
    tabela_encadeamento_fechado[indice] = novo; // Atualiza a tabela
    return 1; // Retorna sucesso
}

// Busca um livro na tabela usando encadeamento fechado
Livro* buscarEncadeamentoFechado(int id) {
    int indice = hash(id); // Calcula o índice da tabela
    No* atual = tabela_encadeamento_fechado[indice]; // Aponta para o início da lista

    // Percorre a lista na posição calculada
    while (atual) {
        if (atual->livro.id == id) return &atual->livro; // Retorna o livro se encontrado
        atual = atual->prox; // Avança para o próximo nó
    }
    return NULL; // Retorna NULL se o livro não foi encontrado
}

// Remove um livro da tabela usando encadeamento fechado
int removerEncadeamentoFechado(int id) {
    int indice = hash(id); // Calcula o índice da tabela
    No* atual = tabela_encadeamento_fechado[indice]; // Aponta para o início da lista
    No* anterior = NULL; // Para rastrear o nó anterior

    // Percorre a lista para encontrar o nó a ser removido
    while (atual) {
        if (atual->livro.id == id) {
            // Remove o nó da lista
            if (anterior) anterior->prox = atual->prox;
            else tabela_encadeamento_fechado[indice] = atual->prox;

            free(atual); // Libera a memória alocada
            return 1; // Retorna sucesso
        }
        anterior = atual; // Atualiza o nó anterior
        atual = atual->prox; // Avança para o próximo nó
    }
    return 0; // Retorna falha se o livro não foi encontrado
}

// Funções de encadeamento aberto

// Insere um livro na tabela usando encadeamento aberto
int inserirEncadeamentoAberto(Livro livro) {
    int indice = hash(livro.id); // Calcula o índice inicial
    // Sondagem linear para encontrar uma posição livre
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        int pos = (indice + i) % TAMANHO_TABELA; // Calcula a posição com sondagem
        if (!ocupado[pos]) { // Verifica se a posição está livre
            tabela_encadeamento_aberto[pos] = livro; // Insere o livro na posição
            ocupado[pos] = 1; // Marca a posição como ocupada
            return 1; // Retorna sucesso
        }
    }
    return 0; // Retorna falha se a tabela estiver cheia
}

// Busca um livro na tabela usando encadeamento aberto
Livro* buscarEncadeamentoAberto(int id) {
    int indice = hash(id); // Calcula o índice inicial
    // Sondagem linear para encontrar o livro
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        int pos = (indice + i) % TAMANHO_TABELA; // Calcula a posição com sondagem
        if (ocupado[pos] && tabela_encadeamento_aberto[pos].id == id) {
            return &tabela_encadeamento_aberto[pos]; // Retorna o livro se encontrado
        }
        if (!ocupado[pos]) break; // Interrompe a busca se encontrar uma posição livre
    }
    return NULL; // Retorna NULL se o livro não foi encontrado
}

// Remove um livro da tabela usando encadeamento aberto
int removerEncadeamentoAberto(int id) {
    int indice = hash(id); // Calcula o índice inicial
    // Sondagem linear para encontrar o livro
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        int pos = (indice + i) % TAMANHO_TABELA; // Calcula a posição com sondagem
        if (ocupado[pos] && tabela_encadeamento_aberto[pos].id == id) {
            ocupado[pos] = 0; // Marca a posição como livre
            return 1; // Retorna sucesso
        }
        if (!ocupado[pos]) break; // Interrompe a busca se encontrar uma posição livre
    }
    return 0; // Retorna falha se o livro não foi encontrado
}
