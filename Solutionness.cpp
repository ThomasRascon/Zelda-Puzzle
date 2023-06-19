#include "ZeldaGraph.hpp"
#include "ZeldaGraph.cpp"
#include "Helper.cpp"

using namespace std;


double solutionness(vector<vector<int>> board){

    GameGraph* graph = new GameGraph(board);
    graph->build("output.txt");
    double solutionRatio = 0;

    for(auto& target : graph->targetStates){
        graph->countOnTarget(target);
    }


    solutionRatio = (double)graph->getNumOnSoln() / graph->mapSize();

    cout << endl << "NumOnSoln: " << graph->getNumOnSoln() << endl 
         << "mapSize: " << graph->mapSize() << endl;
    if(graph->mapSize()==0){
        solutionRatio = 0;
    }

    delete graph;

    return solutionRatio;
}//EOF solutionDensity