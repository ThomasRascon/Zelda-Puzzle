#include <iostream>
#include <ostream>
#include <vector>
#include <map>

using namespace std;

struct GameState {
  int p1;
  int p2;
  int wolf;
  bool connected;
  bool winningPath;
  vector<GameState> neighboors;
  GameState(int p1, int p2, int wolf) {
    this.p1 = p1;
    this.p2 = p2;
    this.wolf = wolf;
    this.connected = false;
    this.winningPath = false;
};

class GameMap {
  public:
    map<int, GameState> gameMap;
  
  private:
  
}
