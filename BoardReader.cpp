#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm>
#include <cctype>
#include <unordered_set>

using namespace std;


void adjustCoordinates(vector<int>& array, int x_limit, int y_limit) {
    for(int i = 0; i < array.size(); ++i){
        if(i%4==1 && array[i] > x_limit){
            std::cerr << "Invalid range out of bounds." << endl;
            exit(1);
        }
        if(i%4==3 && array[i] > y_limit){
            std::cerr << "Invalid range out of bounds." << endl;
            exit(1);
        }
        if(array[i]>=0){
            continue;
        }        
        if(i%4 == 3){
            array[i] = y_limit;
            if(array[i]<array[i-1]){
                std::cerr << "Invalid ranges." << endl;
                exit(1);
            }
        }
        else if(i%4 == 1){
            array[i] = x_limit;
            if(array[i]<array[i-1]){
                std::cerr << "Invalid ranges." << endl;
                exit(1);
            }
        }
        else{
            array[i] = 0;
        }
    }
}//EOF adjustCoordinates


pair<vector<vector<int>>, vector<int>> readBoard(string filename) {
    ifstream file(filename);
    string line;
    int index = 0;
    vector<vector<int>> matrix;
    vector<int> array(12, -1);
    bool matrixComplete = false;

    while(std::getline(file, line)) {
        if(line.empty() || line[0] == '(') {
            matrixComplete = true;
        }

        std::istringstream iss(line);
        if(!matrixComplete){
            std::vector<int> row;
            int value;
            while (iss >> value) {
                row.push_back(value);
            }
            matrix.push_back(row);
        }

        else{
            // Process array lines
            char c;
            string numString = "";
            index += (4-(index%4))%4;
            while(iss.get(c)){
                for(int entry : array){
                    std::cout << entry << " ";
                }
                std::cout << endl;
                std::cout << c << endl;
                if(c==':' || c==',' || c==')'){
                    if(numString==""){
                        std::cerr << "Invalid ranges." << endl;
                        exit(1);
                    }
                    array[index] = stoi(numString);
                    numString = "";
                    index++;
                    continue;
                }
                else if(c==' ' || c=='('){
                    continue;
                }
                else if(!isdigit(c)){
                    std::cerr << "Invalid character" << endl;
                    exit(1);
                }
                else{
                    numString += c;
                }
            }
        }
        std::cout << endl;
    }

    adjustCoordinates(array, matrix[0].size()-1, matrix.size()-1);

    // Print the matrix
    std::cout << "Matrix:" << endl;
    for (const auto& row : matrix) {
        for (const auto& value : row) {
            std::cout << value << ' ';
        }
        std::cout << endl;
    }

    // Print the array
    std::cout << "Array: ";
    for (const auto& value : array) {
        std::cout << value << ' ';
    }
    std::cout << endl;

    return {matrix, array};
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
        std::cout << "Please enter the targets." << endl;
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
    std::advance(it, rand() % spaces.size());
    board[*it/width][*it%width] = 2;
    spaces.erase(it);
    it = spaces.begin();
    std::advance(it, rand() % spaces.size());
    board[*it/width][*it%width] = 2;

    return board;
}//EOF randomBoard