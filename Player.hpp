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

  inline int getId() const { return id; }
  inline std::string getName() const { return name; }
  inline int getScore() const { return score; }
  inline int getTimestamp() const { return timestamp; }
};
