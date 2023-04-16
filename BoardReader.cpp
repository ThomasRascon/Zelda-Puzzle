#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

vector<vector<int>> readBoard(string filename){
    std::ifstream infile("filename.txt");
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
}//EOF readBoard
