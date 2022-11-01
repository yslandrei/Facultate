from random import randint


DIMENSION = 8

class minesweeper():
    def __init__(self, bombs):
        self.bombs = bombs
        self.board = [["0" for i in range(DIMENSION)] for i in range(DIMENSION)]
        self.shown = [[0 for i in range(DIMENSION)] for i in range(DIMENSION)]
        self.flags = [[0 for i in range(DIMENSION)] for i in range(DIMENSION)]

        i = 0
        while(i < bombs):
            r = randint(0, 7)
            c = randint(0, 7)
            if self.board[r][c] == "0":
                self.board[r][c] = "x"
                i += 1
        
        offR = [-1, -1, +0, +1, +1, +1, +0, -1]
        offC = [+0, +1, +1, +1, +0, -1, -1, -1]
        for r in range(DIMENSION):
            for c in range(DIMENSION):
                if self.board[r][c] != "x":
                    for i in range(8):
                        if r + offR[i] >= 0 and r + offR[i]  <= 7 and c + offC[i] >= 0 and c + offC[i]  <= 7:
                            if self.board[r + offR[i]][c + offC[i]] == "x":
                                self.board[r][c] = str(int(self.board[r][c]) + 1)
                    

