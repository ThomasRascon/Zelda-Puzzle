#include "ZeldaPuzzle.hpp"

using namespace std;


GameGraph::GameGraph(int length, int width, vector<int> configuration, int initalIdentifier) {
      this.length = length;
      this.width = width;
      this.configuration = configuration;
      this.initalState = createState(initalIdentifier);
}

GameGraph::createState(int identifier) {
      int newWolf = identifier/10000;     //first 2 digits
      int newP1 = (identifier/100) % 100; //middle 2 digits
      int newP2 = identifier % 100;       //last 2 digits
      
      return newState = GameState(newP1, newP2, newWolf);    //call to GameState constructor
}//EOF createState method

GameGraph::validMove(GameState* currentState, char move) {
  int wolf_x = wolf%width;
  int wolf_y = wolf/width;
  int p1_x = p1%width;
  int p1_y = p1/width;
  int p2_x = p2%width;
  int p2_y = p2/width;
  
  if(move=='U'){
    
    //Check if we fall off the border of the map
    if(wolf_y*p1_y == 0 || p2_y == length-1){
      return false;
    }
    //Make sure there is a space to move onto
    if(configuration[wolf_y-1][wolf_x]*configuration[p1_y-1][p1_x]*configuration[p2_y+1][p2_x] == 0){
      return false;
    }
    //Make sure no collisions occur
    if(wolf_y-1 == p1_y || wolf_y-1 == p2_y || wolf_y-1 == p2_y+1){
      return false;
    }   
  }//EOF Up case
  
  else if(move=='D'){
    
    //Check if we fall off the border of the map
    if(wolf_y == length-1 || p1_y == length-1 || p2_y == 0){
      return false;
    }
    //Make sure there is a space to move onto
    if(configuration[wolf_y+1][wolf_x]*configuration[p1_y+1][p1_x]*configuration[p2_y-1][p2_x] == 0){
      return false;
    }
    //Make sure no collisions occur
    if(wolf_y+1 == p1_y || wolf_y+1 == p2_y || wolf_y+1 == p2_y-1){
      return false;
    }
  }//EOF Down case
  
  else if(move=='L'){
    
    //Check if we fall off the border of the map
    if(wolf_x*p1_x == 0 || p2_x == width-1){
      return false;
    }
    //Make sure there is a space to move onto
    if(configuration[wolf_y][wolf_x-1]*configuration[p1_y][p1_x-1]*configuration[p2_y][p2_x+1] == 0){
      return false;
    }
    //Make sure no collisions occur
    if(wolf_x-1 == p1_x || wolf_x-1 == p2_x || wolf_x-1 == p2_x+1){
      return false;
    }
  }//EOF Left case
  
  else(move=='R'){
    
    //Check if we fall off the border of the map
    if(wolf_x == width-1 || p1_x == width-1 || p2_x == 0){
      return false;
    }
    //Make sure there is a space to move onto
    if(configuration[wolf_y][wolf_x+1]*configuration[p1_y][p1_x+1]*configuration[p2_y][p2_x-1] == 0){
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
