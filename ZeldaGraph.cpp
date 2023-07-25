#include "ZeldaGraph.hpp"
#include "Helper.cpp"
#include "BoardReader.cpp"
#include <fstream>
#include <limits>

using namespace std;


//Declare the array of move types
const char MOVES[4] = {'U','D','L','R'};


GameGraph::GameGraph(vector<vector<int>> configuration, vector<int> coords) 
    : configuration(configuration), coords(coords)
{
    this->length = configuration.size();
    this->width = configuration[0].size();
    this->numSolvableStarts = 0;
    this->numTargetsInRange = 0;
    this->shortest_length = numeric_limits<int>::max();
    this->numStartStates = 0;

    auto targets = findTargets(configuration);
    this->target_1 = targets.first;
    this->target_2 = targets.second;
}//EOF GameGraph constructor


GameState* GameGraph::createState(pair<int,int> ID, bool target) {
    pair<int,int> newWolf = {ID.first / 100, ID.first % 100};	//{first two digits of wolf, last two digits of wolf} 
    pair<int,int> newP1 = {ID.second/1000000, (ID.second/10000)%100};  //{first two digits of ID.second, 3rd and 4th digit}
    pair<int,int> newP2 = {(ID.second/100)%100, ID.second%100};  //{5th and 6th digit, last two digits}

    GameState* newState = new GameState(newP1, newP2, newWolf, target); //creates new state
    return newState;
}//EOF createState method


list<GameState*> GameGraph::populateMap() {
    list<GameState*> statesInRange;
	//iterate through the possible positions of the wolf
	for(int i = width*coords[2]+coords[0]; i <= width*coords[3]+coords[1]; ++i){
        bool first = true;

		int wolf_x = i % width;
        if(wolf_x > coords[1]){
            i += width-(coords[1]+1)+coords[0];
            wolf_x = i % width;
        }
		int wolf_y = i / width;
		
		//if this is not a valid space...
		if(configuration[wolf_y][wolf_x]==0){
			continue;	//move to the next space
		}

		pair<int,int> wolf = {wolf_x, wolf_y};

		//iterate through the possible positions of piece 1
		for(int j = width*coords[6]+coords[4]; j <= width*coords[7]+coords[5]; ++j){

			int p1_x = j % width;
            if(p1_x > coords[5]){
                    j += width-(coords[5]+1)+coords[4];
                    p1_x = j % width;
            }
            int p1_y = j / width;

            //if wolf and p1 collide...
			if(j==i){
				continue;
			}
		
			//if this is not a valid space...
			if(configuration[p1_y][p1_x]==0){
				continue;	//move to the next space
			}
		
			pair<int,int> p1 = {p1_x, p1_y};

			//iterate through the possible positions of piece 2
			for(int k = width*coords[10]+coords[8]; k <= width*coords[11]+coords[9]; ++k){
			
				int p2_x = k % width;
                if(p2_x > coords[9] || p2_x < coords[8]){
                    k += width-(coords[9]+1)+coords[8];
                    p2_x = k % width;
                }
                int p2_y = k / width;

                //if p2 collides with wolf or p1...
				if(k==i || k==j){
					continue;
                }

				//if this is not a valid space...
				if(configuration[p2_y][p2_x]==0){
					continue;	//move to the next space
				}

				pair<int,int> p2 = {p2_x, p2_y};
                        
                pair<int,int> ID = pairsToID(wolf, p1, p2);		//creat its ID
				GameState* state = createState(ID, isTarget(ID.second, target_1, target_2));   //create the new state
				gameMap.insert({ID, state});					//insert it into the map
                statesInRange.push_back(state);

			}//EOF p2 for loop
            first = false;
		}//EOF p1 for loop
	}//EOF wolf for loop

    return statesInRange;
}//EOF populateMap


int GameGraph::getNumStartStates() {
    return this->numStartStates;
}//EOF getNumStartStates


int GameGraph::getNumTargetsInRange(){
    return this->numTargetsInRange;
}//EOF getNumTargetsInRange


int GameGraph::calcNumSolvableStarts() {
    list<GameState*> visitedTargets = findVisitedTargets(); 
    for(auto target : visitedTargets){
        this->countOnTarget(target);
    }
    return this->numSolvableStarts;
}//EOF solutionFinder


list<char> GameGraph::solutionFinder(bool shortest) {
    list<char> move_history;
    unordered_set<GameState*> visited_states;
    list<GameState*> visitedTargets = findVisitedTargets(); 
    for(auto target : visitedTargets){
        visited_states.insert(target);
        solutionDFS(target, move_history, 0, visited_states, shortest);
        visited_states.erase(target);
    }
    if(shortest){
        return this->shortest_solution;
    }
    else{
        return this->longest_solution;
    }
}//EOF solutionFinder


void GameGraph::countOnTarget(GameState* currentState) {
    currentState->onSolution = true;
    if(!currentState->target && insideOfRange(currentState, this->coords)){
        this->numSolvableStarts++;
    }
    for(auto parentPair : currentState->parents){
        auto parent = parentPair.first;
        if(!parent->onSolution){
            countOnTarget(parent);
        }
    }
}//EOF countOnTarget


void GameGraph::solutionDFS(GameState* currentState, list<char>& move_history,
        int path_size, unordered_set<GameState*> visited_states, bool shortest)
{
    if(insideOfRange(currentState, this->coords)){
        if(shortest && move_history.size() < this->shortest_length){
            this->shortest_solution = move_history;
            this->shortest_length = move_history.size();
        }
        else if(!shortest && move_history.size() > this->longest_solution.size()){
            this->longest_solution = move_history;
        }
        return;
    }//EOF if (start state)

    if(shortest && path_size == this->shortest_length - 1){
        return;
    }

    for(auto parentPair : currentState->parents){
        auto parent = parentPair.first;
        char move = parentPair.second;
        if(visited_states.find(parent) != visited_states.end()){
            continue;
        }
        if(shortest && parent->numPrev != -1 && parent->numPrev <= path_size){
            continue;
        }
        else if(!shortest && parent->numPrev > path_size){
            continue;
        }

        parent->numPrev = path_size;
        move_history.push_front(move);
        visited_states.insert(parent);
        solutionDFS(parent, move_history, path_size+1, visited_states, shortest);
        move_history.pop_front();
        visited_states.erase(parent);
    }//EOF parent loop
}//EOF solutionDFS


void GameGraph::createConnections(GameState* currentState) {

    currentState->visited = true;
    if(currentState->target){
        return;
    }

    if(insideOfRange(currentState, this->coords)){
        this->numStartStates++;
    }
    
    for(int i = 0; i < 4; ++i){  

        char move = MOVES[i];

        //if the move is not valid...
        if(!validMove(configuration, currentState, move)){
            continue;
        }
            
        auto neighborID = generateID(configuration, currentState, move);    //identifier of the neighbor
        GameState* neighbor;
        auto temp_iter = gameMap.find(neighborID);  //search the gameMap for the neighbor

        if(temp_iter == gameMap.end()){
            neighbor = createState(neighborID, isTarget(neighborID.second, target_1, target_2));
			gameMap.insert({neighborID, neighbor});					//insert it into the map
        }
        else{
            neighbor = temp_iter->second;
        }

        neighbor->parents.push_back({currentState, move});
        
        //if the neighbor has not been visited yet...
        if(!neighbor->visited){
            createConnections(neighbor);	//recurrsively call createConnections on the neighbor
        }
        
        currentState->moves[i] = true;            //Since the move is valid
        currentState->neighbors[i] = neighbor;    //ith neighbor of currentState is neighbor

    }//EOF for loop (moves loop)
}//EOF createConnections method


list<GameState*> GameGraph::findVisitedTargets() {
    list<GameState*> visitedTargets;
    for(int wolfIter = 0; wolfIter < width*length; ++wolfIter){

        int wolf_x = wolfIter % width;
        int wolf_y = wolfIter / width;

        if(configuration[wolf_y][wolf_x] == 2 || configuration[wolf_y][wolf_x] == 0){
            continue;
        }

        pair<int,int> wolf = {wolf_x, wolf_y};
        pair<int,int> ID_1 = pairsToID(wolf, target_1, target_2);
        pair<int,int> ID_2 = pairsToID(wolf, target_2, target_1);

        auto iter_1 = gameMap.find(ID_1);
        auto iter_2 = gameMap.find(ID_2);

        if(iter_1 != gameMap.end()){
            visitedTargets.push_back(iter_1->second);
        }
        if(iter_2 != gameMap.end()){
            visitedTargets.push_back(iter_2->second);
        }      
    }//EOF wolf loop
    
    return visitedTargets;
}//EOF findVisitedTargets


bool GameGraph::build() {
    bool invalidStart = true;
	list<GameState*> statesInRange = populateMap();
	for(auto curr : statesInRange){
        if(curr->target){
            this->numTargetsInRange++;
            continue;
        }
		if(curr->visited || curr->target){
            continue;
        }
        invalidStart = false;
        createConnections(curr);
	}//EOF for
    if(invalidStart){
        return false;
    }
    return true;
}//EOF build


GameGraph::~GameGraph(){
    for(auto const& entry : gameMap){
        delete entry.second;
    }
}//EOF destructor
