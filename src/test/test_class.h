#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include <list>

#include "../brick_game/snake/snake_controller.h"

namespace s21 {
class Model;
class test_class {
 public:
  void test_draw_snake_part(std::pair<int, int> coord, Model &model);
  int test_read_from_file(Model &model);
  std::list<std::pair<int, int>> test_snake_part(Model &model);
  void test_make_apple(Model &model);
  bool test_check_crash(std::pair<int, int> cell, Model &model);
  void test_check_apple(std::pair<int, int> cell, Model &model);
  void test_update_lvl(Model &model);
  void test_erase_snake_part(Model &model);
  int **get_field(Model &mod);
  int **get_next(Model &model);
  void set_score(Model &model, int score);
  int get_speed(Model &model);
  int get_pause(Model &model);
  int test_get_lvl(Model &mod);
  int get_score(Model &model);
  void set_apple(Model &model);
  void set_pause(Controller &con, int st);
  int get_pause(Controller &con);
  int **get_game(Controller &con);
};
}  // namespace s21
#endif  // TEST_CLASS_H
