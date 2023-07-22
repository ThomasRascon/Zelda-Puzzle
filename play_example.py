from play import *

# Example usage
board = [[1,1,1,1,1,1,1,1,1],
        [1,1,1,1,1,1,1,1,1],
        [1,1,1,0,0,0,1,1,1],
        [0,0,0,1,1,1,0,0,0],
        [0,0,0,1,1,1,0,0,0],
        [0,0,0,1,1,1,0,0,0]]

board[2][2] = 2  # First target position
board[4][4] = 2  # Second target position

initial_positions = ((1, 7), (1, 1), (4, 4))

game = PuzzleGame(board, initial_positions)