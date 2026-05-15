#include <iostream>
#include "Matchmaking.hpp"
#include "Player.hpp"

int main() {
    std::cout << "========================================\n";
    std::cout << "   INICIANDO TESTES DO MATCHMAKING\n";
    std::cout << "========================================\n\n";

    Matchmaking mm;

    Player p1(1, "Alice", 1500, 100);
    Player p2(2, "Bob", 1600, 110);
    Player p3(3, "Carol", 1500, 50); // Empate
    Player p4(4, "Dave", 1400, 120);
    Player p5(5, "Eve", 1550, 130);
    Player p6(6, "Frank", 1560, 140);
    Player p7(7, "Grace", 1800, 150);

    std::cout << "--- 1. INSERCAO DE JOGADORES ---\n";
    mm.insert(p1);
    mm.insert(p2);
    mm.insert(p3);
    mm.insert(p4);
    mm.insert(p5);
    mm.insert(p6);
    mm.insert(p7);

    mm.printWaitingPlayers();
    std::cout << "\n";

    std::cout << "--- 2. REMOCAO DE JOGADORES ---\n";
    std::cout << "Tentando remover Bob (ID 2)...\n";
    if (mm.removePlayer(2)) {
        std::cout << "Jogador removido com sucesso!\n";
    }
    mm.printWaitingPlayers();
    std::cout << "\n";

    std::cout << "--- 3. ORDENACAO UTILIZANDO INSERTION SORT (COM EMPATE) ---\n";
    std::cout << "Ordenando...\n";
    mm.sortByScoreInsertion();

    mm.printWaitingPlayers();
    std::cout << "\n";

    std::cout << "--- 4. ORDENACAO UTILIZANDO MERGE SORT ---\n";
    std::cout << "Para testar, vamos desordenar inserindo um novo jogador com score baixo.\n";
    Player p8(8, "Heidi", 1300, 160);
    mm.insert(p8);
    std::cout << "Estado antes do Merge Sort:\n";
    mm.printWaitingPlayers();

    std::cout << "\nAplicando Merge Sort...\n";
    mm.sortByScoreMerge();
    mm.printWaitingPlayers();
    std::cout << "\n";

    std::cout << "--- 5. TENTATIVA DE FORMACAO DE GRUPO SEM SUCESSO ---\n";
    int n;
    Player* failGroup = nullptr;
    std::cout << "Tentando formar grupo de 3 com delta de 10...\n";
    failGroup = mm.formGroup(3, 10, &n);

    if (failGroup == nullptr) {
        std::cout << "Resultado: Nenhum grupo formado. (Retornou nullptr)\n";
    }
    std::cout << "\n";

    std::cout << "--- 6. FORMACAO BEM-SUCEDIDA DE GRUPO ---\n";
    Player* successGroup = nullptr;
    std::cout << "Tentando formar grupo de 3 com delta de 50...\n";
    successGroup = mm.formGroup(3, 50, &n);

    if (successGroup != nullptr) {
        std::cout << "Grupo formado com sucesso! Jogadores no grupo:\n";
        mm.printPlayers(successGroup, n, "Group:");
        delete[] successGroup; // Liberando a memoria
    }

    std::cout << "\nEstado da fila apos formar o grupo (jogadores devem ter sido removidos):\n";
    mm.printWaitingPlayers();
    std::cout << "\n";

    std::cout << "--- 7. RECUPERACAO DE DADOS VIA getWaitingPlayers ---\n";
    int waitingCount = 0;
    Player* waitingList = mm.getWaitingPlayers(&waitingCount);

    if (waitingList != nullptr) {
        mm.printPlayers(waitingList, waitingCount, "Jogadores recuperados em um novo array dinamico:");
        delete[] waitingList; // Liberando a memoria
    } else {
        std::cout << "A fila esta vazia.\n";
    }
    std::cout << "\n========================================\n";
    std::cout << "           FIM DOS TESTES\n";
    std::cout << "========================================\n";

    return 0;
}
