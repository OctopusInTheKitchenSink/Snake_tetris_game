#include "frontend.h"

extern "C" bool game_loop() {
  init_ncurses();
  bool game_flag = TRUE;
  UserAction_t action = Start;
  GameInfo_t game = {.field = nullptr,
                     .next = nullptr,
                     .score = 0,
                     .high_score = 0,
                     .level = 0,
                     .speed = 0,
                     .pause = ready_to_start};  // локальная переменная, не
                                                // имеющая доступа к статической
  WINDOW *field =
      newwin(FIELD_HEIGHT, FIELD_WIDTH * 2, START_POSITION, START_POSITION);
  WINDOW *info =
      newwin(FIELD_HEIGHT, INFO_WIDTH, START_POSITION, INFO_START_POSITION);
  // тут дать выбрать игру 1 или 2
  // если это змейка, то создать его контроллер
  int dig_game = choose_the_game(field);
  s21::Controller *controller = nullptr;
  if (dig_game == '2') {
    game.field = new int *[FIELD_HEIGHT] { 0 };
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
      game.field[i] = new int[FIELD_WIDTH]{0};
    }
    controller = new s21::Controller;
  }
  if (dig_game == 'q') game_flag = FALSE;
  while (game_flag) {
    print_game(game, field, info);
    if (game.pause == terminate || game.pause == game_over) {
      game_flag = FALSE;
      break;
    }
    process_signal(&action);
    if (game_flag) {
      if (dig_game == '2') {
        controller->userInput(static_cast<s21::UserAction_t>(action), 0);
        converter(controller->updateCurrentState(), game);
      } else if (dig_game == '1') {
        userInput(action, 0);
        game = updateCurrentState();
      }
    }
  }
  if (game.pause == game_over) {
    game_flag = TRUE;
  }
  if (dig_game == '2') {
    delete controller;
    if (game.field) {
      for (int i = 0; i < FIELD_HEIGHT; ++i) {
        delete[] game.field[i];
        game.field[i] = nullptr;
      }
      delete[] game.field;
      game.field = nullptr;
    }
  }
  return game_flag;
};

void converter(s21::GameInfo_t s21_info, GameInfo_t &c_info) {
  if (s21_info.pause != terminate && s21_info.pause != game_over) {
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
      for (int j = 0; j < FIELD_WIDTH; ++j) {
        c_info.field[i][j] = s21_info.field[i][j];
      }
    }
  }
  c_info.high_score = s21_info.high_score;
  c_info.level = s21_info.level;
  c_info.next = nullptr;
  c_info.pause = s21_info.pause;
  c_info.score = s21_info.score;
  c_info.speed = s21_info.speed;
};

extern "C" int choose_the_game(WINDOW *field) {
  werase(field);
  box(field, 0, 0);
  mvwprintw(field, 9, 4, "Press 1 - Tetris");
  mvwprintw(field, 11, 4, "press 2 - snake");
  refresh();
  wrefresh(field);
  char dig_game{0};
  while (dig_game != '1' && dig_game != '2' && dig_game != 'q') {
    dig_game = getch();
  }
  return dig_game;
};

// преобразуем сигнал от пользователя в действие
void process_signal(UserAction_t *action) {
  int signal = getch();
  switch (signal) {
    case KEY_DOWN:
      *action = Down;
      break;
    case KEY_LEFT:
      *action = Left;
      break;
    case KEY_RIGHT:
      *action = Right;
      break;
    case ' ':
      *action = Action;
      break;
    case '\n':
      *action = Start;
      break;
    case 'q':
      *action = Terminate;
      break;
    case 'p':
      *action = Pause;
      break;
    default:
      *action = Up;  // like a stub for a state where nothing is happening.
      break;
  }
}

extern "C" void print_game(GameInfo_t game, WINDOW *field, WINDOW *info) {
  werase(info);
  werase(field);
  box(field, 0, 0);
  box(info, 0, 0);
  if (game.pause == ready_to_start) {
    print_start_status(field);
  } else if (game.pause == game_pause) {
    print_pause_status(field);
  } else if (game.pause == terminate || game.pause == game_over) {
    print_end_status(field, game);
  } else {
    print_game_field(game, field);
  }
  if (game.pause == ready_to_start) {
    print_start_info(info);
  } else if (game.pause != game_over && game.pause != terminate) {
    print_info(info, game);
  }
  wrefresh(info);
  wrefresh(field);
  if (game.pause == terminate || game.pause == game_over) {
    napms(1000);
    delwin(field);
    delwin(info);
  }
}

extern "C" void print_start_status(WINDOW *field) {
  mvwprintw(field, 9, 4, "Press ENTER to");
  mvwprintw(field, 11, 4, "start the game");
}

extern "C" void print_pause_status(WINDOW *field) {
  mvwprintw(field, 9, 4, "Press ENTER to");
  mvwprintw(field, 11, 2, "continue the game");
}

extern "C" void print_end_status(WINDOW *field, GameInfo_t game) {
  mvwprintw(field, 9, 6, "GAME OVER");
  mvwprintw(field, 11, 4, "Your score is");
  if (game.score == 0) {
    mvwprintw(field, 13, 10, "%d", game.score);
  } else {
    mvwprintw(field, 13, 12 - log10(game.score), "%d", game.score);
  }
  if (game.score >= game.high_score && game.score != 0) {
    mvwprintw(field, 15, 5, "NEW RECORD!");
  }
}

extern "C" void print_start_info(WINDOW *info) {
  mvwprintw(info, 2, 5, "WELCOME");
  mvwprintw(info, 4, 8, "TO");
  mvwprintw(info, 6, 4, "BRICK GAME");
  mvwprintw(info, 8, 2, "<- move left");
  mvwprintw(info, 10, 2, "-> move right");
  mvwprintw(info, 12, 2, "key down - fall");
  mvwprintw(info, 14, 2, "p - pause");
  mvwprintw(info, 16, 2, "space - ");
  mvwprintw(info, 18, 2, "rotation figure");
  mvwprintw(info, 20, 2, "q - quit");
  mvwprintw(info, 22, 2, "enter - start");
}

extern "C" void print_game_field(GameInfo_t game, WINDOW *field) {
  for (int i = 1; i < FIELD_HEIGHT; ++i) {
    for (int j = 0; j < FIELD_WIDTH; ++j) {
      if (game.field[i][j] != EMPTY_PLACE) {
        if (game.field[i][j] > 0 && game.field[i][j] < 8) {
          wattron(field, COLOR_PAIR(game.field[i][j]));
          mvwprintw(field, i, j * 2 + 1, "[]");
          wattroff(field, COLOR_PAIR(game.field[i][j]));
        } else if (game.next) {
          wattron(field, COLOR_PAIR(game.next[2][2]));
          mvwprintw(field, i, j * 2 + 1, "[]");
          wattroff(field, COLOR_PAIR(game.next[2][2]));
        }
      }
    }
  }
}

extern "C" void print_info(WINDOW *info, GameInfo_t game) {
  mvwprintw(info, 1, 2, "Next figure");
  if (game.pause != ready_to_start && game.next) {
    if (game.next) {
      for (int i = 0; i < FIGURE_PART; ++i) {
        int x = game.next[i][0] + 5;
        int y = game.next[i][1];
        wattron(info, COLOR_PAIR(game.next[3][2]));
        mvwprintw(info, x - 2, y * 2 - 2, "[]");
        wattroff(info, COLOR_PAIR(game.next[3][2]));
      }
    }
  }
  mvwprintw(info, 6, 2, "High score:");
  mvwprintw(info, 8, 2, "%d", game.high_score);
  mvwprintw(info, 10, 2, "Score: %d", game.score);
  mvwprintw(info, 12, 2, "Level: %d", game.level);
  mvwprintw(info, 14, 2, "p - pause");
  mvwprintw(info, 16, 2, "space - ");
  mvwprintw(info, 18, 2, "rotation figure");
  mvwprintw(info, 20, 2, "q - quit");
  mvwprintw(info, 22, 2, "enter - start");
}

extern "C" void init_ncurses(void) {
  initscr();              // начало работы с ncurses
  noecho();               // не выводим введенное на экран
  curs_set(0);            // скрывает курсор
  keypad(stdscr, TRUE);   // ввод клавиш вверх, вниз и тд
  setlocale(LC_ALL, "");  // использование локализованных настроек
  nodelay(stdscr, TRUE);  //
  start_color();          // инициализация цветовой системы
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6, COLOR_CYAN, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
}
