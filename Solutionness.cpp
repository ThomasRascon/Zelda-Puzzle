//TODO: varify for small cases and statistically varify for large cases

#include "ZeldaGraph.hpp"
#include "ZeldaGraph.cpp"
#include "Helper.cpp"
#include <memory>

using namespace std;


double solutionness(vector<vector<int>> board, vector<int> coords){

    unique_ptr<GameGraph> graph = make_unique<GameGraph>(board, coords);
    if(!graph->build()){
        return -1.0;
    }
    double solutionRatio = 0;

    for(const auto& target : graph->targetStates){
        graph->countOnTarget(target);
    }
    
    solutionRatio = (double)graph->calcNumSolvableStarts() / graph->getNumStartStates();

    if(graph->getNumStartStates()==0){
        solutionRatio = 0;
    }

    return solutionRatio;
}//EOF solutionDensity
