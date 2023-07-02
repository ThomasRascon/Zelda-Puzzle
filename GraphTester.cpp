#include "Solutionness.cpp"

using namespace std;

int main() {
    auto info = readBoard("BoardConfigs/board1.txt");
    vector<vector<int>> board = info.first;
    vector<int> coords = info.second;
    cout << "Solutionness:" << solutionness(board, coords) << endl;
    cout << "Ended successfuly";
}