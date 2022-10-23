import pygame as p
from chessClass import chess
from functions import drawGamestate, loadImages, updateTurn


WIDTH = HEIGHT = 720
DIMENSION = 8
SQ_SIZE = HEIGHT // DIMENSION
MAX_FPS = 15
IMAGES = {}

def drawGUI():
    p.init() # Initialize pyGame Window
    screen = p.display.set_mode((WIDTH, HEIGHT), p.NOFRAME)
    screen.fill(p.Color("white"))
    clock = p.time.Clock()
    loadImages()

    c = chess() # Initialize Variables
    playerClicks = list()
    possibleMoves = list()
    possibleKills = list()
    turn = "w"
    running = True

    while running: # Game Loop
        for e in p.event.get():
            if e.type == p.QUIT:
                running = False
            elif e.type == p.MOUSEBUTTONDOWN:
                location = p.mouse.get_pos()
                clickX = location[0] // SQ_SIZE
                clickY = location[1] // SQ_SIZE
                if len(playerClicks) == 0 and c.validateFirstClick(clickY, clickX, turn): # user selected a piece
                    playerClicks.append((clickX, clickY))
                    possibleMoves, possibleKills = c.getValidMoves(clickY, clickX)
                elif len(playerClicks) == 1:
                    if playerClicks[0] == (clickX, clickY): # user deselected the piece
                        playerClicks.clear()
                        possibleMoves.clear()
                        possibleKills.clear()
                    elif playerClicks[0] != (clickX, clickY) and c.validateSecondClick(clickY, clickX, possibleMoves, possibleKills):
                        playerClicks.append((clickX, clickY)) # user selected the position to move
                        c.makeMove(playerClicks)
                        turn = updateTurn(turn)
                        playerClicks.clear()
                        possibleMoves.clear()
                        possibleKills.clear()
            
        drawGamestate(screen, c.board, possibleMoves, possibleKills) # Refresh Screen
        clock.tick(MAX_FPS)
        p.display.flip()
