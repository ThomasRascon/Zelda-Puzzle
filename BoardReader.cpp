#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>

using namespace std;

vector<vector<int>> readBoard(string filename){
    ifstream infile(filename);
    string line;

    vector<vector<int>> configuration;

    while(getline(infile, line)) {
        istringstream iss(line);
        vector<int> row;

        int val;
        while(iss >> val) {
            row.push_back(val);
        }

        configuration.push_back(row);
    }//EOF while
    return configuration;
}//EOF readBoard


pair<pair<int,int>, pair<int,int>> findTargets(vector<vector<int>> board) {
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

    if(cords.size() != 4){
        cout << "Please enter the targets." << endl;
        exit(1);
    }

    pair<int,int> target_1 = {cords[0], cords[1]};
    pair<int,int> target_2 = {cords[2], cords[3]};

    return {target_1, target_2};
}//EOF findTargets


vector<vector<int>> randomBoard(int width, int height, double density) {

    vector<vector<int>> board = vector<vector<int>>(height, vector<int>(width, 0));
    for(int row = 0; row < height; ++row){
        for(int col = 0; col < width; ++col){
            int binarynum = 0;
            double rndDouble = (double)rand() / RAND_MAX;
            if(rndDouble < density){
                binarynum = 1;
            }
            board[row][col] = binarynum;
        }
    }

    int t1_row = rand() % height;
    int t1_col = rand() % width;
    int t2_row = rand() % height;
    int t2_col = rand() % width;

    while(t1_row == t2_row && t1_col == t2_col){
        t2_row = rand() % height;
        t2_col = rand() % width;
    }

    board[t1_row][t1_col] = 2;
    board[t2_row][t2_col] = 2;

    return board;
}//EOF randomBoard