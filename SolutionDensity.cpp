#include "ZeldaGraph.hpp"
#include "ZeldaGraph.cpp"
#include "Helper.cpp"
#include <memory>

using namespace std;


double SolutionDensity(vector<vector<int>> board, vector<int> coords){

    unique_ptr<GameGraph> graph = make_unique<GameGraph>(board, coords);
    graph->build();
    int totalFinalStates = 0;
    int numVisited = 0;

    for(const auto& target : graph->targetStates){
        if(target->visited){
            numVisited++;
        }
        totalFinalStates++;
    }

    if(totalFinalStates==0){
        return 0;
    }

    return (double)numVisited/totalFinalStates;
}//EOF solutionDensity
