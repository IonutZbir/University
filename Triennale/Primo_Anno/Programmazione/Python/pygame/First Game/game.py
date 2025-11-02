import pygame, os

NAME = "First Game"
WIDTH, HEIGHT = 900, 500 # window dimensions
SPACESHIP_WIDTH, SPACESHIP_HEIGHT = 50, 40 # spaceships dimensions
FPS = 60 # frame rate

# image import
YELLOW_SPACESHIP_IMAGE = pygame.image.load(os.path.join('Assets', 'spaceship_yellow.png'))
RED_SPACESHIP_IMAGE = pygame.image.load(os.path.join('Assets', 'spaceship_red.png'))

# image scaling 
YELLOW_SPACESHIP = pygame.transform.rotate(pygame.transform.scale(YELLOW_SPACESHIP_IMAGE, (SPACESHIP_WIDTH, SPACESHIP_HEIGHT)), 90)
RED_SPACESHIP = pygame.transform.rotate(pygame.transform.scale(RED_SPACESHIP_IMAGE, (SPACESHIP_WIDTH, SPACESHIP_HEIGHT)), 270)

WINDOW = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption(NAME)

# COLORS
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
BLACK = (0, 0, 0)

def drawWindow(color, red, yellow):
    WINDOW.fill(color)  # background
    WINDOW.blit(YELLOW_SPACESHIP, (yellow.x, yellow.y))
    WINDOW.blit(RED_SPACESHIP, (red.x, red.y))
    pygame.display.update() # ogni volta che vengono aggiunti oggetti nuovi alla finestra, bisogna aggiornarla



def main():
    yellow = pygame.Rect(100, 300, SPACESHIP_WIDTH, SPACESHIP_HEIGHT)
    red = pygame.Rect(300, 300, SPACESHIP_WIDTH, SPACESHIP_HEIGHT)
    
    
    clock = pygame.time.Clock()
    run = True
    while run:
        clock.tick(FPS)
        for event in pygame.event.get():
            if event.type == pygame.QUIT: # quando l'utente preme sulla X per chiudere la finestra, il programma termina
                run = False
        drawWindow(WHITE, red, yellow)
    
    
    pygame.quit()

    
if __name__ == "__main__":
    main()