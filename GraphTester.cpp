#include "ZeldaGraph.hpp"
#include "ZeldaGraph.cpp" 
#include "BoardReader.cpp"

using namespace std;

int main() {
    vector<vector<int>> board = readBoard("board1.txt");
    vector<int> targets = findTargets(board);
    if(targets.size() != 4){
        cout << "Invalid input, exiting...\n";
        exit(1);
    }
    pair<int,int> target_1 = {targets[0], targets[1]};
    pair<int,int> target_2 = {targets[2], targets[3]};

    GameGraph* graph = new GameGraph(board, target_1, target_2);
    graph->build("output.txt");
}