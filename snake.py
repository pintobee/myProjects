"""Snake game"""
import os
import sys
import random
import pygame
from pygame.math import Vector2

os.environ['SDL_AUDIODRIVER'] = 'dummy'


class SNAKE:
    """creates the snake"""

    def __init__(self):
        self.body = [Vector2(5, 10), Vector2(4, 10), Vector2(3, 10)]
        self.direction = Vector2(1, 0)
        self.new_block = False

    def draw_snake(self):
        """create a rect, draw the rectangle"""
        for block in self.body:
            x_pos = int(block.x * CELL_SIZE)
            y_pos = int(block.y * CELL_SIZE)
            block_rect = pygame.Rect(x_pos, y_pos, CELL_SIZE, CELL_SIZE)
            pygame.draw.rect(screen, (183, 111, 122), block_rect)

    def move_snake(self):
        """makes the snake move"""
        if self.new_block is True:
            body_copy = self.body[:]
            body_copy.insert(0, body_copy[0] + self.direction)
            self.body = body_copy[:]
            self.new_block = False
        else:
            body_copy = self.body[:-1]
            body_copy.insert(0, body_copy[0] + self.direction)
            self.body = body_copy[:]

    def add_block(self):
        """makes snake grow a little"""
        self.new_block = True


class FRUIT:
    """creates the fruit and appears randomly"""

    def __init__(self):
        self.randomize()

    def draw_fruit(self):
        """draws fruit creates a rect"""
        fruit_rect = pygame.Rect(
            int(self.pos.x * CELL_SIZE), int(self.pos.y * CELL_SIZE), CELL_SIZE, CELL_SIZE)
        pygame.draw.rect(screen, (126, 166, 114), fruit_rect)

    def randomize(self):
        """randomizes fruit"""
        self.x = random.randint(0, CELL_NUMBER - 1)
        self.y = random.randint(0, CELL_NUMBER - 1)
        self.pos = Vector2(self.x, self.y)


class Main:
    """main """

    def __init__(self):
        self.snake = SNAKE()
        self.fruit = FRUIT()

    def update(self):
        """updates program"""
        self.snake.move_snake()
        self.check_collision()
        self.check_fail()

    def draw_elements(self):
        """gets fruit and snake together"""
        self.fruit.draw_fruit()
        self.snake.draw_snake()
        self.draw_score()

    def check_collision(self):
        """reposition fruit"""
        if self.fruit.pos == self.snake.body[0]:
            self.fruit.randomize()
            self.snake.add_block()

    def check_fail(self):
        """check if snake is outside of screen or if it hits itself"""
        if not 0 <= self.snake.body[0].x < CELL_NUMBER or not (
                0 <= self.snake.body[0].y < CELL_NUMBER):
            self.game_over()

        for block in self.snake.body[1:]:
            if block == self.snake.body[0]:
                self.game_over()

    def game_over(self):
        """game over"""
        pygame.quit
        sys.exit()

    def draw_score(self):
        """get scores"""
        score_text = str(len(self.snake.body) - 3)
        score_surface = game_font.render(score_text, True, (56, 74, 12))
        score_x = int(CELL_SIZE * 2)
        score_y = int(CELL_SIZE * 2)
        score_rect = score_surface.get_rect(topleft=(score_x, score_y))
        screen.blit(score_surface, score_rect)


pygame.init()
CELL_SIZE = 40
CELL_NUMBER = 20
screen = pygame.display.set_mode(
    (CELL_NUMBER * CELL_SIZE, CELL_NUMBER * CELL_SIZE))
clock = pygame.time.Clock()
game_font = pygame.font.Font(None, 25)

SCREEN_UPDATE = pygame.USEREVENT
pygame.time.set_timer(SCREEN_UPDATE, 150)

main_game = Main()

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            # pygame.quit
            sys.exit()
        if event.type == SCREEN_UPDATE:
            main_game.update()
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP:
                if main_game.snake.direction.y != 1:
                    main_game.snake.direction = Vector2(0, -1)
            if event.key == pygame.K_RIGHT:
                if main_game.snake.direction.x != -1:
                    main_game.snake.direction = Vector2(1, 0)
            if event.key == pygame.K_DOWN:
                if main_game.snake.direction.y != -1:
                    main_game.snake.direction = Vector2(0, 1)
            if event.key == pygame.K_LEFT:
                if main_game.snake.direction.x != 1:
                    main_game.snake.direction = Vector2(-1, 0)
    # draw all our elements
    screen.fill((175, 215, 70))
    main_game.draw_elements()
    pygame.display.update()
    clock.tick(60)
