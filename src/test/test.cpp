#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../brick_game/snake/snake_controller.h"
#include "test_class.h"

TEST(Snake, constr1) {
  s21::test_class mod;
  s21::Model m;
  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    for (int j = 0; j < FIELD_WIDTH; ++j) {
      if (j == 5 && (i == 9 || i == 10 || i == 11 || i == 12)) {
        EXPECT_EQ(mod.get_field(m)[i][j], s21::snake);
      } else {
        if (mod.get_field(m)[i][j] == s21::apple) {
          EXPECT_EQ(mod.get_field(m)[i][j], s21::apple);
        } else
          EXPECT_EQ(mod.get_field(m)[i][j], 0);
      }
    }
  }
  EXPECT_EQ(mod.get_next(m), nullptr);
  auto snake_parts = mod.test_snake_part(m);
  auto i = snake_parts.begin();
  EXPECT_EQ(i->first, 9);
  EXPECT_EQ(i->second, 5);
  ++i;
  EXPECT_EQ(i->first, 10);
  EXPECT_EQ(i->second, 5);
  ++i;
  EXPECT_EQ(i->first, 11);
  EXPECT_EQ(i->second, 5);
  ++i;
  EXPECT_EQ(i->first, 12);
  EXPECT_EQ(i->second, 5);
  EXPECT_EQ(mod.get_score(m), 0);
  EXPECT_EQ(mod.get_speed(m), 0);
  EXPECT_EQ(mod.get_pause(m), ready_to_start);
}

TEST(Snake, finish_game) {
  s21::test_class mod;
  s21::Model m;
  m.fin_game();
  EXPECT_EQ(mod.get_field(m), nullptr);
  EXPECT_EQ(mod.test_get_lvl(m), 0);
  EXPECT_EQ(mod.get_speed(m), 0);
  EXPECT_EQ(mod.get_pause(m), 0);
}

TEST(Snake, turnLeft) {
  s21::Model m;
  s21::test_class mod;
  m.turn_left();
  m.snake_turn();
  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    for (int j = 0; j < FIELD_WIDTH; ++j) {
      if (j == 4 && i == 9 || j == 5 && (i == 9 || i == 10 || i == 11)) {
        EXPECT_EQ(mod.get_field(m)[i][j], s21::snake);
      } else {
        if (mod.get_field(m)[i][j] == s21::apple) {
          EXPECT_EQ(mod.get_field(m)[i][j], s21::apple);
        } else
          EXPECT_EQ(mod.get_field(m)[i][j], 0);
      }
    }
  }
}

TEST(Snake, turnRight1) {
  s21::Model m;
  s21::test_class mod;
  m.turn_right();
  m.snake_turn();
  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    for (int j = 0; j < FIELD_WIDTH; ++j) {
      if (j == 6 && i == 9 || j == 5 && (i == 9 || i == 10 || i == 11)) {
        EXPECT_EQ(mod.get_field(m)[i][j], s21::snake);
      } else {
        if (mod.get_field(m)[i][j] == s21::apple) {
          EXPECT_EQ(mod.get_field(m)[i][j], s21::apple);
        }
      }
    }
  }
}

TEST(Snake, turnRight2) {
  s21::test_class mod;
  s21::Model m;
  for (int i = 0; i < 9; ++i) m.snake_turn();
  EXPECT_EQ(mod.get_pause(m), game_over);
}

TEST(snake, setStatus) {
  s21::test_class mod;
  s21::Model m;
  m.set_status(shift);
  EXPECT_EQ(mod.get_pause(m), shift);
}

TEST(Snake, readFile1) {
  s21::test_class mod;
  s21::Model m;
  std::ifstream ifs;
  ifs.open("snake_high_score.txt");
  std::string score{0};
  if (ifs.is_open()) {
    std::getline(ifs, score);
    ifs.close();
  }
  EXPECT_EQ(mod.test_read_from_file(m), atoi(score.c_str()));
}

TEST(Snake, readFile2) {
  s21::test_class mod;
  s21::Model m;
  if (std::filesystem::exists("snake_high_score.txt"))
    std::filesystem::remove("snake_high_score.txt");
  EXPECT_EQ(mod.test_read_from_file(m), 0);
}

TEST(Snake, apple) {
  s21::test_class mod;
  s21::Model m;
  bool flag = true;
  for (int i = 0; i < FIELD_HEIGHT && flag; ++i) {
    for (int j = 0; j < FIELD_WIDTH; ++j) {
      if (mod.get_field(m)[i][j] == s21::apple) {
        EXPECT_EQ(mod.get_field(m)[i][j], s21::apple);
        flag = false;
        break;
      }
    }
  }
}

TEST(Snake, checkCrash1) {
  s21::test_class mod;
  s21::Model m;
  EXPECT_EQ(mod.test_check_crash({0, 10}, m), false);
  EXPECT_EQ(m.check_flag(), false);
}

TEST(Snake, checkCrash2) {
  s21::test_class mod;
  s21::Model m;
  m.turn_left();
  m.turn_left();
  EXPECT_EQ(mod.test_check_crash({9, 5}, m), false);
  EXPECT_EQ(m.check_flag(), false);
}

TEST(Snake, checkCrash3) {
  s21::test_class mod;
  s21::Model m;
  EXPECT_EQ(mod.test_check_crash({8, 5}, m), true);
}

TEST(snake, checkCrash4) {
  s21::test_class mod;
  s21::Model m;
  m.turn_left();
  for (int i = 0; i < 5; ++i) {
    m.snake_turn();
  }
  EXPECT_EQ(mod.test_check_crash({9, 0}, m), false);
  EXPECT_EQ(m.check_flag(), false);
}

TEST(snake, newRecord) {
  s21::test_class mod;
  s21::Model m;
  mod.set_score(m, 100);
  EXPECT_EQ(mod.get_score(m), 100);
  mod.test_update_lvl(m);
  EXPECT_EQ(mod.test_get_lvl(m), 10);
  m.fin_game();
  EXPECT_EQ(mod.get_field(m), nullptr);
  EXPECT_EQ(mod.test_get_lvl(m), 10);
  EXPECT_EQ(mod.get_speed(m), 0);
  EXPECT_EQ(mod.get_pause(m), 0);
}

TEST(Snake, updateLvl) {
  s21::test_class mod;
  s21::Model m;
  mod.set_score(m, 10);
  mod.test_update_lvl(m);
  mod.test_update_lvl(m);
  EXPECT_EQ(mod.test_get_lvl(m), 3);
}

TEST(Snake, erase) {
  s21::test_class mod;
  s21::Model m;
  mod.test_erase_snake_part(m);
  EXPECT_EQ(mod.get_field(m)[9][5], s21::snake);
  EXPECT_EQ(mod.get_field(m)[10][5], s21::snake);
  EXPECT_EQ(mod.get_field(m)[11][5], s21::snake);
  EXPECT_EQ(mod.get_field(m)[12][5], 0);
  EXPECT_EQ(mod.get_field(m)[8][5], 0);
}

TEST(snake, set_apple) {
  s21::test_class mod;
  s21::Model m;
  mod.set_apple(m);
  m.snake_turn();
  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    for (int j = 0; j < FIELD_WIDTH; ++j) {
      if (j == 5 && (i == 8 || i == 9 || i == 10 || i == 11 || i == 12)) {
        EXPECT_EQ(mod.get_field(m)[i][j], s21::snake);
      } else {
        if (mod.get_field(m)[i][j] == s21::apple) {
          EXPECT_EQ(mod.get_field(m)[i][j], s21::apple);
        } else
          EXPECT_EQ(mod.get_field(m)[i][j], 0);
      }
    }
  }
  EXPECT_EQ(mod.get_score(m), 1);
}

TEST(snake, UserInput1) {
  s21::Controller c;
  s21::test_class test;
  c.userInput(s21::Start, false);
  EXPECT_EQ(test.get_pause(c), shift);
  c.userInput(s21::Pause, false);
  EXPECT_EQ(test.get_pause(c), game_pause);
  c.userInput(s21::Left, false);
  EXPECT_EQ(test.get_pause(c), game_pause);
  c.userInput(s21::Start, false);
  EXPECT_EQ(test.get_pause(c), shift);
  c.userInput(s21::Left, false);
  EXPECT_EQ(test.get_pause(c), move_left);
  c.userInput(s21::Start, false);
  EXPECT_EQ(test.get_pause(c), move_left);
  c.userInput(s21::Right, false);
  EXPECT_EQ(test.get_pause(c), move_right);
  c.userInput(s21::Action, false);
  EXPECT_EQ(test.get_pause(c), rotation);
  c.userInput(s21::Pause, false);
  c.userInput(s21::Terminate, false);
  EXPECT_EQ(test.get_pause(c), game_over);
}

TEST(snake, UserInput2) {
  s21::Controller c;
  s21::test_class test;
  c.userInput(s21::Terminate, false);
  EXPECT_EQ(test.get_pause(c), game_over);
}

TEST(snake, controller1) {
  s21::Controller c;
  s21::test_class test;
  c.updateCurrentState();
  EXPECT_EQ(test.get_pause(c), ready_to_start);
  c.updateCurrentState();
  EXPECT_EQ(test.get_pause(c), ready_to_start);
  c.userInput(s21::Start, false);
  c.updateCurrentState();
  sleep(0.7);
  c.updateCurrentState();
  EXPECT_EQ(test.get_pause(c), shift);
  EXPECT_EQ(test.get_game(c)[12][5], s21::snake);
  EXPECT_EQ(test.get_game(c)[9][5], s21::snake);
  EXPECT_EQ(test.get_game(c)[10][5], s21::snake);
  EXPECT_EQ(test.get_game(c)[11][5], s21::snake);
  c.userInput(s21::Left, false);
  sleep(1);
  EXPECT_EQ(test.get_pause(c), move_left);
  c.updateCurrentState();
  EXPECT_EQ(test.get_pause(c), shift);
  EXPECT_EQ(test.get_game(c)[9][4], s21::snake);
  EXPECT_EQ(test.get_game(c)[9][5], s21::snake);
  EXPECT_EQ(test.get_game(c)[10][5], s21::snake);
  EXPECT_EQ(test.get_game(c)[11][5], s21::snake);
  c.userInput(s21::Right, false);
  c.updateCurrentState();
  sleep(1);
  c.updateCurrentState();
  EXPECT_EQ(test.get_game(c)[8][4], s21::snake);
  EXPECT_EQ(test.get_game(c)[9][4], s21::snake);
  EXPECT_EQ(test.get_game(c)[9][5], s21::snake);
  EXPECT_EQ(test.get_game(c)[10][5], s21::snake);
  c.userInput(s21::Action, false);
  sleep(1);
  c.updateCurrentState();
  EXPECT_EQ(test.get_game(c)[6][4], s21::snake);
  EXPECT_EQ(test.get_game(c)[7][4], s21::snake);
  EXPECT_EQ(test.get_game(c)[8][4], s21::snake);
  EXPECT_EQ(test.get_game(c)[9][4], s21::snake);
  sleep(1);
  c.updateCurrentState();
  EXPECT_EQ(test.get_game(c)[5][4], s21::snake);
  EXPECT_EQ(test.get_game(c)[6][4], s21::snake);
  EXPECT_EQ(test.get_game(c)[7][4], s21::snake);
  EXPECT_EQ(test.get_game(c)[8][4], s21::snake);
  for (int i = 0; i < 3; ++i) {
    c.userInput(s21::Action, false);
    sleep(1);
    c.updateCurrentState();
  }
}

TEST(snake, controller2) {
  s21::Controller c;
  s21::test_class test;
  c.userInput(s21::Start, false);
  c.updateCurrentState();
  sleep(0.7);
  c.userInput(s21::Terminate, false);
  sleep(1);
  c.updateCurrentState();
}
