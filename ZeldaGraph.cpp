#include "ZeldaPuzzle.hpp"

using namespace std;

//Declare the array of move types
const char moveTypes[4] = {'U','D','L','R'};

GameGraph::GameGraph(int length, int width, vector<int> configuration, int initalIdentifier) {
      this.length = length;
      this.width = width;
      this.configuration = configuration;
      this.initalState = createState(initalIdentifier);
}//EOF GameGraph constructor


vector<GameState*> generateNeighbors(GameState* currentState) {
      currentState->visited = true;
      //loops through each possible move (Up, Down, Left, Right)
      for(int i = 0; i < 4; ++i){  
          char move = moveTypes[i]
          //if the move is valid
          if(validMove(currentState, move)){
              int neighborID = generateID(currentState, move)   //identifier of the neighbor
                  
              auto iter = gameMap.find(neighborID)  //search the gameMap for the neighbor
              //if the neighbor is not found (has not been created)...
              if(iter == gameMap.end()){
                  GameState* neighbor = createState(neighborID);    //create neighbor given the neighborID
                  gameMap.insert(make_pair(neighborID, neighbor));  //add the newly created neighbor to the gameMap
                  generateNeighbors(neighbor);          //recurrsively call generateNeighbors on the new neighbor
              }//EOF if   
              
              currentState->moves[i] = true;            //Since the move is valid
              currentState->neighbors[i] = neighbor;    //ith neighbor of currentState is neighbor (created above)
      }//EOF for loop
}//EOF generateNeighbors method

      
GameGraph::validMove(GameState* currentState, char move) {
  int wolf_x = currentState->wolf%width;
  int wolf_y = currentState->wolf/width;
  int p1_x = currentState->p1%width;
  int p1_y = currentState->p1/width;
  int p2_x = currentState->p2%width;
  int p2_y = currentState->p2/width;
  
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
    if(wolf_x == length-1){
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

      
GameGraph::generateID(GameState* currentState, char move) {
    int newWolf = currentState->wolf;
    int newP1 = currentState->p1;
    int newP2 = currentState->p2;
    
    int wolf_x = currentState->wolf%width;
    int wolf_y = currentState->wolf/width;
    int p1_x = currentState->p1%width;
    int p1_y = currentState->p1/width;
    int p2_x = currentState->p2%width;
    int p2_y = currentState->p2/width;
    
    if(move=='U'){
        //Checks if piece 1 is going to move to a valid space
        if(p1_y-1 => 0 && configuration[p1_y-1][p1_x] != 0){
            newP1 = newP1 - width;  //Moves piece 1 up
        }
        //Checks if piece 2 is going to move to a valid space
        if(p2_y+1 <= length-1 && configuration[p2_y+1][p2_x] != 0){
            newP2 = newP2 + width;  //Moves piece 2 down
        }
        newWolf = newWolf - width;  //Moves the wolf up
    }//EOF Up case
  
    else if(move=='D'){
        //Checks if piece 1 is going to move to a valid space
        if(p1_y+1 <= length-1 && configuration[p1_y+1][p1_x] != 0){
            newP1 = newP1 - width;  //Moves piece 1 up
        }
        //Checks if piece 2 is going to move to a valid space
        if(p2_y-1 >= 0 && configuration[p2_y-1][p2_x] != 0){
            newP2 = newP2 + width;  //Moves piece 2 up
        }
        newWolf = newWolf + width;  //Moves the wolf down
    }//EOF Down case
  
    else if(move=='L'){
        //Checks if piece 1 is going to move to a valid space
        if(p1_x-1 >=0 && configuration[p1_y][p1_x-1] != 0){
            newP1 = newP1 - 1;  //Moves piece 1 left
        }
        //Checks if piece 2 is going to move to a valid space
        if(p2_x+1 <= width-1 && configuration[p2_y][p2_x+1] != 0){
            newP2 = newP2 + 1;  //Moves piece 2 right
        }
        newWolf = newWolf - 1;  //Moves the wolf left

    }//EOF Left case
  
    else{
        //Checks if piece 1 is going to move to a valid space
        if(p1_x+1 <= lenght-1 && configuration[p1_y][p1_x+1] != 0){
            newP1 = newP1 + 1;  //Moves piece 1 right
        }
        //Checks if piece 2 is going to move to a valid space
        if(p2_x-1 >= 0 && configuration[p2_y][p2_x-1] != 0){
            newP2 = newP2 - 1;  //Moves piece 2 left
        }
        newWolf = newWolf + 1;  //Moves the wolf right
    
    }//EOF Right case

    return 10000*newWolf + 100*newP2 + newP1;    //call to GameState constructor
}//EOF generateID method
      
      
GameGraph::createState(int ID) {
    newWolf = ID/10000;      //will give the first two digits
    newP1 = (ID/100) % 100;  //will give the middle two digits
    newP2 = ID % 100;        //will give the last two digits

    GameState* newState = GameState(newP1, newP2, newWolf);  //creates new state
    return newState
}//EOF createNeighbor method
