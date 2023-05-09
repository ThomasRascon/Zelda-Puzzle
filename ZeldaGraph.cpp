#include "ZeldaGraph.hpp"
#include "Helper.cpp"

using namespace std;

//Declare the array of move types
const char moveTypes[4] = {'U','D','L','R'};

// functions from ZeldaGraph.hpp
void populateMap();
bool validMove(GameState* currentState, char move);
int generateID(GameState* currentState, char move);
GameState* createState(int ID);


GameGraph::GameGraph(vector<vector<int>> configuration,
        pair<int,int> target_1, pair<int,int> target_2) {

    this->length = configuration.size();
    this->width = configuration[0].size();
    this->configuration = configuration;
    this->target_1 = target_1;
    this->target_2 = target_2;
}//EOF GameGraph constructor


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


bool GameGraph::validMove(GameState* currentState, char move) {

    int wolf_x = currentState->wolf.first;
    int wolf_y = currentState->wolf.second;
    int p1_x = currentState->p1.first;
    int p1_y = currentState->p1.second;
    int p2_x = currentState->p2.first;
    int p2_y = currentState->p2.second;
    
    if(move=='U'){
        
        //Check if the wolf will fall off the border of the map
        if(wolf_y == 0){
            return false;
        }
        //Check if the wolf is moving onto a nonspace
        if(configuration[wolf_y-1][wolf_x] == 0){
            return false;
        }
        //Make sure no collisions occur
        if((wolf_y-1 == p1_y && wolf_x == p1_x) || (wolf_y-1 == p2_y && wolf_x == p2_x)){
            return false;
        }  
        //Make sure p2 doesn't crush the wolf
        if(wolf_x == p2_x && wolf_y-1 == p2_y+1){
            return false;
        }

    }//EOF Up case
    
    else if(move=='D'){
        
        //Check if the wolf will fall off the border of the map
        if(wolf_y == length-1){
            return false;
        }
        //Check if the wolf is moving onto a nonspace
        if(configuration[wolf_y+1][wolf_x] == 0){
            return false;
        }
        //Make sure no collisions occur
        if((wolf_y+1 == p1_y && wolf_x == p1_x) || (wolf_y+1 == p2_y && wolf_x == p2_x)){
            return false;
        }
        //Make sure p2 doesn't crush the wolf
        if(wolf_x == p2_x && wolf_y+1 == p2_y-1){
            return false;
        }

    }//EOF Down case
    
    else if(move=='L'){
        
        //Check if the wolf will fall off the border of the map
        if(wolf_x == 0){
            return false;
        }
        //Check if the wolf is moving onto an internal nonspace
        if(configuration[wolf_y][wolf_x-1] == 0){
            return false;
        }
        //Make sure no collisions occur
        if((wolf_x-1 == p1_x && wolf_y == p1_y) || (wolf_x-1 == p2_x && wolf_y == p2_y)){
            return false;
        }
        //Make sure p2 doesn't crush the wolf
        if(wolf_y == p2_y && wolf_x-1 == p2_x+1){
            return false;
        }
    }//EOF Left case
    
    else{
        
        //Check if the wolf will fall off the border of the map
        if(wolf_x == width-1){
            return false;
        }
        //Check if the wolf is moving onto a nonspace
        if(configuration[wolf_y][wolf_x+1] == 0){
            return false;
        } 
        //Make sure no collisions occur
        if((wolf_x+1 == p1_x && wolf_y == p1_y) || (wolf_x+1 == p2_x && wolf_y == p2_y)){
            return false;
        }
        //Make sure p2 doesn't crush the wolf
        if(wolf_y == p2_y && wolf_x+1 == p2_x-1){
            return false;
        }
    }//EOF Right case
    
    //if all cases pass, the move is valid
    return true;
  
}//EOF validMove method

      
pair<int,int> GameGraph::generateID(GameState* currentState, char move) {
    pair<int,int> wolf = currentState->wolf;
    pair<int,int> p1 = currentState->p1;
    pair<int,int> p2 = currentState->p2;
    array<bool, 2> canMove;
    
    if(move=='U'){
        --wolf.second;      //Moves the wolf up
        canMove = upCollision(wolf, p1, p2, configuration, length, width);
        if(canMove[0]){
            --p1.second;    //Moves p1 up
        }
        if(canMove[1]){
            ++p2.second;    //Moves p2 down
        }
    }//EOF Up case
  
    else if(move=='D'){
        ++wolf.second;      //Moves the wolf down
        canMove = downCollision(wolf, p1, p2, configuration, length, width);
        if(canMove[0]){
            ++p1.second;    //Moves p1 down
        }
        if(canMove[1]){
            --p2.second;    //Moves p2 up
        }
    }//EOF Down case
  
    else if(move=='L'){
        --wolf.first;       //Moves the wolf left
        canMove = leftCollision(wolf, p1, p2, configuration, length, width);
        if(canMove[0]){
            --p1.first;     //Moves p1 left
        }
        if(canMove[1]){
            ++p2.first;     //Moves p2 right
        }
    }//EOF Left case
  
    else{
        ++wolf.first;       //Moves the wolf right
        canMove = rightCollision(wolf, p1, p2, configuration, length, width);
        if(canMove[0]){
            ++p1.first;     //Moves p1 right
        }
        if(canMove[1]){
            --p2.first;     //Moves p2 left
        }
    }//EOF Right case
	
    return pairsToID(wolf, p1, p2);
}//EOF generateID method


void GameGraph::createConnections(GameState* currentState) {
    //loops through each possible move (Up, Down, Left, Right)
    cout << currentState->wolf.second << "," << currentState->wolf.first << "; " <<
        currentState->p1.second << "," << currentState->p1.first << "; " <<
        currentState->p2.second << "," << currentState->p2.first << endl;

    if (currentState == reinterpret_cast<GameState*>(0xef7e08)) {
        cout << "ptr points to the memory address 0xef7e08" << endl;
    }

    currentState->visited = true;
    for(int i = 0; i < 4; ++i){  
        char move = moveTypes[i];
        //if the move is valid...
        if(validMove(currentState, move)){
            
            auto neighborID = generateID(currentState, move);  //identifier of the neighbor
            auto iter = gameMap.find(neighborID);  		 	 //search the gameMap for the neighbor
            GameState* neighbor = (*iter).second;

            // cout << "(" << neighborID.first << "," << neighborID.second << ") ";
            
            //if the neighbor has not been visited yet and is not a target state...
            if(!(neighbor->visited || neighbor->target)){
                cout << move << ":\t";
                cout << neighbor->wolf.second << "," << neighbor->wolf.first << "; " <<
                neighbor->p1.second << "," << neighbor->p1.first << "; " <<
                neighbor->p2.second << "," << neighbor->p2.first << endl << endl;
                createConnections(neighbor);	//recurrsively call createConnections on the new neighbor
            }//EOF if
            
            currentState->moves[i] = true;            //Since the move is valid
            currentState->neighbors[i] = neighbor;    //ith neighbor of currentState is neighbor (created above)
        }//EOF if (move is valid)
    }//EOF for loop (moves loop)
}//EOF createConnections method


void GameGraph::build() {
	populateMap();
	for(auto iter = gameMap.begin(); iter != gameMap.end(); ++iter) {
		GameState* curr = (*iter).second;
		if(!(curr->visited || curr->target)){
			createConnections(curr);
      		for(int i = 0; i < 4; ++i){
        		auto neighbor = curr->neighbors[i];
      		}
		}
	}


	// for(auto iter = gameMap.begin(); iter != gameMap.end(); ++iter) {
	// 	GameState* curr = (*iter).second;
    // 	cout << curr->wolf.second << "," << curr->wolf.first << "; " <<
    //     curr->p1.second << "," << curr->p1.first << "; " <<
    //     curr->p2.second << "," << curr->p2.first << endl;
    // 	for(int i = 0; i < 4; ++i){
    //   		auto neighbor = curr->neighbors[i];
    //   		if(neighbor!=nullptr){
    //     		cout << "\t" << neighbor->wolf.second << "," << neighbor->wolf.first << "; " <<
    //       		neighbor->p1.second << "," << neighbor->p1.first << "; " <<
    //       		neighbor->p2.second << "," << neighbor->p2.first << endl;
    //   		}
    // 	}
  	// }
}//EOF build