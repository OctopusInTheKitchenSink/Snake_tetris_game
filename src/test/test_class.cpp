#include "test_class.h"
namespace s21 {
void test_class::test_draw_snake_part(std::pair<int, int> coord, Model &model) {
  model.draw_snake_part(coord);
}
int test_class::test_read_from_file(Model &model) {
  return model.read_from_file();
}
std::list<std::pair<int, int>> test_class::test_snake_part(Model &model) {
  return model.snake_elements;
}
void test_class::test_make_apple(Model &model) { model.make_apple(); }
bool test_class::test_check_crash(std::pair<int, int> cell, Model &model) {
  return model.check_crash(cell);
}
void test_class::test_check_apple(std::pair<int, int> cell, Model &model) {
  model.check_apple(cell);
}
void test_class::test_update_lvl(Model &model) { model.update_lvl(); }
void test_class::test_erase_snake_part(Model &model) {
  model.erase_snake_part();
}
int **test_class::get_field(Model &mod) { return mod.game.field; }
int test_class::test_get_lvl(Model &mod) { return mod.game.level; }
int **test_class::get_next(Model &model) { return model.game.next; }
void test_class::set_score(Model &model, int score) {
  model.game.score = score;
}
int test_class::get_speed(Model &model) { return model.game.speed; }
int test_class::get_pause(Model &model) { return model.game.pause; }
int test_class::get_score(Model &model) { return model.game.score; }
void test_class::set_apple(Model &model) {
  model.game.field[8][5] = s21::apple;
}
void test_class::set_pause(Controller &con, int st) {
  con.model.set_status(st);
}
int test_class::get_pause(Controller &con) { return con.model.get_pause(); }
int **test_class::get_game(Controller &con) { return con.model.game.field; }
}  // namespace s21
