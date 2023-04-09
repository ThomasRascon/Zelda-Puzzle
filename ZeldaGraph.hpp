#include <iostream>
#include <ostream>
#include <vector>
#include <map>

using namespace std;

struct GameState {
  int p1;
  int p2;
  int wolf;
  bool connected; // whether or not connected to initial state
  bool winningPath; // whether connected intial and final state
  bool hasBeenVisited;
  vector<char> validMoves; // all possible movements from current state
  vector<GameState> neighboors; // possible neighbors, corresponds to validMoves
  vector<int> winningNeighbors; // which neighbors have a path to final state, index of neighbors 
  GameState(int p1, int p2, int wolf) {
    this.p1 = p1;
    this.p2 = p2;
    this.wolf = wolf;
    this.connected = false;
    this.winningPath = false;
};


// all gamestates 
class GameGraph {
  private:
  
    map<int, GameState> gameMap;
    vector<int> configuration // board configuration
    // dimensions of configuration
    int length
    int width 
      
  public:
    
    // Recursively find path from initial to final states
    // FinalState has arbitrary wolf position
    vector<int> FindPath(GameState InitialState, GameState FinalState);

    // work from initial state
    // iterate through 4 possible directions, asking ValidMove if each direction is possible
    // for all possible moves:
      // check if possible moves have been created, if not create them
      // if possible move has not been visited, run GenerateNeighbors on it
    vector<GameState> GenerateNeighbors(GameState CurrentState);

    // uses configuration, which is a global variable and game rules to return whether
    // you can go from CurrentState to direction up, down, left, or right, specified 
    // by u, d, l, r
    bool ValidMove(GameState CurrentState, char move);
}
