#include "ZeldaGraph.cpp"
#include "Helper.cpp"
#include <memory>

using namespace std;

#define PRINT_STATE cout << wolf.first+1 << "," << wolf.second+1 << "; " << p1.first+1\
                    << "," << p1.second+1 << "; " << p2.first+1 << "," << p2.second+1

int main() {
    auto boards = readBoard("BoardConfigs/board1.txt");
    int index = 1;
    for(auto const& config : boards){
        cout << endl << "Board " << index << ":" << endl;
        vector<vector<int>> board = config.first;
        vector<int> coords = config.second;
        bool finishedIter = false;

        pair<int,int> wolf={coords[0],coords[2]},p1={coords[4],coords[6]},p2={coords[8],coords[10]};
        PRINT_STATE;

        for(int i = 0; i < coords.size(); ++i){
            if(i%2 == 1){
                if(coords[i] != coords[i-1]){
                    cout << ":" << endl << "Specify exact start position, not a range" << endl;
                    finishedIter = true;
                }
            }
        }
        if(finishedIter){
            continue;
        }

        unique_ptr<GameGraph> graph = make_unique<GameGraph>(board, coords);
        if(!graph->build()){
            cout << ":" << endl << "INVALID START STATE" << endl;
            index++;
            continue;
        }

        list<char> solution = graph->solutionFinder(true);

        if(solution.size() == 0){
            cout << ":" << endl << "NO SOLUTION" << endl;
        }
        else{
            cout << " (" << solution.size() << " move";
            if(solution.size() > 1){
                cout << "s";
            }
            cout << "):" << endl;
            for(const char& move : solution){
                cout << move << " ";
            }
        }
        cout << endl;
        index++;
    }//EOF board configs loop
    cout << endl << "Ended successfuly" << endl;
}//EOF main