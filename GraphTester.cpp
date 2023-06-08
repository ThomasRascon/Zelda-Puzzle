#include "BoardReader.cpp"
#include "SolutionDensity.cpp"

using namespace std;

int main() {
    vector<vector<int>> board = readBoard("BoardConfigs/board1.txt");
    SolutionDensity(board);
}