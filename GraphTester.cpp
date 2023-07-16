#define SOLN_DENSITY 0

#if SOLN_DENSITY==1
#include "SolutionDensity.cpp"
#define FUNC(board, coords) cout << "Solution Density:" << solutionDensity(board, coords) << endl
#else
#include "Solutionness.cpp"
#define FUNC(board, coords) cout << "Solutionness: " << solutionness(board, coords) << endl
#endif


using namespace std;

int main() {
    auto boards = readBoard("BoardConfigs/board1.txt");
    int index = 1;
    for(auto const& config : boards){
        cout << endl << "Board " << index << ":" << endl;
        vector<vector<int>> board = config.first;
        vector<int> coords = config.second;
        FUNC(board, coords);
        index++;
    }
    cout << endl << "Ended successfuly";
}