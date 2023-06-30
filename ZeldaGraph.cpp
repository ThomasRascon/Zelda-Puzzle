#include "ZeldaGraph.hpp"
#include "Helper.cpp"
#include "BoardReader.cpp"
#include <fstream>

using namespace std;


//Declare the array of move types
const char moveTypes[4] = {'U','D','L','R'};


GameGraph::GameGraph(vector<vector<int>> configuration)
    : configuration(configuration)
{
    this->length = configuration.size();
    this->width = configuration[0].size();
    this->numOnSoln = 0;

    auto targets = findTargets(configuration);
    this->target_1 = targets.first;
    this->target_2 = targets.second;
}//EOF GameGraph constructor


void GameGraph::countOnTarget(GameState* currentState) {
    currentState->onSolution = true;
    numOnSoln++;
    for(auto parent : currentState->parents){
        if(!parent->onSolution){
            countOnTarget(parent);
        }
    }
}//EOF countOnTarget


int GameGraph::getNumOnSoln() {
    return numOnSoln;
}//EOF getNumOnSoln


int GameGraph::mapSize() {
    return gameMap.size();
}//EOF mapSize


GameState* GameGraph::createState(pair<int,int> ID, bool target) {
	//ex ID={2312 78900137} -> ID.first=2312, newWolf={23,12}
	//ID.second = 78900137, newP1={78,90}, newP2={01,37}
    pair<int,int> newWolf = {ID.first / 100, ID.first % 100};	//{first two digits of wolf, last two digits of wolf} 
    pair<int,int> newP1 = {ID.second/1000000, (ID.second/10000)%100};  //{first two digits of ID.second, 3rd and 4th digit}
    pair<int,int> newP2 = {(ID.second/100)%100, ID.second%100};  //{5th and 6th digit, last two digits}

    GameState* newState = new GameState(newP1, newP2, newWolf, target); //creates new state
    return newState;
}//EOF createState method


void GameGraph::populateMap() {
	//iterate through the possible positions of the wolf
	for(int i = 0; i < this->length*this->width; ++i){
		int wolf_x = i % width;
		int wolf_y = i / width;
		
		//if this is not a valid space...
		if(configuration[wolf_y][wolf_x]==0){
			continue;	//move to the next space
		}

		pair<int,int> wolf = {wolf_x, wolf_y};

		//iterate through the possible positions of piece 1
		for(int j = 0; j < this->length*this->width; ++j){
			//if wolf and p1 collide...
			if(j==i){
				continue;
			}
			
			int p1_x = j % width;
			int p1_y = j / width;
		
			//if this is not a valid space...
			if(configuration[p1_y][p1_x]==0){
				continue;	//move to the next space
			}
		
			pair<int,int> p1 = {p1_x, p1_y};

			//iterate through the possible positions of piece 2
			for(int k = 0; k < this->length*this->width; ++k){
				
				//if p2 collides with wolf or p1...
				if(k==i || k==j){
					continue;
				}
				
				int p2_x = k % width;
				int p2_y = k / width;

				//if this is not a valid space...
				if(configuration[p2_y][p2_x]==0){
					continue;	//move to the next space
				}

				pair<int,int> p2 = {p2_x, p2_y};

                bool p1Final = (p1==this->target_1 || p1==this->target_2);	//if p1 is on a final position
                bool p2Final = (p2==this->target_1 || p2==this->target_2);	//if p2 is on a final position
                bool isTarget = p1Final && p2Final;
                        
                pair<int,int> ID = pairsToID(wolf, p1, p2);		//creat its ID
				GameState* state = createState(ID, isTarget);   //create the new state
				gameMap.insert({ID, state});					//insert it into the map

			}//EOF p2 for loop
		}//EOF p1 for loop
	}//EOF wolf for loop
}//EOF populateMap


void GameGraph::createConnections(GameState* currentState) {
    currentState->visited = true;
    if(currentState->target){
        return;
    }
    
    for(int i = 0; i < 4; ++i){  

        char move = moveTypes[i];

        //if the move is not valid...
        if(!validMove(configuration, currentState, move)){
            continue;
        }
            
        auto neighborID = generateID(configuration, currentState, move);        //identifier of the neighbor
        GameState* neighbor = gameMap.find(neighborID)->second;  //search the gameMap for the neighbor
        neighbor->parents.push_back(currentState);
        
        //if the neighbor has not been visited yet...
        if(!neighbor->visited){
            createConnections(neighbor);	//recurrsively call createConnections on the neighbor
        }
        
        currentState->moves[i] = true;            //Since the move is valid
        currentState->neighbors[i] = neighbor;    //ith neighbor of currentState is neighbor (created above)

    }//EOF for loop (moves loop)
}//EOF createConnections method


void GameGraph::findTargetStates() {
    for(int wolfIter = 0; wolfIter < width*length; ++wolfIter){

        int wolf_x = wolfIter % width;
        int wolf_y = wolfIter / width;

        if(configuration[wolf_y][wolf_x] == 2 || configuration[wolf_y][wolf_x] == 0){
            continue;
        }

        pair<int,int> wolf = {wolf_x, wolf_y};
        pair<int,int> ID_1 = pairsToID(wolf, target_1, target_2);
        pair<int,int> ID_2 = pairsToID(wolf, target_2, target_1);
        targetStates.push_back(gameMap.find(ID_1)->second);
        targetStates.push_back(gameMap.find(ID_2)->second);
        
    }//EOF wolf loop
}//EOF findTargetStates


void GameGraph::build() {
	populateMap();
	for(auto pair : gameMap){
		GameState* curr = pair.second;
		if(curr->visited || curr->target){
            continue;
        }
        createConnections(curr);
	}//EOF for
    findTargetStates();
}//EOF build


GameGraph::~GameGraph(){
    for(auto const& entry : gameMap){
        delete entry.second;
    }
}//EOF destructor
