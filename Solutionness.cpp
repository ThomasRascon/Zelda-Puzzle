//TODO: varify for small cases and statistically varify for large cases

#include "ZeldaGraph.hpp"
#include "ZeldaGraph.cpp"
#include "Helper.cpp"

using namespace std;


double solutionness(vector<vector<int>> board, vector<int> cords){

    GameGraph* graph = new GameGraph(board, cords);
    graph->build();
    double solutionRatio = 0;

    for(const auto& target : graph->targetStates){
        graph->countOnTarget(target);
    }

    solutionRatio = (double)graph->getNumSolvableStarts() / graph->getNumStartStates();

    if(graph->getNumStartStates()==0){
        solutionRatio = 0;
    }

    delete graph;

    return solutionRatio;
}//EOF solutionDensity
