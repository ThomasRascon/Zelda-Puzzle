#include "ZeldaGraph.hpp"
#include "ZeldaGraph.cpp"
#include "Helper.cpp"

using namespace std;


double solutionness(vector<vector<int>> board){

    GameGraph* graph = new GameGraph(board);
    graph->build();
    int solutionRatio = 0;

    for(auto& target : graph->targetStates){
        graph->countOnTarget(target);
    }

    solutionRatio = (double)graph->getNumOnSoln() / graph->mapSize();

    delete graph;

    if(graph->mapSize()==0){
        return 0;
    }

    return solutionRatio;
}//EOF solutionDensity