#include <chrono>
#include <ncurses.h>
#include <thread>

int main() {
  WINDOW *my_win;
  initscr();
  cbreak();
  noecho();
  curs_set(0);

  mvprintw(1, 1, "Size: %i x %i", LINES, COLS);
  refresh();

  std::this_thread::sleep_for(std::chrono::seconds(2));

  endwin();
  return 0;
}
