#include "tetrisgame.h"

namespace s21 {

void TetrisGame::LeftClicked() {
  userInput(static_cast<::UserAction_t>(Left), false);
}

void TetrisGame::RightClicked() {
  userInput(static_cast<::UserAction_t>(Right), false);
}

void TetrisGame::StartClicked() {
  if (game.pause == game_pause) {
    userInput(static_cast<::UserAction_t>(Start), false);
  } else {
    gameLoop();
    userInput(static_cast<::UserAction_t>(Start), false);
  }
}

void TetrisGame::PauseClicked() {
  userInput(static_cast<::UserAction_t>(Pause), false);
}

void TetrisGame::DropClicked() {
  userInput(static_cast<::UserAction_t>(Down), false);
}

void TetrisGame::ExitClicked() {
  userInput(static_cast<::UserAction_t>(Terminate), false);
  emit ExitSignal();
  if (gameTimer && gameTimer->isActive()) {
    gameTimer->stop();
  }
  game.pause = ready_to_start;
  gameWindow->close();
}

void TetrisGame::BoostClicked() {
  userInput(static_cast<::UserAction_t>(Action), false);
}

TetrisGame::TetrisGame(QObject *parent) {
  gameWindow = new GameWindow('t');
  game.field = new int *[FIELD_HEIGHT];
  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    game.field[i] = new int[FIELD_WIDTH]{0};
  }
  game.next = new int *[FIGURE_PART];
  for (int i = 0; i < FIGURE_PART; ++i) {
    game.next[i] = new int[3]{0};
  }
  game.score = 0;
  game.level = 1;
  game.pause = ready_to_start;
  game.speed = START_SPEED;
  addConnection();
}

void TetrisGame::addConnection() {
  connect(gameWindow, &GameWindow::BoostSignal, this,
          &TetrisGame::BoostClicked);
  connect(gameWindow, &GameWindow::DropSignal, this, &TetrisGame::DropClicked);
  connect(gameWindow, &GameWindow::ExitSignal, this, &TetrisGame::ExitClicked);
  connect(gameWindow, &GameWindow::LeftSignal, this, &TetrisGame::LeftClicked);
  connect(gameWindow, &GameWindow::PauseSignal, this,
          &TetrisGame::PauseClicked);
  connect(gameWindow, &GameWindow::RightSignal, this,
          &TetrisGame::RightClicked);
  connect(gameWindow, &GameWindow::StartSignal, this,
          &TetrisGame::StartClicked);
}

void TetrisGame::gameLoop() {
  gameTimer = new QTimer(this);
  connect(gameTimer, &QTimer::timeout, this, &TetrisGame::gameUpdate);
  gameTimer->start(33);
}

void TetrisGame::gameUpdate() {
  ::GameInfo_t tmp = updateCurrentState();
  if (tmp.pause == terminate || tmp.pause == game_over) {
    game.pause = tmp.pause;
    game.high_score = tmp.high_score;
    gameTimer->stop();
    QTimer::singleShot(3000, this, &TetrisGame::ExitClicked);
    gameWindow->updateField(&game);
    return;
  }
  converter(tmp);
  gameWindow->updateField(&game);
}

void TetrisGame::converter(::GameInfo_t s21_info) {
  if (s21_info.pause != terminate && s21_info.pause != game_over &&
      s21_info.field) {
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
      for (int j = 0; j < FIELD_WIDTH; ++j) {
        game.field[i][j] = s21_info.field[i][j];
      }
    }
    for (int i = 0; i < FIGURE_PART; ++i) {
      for (int j = 0; j < 3; ++j) {
        game.next[i][j] = s21_info.next[i][j];
      }
    }
  }
  game.high_score = s21_info.high_score;
  game.level = s21_info.level;
  game.pause = s21_info.pause;
  game.score = s21_info.score;
  game.speed = s21_info.speed;
}
}  // namespace s21
