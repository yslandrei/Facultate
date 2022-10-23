import pygame as p


WIDTH = HEIGHT = 720
DIMENSION = 8
SQ_SIZE = HEIGHT // DIMENSION
MAX_FPS = 15
IMAGES = {}


def loadImages():
    pieces = ["bP", "bR", "bH", "bB", "bQ", "bK", "wP", "wR", "wH", "wB", "wQ", "wK", "dot", "border"]
    for piece in pieces:
        IMAGES[piece] = p.transform.scale(p.image.load("images/" + piece + ".png"), (SQ_SIZE, SQ_SIZE))

def drawBoard(screen):
    colors = [p.Color("white"), p.Color("grey")]
    for r in range(DIMENSION):
        for c in range(DIMENSION):
            color = colors[(r + c) % 2]
            p.draw.rect(screen, color, p.Rect(c * SQ_SIZE, r * SQ_SIZE, SQ_SIZE, SQ_SIZE))

def drawPieces(screen, board):
    for r in range(DIMENSION):
        for c in range(DIMENSION):
            piece = board[r][c]
            if piece != "--":
                screen.blit(IMAGES[piece], p.Rect(c * SQ_SIZE, r * SQ_SIZE, SQ_SIZE, SQ_SIZE))

def drawPossibleMoves(screen, possibleMoves):
    for i in range(len(possibleMoves)):
        screen.blit(IMAGES["dot"], p.Rect(possibleMoves[i][1] * SQ_SIZE, possibleMoves[i][0] * SQ_SIZE, SQ_SIZE, SQ_SIZE))

def drawPossibleKills(screen, possibleKills):
    for i in range(len(possibleKills)):
        screen.blit(IMAGES["border"], p.Rect(possibleKills[i][1] * SQ_SIZE, possibleKills[i][0] * SQ_SIZE, SQ_SIZE, SQ_SIZE))

def drawGamestate(screen, board, possibleMoves, possibleKills):
    drawBoard(screen)
    drawPieces(screen, board)
    drawPossibleMoves(screen, possibleMoves)
    drawPossibleKills(screen, possibleKills)

def updateTurn(turn):
    if turn == "w":
        return "b"
    return "w"