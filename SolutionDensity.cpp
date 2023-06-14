#include "ZeldaGraph.hpp"
#include "ZeldaGraph.cpp"
#include "Helper.cpp"

using namespace std;


double SolutionDensity(vector<vector<int>> board){

    GameGraph* graph = new GameGraph(board);
    graph->build("output.txt");
    int totalFinalStates = 0;
    int numVisited = 0;

    for(const auto& target : graph->targetStates){
        if(target->visited){
            numVisited++;
        }
        totalFinalStates++;
    }

    delete graph;

    if(totalFinalStates==0){
        return 0;
    }

    return (double)numVisited/totalFinalStates;
}//EOF solutionDensity