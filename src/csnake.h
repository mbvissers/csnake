#include <deque>
#include <stdlib.h>

struct Position {
  int x;
  int y;
};

struct Arena {
  int min_x;
  int max_x;
  int min_y;
  int max_y;
};

enum StepResult { Moved, Ate, Died };

std::deque<Position> move_snake(int dx, int dy, std::deque<Position> snake,
                                Arena arena, Position fruit);
void draw_arena(Arena);
void draw_fruit(Position);
void draw_snake(std::deque<Position>);
void draw_score(int);
std::deque<Position> random_snake(int, int, int, int, int);
Position get_direction(int, Position);
void init_colors();
StepResult checkStep(Arena arena, std::deque<Position> snake, Position fruit);
std::deque<Position> grow_snake(std::deque<Position>);
