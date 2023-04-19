#include "ZeldaGraph.hpp"

using namespace std;

//Declare the array of move types
const char moveTypes[4] = {'U','D','L','R'};

// functions from ZeldaGraph.hpp
void populateMap();
bool validMove(GameState* currentState, char move);
int generateID(GameState* currentState, char move);
GameState* createState(int ID);

pair<int,int> pairsToID(pair<int,int> wolf, pair<int,int> p1, pair<int, int> p2){
	int wolfID = 100*wolf.first+wolf.second;    //wolfXwolfY format
	int piecesID = 1000000*p1.first+10000*p1.second+100*p2.first+p2.second;    //p1Xp1Yp2Xp2Y
  //01000000+000000+0200+00 = 1000000+200 = 1000200
	pair<int,int> ID = {wolfID, piecesID};		//{wolfXwolfY,p1Xp1Yp2Xp2Y} format
	
	return ID;
}//EOF pairToID


GameGraph::GameGraph(vector<vector<int>> configuration,
        pair<int,int> target_1, pair<int,int> target_2) {
      this->length = configuration.size();
      this->width = configuration[0].size();
      this->configuration = configuration;
      this->target_1 = target_1;
      this->target_2 = target_2;
}//EOF GameGraph constructor


GameState* GameGraph::createState(pair<int,int> ID) {
	//ex ID={2312 78900137} -> ID.first=2312, newWolf={23,12}
	//ID.second = 78900137, newP1={78,90}, newP2={01,37}
    pair<int,int> newWolf = {ID.first / 100, ID.first % 100};	//{first two digits of wolf, last two digits of wolf} 
    pair<int,int> newP1 = {ID.second/1000000, (ID.second/10000)%100};  //{first two digits of ID.second, 3rd and 4th digit}
    pair<int,int> newP2 = {(ID.second/100)%100, ID.second%100};  //{5th and 6th digit, last two digits}

    GameState* newState = new GameState(newP1, newP2, newWolf);  //creates new state
    return newState;
}//EOF createState method


void GameGraph::populateMap(){
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
				
        pair<int,int> ID = pairsToID(wolf, p1, p2);			//creat its ID
				GameState* state = createState(ID);	      //create the new state
        cout << state->wolf.second << "," << state->wolf.first << "; " <<
            state->p1.second << "," << state->p1.first << "; " <<
            state->p2.second << "," << state->p2.first << endl;
				gameMap.insert({ID, state});						//insert it into the map

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
    
    //Check if the wolf falls off the border of the map
    if(wolf_y == 0){
      return false;
    }
    //Check if the wolf is moving onto a nonspace
    if(configuration[wolf_y-1][wolf_x] == 0){
      return false;
    }
    //Make sure no collisions occur
    if(wolf_y-1 == p1_y || wolf_y-1 == p2_y || wolf_y-1 == p2_y+1){
      return false;
    }   
  }//EOF Up case
  
  else if(move=='D'){
    
    //Check if the wolf falls off the border of the map
    if(wolf_y == length-1){
      return false;
    }
    //Check if the wolf is moving onto a nonspace
    if(configuration[wolf_y+1][wolf_x] == 0){
      return false;
    }
    //Make sure no collisions occur
    if(wolf_y+1 == p1_y || wolf_y+1 == p2_y || wolf_y+1 == p2_y-1){
      return false;
    }
  }//EOF Down case
  
  else if(move=='L'){
    
    //Check if the wolf falls off the border of the map
    if(wolf_x == 0){
      return false;
    }
    //Check if the wolf is moving onto a nonspace
    if(configuration[wolf_y][wolf_x-1] == 0){
      return false;
    }
    //Make sure no collisions occur
    if(wolf_x-1 == p1_x || wolf_x-1 == p2_x || wolf_x-1 == p2_x+1){
      return false;
    }
  }//EOF Left case
  
  else{
    
    //Check if the wolf falls off the border of the map
    if(wolf_x+1 == length){
      return false;
    }
    //Check if the wolf is moving onto a nonspace
    if(configuration[wolf_y][wolf_x+1] == 0){
      return false;
    } 
    //Make sure no collisions occur
    if(wolf_x+1 == p1_x || wolf_x+1 == p2_x || wolf_x+1 == p2_x-1){
      return false;
    }
  }//EOF Right case
  
  //if all cases pass, the move is valid
  return true;
  
}//EOF validMove method

      
pair<int,int> GameGraph::generateID(GameState* currentState, char move) {
    pair<int,int> newWolf = currentState->wolf;
    pair<int,int> newP1 = currentState->p1;
    pair<int,int> newP2 = currentState->p2;
    
    int wolf_x = currentState->wolf.first;
    int wolf_y = currentState->wolf.second;
    int p1_x = currentState->p1.first;
    int p1_y = currentState->p1.second;
    int p2_x = currentState->p2.first;
    int p2_y = currentState->p2.second;
    
    if(move=='U'){
        //Checks if piece 1 is going to move to a valid space
        if(p1_y-1 >= 0 && configuration[p1_y-1][p1_x] != 0){
            --newP1.second;  //Moves piece 1 up
        }
        //Checks if piece 2 is going to move to a valid space
        if(p2_y+1 <= length-1 && configuration[p2_y+1][p2_x] != 0){
            ++newP2.second;  //Moves piece 2 down
        }
        --newWolf.second;  //Moves the wolf up
    }//EOF Up case
  
    else if(move=='D'){
        //Checks if piece 1 is going to move to a valid space
        if(p1_y+1 <= length-1 && configuration[p1_y+1][p1_x] != 0){
            ++newP1.second;  //Moves piece 1 down
        }
        //Checks if piece 2 is going to move to a valid space
        if(p2_y-1 >= 0 && configuration[p2_y-1][p2_x] != 0){
            --newP2.second;  //Moves piece 2 up
        }
        ++newWolf.second;  //Moves the wolf down
    }//EOF Down case
  
    else if(move=='L'){
        //Checks if piece 1 is going to move to a valid space
        if(p1_x-1 >=0 && configuration[p1_y][p1_x-1] != 0){
            --newP1.first;  //Moves piece 1 left
        }
        //Checks if piece 2 is going to move to a valid space
        if(p2_x+1 <= width-1 && configuration[p2_y][p2_x+1] != 0){
            ++newP2.first;  //Moves piece 2 right
        }
        --newWolf.first;  //Moves the wolf left

    }//EOF Left case
  
    else{
        //Checks if piece 1 is going to move to a valid space
        if(p1_x+1 <= length-1 && configuration[p1_y][p1_x+1] != 0){
            ++newP1.first;  //Moves piece 1 right
        }
        //Checks if piece 2 is going to move to a valid space
        if(p2_x-1 >= 0 && configuration[p2_y][p2_x-1] != 0){
            --newP2.first;  //Moves piece 2 left
        }
        ++newWolf.first;  //Moves the wolf right
    
    }//EOF Right case
	
    return pairsToID(newWolf, newP1, newP2);
}//EOF generateID method


void GameGraph::createConnections(GameState* currentState) {
      //loops through each possible move (Up, Down, Left, Right)
	  currentState->visited = true;
      for(int i = 0; i < 4; ++i){  
          char move = moveTypes[i];
          //if the move is valid...
          if(validMove(currentState, move)){
			  
              auto neighborID = generateID(currentState, move);  //identifier of the neighbor
              auto iter = gameMap.find(neighborID);  		 	 //search the gameMap for the neighbor
			        GameState* neighbor = (*iter).second;
			  
              //if the neighbor has not been visited yet...
              if(!neighbor->visited){
		      
                  bool p1Final = (neighbor->p1==this->target_1 || neighbor->p2==this->target_2);	//if p1 is on a final position
                  bool p2Final = (neighbor->p2==this->target_1 || neighbor->p2==this->target_2);	//if p2 is on a final position

                  //if p1 and p2 aren't both on final spaces (i.e. *iter isn't a target state)...
                  if(!(p1Final && p2Final)){
                    createConnections(neighbor);	//recurrsively call createConnections on the new neighbor
                  }

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
		if(!curr->visited){
			createConnections(curr);
		}
	}
}//EOF build
