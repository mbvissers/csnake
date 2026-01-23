#include "csnake.h"
#include <chrono>
#include <cstdlib>
#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <thread>

int main() {
  srandom(time(NULL));
  WINDOW *my_win;
  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);
  init_colors();

  // Arena size
  int min_x = 2;
  int max_x = COLS - 3;
  int min_y = 2;
  int max_y = LINES - 3;

  Arena arena = {min_x, max_x, min_y, max_y};

  // Keep fruit in bounds
  min_x = min_x + 1;
  max_x = max_x - 1;
  min_y = min_y + 1;
  max_y = max_y - 1;

  int rand_x = min_x + (random() % (arena.max_x - arena.min_x - 1 + 1));
  int rand_y = min_y + (random() % (arena.max_y - arena.min_y - 1 + 1));

  // Initial values
  int score = 0;
  std::deque<Position> snake = random_snake(min_x, max_x, min_y, max_y, 5);
  Position fruit = {rand_x, rand_y};
  Position direction_delta = {-1, 0};

  draw_arena(arena);
  draw_snake(snake);
  draw_fruit(fruit);

  refresh();

  while (true) {
    int ch = getch();

    direction_delta = get_direction(ch, direction_delta);
    if (direction_delta.x == 0 && direction_delta.y == 0) {
      break;
    }

    snake =
        move_snake(direction_delta.x, direction_delta.y, snake, arena, fruit);
    StepResult res = checkStep(arena, snake, fruit);

    if (res == Ate) {
      int rand_x = min_x + (random() % (arena.max_x - arena.min_x - 1 + 1));
      int rand_y = min_y + (random() % (arena.max_y - arena.min_y - 1 + 1));
      fruit = {rand_x, rand_y};
      score += 1;
    } else if (res == Died) {
      break;
    }

    draw_snake(snake);
    draw_fruit(fruit);
    draw_score(score);

    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  endwin();
  return 0;
}

std::deque<Position> random_snake(int min_x, int max_x, int min_y, int max_y,
                                  int size) {
  // Move snake to the right (tail at the right, snake looks left)
  Position direction = Position({1, 0});

  std::deque<Position> snake = {};

  // Keep snake in bounds after generating its body
  min_x = min_x + size;
  max_x = max_x - size;
  min_y = min_y + size;
  max_y = max_y - size;

  int head_x = min_x + (random() % (max_x - min_x - 1 + 1));
  int head_y = min_y + (random() % (max_y - min_y - 1 + 1));
  snake.push_back({head_x, head_y});

  for (int i = 0; i < size; i++) {
    head_x = head_x + direction.x;
    head_y = head_y + direction.y;
    snake.push_back({head_x, head_y});
  }

  return snake;
}

std::deque<Position> move_snake(int dx, int dy, std::deque<Position> snake,
                                Arena arena, Position fruit) {
  Position head = snake.front();
  Position tail = snake.back();

  snake.push_front({head.x + dx, head.y + dy});

  StepResult res = checkStep(arena, snake, fruit);

  color_set(4, NULL);
  if (res != Ate) {
    mvprintw(tail.y, tail.x, " ");
    snake.pop_back();
  }

  return snake;
}

void draw_snake(std::deque<Position> snake) {
  color_set(2, NULL);
  for (int i = 0; i < snake.size(); i++) {
    mvprintw(snake[i].y, snake[i].x, "o");
  }
}

void draw_arena(Arena arena) {
  int min_x = arena.min_x;
  int max_x = arena.max_x;
  int min_y = arena.min_y;
  int max_y = arena.max_y;

  color_set(1, NULL);
  for (int y = min_y; y <= max_y; y++) {
    for (int x = min_x; x <= max_x; x++) {
      bool is_wall = (x == min_x || x == max_x) || (y == min_y || y == max_y);
      if (is_wall) {
        mvprintw(y, x, "#");
      }
    }
  }
}

void draw_fruit(Position pos) {
  int x = pos.x;
  int y = pos.y;

  color_set(2, NULL);
  mvprintw(y, x, "A");
}

void draw_score(int score) {
  color_set(3, NULL);
  mvprintw(1, 2, " Score: %i ", score);
}

Position get_direction(int ch, Position dir) {
  switch (ch) {
  case 'q':
    dir = {0, 0};
    break;
  case 'w':
    if (dir.y != 1)
      dir = {0, -1};
    break;
  case 'a':
    if (dir.x != 1)
      dir = {-1, 0};
    break;
  case 's':
    if (dir.y != -1)
      dir = {0, 1};
    break;
  case 'd':
    if (dir.x != -1)
      dir = {1, 0};
    break;
  };

  return dir;
}

StepResult checkStep(Arena arena, std::deque<Position> snake, Position fruit) {
  Position head = snake.front();

  if (head.x == arena.min_x || head.x == arena.max_x || head.y == arena.min_y ||
      head.y == arena.max_y) {
    return Died;
  }
  if (head.x == fruit.x && head.y == fruit.y) {
    return Ate;
  }

  return Moved;
}

void init_colors() {
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(4, COLOR_BLACK, COLOR_BLACK);
}
