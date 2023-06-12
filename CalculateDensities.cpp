#include <ctime>
#include "SolutionDensity.cpp"

int main(int argc, char* argv[]){
    int width;
    int height;
    int iterations;
    double density;
    srand(time(0));

    if(argc != 5){
        cout << "Please specify a width, height, probability density, and number of iterations." << endl;
        exit(1);
    }

    try{
        width = stoi(argv[1]);
        height = stoi(argv[2]);
        density = stod(argv[3]);
        iterations = stoi(argv[4]);
    } catch (const exception&){
        cout << "Please enter the correct types." << endl;
        exit(1);
    }

    for(int i = 0; i < iterations; ++i){
        vector<vector<int>> board = randomBoard(width, height, density);

        cout << endl << "Board " << i+1 << ":"<< endl;
        for(int row = 0; row < height; ++row){
            for(int col = 0; col < width; ++col){
                cout << board[row][col] << " ";
            }
            cout << endl;
        }
        cout << endl;

        cout << "Density: " << SolutionDensity(board) << endl;

    }//EOF iteration loop

    return 0;
}//EOF main