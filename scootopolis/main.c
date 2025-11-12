#include <float.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct Point {
  int row;
  int col;
} Point;

static Point p_add(Point p1, Point p2)
{
  return (Point){p1.row + p2.row, p1.col + p2.col};
}

static bool in_rock_list(Point point, Point* rock_list, size_t num_rocks)
{
  for (int i = 0; i < num_rocks; i++) {
    if (point.row == rock_list[i].row && point.col == rock_list[i].col) {
      return true;
    }
  }
  return false;
}

static bool in_bounds(Point point, size_t row, size_t col)
{
  return (point.row >= 0 && point.row < row && point.col >= 0 && point.col < col);
}

static void free_grid(bool** ice_grid, size_t row)
{
  for (size_t i = 0; i < row; i++) {
    if (ice_grid[i]) free(ice_grid[i]);
  }
  free(ice_grid);
}

static inline Point str_to_move(const char* move_ch)
{
  switch (*move_ch) {
    case 'U': return (Point){-1, 0};
    case 'D': return (Point){1, 0};
    case 'L': return (Point){0, -1};
    case 'R': return (Point){0, 1};
  }
  return (Point){0};
}

static Point* get_moves(char* move_str, int* num_moves)
{
  size_t move_str_len = strlen(move_str);
  Point* moves = (Point*)malloc(sizeof(Point) * move_str_len);
  const char* tok;
  int cnt = 0;
  for (tok = move_str; *tok; tok++) {
    //printf("curr tok: %c\n", *tok);
    moves[cnt++] = str_to_move(tok);
  }
  *num_moves = cnt;
  //printf("num_moves: %d\n", *num_moves);
  return moves;
}

static void print_grid(bool **grid, int rows, int cols,
                       const Point *rocks, int n_rocks,
                       Point player)
{
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            Point p = {r, c};
            char ch = '~';

            if (player.row == r && player.col == c) ch = 'S';
            else if (in_rock_list(p, rocks, n_rocks)) ch = 'R';
            else if (grid[r][c]) ch = '*';

            putchar(ch);
        }
        putchar('\n');
    }
    putchar('\n');
}


void scoot(size_t row, size_t col, Point* rock_list, size_t num_rocks, char* move_str)
{
  //printf("size: %lu, %lu\n", row, col);
  Point curr_pos = {0};
  //ice_grid[row][col]
  bool** ice_grid = calloc(row, sizeof(bool *));
  if (!ice_grid) return;
  bool fell = false;
  //alloc
  for (size_t r = 0; r < row; r++) {
    ice_grid[r] = calloc(col, sizeof(bool));
    if (!ice_grid[r]) free_grid(ice_grid, row);
  }
  ice_grid[curr_pos.row][curr_pos.col] = true;

  int num_moves;
  Point* moves = get_moves(move_str, &num_moves);
  if (!moves) free_grid(ice_grid, row);
  for (int i = 0; i < num_moves; i++) {
    //printf("curr: %d, %d\n", curr_pos.row, curr_pos.col);
    //printf("move %d: (%d, %d)\n", i, moves[i].row, moves[i].col);
    //printf("inbounds: %d\n", in_bounds(curr_pos, row, col));
    //printf("rock: %d\n", in_rock_list(curr_pos, rock_list, num_rocks));
    Point next_pos = p_add(curr_pos, moves[i]);
    if (!in_bounds(next_pos, row, col)) {
      printf("OOB\n");
      free(moves);
      return;
    } else if (in_rock_list(next_pos, rock_list, num_rocks)) {
      printf("ROCK\n");
      continue;
    } else if (ice_grid[next_pos.row][next_pos.col] == true) {
      fell = true;
      printf("FELL\n");
      free(moves);
      free_grid(ice_grid, row);
      return;
    }

    curr_pos = next_pos;
    ice_grid[curr_pos.row][curr_pos.col] = true;
  }

  print_grid(ice_grid, row, col, rock_list, num_rocks, curr_pos);
  free(moves);
  free_grid(ice_grid, row);
}

int main(int argc, char** argv)
{
  //get grid size
  Point size;
  scanf("%d,%d", &size.row, &size.col);
  //get rock positions
  Point* rock_list = malloc(size.row*size.col*sizeof(Point));
  Point rock;
  int num_rocks = 0;
  while (scanf("%d,%d", &rock.row, &rock.col) == 2) {
    rock_list[num_rocks++] = rock;
  }
  //get user moves
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF) {}

  char move_str[256];
  scanf("%255s", move_str);
  scoot(size.row, size.col, rock_list, num_rocks, move_str);

  free(rock_list);
  return 0;
}
