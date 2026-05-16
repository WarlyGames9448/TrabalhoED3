#include "Matchmaking.hpp"

#include <iostream>

Matchmaking::Matchmaking() { size = 0; }

Matchmaking::~Matchmaking() { delete[] this->players; }

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
        Player key = players[i];
        int j = i - 1;

        // passa todo os players maiores que a 'key' para frente
        while (j >= 0 && comparePlayers(key, players[j])) {
            players[j + 1] = players[j];
            j--;
        }
        players[j + 1] = key;
    }
}

void Matchmaking::mergeSortAux(Player* arr, Player* temp, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSortAux(arr, temp, left, mid);
    mergeSortAux(arr, temp, mid + 1, right);

    merge(arr, temp, left, mid, right);
}

void Matchmaking::merge(Player* arr, Player* temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (comparePlayers(arr[i], arr[j])) {
            temp[k] = arr[i];
            i++;
        } else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }
    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for (int p = left; p <= right; p++) {
        arr[p] = temp[p];
    }
}

void Matchmaking::sortByScoreMerge() {
    if (size <= 1) return;

    // temporário a ser usado no mergeSortAux
    Player* temp = new Player[size];

    mergeSortAux(players, temp, 0, size - 1);

    delete[] temp;
}

Player* Matchmaking::formGroup(int groupSize, int delta, int* n) {
    *n = 0;
    if (groupSize <= 0 || groupSize > size) return nullptr;

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
