#pragma once

#include "Player.hpp"

// Tornado estático para usar na criação do Player
static const int MAX_PLAYERS = 100000;

class Matchmaking {

  private:
    // Alocação dinâmica para utilizar a lógica de ponteiros sem erros.
    Player* players = new Player[MAX_PLAYERS];
    int size;

  private:
    /**
     * @brief Compara a prioridade entre dois jogadores.
     *
     * Avalia qual dos dois jogadores deve ter preferência na ordenação.
     * Seguindo as regras do sistema, a maior prioridade geralmente pertence ao
     * jogador com o menor score e, em caso de empate, ao jogador com o menor
     * timestamp.
     *
     * @param player1 Ponteiro para o primeiro jogador a ser comparado.
     * @param player2 Ponteiro para o segundo jogador a ser comparado.
     * @return true se player1 tiver maior prioridade que player2.
     * @return false caso contrário (se player2 tiver maior ou igual prioridade).
     */
    bool comparePlayers(const Player& player1, const Player& player2);

    /**
     * @brief CMétodo auxiliar para o sortByScoreMerge()
     *
     *
     * @param arr Ponteiro para um elemento de players.
     * @param n tamanho da sublista, isto é, pega n consecutivos de players, onde o primeiro deles está sendo apontado
     * por arr.
     * @return Ponteiro para a lista ordenada
     *
     * @note Não é criado nenhuma lista auxiliar, todas as operações são feitas dentro da original
     * Portanto, deve-se passar um cópia de players.
     */
    void merge(Player* arr, int n);

  public:
    Matchmaking();
    ~Matchmaking();

    /**
     * @brief Insere um novo jogador no final do array da fila de espera.
     *
     * @param player O objeto Player a ser inserido.
     * @return true se existir espaço disponível e o jogador for inserido com
     * sucesso.
     * @return false se a capacidade máxima (MAX_PLAYERS) já tiver sido atingida.
     */
    bool insert(Player player);

    /**
     * @brief Remove um jogador específico da fila de espera.
     *
     * @param id O identificador do jogador a ser removido.
     * @return true se o jogador foi encontrado e removido com sucesso.
     * @return false caso nenhum jogador com o ID informado seja encontrado.
     */
    bool removePlayer(int id);

    /**
     * @brief Ordena os jogadores por score em ordem crescente utilizando o
     * algoritmo Insertion Sort.
     *
     * Em caso de empate no score, o jogador com menor timestamp tem prioridade
     * (vem primeiro).
     * @note Este algoritmo possui custo quadrático (O(n²)) no pior caso.
     */
    void sortByScoreInsertion();

    /**
     * @brief Ordena os jogadores por score em ordem crescente utilizando o
     * algoritmo Merge Sort.
     *
     * Em caso de empate no score, o jogador com menor timestamp tem prioridade
     * (vem primeiro).
     * @note Estratégia baseada em divisão e conquista, possuindo custo de tempo
     * O(n log n) no pior caso.
     */
    void sortByScoreMerge();

    /**
     * @brief Tenta formar um grupo com a quantidade especificada de jogadores.
     *
     * Assume que os jogadores já foram previamente ordenados por score.
     * Caso um grupo válido seja formado, os jogadores escolhidos são removidos da
     * fila.
     *
     * @param groupSize A quantidade de jogadores necessária para formar o grupo.
     * @param delta A diferença ou critério máximo (tolerância) permitido na
     * formação do grupo.
     * @param n Ponteiro de saída que receberá o valor de groupSize em caso de
     * sucesso, ou 0 em caso de falha.
     * @return Ponteiro para um array dinâmico contendo os jogadores do grupo
     * formado, ou nullptr caso nenhum grupo válido seja encontrado.
     * @warning A memória alocada para o array retornado deve ser liberada por
     * quem chamou a função utilizando `delete[]`.
     */
    Player* formGroup(int groupSize, int delta, int* n);

    /**
     * @brief Obtém uma cópia de todos os jogadores atualmente na fila de espera.
     *
     * @param n Ponteiro de saída utilizado para informar a quantidade de
     * jogadores retornados.
     * @return Ponteiro para um array dinâmico contendo cópias dos jogadores, ou
     * nullptr caso a fila esteja vazia (neste caso, `*n` será definido como 0).
     * @warning A memória alocada para o array retornado deve ser liberada por
     * quem chamou a função utilizando `delete[]`.
     */
    Player* getWaitingPlayers(int* n);

    /**
     * @brief Exibe o estado atual da fila de espera de forma legível.
     *
     * A saída inclui a identificação "Waiting Players". Caso não existam
     * jogadores armazenados, exibe a indicação "(empty)".
     */
    void printWaitingPlayers();

    /**
     * @brief Imprime o conteúdo de um array de jogadores.
     *
     * Exibe o estado e as informações dos jogadores contidos no array informado
     * de forma legível e consistente com a saída padrão do sistema.
     *
     * @param players Ponteiro para o array de objetos Player a ser exibido.
     * @param size A quantidade de jogadores contidos no array.
     * @param type A mensagem a ser imprimida na primeira linha.
     */
    void printPlayers(Player* players, int size, const char* type);
};
