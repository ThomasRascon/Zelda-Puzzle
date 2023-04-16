#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

vector<vector<int>> readBoard(string filename){
    std::ifstream infile(filename);
    std::string line;

    std::vector<std::vector<int>> configuration;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::vector<int> row;

        int val;
        while (iss >> val) {
            row.push_back(val);
        }

        configuration.push_back(row);
    }//EOF while
    return configuration;
}//EOF readBoard

int main() {

    vector<vector<int>> board = readBoard("board1.txt");
    
    for(const auto& row:board) {
        for(const auto& val:row) {

            
            cout << val << " ";
        }
        cout << "\n";
    }

    return 0;       
}

