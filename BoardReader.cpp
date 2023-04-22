#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

vector<vector<int>> readBoard(string filename){
    std::ifstream infile(filename);
    std::string line;

    std::vector<std::vector<int>> configuration;

    while(std::getline(infile, line)) {
        std::istringstream iss(line);
        std::vector<int> row;

        int val;
        while(iss >> val) {
            row.push_back(val);
        }

        configuration.push_back(row);
    }//EOF while
    return configuration;
}//EOF readBoard


vector<int> findTargets(vector<vector<int>> board) {
    int length = board.size();
    int width = board[0].size();
    vector<int> cords;
    for(int i = 0; i < length; ++i){
        for(int j = 0; j < width; ++j){
            if(board[i][j]==2){
                cords.push_back(j);
                cords.push_back(i);
            }
        }
    }
    return cords;
}//EOF findTargets