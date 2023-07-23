#define SOLN_DENSITY 1

#if SOLN_DENSITY==1
#include "SolutionDensity.cpp"
#define FUNC(board, coords) solutionDensity(board, coords)
#define RESULT_TYPE "Solution Density"
#else
#include "Solutionness.cpp"
#define FUNC(board, coords) solutionness(board, coords)
#define RESULT_TYPE "Solutionness"
#endif


using namespace std;

int main() {
    auto boards = readBoard("BoardConfigs/board1.txt");
    int index = 1;
    for(auto const& config : boards){
        cout << endl << "Board " << index << ":" << endl;
        vector<vector<int>> board = config.first;
        vector<int> coords = config.second;
        double result = FUNC(board, coords);
        if(result < 0){
            cout << "INVALID RANGES" << endl;
            continue;
        }
        cout << RESULT_TYPE << ": " << result << endl; 
        index++;
    }
    cout << endl << "Ended successfuly" << endl;
}