#include "Matchmaking.hpp"
#include "Player.hpp"

#include <iostream>

int main() {
  Matchmaking sys;

  sys.insert({1, "Ana", 1000, 3});
  sys.insert({2, "Bruno", 900, 2});
  sys.insert({3, "Carla", 1100, 1});

  if (sys.insert({4, "Maranhão", 800, 4}))
    std::cout << "Maranhão foi adicionado!" << std::endl;

  sys.printWaitingPlayers();

  std::cout << "\n===================== Ordenando ===================\n";

  sys.sortByScoreMerge();
  sys.printWaitingPlayers();

  std::cout << "\n===================== Com Empate ===================\n";

  sys.insert({5, "Zé", 900, 5});
  sys.sortByScoreMerge();
  sys.printWaitingPlayers();

  std::cout << "\n===================== Formação de Grupos ===================\n";

  int n;
  Player *group = sys.formGroup(3, 150, &n);
  sys.printPlayers(group, n, "Group:");

  // Nenhuma formação de grupo possível
  Player *group2 = sys.formGroup(3, 10, &n);
  sys.printPlayers(group2, n,"Group:");

  std::cout << "\n===================== Removendo Players ===================\n";
  if(sys.removePlayer(3)) std::cout << "Player com id 3 removido!\n";
  sys.printWaitingPlayers();

  std::cout << "\n===================== Metodo get ===================\n";
  Player* players = sys.getWaitingPlayers(&n);
  sys.printPlayers(players, n, "Waiting Players:");

  return 0;
}
