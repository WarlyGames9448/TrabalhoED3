#include "Matchmaking.hpp"

#include <iostream>

Matchmaking::Matchmaking() { size = 0; }

Matchmaking::~Matchmaking() {}

bool Matchmaking::comparePlayers(const Player& player1, const Player& player2) {
    int score1 = player1.getScore();
    int score2 = player2.getScore();
    if (score1 != score2) {
        return score1 < score2;
    }
    return player1.getTimestamp() < player2.getTimestamp();
}

bool Matchmaking::insert(Player player) {
    if (size >= MAX_PLAYERS) {
        return false;
    }
    players[size] = player;
    size++;
    return true;
}

bool Matchmaking::removePlayer(int id) {
    for (int i = 0; i < size; i++) {
        if (players[i].getId() == id) {
            for (int j = i; j < size - 1; j++) {
                players[j] = players[j + 1];
            }
            size--;
            return true;
        }
    }
    return false;
}

void Matchmaking::sortByScoreInsertion() {
    for (int i = 1; i < size; i++) {
        int j = i - 1;

        while (j >= 0 && comparePlayers(players[i], players[j])) {
            players[j + 1] = players[j];
            j--;
        }
        players[j + 1] = players[i];
    }
}

void Matchmaking::merge(Player* arr, int n) {
    int mid = n / 2;
    if (n <= 1) return;

    Player* left_part = new Player[mid];
    for (int index = 0; index < mid; index++) {
        left_part[index] = arr[index];
    }
    Player* right_part = new Player[n - mid];
    for (int index = 0; index < n - mid; index++) {
        right_part[index] = arr[index + mid];
    }
    merge(left_part, mid);
    merge(right_part, n - mid);

    int i = 0; // percorrer esquerda
    int j = 0; // percorrer a direita
    int k = 0; // percorrer o array original

    while (i < mid && j < n - mid) {
        if (comparePlayers(left_part[i], right_part[j])) {
            arr[k] = left_part[i];
            i++;
        } else {
            arr[k] = right_part[j];
            j++;
        }
        k++;
    }

    // caso tenha sobrado algum jogador auxiliar (se um acabou antes), copia-se para o original
    while (i < mid) {
        arr[k] = left_part[i];
        i++;
        k++;
    }
    while (j < n - mid) {
        arr[k] = right_part[j];
        j++;
        k++;
    }

    delete[] left_part;
    delete[] right_part;
}

void Matchmaking::sortByScoreMerge() { merge(players, size); }

Player* Matchmaking::formGroup(int groupSize, int delta, int* n) {
    *n = 0;
    if (groupSize > size) return nullptr;

    int i = 0;
    int j = groupSize - 1;

    while (j < size) {
        if (this->players[j].getScore() - this->players[i].getScore() <= delta) {
            // Cria novo array
            *n = groupSize;
            Player* group = new Player[groupSize];
            for (int index = 0; index < groupSize; index++)
                group[index] = this->players[i + index];

            // Deleta-os da lista.

            for (int k = 0; k < size - j - 1; k++) {
                this->players[i + k] = this->players[j + k + 1];
            }

            size -= groupSize;
            return group;
        }

        i++;
        j++;
    }

    // Não encontrou grupo
    return nullptr;
}

Player* Matchmaking::getWaitingPlayers(int* n) {
    *n = this->size;

    Player* waitingPlayers = new Player[this->size];
    for (int index = 0; index < this->size; index++)
        waitingPlayers[index] = this->players[index];

    return waitingPlayers;
}

void Matchmaking::printWaitingPlayers() {
    std::cout << "Waiting Players:" << std::endl;

    if (this->size == 0) {
        std::cout << "(empty)" << std::endl;
        return;
    }

    for (int index = 0; index < this->size; index++) {
        std::cout << "[" << this->players[index].getId() << " | " << this->players[index].getName() << " | "
                  << this->players[index].getScore() << " | " << this->players[index].getTimestamp() << "]"
                  << std::endl;
    }
}

void Matchmaking::printPlayers(Player* players, int size, const char* type) {
    std::cout << type << std::endl;

    if (size == 0) {
        std::cout << "(empty)" << std::endl;
        return;
    }

    for (int index = 0; index < size; index++) {
        std::cout << "[" << players[index].getId() << " | " << players[index].getName() << " | "
                  << players[index].getScore() << " | " << players[index].getTimestamp() << "]" << std::endl;
    }
}
