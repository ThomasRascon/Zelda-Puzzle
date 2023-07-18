import tkinter as tk
from collections import deque

class PuzzleGame:
    def __init__(self, board, initial_positions):
        self.board = board
        self.target_positions = self.find_targets()
        self.wolf_pos, self.piece1_pos, self.piece2_pos = initial_positions
        self.path = []

        self.root = tk.Tk()
        self.canvas = tk.Canvas(self.root, width=len(self.board[0]) * 80, height=len(self.board) * 80)
        self.canvas.pack()
        self.draw_board()
        self.root.bind('<Up>', self.move_wolf_up)
        self.root.bind('<Down>', self.move_wolf_down)
        self.root.bind('<Left>', self.move_wolf_left)
        self.root.bind('<Right>', self.move_wolf_right)
        self.root.mainloop()

    def find_targets(self):
        targets = []
        for i in range(len(self.board)):
            for j in range(len(self.board[0])):
                if self.board[i][j] == 2:
                    targets.append((i, j))
        return targets

    def draw_board(self):
        self.canvas.delete(tk.ALL)
        for i in range(len(self.board)):
            for j in range(len(self.board[0])):
                x1, y1 = j * 80, i * 80
                x2, y2 = x1 + 80, y1 + 80

                if self.board[i][j] == 0:
                    self.canvas.create_rectangle(x1, y1, x2, y2, fill='gray')
                elif self.board[i][j] == 1:
                    self.canvas.create_rectangle(x1, y1, x2, y2, fill='white')
                elif self.board[i][j] == 2:
                    self.canvas.create_rectangle(x1, y1, x2, y2, fill='green')

        self.canvas.create_oval(self.wolf_pos[1] * 80 + 10, self.wolf_pos[0] * 80 + 10,
                                self.wolf_pos[1] * 80 + 70, self.wolf_pos[0] * 80 + 70, fill='red')
        self.canvas.create_oval(self.piece1_pos[1] * 80 + 10, self.piece1_pos[0] * 80 + 10,
                                self.piece1_pos[1] * 80 + 70, self.piece1_pos[0] * 80 + 70, fill='yellow')
        self.canvas.create_oval(self.piece2_pos[1] * 80 + 10, self.piece2_pos[0] * 80 + 10,
                                self.piece2_pos[1] * 80 + 70, self.piece2_pos[0] * 80 + 70, fill='blue')

    def move_wolf(self, new_pos):
        if self.is_valid_move(new_pos):
            self.wolf_pos = new_pos
            self.piece1_pos = self.get_new_position(self.piece1_pos, self.wolf_pos, self.path[-1], same_direction=True)
            self.piece2_pos = self.get_new_position(self.piece2_pos, self.wolf_pos, self.path[-1], same_direction=False)
            self.draw_board()
            if (self.piece1_pos, self.piece2_pos) == self.target_positions:
                self.canvas.create_text(200, 200, text="Congratulations! You won!", font=('Arial', 24, 'bold'))

    def move_wolf_up(self, event):
        self.path.append(self.wolf_pos)
        self.move_wolf((self.wolf_pos[0] - 1, self.wolf_pos[1]))

    def move_wolf_down(self, event):
        self.path.append(self.wolf_pos)
        self.move_wolf((self.wolf_pos[0] + 1, self.wolf_pos[1]))

    def move_wolf_left(self, event):
        self.path.append(self.wolf_pos)
        self.move_wolf((self.wolf_pos[0], self.wolf_pos[1] - 1))

    def move_wolf_right(self, event):
        self.path.append(self.wolf_pos)
        self.move_wolf((self.wolf_pos[0], self.wolf_pos[1] + 1))

    def is_valid_move(self, new_pos):
        if not (0 <= new_pos[0] < len(self.board) and 0 <= new_pos[1] < len(self.board[0])):
            return False

        if self.board[new_pos[0]][new_pos[1]] == 0:
            return False

        if new_pos == self.piece1_pos or new_pos == self.piece2_pos:
            return False

        return True

    def get_new_position(self, current_pos, wolf_pos, move, same_direction=True):
        direction = 1 if same_direction else -1
        return current_pos[0] + direction * (move[0] - wolf_pos[0]), current_pos[1] + direction * (move[1] - wolf_pos[1])
    
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