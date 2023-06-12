#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <unordered_set>

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
    unordered_set<int> spaces;
    int numSpaces = 0;
    for(int row = 0; row < height; ++row){
        for(int col = 0; col < width; ++col){
            double rndDouble = (double)rand() / RAND_MAX;
            if(rndDouble < density){
                board[row][col] = 1;
                spaces.insert(row*width+col);
                numSpaces++;
            }
        }
    }

    if(numSpaces < 3){
        board[0][0] = 2;
        board[0][1] = 2;
        return board;
    }

    auto it = spaces.begin();
    advance(it, rand() % spaces.size());
    board[*it/width][*it%width] = 2;
    // cout << *it/width << " " << *it%width << endl << 
    //         spaces.size() << endl;
    spaces.erase(it);
    it = spaces.begin();
    //cout << spaces.size() << endl;
    advance(it, rand() % spaces.size());
    // cout << *it/width << " " << *it%width << endl << 
    //         spaces.size() << endl;
    board[*it/width][*it%width] = 2;

    return board;
}//EOF randomBoard