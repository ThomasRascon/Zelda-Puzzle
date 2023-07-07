//TODO: varify for small cases and statistically varify for large cases

#include "ZeldaGraph.hpp"
#include "ZeldaGraph.cpp"
#include "Helper.cpp"
#include <memory>

using namespace std;


double solutionness(vector<vector<int>> board, vector<int> coords){

    unique_ptr<GameGraph> graph = make_unique<GameGraph>(board, coords);
    graph->build();
    double solutionRatio = 0;
    int i = 0;

    for(const auto& target : graph->targetStates){
        i += 1;
        cout << "Target"<< i << ":" << endl;
        graph->countOnTarget(target);
    }

    cout << graph->getNumStartStates() << " " << graph->getNumSolvableStarts() << endl;
    solutionRatio = (double)graph->getNumSolvableStarts() / graph->getNumStartStates();

    if(graph->getNumStartStates()==0){
        solutionRatio = 0;
    }

    return solutionRatio;
}//EOF solutionDensity
