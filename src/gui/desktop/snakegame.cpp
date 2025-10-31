#include "snakegame.h"

namespace s21 {

void SnakeGame::BoostClicked() { controller->userInput(Action, false); }
void SnakeGame::LeftClicked() { controller->userInput(Left, false); }
void SnakeGame::RightClicked() { controller->userInput(Right, false); }
void SnakeGame::PauseClicked() { controller->userInput(Pause, false); }
void SnakeGame::ExitClicked() {
  controller->userInput(Terminate, false);
  emit ExitSignal();
  if (gameTimer && gameTimer->isActive()) {
    gameTimer->stop();
  }
  gameWindow->close();
}
void SnakeGame::StartClicked() { controller->userInput(Start, false); }

void SnakeGame::DropClicked() {}

SnakeGame::SnakeGame(QObject *parent) : QObject(parent) {
  controller = new Controller;
  gameWindow = new GameWindow('s');
  game.field = new int *[FIELD_HEIGHT];
  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    game.field[i] = new int[FIELD_WIDTH]{0};
  }
  addConnections();
  gameLoop();
}

void SnakeGame::clear() {
  delete controller;
  controller = nullptr;
  delete gameTimer;
  gameTimer = nullptr;
  delete gameWindow;
  gameWindow = nullptr;
}

void SnakeGame::GameUpdate() {
  game = controller->updateCurrentState();
  game.next = nullptr;
  gameWindow->updateField(&game);
  if (game.pause == terminate || game.pause == game_over) {
    gameTimer->stop();
    QTimer::singleShot(3000, this, &SnakeGame::ExitClicked);
  }
}

void SnakeGame::gameLoop() {
  gameTimer = new QTimer(this);
  connect(gameTimer, &QTimer::timeout, this, &SnakeGame::GameUpdate);
  gameTimer->start(33);
}

void SnakeGame::addConnections() {
  connect(gameWindow, &GameWindow::BoostSignal, this, &SnakeGame::BoostClicked);
  connect(gameWindow, &GameWindow::PauseSignal, this, &SnakeGame::PauseClicked);
  connect(gameWindow, &GameWindow::ExitSignal, this, &SnakeGame::ExitClicked);
  connect(gameWindow, &GameWindow::LeftSignal, this, &SnakeGame::LeftClicked);
  connect(gameWindow, &GameWindow::RightSignal, this, &SnakeGame::RightClicked);
  connect(gameWindow, &GameWindow::StartSignal, this, &SnakeGame::StartClicked);
}
}  // namespace s21
