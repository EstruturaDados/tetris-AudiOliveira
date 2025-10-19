#include <stdio.h>
#include <stdlib.h> // Para a função rand()
#include <time.h>   // Para a função time()

// --- Constantes ---
#define TAMANHO_FILA 5 // Tamanho fixo da fila de peças futuras

// --- Estrutura de Dados ---

/**
 * @brief Define a estrutura de uma Peça do Tetris Stack.
 * * Uma peça possui um tipo ('nome') e um identificador único ('id').
 */
typedef struct {
    char nome;   // Tipo da peça ('I', 'O', 'T', 'L', etc.)
    int id;      // Identificador único da peça
} Peca;

// --- Variáveis Globais para a Fila ---

Peca filaPecas[TAMANHO_FILA]; // Array estático que armazena a fila
int frente = 0;              // Índice da frente da fila (onde a próxima peça será jogada)
int traseira = -1;           // Índice da traseira da fila (onde a próxima peça será inserida)
int contadorPecas = 0;       // Número atual de peças na fila
int idProximaPeca = 0;       // Contador global para gerar IDs únicos para cada nova peça

// --- Protótipos das Funções ---

void inicializarFila();
Peca gerarPeca();
int isFilaCheia();
int isFilaVazia();
void enfileirar(Peca novaPeca);
Peca desenfileirar();
void exibirFila();
void exibirMenu();

// --- Funções da Lógica do Jogo e da Fila ---

/**
 * @brief Gera uma nova peça com um tipo aleatório e um ID único.
 * * O tipo da peça é escolhido aleatoriamente entre 'I', 'O', 'T', 'L', 'J', 'Z', 'S'.
 * O ID é gerado sequencialmente.
 * * @return A nova Peca gerada.
 */
Peca gerarPeca() {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'Z', 'S'};
    int numTipos = sizeof(tipos) / sizeof(tipos[0]);

    // Escolhe um tipo de peça aleatoriamente
    int indiceTipo = rand() % numTipos; 
    novaPeca.nome = tipos[indiceTipo];
    
    // Atribui o ID único e incrementa o contador global
    novaPeca.id = idProximaPeca++; 

    return novaPeca;
}

/**
 * @brief Inicializa a fila de peças com um número fixo de elementos.
 * * Enche a fila com peças geradas automaticamente até atingir o TAMANHO_FILA.
 */
void inicializarFila() {
    // Inicializa o gerador de números aleatórios com a hora atual para garantir 
    // que as peças sejam diferentes a cada execução.
    srand(time(NULL)); 

    printf("--- Inicializando Fila de Pecas ---\n");
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca p = gerarPeca();
        // A função enfileirar é usada aqui para preencher a fila
        // A lógica de controle da fila é a mesma.
        enfileirar(p); 
    }
    printf("Fila inicializada com %d pecas.\n", TAMANHO_FILA);
}

/**
 * @brief Verifica se a fila circular está cheia.
 * * @return 1 se cheia, 0 caso contrário.
 */
int isFilaCheia() {
    return contadorPecas == TAMANHO_FILA;
}

/**
 * @brief Verifica se a fila circular está vazia.
 * * @return 1 se vazia, 0 caso contrário.
 */
int isFilaVazia() {
    return contadorPecas == 0;
}

/**
 * @brief Insere uma nova peça no final da fila (enqueue).
 * * Implementa a lógica da fila circular para inserção.
 * * @param novaPeca A peça a ser inserida.
 */
void enfileirar(Peca novaPeca) {
    if (isFilaCheia()) {
        printf("ERRO: A fila de pecas futuras esta cheia! Nao foi possivel inserir.\n");
        return;
    }

    // Calcula a nova posição da traseira (circular)
    traseira = (traseira + 1) % TAMANHO_FILA;
    // Insere a peça na posição calculada
    filaPecas[traseira] = novaPeca;
    // Incrementa o contador de peças
    contadorPecas++;

    printf("SUCESSO: Peca [%c %d] inserida no final da fila (enqueue).\n", novaPeca.nome, novaPeca.id);
}

/**
 * @brief Remove a peça da frente da fila (dequeue).
 * * Implementa a lógica da fila circular para remoção.
 * * @return A peça removida. Retorna uma peça com nome 'X' se a fila estiver vazia.
 */
Peca desenfileirar() {
    Peca pecaRemovida = {'X', -1}; // Peça de erro/vazia

    if (isFilaVazia()) {
        printf("ERRO: A fila de pecas futuras esta vazia! Nao ha pecas para jogar (dequeue).\n");
        return pecaRemovida;
    }

    // Pega a peça na posição da frente
    pecaRemovida = filaPecas[frente];

    // Calcula a nova posição da frente (circular)
    frente = (frente + 1) % TAMANHO_FILA;
    // Decrementa o contador de peças
    contadorPecas--;

    printf("SUCESSO: Peca [%c %d] jogada/removida da frente da fila (dequeue).\n", pecaRemovida.nome, pecaRemovida.id);
    return pecaRemovida;
}

/**
 * @brief Exibe o estado atual da fila de peças no console.
 * * Mostra a posição (índice), o nome e o ID de cada peça.
 * Indica o índice da frente e da traseira.
 */
void exibirFila() {
    printf("\n--- Estado Atual da Fila de Pecas ---\n");

    if (isFilaVazia()) {
        printf("A fila esta vazia.\n");
        return;
    }

    printf("Fila de Pecas: ");
    int i = frente;
    int pecasExibidas = 0;

    // Itera através dos elementos da fila de forma circular
    while (pecasExibidas < contadorPecas) {
        printf("[%c %d]", filaPecas[i].nome, filaPecas[i].id);
        
        // Marca a frente e a traseira
        if (i == frente) {
            printf("(Frente)");
        }
        if (i == traseira) {
            printf("(Traseira)");
        }
        
        printf(" ");
        
        i = (i + 1) % TAMANHO_FILA; // Move para o próximo índice de forma circular
        pecasExibidas++;
    }

    printf("\nTotal de Pecas: %d / %d\n", contadorPecas, TAMANHO_FILA);
    printf("--------------------------------------\n");
}

/**
 * @brief Exibe o menu de opções para o jogador.
 */
void exibirMenu() {
    printf("\n======================================\n");
    printf("        Tetris Stack - Fila         \n");
    printf("======================================\n");
    printf("Opcoes de acao:\n");
    printf("Codigo | Acao\n");
    printf("--------------------------------------\n");
    printf("  1    | Jogar peca (dequeue)\n");
    printf("  2    | Inserir nova peca (enqueue)\n");
    printf("  0    | Sair\n");
    printf("--------------------------------------\n");
    printf("Selecione uma opcao: ");
}

// --- Função Principal ---

int main() {
    int escolha;

    // 1. Inicializa a fila de peças
    inicializarFila();
    exibirFila();

    // Loop principal do jogo/simulação
    do {
        exibirMenu();
        
        // Leitura da escolha do jogador
        if (scanf("%d", &escolha) != 1) {
            // Lidar com entrada inválida (não numérica)
            printf("Entrada invalida. Por favor, digite um numero.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            escolha = -1; // Garante que o loop continue
            continue;
        }

        printf("\n--- Executando Acao ---\n");

        switch (escolha) {
            case 1:
                // Ação: Jogar peça (dequeue)
                // Remove a peça da frente e a "joga" (desenfileira)
                Peca pecaJogada = desenfileirar();
                // O estado da fila é exibido após a ação.
                exibirFila();
                break;
            case 2:
                // Ação: Inserir nova peça (enqueue)
                // 1. Gera uma nova peça
                Peca novaPeca = gerarPeca();
                // 2. Insere a peça no final da fila (enfileira)
                enfileirar(novaPeca);
                // O estado da fila é exibido após a ação.
                exibirFila();
                break;
            case 0:
                // Ação: Sair
                printf("Encerrando simulacao. Obrigado por testar o controle de pecas do Tetris Stack!\n");
                break;
            default:
                // Ação: Opção inválida
                printf("Opcao invalida. Por favor, escolha 1, 2 ou 0.\n");
                exibirFila();
                break;
        }

    } while (escolha != 0);

    return 0;
}