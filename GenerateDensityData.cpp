// TODO: run for large board, large space density, small samp size
//       run for large board, low space density, large samp
//       formatting console output
//       generate data for various moderate board sizes for large samp size to graph

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


    double tempDensity;
    int t = time(0);    

    srand(1);

    if(argc != 6){
        cout << "Please specify a width, height, sample size, step size, and output file name." << endl;
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

    for(int stepIter=0; stepIter<floor(1/stepSize); stepIter++){  
        density = stepIter*stepSize;
        average = 0;

        for(int sampleIter=1; sampleIter<=sampleSize; sampleIter++){
        
            vector<vector<int>> board = randomBoard(width, height, density);

            cout << endl << "Board:"<< endl;
            for(int row = 0; row < height; ++row){
                for(int col = 0; col < width; ++col){
                    cout << board[row][col] << " ";
                }
                cout << endl;
            }
            cout << endl;

            tempDensity = SolutionDensity(board);
            average += tempDensity;

            t = time(0)-t;
            cout << "Space Density: " << density << endl
                 << "Sample number: " << sampleIter << endl
                 << "Solution Density: " << tempDensity << endl
                 << "Time to calculate: " << t/60 << ":" << t%60 << endl;
            t = time(0);
            
        }
        cout << endl;
        average = average/sampleSize;
        o << density << " " << average << endl;
    }
}