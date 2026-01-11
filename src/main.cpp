#include <chrono>
#include <ncurses.h>
#include <thread>

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
  for (int y = min_y; y <= max_y; y++) {
    for (int x = min_x; x <= max_x; x++){
      bool is_wall = (x == min_x || x == max_x) || (y == min_y || y == max_y);
      if (is_wall)
        mvprintw(y, x, "#");
    }
  }
  refresh();

  std::this_thread::sleep_for(std::chrono::seconds(5));

  endwin();
  return 0;
}
