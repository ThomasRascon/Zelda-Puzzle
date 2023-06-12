#include <ctime>
#include "SolutionDensity.cpp"
#include <fstream>

int main(int argc, char* argv[]){
    
    // arguments
    int width;
    int height;
    int iterations;
    double density;
    string outputFile;
    
    srand(time(0));

    if(argc != 5){
        cout << "Please specify a width, height, probability density, number of iterations, and output file name." << endl;
        exit(1);
    }

    try{
        width = stoi(argv[1]);
        height = stoi(argv[2]);
        density = stod(argv[3]);
        iterations = stoi(argv[4]);
        outputFile = argv[5];
    } catch (const exception&){
        cout << "Please enter the correct types." << endl;
        exit(1);
    }

    ofstream o;
    o.open("OutputFiles/"+outputFile);

    for(int i = 0; i < iterations; ++i){
        vector<vector<int>> board = randomBoard(width, height, density);

        o << endl << "Board " << i+1 << ":"<< endl;
        for(int row = 0; row < height; ++row){
            for(int col = 0; col < width; ++col){
                o << board[row][col] << " ";
            }
            o << endl;
        }
        o << endl;

        o << "Density: " << SolutionDensity(board) << endl;

    }//EOF iteration loop

    return 0;
}//EOF main