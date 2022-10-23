from gameState import gameState
from gui import drawGamestate, p, loadImages, WIDTH, HEIGHT, MAX_FPS

def main():
    p.init()
    screen = p.display.set_mode((WIDTH, HEIGHT))
    clock = p.time.Clock()
    screen.fill(p.Color("white"))
    gs = gameState()
    loadImages()
    running = True
    while running:
        for e in p.event.get():
            if e.type == p.QUIT:
                running = False
        drawGamestate(screen, gs)
        clock.tick(MAX_FPS)
        p.display.flip()


if __name__ == "__main__":
    main()