#include <chrono>
#include <ncursesw/ncurses.h>
#include <thread>

void draw_arena(int, int, int, int);

int main() {
  WINDOW *my_win;
  initscr();
  cbreak();
  noecho();
  curs_set(0);

  int min_x = 2;
  int max_x = COLS - 3;
  int min_y = 2;
  int max_y = LINES - 3;

  mvprintw(1, 2, "Size: %i x %i", max_y, max_x);
  draw_arena(min_x, max_x, min_y, max_y);
  refresh();

  std::this_thread::sleep_for(std::chrono::seconds(5));

  endwin();
  return 0;
}

void draw_arena(int min_x, int max_x, int min_y, int max_y) {
  for (int y = min_y; y <= max_y; y++) {
    for (int x = min_x; x <= max_x; x++) {
      bool is_wall = (x == min_x || x == max_x) || (y == min_y || y == max_y);
      if (is_wall)
        mvprintw(y, x, "#");
    }
  }
}
