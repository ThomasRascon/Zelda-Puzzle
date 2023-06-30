#include "Solutionness.cpp"

using namespace std;

int main() {
    auto info = readBoard("BoardConfigs/board1.txt");
    vector<vector<int>> board = info.first;
    vector<int> cords = info.second;
    std::cout << "Solutionness:" << solutionness(board) << endl;
    std::cout << "Ended successfuly";
}