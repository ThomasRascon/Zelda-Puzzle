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


array<bool, 2> upCollision(pair<int,int> wolf,  pair<int,int> p1,  
    pair<int,int> p2, vector<vector<int>> configuration, int length, int width) {

    array<bool, 2> canMove = {true, true};

    //Checks if piece 1 is going to move to a valid space
    if(p1.second == 0 || configuration[p1.second-1][p1.first] == 0){
        canMove[0] = false;  //Moves piece 1 up
    }

    //case: pieces collide into each other...
    else if(p1.first==p2.first){
        if(p1.second-p2.second <= 2 && p1.second-p2.second > 0){
            return {false, false};   //neither can move
        }
    }

    //Checks if piece 2 is going to move to a valid space
    if(p2.second == length-1 || configuration[p2.second+1][p2.first] == 0){
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


array<bool, 2> downCollision(pair<int,int> wolf,  pair<int,int> p1,  
    pair<int,int> p2, vector<vector<int>> configuration, int length, int width) {

    array<bool, 2> canMove = {true, true};

    //Checks if piece 1 is going to move to a valid space
    if(p1.second == length-1 || configuration[p1.second+1][p1.first] == 0){
        canMove[0] = false;  //Moves piece 1 down
    }

    //case: pieces collide into each other...
    else if(p1.first==p2.first){
        if(p2.second-p1.second <= 2 && p2.second-p1.second > 0){
            return {false, false};   //neither can move
        }
    }

    //Checks if piece 2 is going to move to a valid space
    if(p2.second == 0 || configuration[p2.second-1][p2.first] == 0){
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


array<bool, 2> leftCollision(pair<int,int> wolf,  pair<int,int> p1,  
    pair<int,int> p2, vector<vector<int>> configuration, int length, int width) {

    array<bool, 2> canMove = {true, true};

    //Checks if piece 1 is going to move to a valid space
    if(p1.first == 0 || configuration[p1.second][p1.first-1] == 0){
        canMove[0] = false;  //Moves piece 1 left
    }

    //case: pieces collide into each other...
    else if(p1.second==p2.second){
        if(p1.first-p2.first <= 2 && p1.first-p2.first > 0){
            return {false, false};   //neither can move
        }
    }

    //Checks if piece 2 is going to move to a valid space
    if(p2.first == width-1 || configuration[p2.second][p2.first+1] == 0){
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


array<bool, 2> rightCollision(pair<int,int> wolf,  pair<int,int> p1,  
    pair<int,int> p2, vector<vector<int>> configuration, int length, int width) {

    array<bool, 2> canMove = {true, true};

    //Checks if piece 1 is going to move to a valid space
    if(p1.first == width-1 || configuration[p1.second][p1.first+1] == 0){
        canMove[0] = false;  //Moves piece 1 right
    }

    //case: pieces collide into each other...
    else if(p1.second==p2.second){
        if(p2.first-p1.first <= 2 && p2.first-p1.first > 0){
            return {false, false};   //neither can move
        }
    }

    //Checks if piece 2 is going to move to a valid space
    if(p2.first == 0 || configuration[p2.second][p2.first-1] == 0){
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

#endif // HELPER