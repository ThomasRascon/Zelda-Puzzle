#include "ZeldaGraph.hpp"
#include "ZeldaGraph.cpp"
#include "Helper.cpp"
#include <memory>

using namespace std;


double solutionDensity(const vector<vector<int>>& board, const vector<int>& coords){

    unique_ptr<GameGraph> graph = make_unique<GameGraph>(board, coords);
    if(!graph->build()){
        return -1.0;
    }

    list<GameState*> visitedTargets = graph->findVisitedTargets();
    int numVisitedTargets = 0;
    for(const auto& target : visitedTargets){
        if(insideOfRange(target, coords)){
            numVisitedTargets++;
        }
    }
    int totalTargetStates = graph->getNumTargetsInRange();

    if(totalTargetStates==0){
        return 0;
    }

    return (double)numVisitedTargets / totalTargetStates;
}//EOF solutionDensity