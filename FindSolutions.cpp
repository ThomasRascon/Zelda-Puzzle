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
        for(int i = 0; i < coords.size(); ++i){
            if(i%2 == 1){
                if(coords[i] != coords[i-1]){
                    cout << "Specify exact start position, not a range.";
                    exit(1);
                }
            }
        }
        unique_ptr<GameGraph> graph = make_unique<GameGraph>(board, coords);
        graph->build();
        pair<int,int> wolf={coords[0],coords[2]},p1={coords[4],coords[6]},p2={coords[8],coords[10]};
        list<char> solution = graph->solutionFinder(wolf, p1, p2, false);
        cout << wolf.first+1 << "," << wolf.second+1 << "; " << p1.first+1 << "," << p1.second+1 <<
        "; " << p2.first+1 << "," << p2.second+1 << " (" << solution.size() << " moves):" << endl;
        for(const char& move : solution){
            cout << move << " ";
        }
        cout << endl;
        index++;
    }
    cout << endl << "Ended successfuly";
}//EOF main