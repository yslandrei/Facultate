class chess():
    def __init__(self):
        self.board = [
            ["bR", "bH", "bB", "bQ", "bK", "bB", "bH", "bR"],
            ["bP", "bP", "bP", "bP", "bP", "bP", "bP", "bP"],
            ["--", "--", "--", "--", "--", "--", "--", "--"],
            ["--", "--", "--", "--", "--", "--", "--", "--"],
            ["--", "--", "--", "--", "--", "--", "--", "--"],
            ["--", "--", "--", "--", "--", "--", "--", "--"],
            ["wP", "wP", "wP", "wP", "wP", "wP", "wP", "wP"],
            ["wR", "wH", "wB", "wQ", "wK", "wB", "wH", "wR"]
        ]

    def makeMove(self, playerClicks):
        self.startRow = playerClicks[0][1]
        self.startCol = playerClicks[0][0]
        self.finishRow = playerClicks[1][1]
        self.finishCol = playerClicks[1][0]
        self.board[self.finishRow][self.finishCol] = self.board[self.startRow][self.startCol]
        self.board[self.startRow][self.startCol] = "--"

    def validateFirstClick(self, r, c, turn):
        if self.board[r][c][0] != turn:
            return False
        return True

    def validateSecondClick(self, r, c, possibleMoves, possibleKills):
        answear = False
        for i in range(len(possibleMoves)):
            if possibleMoves[i][0] == r and possibleMoves[i][1] == c:
                answear = True
                break
        for i in range(len(possibleKills)):
            if possibleKills[i][0] == r and possibleKills[i][1] == c:
                answear = True
                break
        return answear

    def getValidMoves(self, r, c):
        validMoves = list()
        validKills = list()
        piece = self.board[r][c] # Pawn, Rook, Knight, Bishop, King, Queen = Rook + Bishop
        if piece == "bP": # Black Pawn
            if r < 7:
                if self.board[r + 1][c] == "--":
                    validMoves.append((r + 1, c))
                if self.board[r + 1][c - 1] != "--": # Attack
                    validKills.append((r + 1, c - 1))
                if self.board[r + 1][c + 1] != "--": # Attack
                    validKills.append((r + 1, c + 1))
            if r == 1 and self.board[r + 2][c] == "--": # First move
                validMoves.append((r + 2, c))

        if piece == "wP": # White Pawn
            if r > 0:
                if self.board[r - 1][c] == "--":
                    validMoves.append((r - 1, c))
                if self.board[r - 1][c - 1] != "--": # Attack
                    validKills.append((r - 1, c - 1))
                if self.board[r - 1][c + 1] != "--": # Attack
                    validKills.append((r - 1, c + 1))
            if r == 6: # First move
                validMoves.append((r - 2, c))

        if piece == "bR" or piece == "wR" or piece == "bQ" or piece == "wQ": # Black and White Rook
            for C in range(c + 1, 8): # right
                if self.board[r][C] != "--":
                    validKills.append((r, C))
                    break
                validMoves.append((r, C))
            for C in range(c - 1, -1, -1): # left
                if self.board[r][C] != "--":
                    validKills.append((r, C))
                    break
                validMoves.append((r, C))
            for R in range(r + 1, 8): # down
                if self.board[R][c] != "--":
                    validKills.append((R, c))
                    break
                validMoves.append((R, c))
            for R in range(r - 1, -1, -1): # up
                if self.board[R][c] != "--":
                    validKills.append((R, c))
                    break
                validMoves.append((R, c))
        
        if piece == "bH" or piece == "wH": # Black and White Knight
            offsetR = [-2, -2, -1, +1, +2, +2, -1, +1]
            offsetC = [-1, +1, +2, +2, -1, +1, -2, -2]
            for i in range(8):
                if r + offsetR[i] >= 0 and r + offsetR[i] <= 7 and c + offsetC[i] >= 0 and c + offsetC[i] <= 7:
                    if self.board[r + offsetR[i]][c + offsetC[i]] == "--":
                        validMoves.append((r + offsetR[i], c + offsetC[i]))
                    else:
                        validKills.append((r + offsetR[i], c + offsetC[i]))

        if piece == "bB" or piece == "wB" or piece == "bQ" or piece == "wQ":  # Black and White Bishop
            R, C = r + 1, c + 1
            while R <= 7 and C <= 7: # down and right
                if(self.board[R][C] != "--"):
                    validKills.append((R, C))
                    break
                validMoves.append((R, C))
                R += 1
                C += 1
            R, C = r + 1, c - 1
            while R <= 7 and C >= 0: # down and left
                if(self.board[R][C] != "--"):
                    validKills.append((R, C))
                    break
                validMoves.append((R, C))
                R += 1
                C -= 1
            R, C = r - 1, c + 1
            while R >= 0 and C <= 7: # up and right
                if(self.board[R][C] != "--"):
                    validKills.append((R, C))
                    break
                validMoves.append((R, C))
                R -= 1
                C += 1
            R, C = r - 1, c - 1
            while R >= 0 and C >= 0: # up and left
                if(self.board[R][C] != "--"):
                    validKills.append((R, C))
                    break
                validMoves.append((R, C))
                R -= 1
                C -= 1

        if piece == "bK" or piece == "wK": # Black and White King
            offsetR = [-1, -1, -1, +0, +0, +1, +1, +1]
            offsetC = [-1, +0, +1, -1, +1, -1, +0, +1]
            for i in range(8):
                if r + offsetR[i] >= 0 and r + offsetR[i] <= 7 and c + offsetC[i] >= 0 and c + offsetC[i] <= 7:
                    if self.board[r + offsetR[i]][c + offsetC[i]] == "--":
                        validMoves.append((r + offsetR[i], c + offsetC[i]))
                    else:
                        validKills.append((r + offsetR[i], c + offsetC[i]))
        
        offset = 0
        for i in range(len(validMoves)): # check for out of board moves
            if validMoves[i - offset][0] < 0 or validMoves[i - offset][1] < 0 or validMoves[i - offset][0] > 8 or validMoves[i - offset][1] > 8:
                validMoves.pop(i - offset)
                offset += 1

        offset = 0
        for i in range(len(validKills)):
            if self.board[validKills[i - offset][0]][validKills[i - offset][1]][0] == piece[0]:
                validKills.pop(i - offset)
                offset += 1

        return validMoves, validKills