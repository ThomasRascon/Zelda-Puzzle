#include "ZeldaGraph.hpp"
#include "BoardReader.cpp"

using namespace std;

int main() {
    vector<vector<int>> board = readBoard("BoardConfigs/board1.txt");
    GameGraph* graph = new GameGraph(board);
    graph->build("OutputFiles/output.txt");
}