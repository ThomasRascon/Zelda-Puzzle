#include "ZeldaGraph.hpp"
#include "ZeldaGraph.cpp"
#include "Helper.cpp"
#include <memory>

using namespace std;


double solutionDensity(vector<vector<int>> board, vector<int> coords){

    unique_ptr<GameGraph> graph = make_unique<GameGraph>(board, coords);
    if(!graph->build()){
        return -1.0;
    }
    int totalFinalStates = 0;
    int numVisited = 0;

    for(const auto& target : graph->targetStates){
        if(insideOfRange(target, coords)){
            if(target->visited){
                numVisited++;
            }
            totalFinalStates++;
        }
    }

    if(totalFinalStates==0){
        return 0;
    }

    return (double)numVisited/totalFinalStates;
}//EOF solutionDensity