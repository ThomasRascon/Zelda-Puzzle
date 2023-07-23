import tkinter as tk
from collections import deque

class PuzzleGame:
    def __init__(self, board, initial_positions):
        self.board = board
        self.target_positions = self.find_targets()
        self.wolf_pos, self.piece1_pos, self.piece2_pos = initial_positions
        self.path = deque()  # Use a deque to store the move history

        self.root = tk.Tk()
        self.canvas = tk.Canvas(self.root, width=len(self.board[0]) * 80, height=len(self.board) * 80)
        self.canvas.pack()
        self.draw_board()
        self.root.bind('<Up>', self.move_wolf_up)
        self.root.bind('<Down>', self.move_wolf_down)
        self.root.bind('<Left>', self.move_wolf_left)
        self.root.bind('<Right>', self.move_wolf_right)
        self.root.bind('u', self.undo_move)  # Bind the 'U' key to undo_move
        self.root.mainloop()

    def find_targets(self):
        targets = []
        for i in range(len(self.board)):
            for j in range(len(self.board[0])):
                if self.board[i][j] == 2:
                    targets.append((i, j))
        return tuple(targets)

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
            current_positions = (self.wolf_pos, self.piece1_pos, self.piece2_pos)
            self.path.append(current_positions)
            new_piece1_pos = self.get_new_position(self.piece1_pos, self.wolf_pos, new_pos, same_direction=True)
            new_piece2_pos = self.get_new_position(self.piece2_pos, self.wolf_pos, new_pos, same_direction=False)

            if new_pos == self.piece2_pos or new_pos in [self.piece1_pos, self.piece2_pos]:
                self.display_message("Can't do that move", duration=1000)
            elif new_piece1_pos == new_piece2_pos:
                self.display_message("Can't do that move", duration=1000)
            elif self.wolf_and_piece2_will_overlap(new_pos):
                self.display_message("Can't do that move", duration=1000)
            else:
                if self.is_valid_piece_move(new_piece1_pos, self.piece2_pos):
                    self.piece1_pos = new_piece1_pos
                if self.is_valid_piece_move(new_piece2_pos, self.piece1_pos):
                    self.piece2_pos = new_piece2_pos

                self.wolf_pos = new_pos
                self.draw_board()
                if (self.piece1_pos, self.piece2_pos) == self.target_positions or (self.piece2_pos, self.piece1_pos) == self.target_positions:
                    self.canvas.create_text(200, 200, text="You win", font=('Arial', 24, 'bold'))

    def wolf_and_piece2_will_overlap(self, new_pos):
        movement=(new_pos[0]-self.wolf_pos[0],new_pos[1]-self.wolf_pos[1])
        new_piece2_position=(self.piece2_pos[0]-movement[0],self.piece2_pos[1]-movement[1])
        return new_pos==new_piece2_position

    def display_message(self, message, duration):
        message_obj = self.canvas.create_text(200, 200, text=message, font=('Arial', 24, 'bold'))
        self.root.after(duration, lambda: self.canvas.delete(message_obj))

    def undo_move(self, event):
        if not self.path:
            self.display_message("Can't undo: beginning", duration=1000)
        else:
            last_positions = self.path.pop()  # Get the last recorded positions
            if len(last_positions) == 3:  # Check if the history contains all positions
                self.wolf_pos, self.piece1_pos, self.piece2_pos = last_positions  # Revert all positions
            else:
                self.display_message("Can't undo: beginning", duration=1000)
            self.draw_board()  # Redraw the board after undoing the moves
            self.display_message("UNDO", duration=1000)

    def get_move_symbol(self, move):
        # Helper method to convert move positions to move symbols (U, D, L, R)
        if move == (self.wolf_pos[0] - 1, self.wolf_pos[1]):
            return "U"
        elif move == (self.wolf_pos[0] + 1, self.wolf_pos[1]):
            return "D"
        elif move == (self.wolf_pos[0], self.wolf_pos[1] - 1):
            return "L"
        elif move == (self.wolf_pos[0], self.wolf_pos[1] + 1):
            return "R"
        else:
            return ""
        
    def move_wolf_up(self, event):
        self.path.append(self.wolf_pos)
        new_pos = (self.wolf_pos[0] - 1, self.wolf_pos[1])
        if self.is_valid_move(new_pos):
            self.move_wolf(new_pos)

    def move_wolf_down(self, event):
        self.path.append(self.wolf_pos)
        new_pos = (self.wolf_pos[0] + 1, self.wolf_pos[1])
        if self.is_valid_move(new_pos):
            self.move_wolf(new_pos)

    def move_wolf_left(self, event):
        self.path.append(self.wolf_pos)
        new_pos = (self.wolf_pos[0], self.wolf_pos[1] - 1)
        if self.is_valid_move(new_pos):
            self.move_wolf(new_pos)

    def move_wolf_right(self, event):
        self.path.append(self.wolf_pos)
        new_pos = (self.wolf_pos[0], self.wolf_pos[1] + 1)
        if self.is_valid_move(new_pos):
            self.move_wolf(new_pos)

    def is_valid_move(self, new_pos):
        if not (0 <= new_pos[0] < len(self.board) and 0 <= new_pos[1] < len(self.board[0])):
            return False

        if self.board[new_pos[0]][new_pos[1]] == 0:
            return False

        return True

    def is_valid_piece_move(self, new_piece_pos, other_piece_pos):
        if new_piece_pos == other_piece_pos:
            return False

        if not (0 <= new_piece_pos[0] < len(self.board) and 0 <= new_piece_pos[1] < len(self.board[0])):
            return False

        if self.board[new_piece_pos[0]][new_piece_pos[1]] == 0:
            return False

        return True

    def get_new_position(self, current_pos, wolf_pos, move, same_direction=True):
        if same_direction:
            direction = 1
        else:
            direction = -1

        dx, dy = move[0] - wolf_pos[0], move[1] - wolf_pos[1]
        new_pos = current_pos[0] + direction * dx, current_pos[1] + direction * dy

        return new_pos

# Example usage
board = [[1, 1, 1, 1, 1, 1, 1, 1, 1],
         [1, 2, 1, 1, 1, 1, 1, 1, 1],
         [1, 1, 1, 0, 0, 0, 1, 1, 1],
         [0, 0, 0, 1, 1, 1, 0, 0, 0],
         [0, 0, 0, 1, 2, 1, 0, 0, 0],
         [0, 0, 0, 1, 1, 1, 0, 0, 0]]

initial_positions = ((1, 7), (4, 5), (1, 1))

game = PuzzleGame(board, initial_positions)