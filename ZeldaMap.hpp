#include <iostream>
#include <ostream>
#include <vector>
#include "Helper.hpp"
#include "HCTree.hpp"

using namespace std;

struct GameState {
  int p1;
  int p2;
  int wolf;
  bool connected;
  vector<GameState> neighboors;
  GameState(int p1, int p2, int wolf) {
    this.p1 = p1;
    this.p2 = p2;
    this.wolf = wolf;
    this.connected = false;
};

class GameMap {
  public:
  
  private:
  
}
