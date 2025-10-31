#include "snake_model.h"

namespace s21 {
Model::Model() {                               // GCOVR_EXCL_LINE
  game.field = new int* [FIELD_HEIGHT] { 0 };  // GCOVR_EXCL_LINE
  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    game.field[i] = new int[FIELD_WIDTH]{0};  // GCOVR_EXCL_LINE
  }
  // start snake position
  game.next = nullptr;
  snake_elements.push_back({9, 5});   // GCOVR_EXCL_LINE
  snake_elements.push_back({10, 5});  // GCOVR_EXCL_LINE
  snake_elements.push_back({11, 5});  // GCOVR_EXCL_LINE
  snake_elements.push_back({12, 5});  // GCOVR_EXCL_LINE
  for (std::pair<int, int> part : snake_elements) {
    draw_snake_part(part);
  }
  // apple start position
  make_apple();
  game.high_score = read_from_file();  // GCOVR_EXCL_LINE
  now_time = get_time_nanos();
}
void Model::fin_game() {
  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    delete[] game.field[i];  // GCOVR_EXCL_LINE
  }
  delete[] game.field;  // GCOVR_EXCL_LINE
  game.field = nullptr;
  if (game.score >= game.high_score) {
    std::ofstream ofs("snake_high_score.txt",
                      std::ios::out);             // GCOVR_EXCL_LINE
    if (!ofs.is_open()) {                         // GCOVR_EXCL_LINE
      throw std::logic_error("Can't open file");  // GCOVR_EXCL_LINE
    }
    ofs << game.score;  // GCOVR_EXCL_LINE
    ofs.close();        // GCOVR_EXCL_LINE
  }
}

long Model::get_time_nanos() const {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}

void Model::turn_left() {
  --dir_num;
  if (dir_num == -1) dir_num = 3;
}

void Model::turn_right() {
  ++dir_num;
  if (dir_num == 4) dir_num = 0;
}

void Model::set_status(int st) {
  if (game.pause == game_pause && st == Pause) game.pause = shift;
  game.pause = st;
}

int Model::read_from_file() {
  std::ifstream ifs("snake_high_score.txt");               // GCOVR_EXCL_LINE
  if (!ifs.is_open()) {                                    // GCOVR_EXCL_LINE
    std::ofstream new_file("../../snake_high_score.txt");  // GCOVR_EXCL_LINE
    new_file << "0";                                       // GCOVR_EXCL_LINE
    new_file.close();                                      // GCOVR_EXCL_LINE
    return 0;
  }
  std::string score{0};        // GCOVR_EXCL_LINE
  std::getline(ifs, score);    // GCOVR_EXCL_LINE
  return atoi(score.c_str());  // GCOVR_EXCL_LINE
}

void Model::make_apple() {
  std::srand(time(0));
  bool correct_pos = false;
  int x{0}, y{0};
  while (!correct_pos) {
    x = 1 + rand() % (FIELD_HEIGHT - 2);
    y = 1 + rand() % (FIELD_WIDTH - 2);
    correct_pos = !game.field[x][y];
  }
  game.field[x][y] = apple;
}

void Model::snake_turn() {
  std::pair<int, int> turn_shift = snake_dir[dir_num];
  std::pair<int, int> head = snake_elements.front();
  std::pair<int, int> new_head;
  new_head.first = head.first + turn_shift.first;
  new_head.second = head.second + turn_shift.second;
  if (check_crash(new_head)) {
    check_apple(new_head);
    snake_elements.push_front(new_head);
    draw_snake_part(new_head);
  }
}

bool Model::check_crash(std::pair<int, int> cell) {
  bool flag = true;
  if (cell.first <= ZERO_X || cell.first >= FIELD_HEIGHT - 1 ||
      cell.second < ZERO_Y || cell.second >= FIELD_WIDTH - 1 ||
      game.field[cell.first][cell.second] == snake) {
    game.pause = game_over;
    flag = false;
  }
  if (game.score == 200) {
    game.pause = game_over;
    flag = false;
  }
  return flag;
}

void Model::check_apple(std::pair<int, int> cell) {
  if (game.field[cell.first][cell.second] == apple) {
    ++game.score;
    make_apple();
    if (game.level < 10) update_lvl();
  } else {
    erase_snake_part();
  }
}

void Model::update_lvl() {
  game.level = (game.score / 5 + 1) < 10 ? (game.score / 5 + 1) : 10;
  if (game.high_score < game.score) game.high_score = game.score;
  delay = (int)start_speed - game.level * 0.07 * (int)start_speed;
}

void Model::erase_snake_part() {
  std::pair<int, int> coords = snake_elements.back();
  game.field[coords.first][coords.second] = empty;
  snake_elements.pop_back();
}
}  // namespace s21
