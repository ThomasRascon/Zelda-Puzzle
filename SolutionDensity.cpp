#include "ZeldaGraph.hpp"
#include "ZeldaGraph.cpp"
#include "Helper.cpp"

using namespace std;


double SolutionDensity(vector<vector<int>> board){

    GameGraph* graph = new GameGraph(board);
    graph->build("output.txt");
    auto targets = findTargets(board);
    int totalFinalStates = 0;
    int numVisited = 0;
    int width = board[0].size();
    int height = board.size();

    for(int wolfIter = 0; wolfIter < width*height; ++wolfIter){

        int wolf_x = wolfIter % width;
        int wolf_y = wolfIter / width;

        if(board[wolf_y][wolf_x] == 2 || board[wolf_y][wolf_x] == 0){
            continue;
        }

        pair<int,int> wolf = {wolf_x, wolf_y};
        pair<int,int> ID_1 = pairsToID(wolf, targets.first, targets.second);
        pair<int,int> ID_2 = pairsToID(wolf, targets.second, targets.first);
        GameState* state_1 = graph->getGameState(ID_1);
        GameState* state_2 = graph->getGameState(ID_2);

        if(state_1->visited){
            numVisited++;
        }
        if(state_2->visited){
            numVisited++;
        }
        totalFinalStates += 2;
    }//EOF wolf loop

    if(totalFinalStates==0) {
        totalFinalStates=1;
    }

    return (double)numVisited/totalFinalStates;
}//EOF solutionDensity


