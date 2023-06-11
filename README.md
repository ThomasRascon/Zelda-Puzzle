These programs are a collection of tools for analyzing puzzles similar to a puzzle 
found in The Legend of Zelda: Twilight Princess just before unlocking the master sword.
Unfortunately, this puzzle was not given a name, so we colloquially refer to 
it as "zelda puzzle".
__________________________________________________________________________________________________

Rules of the puzzle:

There are 3 pieces on a board that is a rectangualar grid, made of regular spaces, null 
spaces, and 2 target spaces, which we elaborate on below. 
The 3 pieces consist of a "wolf" piece, which is in reference to the source game, and 2 
additional pieces (piece 1 and piece 2) that move depending on the most recent move of 
the wolf piece. The goal of the puzzle is to get pieces 1 and 2 to occupy the target 
spaces. Either piece may be in either target space, and the position of the wolf is 
not important to the win state. 
The 3 peices move according to the following rules:

    (1) The wolf may only move to a nondiagonally adjacent open regular space
    (2) When the wolf moves, piece 1 moves one space in the same direction the wolf just 
        moved, and piece 2 moves 1 space in the opposite direction the wolf just moved.
        For example, if the wolf moves to the space above it, piece 1 also moves 1 space 
        up, and piece 2 moves 1 space down.
    (3) If a valid move by the wolf would cause the other pieces to move to a null space,
        or collide with each other, then the pieces with such issues remains still. For 
        example, if the wolf moving right would cause piece 1 to move to a null space, 
        but piece 2 to move to a regular space, piece 2 moves according to (2), while 
        piece 1 stays still. Another important example is if a movement by the wolf were 
        to cause pieces 1 and 2 to occupy the same regular space, then both pieces 1 and 2 
        remain still.
    (4) In the context of the original puzzle, one considers the wolf to move first, followed 
        by pieces 1 and 2 in accordance to the wolf's "chosen" move. Thus 
        (a) If piece 1 or 2 occupy a nondiagonally adjacent regular space, the wolf may not 
            move to that space, even if such a movement would cause the piece to no longer 
            occupy that space, because the space would not be open at the moment the wolf is 
            trying to move to it.
        (b) If a movement by the wolf would cause piece 2 to and the wolf to occupy the same 
            space, then this would "crush" the wolf, terminating the puzzle. As such, for our 
            programs, we consider this to be a nonallowed move. An example of such a move would 
            be if piece 2 were 2 valid pieces above the wolf, and the wolf moved up, which would 
            cause piece 2 to move down, hence they would occupy the same space. 

__________________________________________________________________________________________________

Description of files/ folders:

README.md             : You're reading this one now.   
BoardReader.cpp       : Contains two methods that convert files containing boards to data 
                        that other functions can use, as well as an additional method that 
                        randomly generates a board.
SolutionDensity.cpp   : Contains a function that calculates the solution density of a board,
                        and a main method that calls this function on a specified number 
                        of boards, with specified dimensions. 
                        We define solution density as the ratio between the number of win states 
                        that are reachable from a different state, and the number of win states 
                        that a board has. The goal of investigating this is to gain insight on 
                        "strong nonsolution states", which is what we are calling win states that 
                        are not reachable by a different state.
ZeldaGraph.cpp & hpp  : Contain the various functions for analyzing possible states of boards  
Helper.cpp            : Contains methods relevant to the logic of the puzzle, and converting 
                        states to a unique ID.
GraphTester.cpp       : Mainly used for testing new methods we're working on. At the moment,
                        it returns the solution desity of a single board, defined in 
                        BoardConfigs. 
BoardConfigs          : Contains board configurations as text files, which are used in various 
                        programs. 1's represent regular spaces, 0's represent null spaces, and
                        2's represent target spaces.
OutputFiles           : Contains text files that are output by the build method in 
                        ZeldaGraph.cpp. These the board configuration passed to build, all 
                        possible states of said board, as well as what states they connect to 
                        within 1 movement.

        
