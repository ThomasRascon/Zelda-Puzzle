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
  bool visited;
  bool moves[4]; // all possible movements from current state (order: Up, Down, Left, Right)
  GameState* neighbors[4]; // possible neighbors, corresponds to validMoves (nullptr if invalid)
  GameState(int p1, int p2, int wolf) {
    this->p1 = p1;
    this->p2 = p2;
    this->wolf = wolf;
    this->connected = false;
    this->visited = false;
  }
};


// all gamestates 
class GameGraph {
  private:
    // dimensions of configuration
    int length;
    int width;
    vector<vector<int>> configuration; // board configuration
    GameState* initalState;
    map<int, GameState*> gameMap;
      
  public:
  
    /**
     * GameGraph constructor
     */
    GameGraph(int length, int width, vector<vector<int>> configuration, int initalIdentifier);

    // work from initial state
    // iterate through 4 possible directions, asking ValidMove if each direction is possible
    // for all possible moves:
      // check if possible moves have been created, if not create them
      // if possible move has not been visited, run GenerateNeighbors on it
    // NOTE: This seems to also be defined in ZeldaGraph.cpp
    void generateNeighbors(GameState* currentState);
  
    // uses configuration, which is a global variable and game rules to return whether
    // you can go from CurrentState to direction up, down, left, or right, specified 
    // by u, d, l, r
    bool validMove(GameState* currentState, char move);
  
    /**
     * Takes in the current state and the move you wish to make and creates the ID of the next state
     */
    int generateID(GameState* currentState, char move);
  
    /**
     * Takes in the unique identifier of a state and creates it
     */
    GameState* createState(int ID);
};
