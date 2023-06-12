#include "SolutionDensity.cpp"

using namespace std;

int main() {

    vector<vector<int>> board = readBoard("BoardConfigs/board1.txt");
    cout << "Density:" << SolutionDensity(board) << endl;
    cout << "Ended successfuly";
}