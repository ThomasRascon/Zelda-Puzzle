// TODO: run for large board, large space density, small samp size
//       run for large board, low space density, large samp
//       formatting console output
//       generate data for various moderate board sizes for large samp size to graph
//       plot all solution densities as a scatter plot/ heat map
//       rewrite for solutionness
#include <ctime>
#include <fstream>

#define SOLN_DENSITY 0

#if SOLN_DENSITY==1
#include "SolutionDensity.cpp"
#define FUNC(board, coords) solutionDensity(board, coords)
#define RESULT_TYPE "SolutionDensity"
#else
#include "Solutionness.cpp"
#define FUNC(board, coords) solutionness(board, coords)
#define RESULT_TYPE "Solutionness"
#endif

using namespace std;

int main(int argc, char* argv[]){

    // arguments
    int width;
    int height;
    int sampleSize;
    double stepSize;

    // values output to file
    double average;
    double density;

    vector<int> coords(12, -1);
    string outputFile;
    double tempDensity;
    int t = time(0); 
    srand(1);

    if(argc != 5){
        cout << "Please specify a width, height, sample size, and step size." << endl;
        exit(1);
    }
    try{
        width = stoi(argv[1]);
        height = stoi(argv[2]);
        sampleSize = stod(argv[3]);
        stepSize = stod(argv[4]);
    } catch (const exception&){
        cout << "Please enter the correct types." << endl;
        exit(1);
    }

    adjustCoordinates(coords, width-1, height-1);

    string place = RESULT_TYPE;
    outputFile = to_string(width)+"by"+to_string(height)+
                 "Sampling"+to_string(sampleSize)+".dat";
    ofstream o;
    o.open("OutputFiles/"+place+"/"+outputFile);

    ofstream o2;
    o2.open("OutputFiles/"+place+"/AllPointsOf"+outputFile);

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

            tempDensity = FUNC(board, coords);
            o2 << density << " " << tempDensity << endl;
            average += tempDensity;

            t = time(0)-t;
            cout << "Space Density: " << density << endl
                 << "Sample number: " << sampleIter << endl
                 << RESULT_TYPE << ": " << tempDensity << endl
                 << "Time to calculate: " << t/60 << ":" << t%60 << endl;
            t = time(0);
            
        }
        cout << endl;
        average = average/sampleSize;
        o << density << " " << average << endl;
    }
}
