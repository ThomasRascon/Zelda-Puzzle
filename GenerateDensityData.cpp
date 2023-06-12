// TODO: Program stops abruptly for larger boards.
//       For 10 by 10, it stops in the early 6's, 
//       and for 15 by 15, it stops in the early 5's.

#include <ctime>
#include <fstream>
#include "SolutionDensity.cpp"

int main(int argc, char* argv[]){
    
    // arguments
    int width;
    int height;
    int sampleSize;
    double stepSize;
    string outputFile;

    // values output to file
    double average;
    double density;


    int t = time(0);

    srand(time(0));

    if(argc != 6){
        cout << "Please specify a width, height, step size, sample size, and output file name." << endl;
        exit(1);
    }
    try{
        width = stoi(argv[1]);
        height = stoi(argv[2]);
        sampleSize = stod(argv[3]);
        stepSize = stod(argv[4]);
        outputFile = argv[5];
    } catch (const exception&){
        cout << "Please enter the correct types." << endl;
        exit(1);
    }

    ofstream o;
    o.open("OutputFiles/"+outputFile);

    for(int stepIter=0; stepIter<floor(1./stepSize); stepIter++){  
        density = stepIter*stepSize;
        average = 0;
        //cout << stepIter << " " << floor(1./stepSize) << endl;
        for(int sampleIter=0; sampleIter<sampleSize; sampleIter++){
        
            vector<vector<int>> board = randomBoard(width, height, density);

            cout << endl << "Board:"<< endl;
            for(int row = 0; row < height; ++row){
                for(int col = 0; col < width; ++col){
                    cout << board[row][col] << " ";
                }
                cout << endl;
            }
            cout << endl;

            average += SolutionDensity(board);
            cout << stepIter << " " << sampleIter << " " << time(0)-t << endl;
            t = time(0);
            
        }
        cout << endl;
        average = average/sampleSize;
        o << density << " " << average << endl;
    }
}