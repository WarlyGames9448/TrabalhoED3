#pragma once

#include <string>

class Player {

private:
  int id;
  std::string name;
  int score;
  int timestamp;

public:
  Player() = default;
  Player(int id, std::string name, int score, int timestamp);
  ~Player() = default;

  inline int getId() { return id; }
  inline std::string getName() { return name; }
  inline int getScore() { return score; }
  inline int getTimestamp() { return timestamp; }
};
