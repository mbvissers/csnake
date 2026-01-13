#include <chrono>
#include <cstdlib>
#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <thread>
#include <vector>

struct Position {
  int x;
  int y;
};

void draw_arena(int, int, int, int);
void draw_fruit(int, int);
std::vector<Position> random_snake(int, int, int, int, int);
void draw_snake(std::vector<Position>);
void draw_score(int);

int main() {
  srandom(time(NULL));
  WINDOW *my_win;
  initscr();
  start_color();
  cbreak();
  noecho();
  curs_set(0);

  // Arena size
  int min_x = 2;
  int max_x = COLS - 3;
  int min_y = 2;
  int max_y = LINES - 3;

  std::vector<Position> snake = random_snake(min_x, max_x, min_y, max_y, 5);

  // mvprintw(1, 2, "Size: %i x %i", max_y, max_x);
  draw_arena(min_x, max_x, min_y, max_y);
  draw_snake(snake);
  draw_score(123);

  int rand_x = min_x + (random() % (max_x - min_x - 1 + 1));
  int rand_y = min_y + (random() % (max_y - min_y - 1 + 1));
  // Keep fruit in bounds
  min_x = min_x + 1;
  max_x = max_x - 1;
  min_y = min_y + 1;
  max_y = max_y - 1;
  draw_fruit(rand_x, rand_y);

  refresh();

  std::this_thread::sleep_for(std::chrono::seconds(5));

  endwin();
  return 0;
}

std::vector<Position> random_snake(int min_x, int max_x, int min_y, int max_y,
                                   int size) {
  // TODO: Make this a random direction
  Position direction = Position({-1, 0});

  std::vector<Position> snake = {};

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

void draw_snake(std::vector<Position> snake) {
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  color_set(2, NULL);
  for (int i = 0; i < snake.size(); i++) {
    mvprintw(snake[i].y, snake[i].x, "o");
  }
}

void draw_arena(int min_x, int max_x, int min_y, int max_y) {
  init_pair(1, COLOR_RED, COLOR_BLACK);
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

void draw_fruit(int x, int y) {
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  color_set(2, NULL);
  mvprintw(y, x, "A");
}

void draw_score(int score) {
  init_pair(3, COLOR_BLACK, COLOR_MAGENTA);
  color_set(3, NULL);
  mvprintw(1, 2, " Score: %i ", score);
}
