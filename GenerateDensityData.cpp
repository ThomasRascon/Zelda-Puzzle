#include <ctime>
#include <fstream>
#include "SolutionDensity.cpp"

int main(int argc, char* argv[]){
    
    // arguments
    int width;
    int height;
    int sampleSize;
    double stepSize;

    // values output to file
    double average;
    double density;

    srand(time(0));

    if(argc != 5){
        cout << "Please specify a width, height, step size, and sample size." << endl;
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

    ofstream o;
    o.open("Density.dat");

    for(int stepIter=0; stepIter<floor(1./stepSize); stepIter++){  
        density = stepIter*stepSize;
        average = 0;
        for(int sampleIter=0; sampleIter<sampleSize; sampleIter++){
        
            //cout << average << endl;
            average += SolutionDensity(randomBoard(width, height, density));
            
        }
        //cout << endl;
        average = average/sampleSize;
        o << density << " " << average << endl;
    }
}