import pygame as p


WIDTH = HEIGHT = 720
DIMENSION = 8
SQ_SIZE = HEIGHT // DIMENSION
OFFSET = 10
FONT_SIZE = 54
LIGHT_GREY = (240, 240, 240)

def drawBoard(screen, shown):
    for r in range(DIMENSION):
        for c in range(DIMENSION):
            if shown[r][c]:
                p.draw.rect(screen, p.Color(LIGHT_GREY), p.Rect(c * SQ_SIZE + OFFSET, r * SQ_SIZE + OFFSET, SQ_SIZE - OFFSET, SQ_SIZE - OFFSET))
            else:
                p.draw.rect(screen, p.Color("grey"), p.Rect(c * SQ_SIZE + OFFSET, r * SQ_SIZE + OFFSET, SQ_SIZE - OFFSET, SQ_SIZE - OFFSET))

def drawNumbers(screen, board, shown, flags):
    font = p.font.SysFont(None, FONT_SIZE)
    colors = {
        "x": "black",
        "0": LIGHT_GREY,
        "1": "blue",
        "2": "green",
        "3": "red",
        "4": "cyan",
        "5": "brown",
        "6": "yellow",
        "7": "black",
        "8": "purple",
    }
    for r in range(DIMENSION):
        for c in range(DIMENSION):
            if flags[r][c]:
                numberImg = font.render("F", True, p.Color("red"))
            else:
                if shown[r][c]:
                    numberImg = font.render(board[r][c], True, p.Color(colors[board[r][c]]))
                else:
                    numberImg = font.render(board[r][c], True, p.Color("grey"))
            screen.blit(numberImg, p.Rect((c + 0.45) * SQ_SIZE, (r + 0.38) * SQ_SIZE, SQ_SIZE, SQ_SIZE))
        
def drawGamestate(screen, board, shown, flags):
    drawBoard(screen, shown)
    drawNumbers(screen, board, shown, flags)    

def dig(r, c, board, shown):
    offR = [-1, -1, +0, +1, +1, +1, +0, -1]
    offC = [+0, +1, +1, +1, +0, -1, -1, -1]
    if board[r][c] == "0":
        shown[r][c] = 1
        for i in range(8):
            if r + offR[i] >= 0 and r + offR[i] < DIMENSION and c + offC[i] >= 0 and c + offC[i] < DIMENSION:
                if shown[r + offR[i]][c + offC[i]] == 0:
                    dig(r + offR[i], c + offC[i], board, shown)
    elif board[r][c] >= "1" and board[r][c] <= "8":
        shown[r][c] = 1

def verifyWin(board, flags):
    for r in range(DIMENSION):
        for c in range(DIMENSION):
            if board[r][c] == "x" and flags[r][c] == 0:
                return 0
    return 1



