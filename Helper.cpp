#ifndef HELPER
#define HELPER
#include <fstream>
#include <iostream>
#include <array>
#include <vector>

using namespace std;


pair<int,int> pairsToID(pair<int,int> wolf, pair<int,int> p1, pair<int, int> p2){
	int wolfID = 100*wolf.first+wolf.second;    //wolfXwolfY format
	int piecesID = 1000000*p1.first+10000*p1.second+100*p2.first+p2.second;    //p1Xp1Yp2Xp2Y
	pair<int,int> ID = {wolfID, piecesID};		//{wolfXwolfY,p1Xp1Yp2Xp2Y} format
	
	return ID;
}//EOF pairToID


bool isTarget(int p1_p2, pair<int,int> target_1, pair<int,int> target_2){
    pair<int,int> p1 = {p1_p2/1000000, (p1_p2/10000)%100};
    pair<int,int> p2 = {(p1_p2/100)%100, p1_p2%100};
    return (p1==target_1 || p1==target_2) && (p2==target_1 || p2==target_2);
}//EOF isTarget


bool insideOfRange(const GameState* currentState, const vector<int>& coords) {
    return currentState->wolf.first >= coords[0] && currentState->wolf.first <= coords[1] &&
           currentState->wolf.second >= coords[2] && currentState->wolf.second <= coords[3] &&
           currentState->p1.first >= coords[4] && currentState->p1.first <= coords[5] &&
           currentState->p1.second >= coords[6] && currentState->p1.second <= coords[7] &&
           currentState->p2.first >= coords[8] && currentState->p2.first <= coords[9] &&
           currentState->p2.second >= coords[10] && currentState->p2.second <= coords[11];
}//EOF insideOfRange


array<bool, 2> upCollision(pair<int,int> wolf,  pair<int,int> p1, pair<int,int> p2,
    const vector<vector<int>>& board, int length, int width)
{

    array<bool, 2> canMove = {true, true};

    //Checks if piece 1 is going to move to a valid space
    if(p1.second == 0 || board[p1.second-1][p1.first] == 0){
        canMove[0] = false;  //Moves piece 1 up
    }

    //case: pieces collide into each other...
    else if(p1.first==p2.first){
        if(p1.second-p2.second <= 2 && p1.second-p2.second > 0){
            return {false, false};   //neither can move
        }
    }

    //Checks if piece 2 is going to move to a valid space
    if(p2.second == length-1 || board[p2.second+1][p2.first] == 0){
        canMove[1] = false;  //Moves piece 2 down
    }

    //case: p2 collides into wolf...
    else if(p2.first==wolf.first){
        if(p2.second+1 == wolf.second){
            canMove[1] = false;
        }
    }

    return canMove;
}//EOF upCollision


array<bool, 2> downCollision(pair<int,int> wolf,  pair<int,int> p1, pair<int,int> p2,
    const vector<vector<int>>& board, int length, int width)
{

    array<bool, 2> canMove = {true, true};

    //Checks if piece 1 is going to move to a valid space
    if(p1.second == length-1 || board[p1.second+1][p1.first] == 0){
        canMove[0] = false;  //Moves piece 1 down
    }

    //case: pieces collide into each other...
    else if(p1.first==p2.first){
        if(p2.second-p1.second <= 2 && p2.second-p1.second > 0){
            return {false, false};   //neither can move
        }
    }

    //Checks if piece 2 is going to move to a valid space
    if(p2.second == 0 || board[p2.second-1][p2.first] == 0){
        canMove[1] = false;  //Moves piece 2 up
    }

    //case: p2 collides into wolf...
    else if(p2.first==wolf.first){
        if(p2.second-1 == wolf.second){
            canMove[1] = false;
        }
    }

    return canMove;
}//EOF downCollision


array<bool, 2> leftCollision(pair<int,int> wolf,  pair<int,int> p1, pair<int,int> p2,
    const vector<vector<int>>& board, int length, int width) 
{

    array<bool, 2> canMove = {true, true};

    //Checks if piece 1 is going to move to a valid space
    if(p1.first == 0 || board[p1.second][p1.first-1] == 0){
        canMove[0] = false;  //Moves piece 1 left
    }

    //case: pieces collide into each other...
    else if(p1.second==p2.second){
        if(p1.first-p2.first <= 2 && p1.first-p2.first > 0){
            return {false, false};   //neither can move
        }
    }

    //Checks if piece 2 is going to move to a valid space
    if(p2.first == width-1 || board[p2.second][p2.first+1] == 0){
        canMove[1] = false;  //Moves piece 2 right
    }

    //case: p2 collides into wolf...
    else if(p2.second==wolf.second){
        if(p2.first+1 == wolf.first){
            canMove[1] = false;
        }
    }

    return canMove;
}//EOF leftCollision


array<bool, 2> rightCollision(pair<int,int> wolf,  pair<int,int> p1, pair<int,int> p2,
    const vector<vector<int>>& board, int length, int width)
{

    array<bool, 2> canMove = {true, true};

    //Checks if piece 1 is going to move to a valid space
    if(p1.first == width-1 || board[p1.second][p1.first+1] == 0){
        canMove[0] = false;  //Moves piece 1 right
    }

    //case: pieces collide into each other...
    else if(p1.second==p2.second){
        if(p2.first-p1.first <= 2 && p2.first-p1.first > 0){
            return {false, false};   //neither can move
        }
    }

    //Checks if piece 2 is going to move to a valid space
    if(p2.first == 0 || board[p2.second][p2.first-1] == 0){
        canMove[1] = false;  //Moves piece 2 left
    }

    //case: p2 collides into wolf...
    else if(p2.second==wolf.second){
        if(p2.second-1 == wolf.second){
            canMove[1] = false;
        }
    }

    return canMove;
}//EOF rightCollision


bool validMove(const vector<vector<int>>& board, GameState* currentState, char move) {

    int wolf_x = currentState->wolf.first;
    int wolf_y = currentState->wolf.second;
    int p1_x = currentState->p1.first;
    int p1_y = currentState->p1.second;
    int p2_x = currentState->p2.first;
    int p2_y = currentState->p2.second;
    int length = board.size();
    int width = board[0].size();
    
    if(move=='U'){
        
        //Check if the wolf will fall off the border of the map
        if(wolf_y == 0){
            return false;
        }
        //Check if the wolf is moving onto a nonspace
        if(board[wolf_y-1][wolf_x] == 0){
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
        if(board[wolf_y+1][wolf_x] == 0){
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
        if(board[wolf_y][wolf_x-1] == 0){
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
        if(board[wolf_y][wolf_x+1] == 0){
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
    
    return true;
}//EOF validMove method


pair<int,int> generateID(const vector<vector<int>>& board, GameState* currentState, char move) {
    pair<int,int> wolf = currentState->wolf;
    pair<int,int> p1 = currentState->p1;
    pair<int,int> p2 = currentState->p2;
    array<bool, 2> canMove;
    int length = board.size();
    int width = board[0].size();
    
    if(move=='U'){
        --wolf.second;      //Moves the wolf up
        canMove = upCollision(wolf, p1, p2,board, length, width);
        if(canMove[0]){
            --p1.second;    //Moves p1 up
        }
        if(canMove[1]){
            ++p2.second;    //Moves p2 down
        }
    }//EOF Up case
  
    else if(move=='D'){
        ++wolf.second;      //Moves the wolf down
        canMove = downCollision(wolf, p1, p2, board, length, width);
        if(canMove[0]){
            ++p1.second;    //Moves p1 down
        }
        if(canMove[1]){
            --p2.second;    //Moves p2 up
        }
    }//EOF Down case
  
    else if(move=='L'){
        --wolf.first;       //Moves the wolf left
        canMove = leftCollision(wolf, p1, p2, board, length, width);
        if(canMove[0]){
            --p1.first;     //Moves p1 left
        }
        if(canMove[1]){
            ++p2.first;     //Moves p2 right
        }
    }//EOF Left case
  
    else{
        ++wolf.first;       //Moves the wolf right
        canMove = rightCollision(wolf, p1, p2, board, length, width);
        if(canMove[0]){
            ++p1.first;     //Moves p1 right
        }
        if(canMove[1]){
            --p2.first;     //Moves p2 left
        }
    }//EOF Right case
	
    return pairsToID(wolf, p1, p2);
}//EOF generateID method


#endif // HELPER