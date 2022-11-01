import pygame as p
from functions import dig, drawGamestate, verifyWin
from minesweeperClass import minesweeper


WIDTH = HEIGHT = 720
DIMENSION = 8
SQ_SIZE = HEIGHT // DIMENSION
MAX_FPS = 15
OFFSET = 10
BOMBS = 10

def drawGame():
    p.init()
    screen = p.display.set_mode((WIDTH + OFFSET, HEIGHT + OFFSET), p.NOFRAME)
    screen.fill(p.Color("white"))
    clock = p.time.Clock()
    running = True
    firstDig = True
    m = minesweeper(BOMBS)

    while running:
        for e in p.event.get():
            if e.type == p.QUIT:
                running = False
            elif e.type == p.MOUSEBUTTONDOWN:
                location = p.mouse.get_pos()
                clickC = location[0] // SQ_SIZE
                clickR = location[1] // SQ_SIZE
                if e.button == 1:
                    if firstDig:
                        while m.board[clickR][clickC] != "0":
                            m = minesweeper(BOMBS)
                        firstDig = False
                    if m.board[clickR][clickC] == "x":
                        print("You Lost!")
                        for r in range(DIMENSION):
                            for c in range(DIMENSION):
                                m.shown[r][c] = 1
                        for r in range(DIMENSION):
                            for c in range(DIMENSION):
                                m.flags[r][c] = 0
                    dig(clickR, clickC, m.board, m.shown)
                elif e.button == 3:
                    m.flags[clickR][clickC] = (m.flags[clickR][clickC] + 1) % 2
        if verifyWin(m.board, m.flags):
            print("You Won!")
            for r in range(DIMENSION):
                for c in range(DIMENSION):
                    m.shown[r][c] = 1
        drawGamestate(screen, m.board, m.shown, m.flags)
        clock.tick(MAX_FPS)
        p.display.flip()