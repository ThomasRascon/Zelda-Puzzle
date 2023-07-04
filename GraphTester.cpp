#define SOLN_DENSITY 0

#if SOLN_DENSITY==1
#include "SolutionDensity.cpp"
#define FUNC(board, coords) cout << "Solution Density:" << solutionDensity(board, coords) << endl
#else
#include "Solutionness.cpp"
#define FUNC(board, coords) cout << "Solutionness:" << solutionness(board, coords) << endl
#endif


using namespace std;

int main() {
    auto info = readBoard("BoardConfigs/board1.txt");
    vector<vector<int>> board = info.first;
    vector<int> coords = info.second;
    FUNC(board, coords);
    cout << "Ended successfuly";
}