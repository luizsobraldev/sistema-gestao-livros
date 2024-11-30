#include <stdio.h>
#include "tabela_hash.h" // Inclui o cabeçalho com as funções e definições da tabela hash

// Função principal do programa
int main() {
    // Inicialização das tabelas hash para encadeamento fechado e aberto
    printf("Inicializando as tabelas hash...\n");
    inicializarTabelas(); // Configura todas as posições das tabelas como vazias

    int opcao, metodo; // Armazena a opção escolhida pelo usuário e o método (1 = fechado, 2 = aberto)
    Livro livro; // Estrutura temporária para manipular os dados do livro

    do {
        // Menu do sistema
        printf("\n--- Sistema de Gerenciamento de Livros ---\n");
        printf("1. Inserir livro\n");
        printf("2. Buscar livro\n");
        printf("3. Remover livro\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        
        // Valida a entrada para evitar erros
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer do teclado
            continue;
        }

        // Para opções de 1 a 3, solicita o método de tratamento de colisões
        if (opcao >= 1 && opcao <= 3) {
            printf("\nEscolha o método de tratamento de colisões:\n");
            printf("1. Encadeamento Fechado\n");
            printf("2. Encadeamento Aberto\n");
            printf("Escolha uma opcao: ");
            if (scanf("%d", &metodo) != 1 || (metodo != 1 && metodo != 2)) {
                printf("Metodo invalido. Tente novamente.\n");
                while (getchar() != '\n'); // Limpa o buffer do teclado
                continue;
            }
        }

        // Processa a escolha do usuário com base na opção selecionada
        switch (opcao) {
            case 1: // Inserir livro
                printf("Inserindo um livro...\n");
                // Lê os dados do livro: ID, título, autor e ano de publicação
                printf("Digite o ID do livro: ");
                scanf("%d", &livro.id);
                printf("Digite o título do livro: ");
                scanf(" %[^\n]", livro.titulo); // Lê o título, incluindo espaços
                printf("Digite o autor do livro: ");
                scanf(" %[^\n]", livro.autor); // Lê o autor, incluindo espaços
                printf("Digite o ano do livro: ");
                scanf("%d", &livro.ano);

                // Insere o livro no método escolhido
                if (metodo == 1) { // Encadeamento Fechado
                    if (inserirEncadeamentoFechado(livro)) {
                        printf("Livro inserido com sucesso (Fechado)!\n");
                    } else {
                        printf("Erro ao inserir livro (Fechado).\n");
                    }
                } else { // Encadeamento Aberto
                    if (inserirEncadeamentoAberto(livro)) {
                        printf("Livro inserido com sucesso (Aberto)!\n");
                    } else {
                        printf("Erro ao inserir livro (Aberto).\n");
                    }
                }
                break;

            case 2: // Buscar livro
                printf("Buscando um livro...\n");
                // Lê o ID do livro que o usuário deseja buscar
                printf("Digite o ID do livro para buscar: ");
                scanf("%d", &livro.id);

                // Busca o livro no método escolhido
                Livro* encontrado;
                if (metodo == 1) { // Encadeamento Fechado
                    encontrado = buscarEncadeamentoFechado(livro.id);
                } else { // Encadeamento Aberto
                    encontrado = buscarEncadeamentoAberto(livro.id);
                }

                // Verifica se o livro foi encontrado e exibe os detalhes
                if (encontrado) {
                    printf("Livro encontrado: %d - %s - %s (%d)\n", 
                           encontrado->id, encontrado->titulo, encontrado->autor, encontrado->ano);
                } else {
                    printf("Livro não encontrado.\n");
                }
                break;

            case 3: // Remover livro
                printf("Removendo um livro...\n");
                // Lê o ID do livro que o usuário deseja remover
                printf("Digite o ID do livro para remover: ");
                scanf("%d", &livro.id);

                // Remove o livro no método escolhido
                int sucesso;
                if (metodo == 1) { // Encadeamento Fechado
                    sucesso = removerEncadeamentoFechado(livro.id);
                } else { // Encadeamento Aberto
                    sucesso = removerEncadeamentoAberto(livro.id);
                }

                // Verifica se a remoção foi bem-sucedida
                if (sucesso) {
                    printf("Livro removido com sucesso!\n");
                } else {
                    printf("Livro não encontrado.\n");
                }
                break;

            case 4: // Sair do programa
                printf("Saindo do programa...\n");
                break;

            default: // Tratamento para opção inválida
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4); // Continua executando enquanto o usuário não escolher sair

    return 0; // Encerra o programa com sucesso
}
