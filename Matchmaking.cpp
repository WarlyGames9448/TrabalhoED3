#include "Matchmaking.hpp"

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

void Matchmaking::merge(Player* arr, int left, int mid, int right) {
    int left_size = mid - left + 1;
    int right_size = right - mid;

    Player* left_part = new Player[left_size];
    Player* right_part = new Player[right_size];

    for (int i = left, j = 0; i <= mid; i++, j++) {
        left_part[j] = arr[i];
    }
    for (int i = mid + 1, j = 0; i <= right; i++, j++) {
        right_part[j] = arr[i];
    }

    int i = 0;    // percorrer esquerda
    int j = 0;    // percorrer a direita
    int k = left; // percorrer o array original

    while (i < left_size && j < right_size) {
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
    while (i < left_size) {
        arr[k] = left_part[i];
        i++;
        k++;
    }
    while (j < right_size) {
        arr[k] = right_part[j];
        j++;
        k++;
    }

    delete[] left_part;
    delete[] right_part;
}

void Matchmaking::mergeSortHelper(Player* arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid);
    mergeSortHelper(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void Matchmaking::sortByScoreMerge() {
    if (size > 1) {
        mergeSortHelper(players, 0, size - 1);
    }
}

Player* Matchmaking::formGroup(int groupSize, int delta, int* n) { return nullptr; }
Player* Matchmaking::getWaitingPlayers(int* n) { return nullptr; }

void Matchmaking::printWaitingPlayers() {}

void Matchmaking::printPlayers(Player* players, int size) {}
