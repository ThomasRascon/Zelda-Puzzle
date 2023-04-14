#include "ZeldaGraph.hpp"

using namespace std;

//Declare the array of move types
const char moveTypes[4] = {'U','D','L','R'};

// functions from ZeldaGraph.hpp
bool validMove(GameState* currentState, char move);
int generateID(GameState* currentState, char move);
GameState* createState(int ID);

GameGraph::GameGraph(int length, int width, vector<vector<int>> configuration, pair<int,int> target_1, pair<int,int> target_2) {
      this->length = length;
      this->width = width;
      this->configuration = configuration;
      this->target_1 = target_1;
      this->target_2 = target_2;
}//EOF GameGraph constructor


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

      
int GameGraph::generateID(GameState* currentState, char move) {
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
        --newWolf.second  //Moves the wolf up
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

    return 100000*newWolf.first + 10000*newWolf.second + 1000*newP2.first
	    		+ 100*newP2.second + 10*newP1.first + newP1.second;
}//EOF generateID method
      
      
GameState* GameGraph::createState(int ID) {
    int newWolf = ID/10000;      //will give the first two digits
    int newP1 = (ID/100) % 100;  //will give the middle two digits
    int newP2 = ID % 100;        //will give the last two digits

    GameState* newState = new GameState(newP1, newP2, newWolf);  //creates new state
    return newState;
}//EOF createNeighbor method


void GameGraph::generateNeighbors(GameState* currentState) {
      //loops through each possible move (Up, Down, Left, Right)
      for(int i = 0; i < 4; ++i){  
          char move = moveTypes[i];
          GameState* neighbor;
          //if the move is valid
          if(validMove(currentState, move)){
              int neighborID = generateID(currentState, move);   //identifier of the neighbor
              auto iter = gameMap.find(neighborID);  		 //search the gameMap for the neighbor
              //if the neighbor is not found (has not been created)...
              if(iter == gameMap.end()){
		      
                  neighbor = createState(neighborID);    		//create neighbor given the neighborID
                  gameMap.insert(make_pair(neighborID, neighbor));  	//add the newly created neighbor to the gameMap
		      
		  bool p1Final = (neighbor.p1==this->target_1 || neighbor.p2==this->target_2);	//if p1 is on a final position
		  bool p2Final = (neighbor.p2==this->target_1 || neighbor.p2==this->target_2);	//if p2 is on a final position
		      
		  //if p1 and p2 aren't both on final spaces...
		  if(!(p1Final && p2Final)){
		      generateNeighbors(neighbor);       //recurrsively call generateNeighbors on the new neighbor
		  }      
	      }//EOF if
          }//EOF if
          currentState->moves[i] = true;            //Since the move is valid
          currentState->neighbors[i] = neighbor;    //ith neighbor of currentState is neighbor (created above)
      }//EOF for loop
}//EOF generateNeighbors method
