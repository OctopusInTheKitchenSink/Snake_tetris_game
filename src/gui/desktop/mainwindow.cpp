#include "mainwindow.h"
namespace s21 {
void MainWindow::TetrisClicked() {
  if (tetris) {
    delete tetris;
    tetris = nullptr;
  }
  tetris = new TetrisGame(this);
  connect(tetris, &TetrisGame::ExitSignal, this, &MainWindow::show);
  hide();
  tetris->get_window()->show();
  emit TetrisSignal();
}
void MainWindow::SnakeClicked() {
  if (snake) {
    delete snake;
    snake = nullptr;
  }
  snake = new SnakeGame(this);
  connect(snake, &SnakeGame::ExitSignal, this, &MainWindow::show);
  hide();
  snake->get_window()->show();
  emit SnakeSignal();
}
void MainWindow::ExitClicked() {
  emit ExitSignal();
  close();
}
MainWindow::MainWindow() {
  setWindowTitle("BrickGame v2.0");
  addMenu();
  addConnection();
}
MainWindow::~MainWindow() {
  delete text;
  delete snake;
  delete tetris;
}
void MainWindow::addMenu() {
  MainWidget = new QWidget(this);
  setCentralWidget(MainWidget);
  QVBoxLayout *mainLayout = new QVBoxLayout;
  QHBoxLayout *gameLayout = new QHBoxLayout;

  text = new MyLabel(MainWidget);
  text->setText(text->get_menu_instruction());
  mainLayout->addWidget(text);

  SnakeButton = new QPushButton("Snake", MainWidget);
  // color, disigin
  TetrisButton = new QPushButton("Tetris", MainWidget);
  ExitButton = new QPushButton("Exit", MainWidget);

  gameLayout->addWidget(TetrisButton);
  gameLayout->addWidget(SnakeButton);

  mainLayout->addLayout(gameLayout);
  mainLayout->addWidget(ExitButton);

  MainWidget->setLayout(mainLayout);
  show();
}
void MainWindow::addConnection() {
  connect(SnakeButton, &QPushButton::clicked, this, &MainWindow::SnakeClicked);
  connect(TetrisButton, &QPushButton::clicked, this,
          &MainWindow::TetrisClicked);
  connect(ExitButton, &QPushButton::clicked, this, &MainWindow::ExitClicked);
}
}  // namespace s21
