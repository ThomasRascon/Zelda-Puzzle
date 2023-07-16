#include "ZeldaGraph.cpp"
#include "Helper.cpp"
#include <memory>

using namespace std;

int main() {
    auto boards = readBoard("BoardConfigs/board1.txt");
    int index = 1;
    for(auto const& config : boards){
        cout << endl << "Board " << index << ":" << endl;
        vector<vector<int>> board = config.first;
        vector<int> coords = config.second;
        unique_ptr<GameGraph> graph = make_unique<GameGraph>(board, coords);
        graph->build(true);
        index++;
    }
    cout << endl << "Ended successfuly";
}