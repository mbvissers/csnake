#include <chrono>
#include <cstdlib>
#include <ncursesw/ncurses.h>
#include <thread>

void draw_arena(int, int, int, int);
void draw_fruit(int, int);

int main() {
  srandom(time(NULL));
  WINDOW *my_win;
  initscr();
  start_color();
  cbreak();
  noecho();
  curs_set(0);

  int min_x = 2;
  int max_x = COLS - 3;
  int min_y = 2;
  int max_y = LINES - 3;

  // mvprintw(1, 2, "Size: %i x %i", max_y, max_x);
  draw_arena(min_x, max_x, min_y, max_y);
  int rand_x = min_x + (random() % (max_x - min_x - 1 + 1));
  int rand_y = min_y + (random() % (max_y - min_y - 1 + 1));
  mvprintw(1, 2, "Rand: %i x %i", rand_x, rand_y);
  draw_fruit(rand_x, rand_y);
  refresh();

  std::this_thread::sleep_for(std::chrono::seconds(5));

  endwin();
  return 0;
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
  init_pair(1, COLOR_RED, COLOR_BLACK);
  color_set(1, NULL);
  mvprintw(y, x, "A");
}
