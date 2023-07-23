#ifndef ZELDA_GRAPH_H
#define ZELDA_GRAPH_H

#include <iostream>
#include <ostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <list>

using namespace std;


struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

struct GameState {
  pair<int,int> p1;
  pair<int,int> p2;
  pair<int,int> wolf;
  int numPrev;
  bool visited;
  bool target;
  bool onSolution;    //if you can get from this state to a target state
  bool moves[4]{};    //all possible movements from current state (order: Up, Down, Left, Right)
  GameState* neighbors[4]{};  // possible neighbors, corresponds to validMoves (nullptr if invalid)
  list<pair<GameState*, char>> parents; //list of all states connecting to this state
  GameState(pair<int,int> p1, pair<int,int> p2, pair<int,int> wolf, bool target) {
    this->p1 = p1;
    this->p2 = p2;
    this->wolf = wolf;
    this->visited = false;
    this->onSolution = false;
    this->target = target;
    this->numPrev = -1;
  }
};


// all gamestates 
class GameGraph {
  private:
    // dimensions of configuration
    int length;
    int width;
    int shortest_length;
    int numStartStates;
    int numSolvableStarts;
    pair<int,int> target_1;
    pair<int,int> target_2;
    const vector<int> coords;
    list<char> shortest_solution;
    list<char> longest_solution;
    const vector<vector<int>> configuration; // board configuration
    unordered_map<pair<int,int>, GameState*, pair_hash> gameMap;
      
  public:
    list<GameState*> targetStates;
  
    /**
     * GameGraph constructor
     */
    GameGraph(vector<vector<int>> configuration, vector<int> coords);

    /**
     * GameGraph destructor
     */
    ~GameGraph();

    int calcNumSolvableStarts();

    int getNumStartStates();

    int mapSize();
  
    void populateMap();

    // work from initial state
    // iterate through 4 possible directions, asking ValidMove if each direction is possible
    // for all possible moves:
      // check if possible moves have been created, if not create them
      // if possible move has not been visited, run GenerateNeighbors on it
    // NOTE: This seems to also be defined in ZeldaGraph.cpp
    void createConnections(GameState* currentState);

    void countOnTarget(GameState* currentState);

    list<char> solutionFinder(bool shortest);

    void solutionDFS(GameState* currentState, list<char>& move_history,
        int path_size, unordered_set<GameState*> visited_states, bool shortest);
  
    void findTargetStates();
  
    /**
     * Takes in the unique identifier of a state and creates it
     */
    GameState* createState(pair<int,int> ID, bool target);
  
    bool build();
};

#endif