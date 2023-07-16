#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <cctype>
#include <list>
#include <unordered_set>

#define INVALID_RANGES cerr << "Invalid ranges." << endl;\
exit(1);
#define INVALID_CHARACTER(x) cerr << "Invalid character: " << x << endl;\
exit(1);
#define ENTER_TARGETS cerr << "Please enter the targets." << endl;\
exit(1);


using namespace std;


void adjustCoordinates(vector<int>& array, int x_limit, int y_limit) {
    for(int i = 0; i < array.size(); ++i){
        if(i%4 <= 1 && array[i] > x_limit){
            INVALID_RANGES
        }
        else if(i%4 > 1 && array[i] > y_limit){
            INVALID_RANGES
        }
        if(array[i]>0){
            continue;
        }        
        if(i%4 == 3){
            array[i] = y_limit;
            if(array[i]<array[i-1]){
                INVALID_RANGES
            }
        }
        else if(i%4 == 1){
            array[i] = x_limit;
            if(array[i]<array[i-1]){
                INVALID_RANGES
            }
        }
        else{
            array[i] = 1;
        }
    }
}//EOF adjustCoordinates


list<pair<vector<vector<int>>, vector<int>>> readBoard(string filename) {
    ifstream file(filename);
    string line;
    int index = 0;
    list<pair<vector<vector<int>>, vector<int>>> boards;
    vector<vector<int>> matrix;
    vector<int> array(12, 0);
    bool matrixComplete = false;

    while(getline(file, line)) {
        char c;
        if(line.empty()){
            continue;
        }
        if(line[0] == '(') {
            matrixComplete = true;
        }

        istringstream iss(line);
        if(!matrixComplete){
            vector<int> row;
            int value;
            while (iss >> value) {
                row.push_back(value);
            }
            matrix.push_back(row);
        }

        else{
            // Process array lines
            string numString = "";
            index += (4-(index%4))%4;
            while(iss.get(c)){
                if(c==':' || c==',' || c==')'){
                    if(numString==""){
                        INVALID_RANGES
                    }
                    array[index] = stoi(numString);
                    numString = "";
                    index++;
                    continue;
                }
                else if(c==' ' || c=='('){
                    continue;
                }
                else if(c==';'){
                    break;
                }
                else if(!isdigit(c)){
                    INVALID_CHARACTER(c)
                }
                else{
                    numString += c;
                }
            }//EOF while
        }//EOF else
        if(c==';'){
            if(matrix.size()==0){
                matrix = boards.back().first;
            }
            for(int i = 0; i < 12; i++){
                if(array[i]==0){
                    array[i] = boards.back().second[i];
                }
            }
            if(boards.size()==0){
                adjustCoordinates(array, matrix[0].size(), matrix.size());
            }
            boards.push_back({matrix, array});
            matrix.clear();
            matrix.resize(0);
            array.assign(12, 0);
            matrixComplete = false;
        }
    }

    return boards;
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
        ENTER_TARGETS
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
    spaces.erase(it);
    it = spaces.begin();
    advance(it, rand() % spaces.size());
    board[*it/width][*it%width] = 2;

    return board;
}//EOF randomBoard
