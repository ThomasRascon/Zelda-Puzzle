#include <ctime>
#include "ZeldaGraph.hpp"
#include "ZeldaGraph.cpp"
//#include "BoardReader.cpp"
#include "Helper.cpp"

using namespace std;


double SolutionDensity(vector<vector<int>> board){

    GameGraph* graph = new GameGraph(board);
    graph->build("output.txt");
    auto targets = findTargets(board);
    int totalFinalStates = 0;
    int numVisited = 0;
    int width = board[0].size();
    int height = board.size();

    for(int wolfIter = 0; wolfIter < width*height; ++wolfIter){

        int wolf_x = wolfIter % width;
        int wolf_y = wolfIter / width;

        if(board[wolf_y][wolf_x] == 2 || board[wolf_y][wolf_x] == 0){
            continue;
        }

        pair<int,int> wolf = {wolf_x, wolf_y};
        pair<int,int> ID_1 = pairsToID(wolf, targets.first, targets.second);
        pair<int,int> ID_2 = pairsToID(wolf, targets.second, targets.first);
        GameState* state_1 = graph->getGameState(ID_1);
        GameState* state_2 = graph->getGameState(ID_2);

        if(state_1->visited){
            numVisited++;
        }
        if(state_2->visited){
            numVisited++;
        }
        totalFinalStates += 2;
    }//EOF wolf loop

    return (double)numVisited/totalFinalStates;
}//EOF solutionDensity


int main(int argc, char* argv[]){
    int width;
    int height;
    int iterations;
    double density;
    srand(time(0));

    if(argc != 5){
        cout << "Please specify a width, heigh, probability density, and number of iterations." << endl;
        exit(1);
    }
    try
    {
        width = stoi(argv[1]);
        height = stoi(argv[2]);
        density = stod(argv[3]);
        iterations = stoi(argv[4]);
    }
    catch (const exception&)
    {
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

        cout << SolutionDensity(board) << endl;

    }//EOF iteration loop

    return 0;
}//EOF main