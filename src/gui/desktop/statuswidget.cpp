#include "statuswidget.h"

namespace s21 {

StatusWidget::StatusWidget(QWidget *parent) {
  figure = new int *[FIGURE_PART];
  for (int i = 0; i < FIGURE_PART; ++i) {
    figure[i] = new int[3]{0};
  }
  addButtons();
  addConnections();
  managment = new MyLabel(this);
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  QHBoxLayout *firstLayout = new QHBoxLayout;
  firstLayout->addWidget(managment);
  QHBoxLayout *secondLayout = new QHBoxLayout;
  secondLayout->addWidget(TurnLeft);
  secondLayout->addWidget(TurnRight);
  QHBoxLayout *thirdLayout = new QHBoxLayout;
  thirdLayout->addWidget(Boost);
  QHBoxLayout *fourthLayout = new QHBoxLayout;
  fourthLayout->addWidget(Pause);
  fourthLayout->addWidget(ExitButton);
  QHBoxLayout *fithLayout = new QHBoxLayout;
  fithLayout->addWidget(StartButton);
  fithLayout->addWidget(DropButton);
  mainLayout->addLayout(firstLayout);
  mainLayout->addLayout(secondLayout);
  mainLayout->addLayout(thirdLayout);
  mainLayout->addLayout(fourthLayout);
  mainLayout->addLayout(fithLayout);
}

void StatusWidget::updateGame(GameInfo_t *game) {
  if (game) {
    if (game->next) {
      for (int i = 0; i < FIGURE_PART; ++i) {
        for (int j = 0; j < 3; ++j) {
          figure[i][j] = game->next[i][j];
        }
      }
    }
    high_score = game->high_score;
    score = game->score;
    level = game->level;
    pause = game->pause;
  }
  update();
}

void StatusWidget::paintEvent(QPaintEvent *) {
  if (pause == terminate || pause == game_over) return;
  QPainter painter(this);
  if (figure && figure[3][2]) {
    QRect textRect(5, 105, 250, 200);
    painter.drawText(textRect, managment->get_tetris_managment());
  } else {
    QRect textRect(5, 105, 250, 200);
    painter.drawText(textRect, managment->get_snake_managment());
  }
  QRect dataRect(5, 0, 80, 180);
  QString text = QString("Score: %1\nHigh score:%2\nLever: %3")
                     .arg(score)
                     .arg(high_score)
                     .arg(level);
  painter.drawText(dataRect, text);
  if (figure && figure[3][2]) {
    painter.drawText(150, 15, "Next Figure:");
    int color = figure[3][2];
    for (int i = 0; i < FIGURE_PART; ++i) {
      int x = figure[i][0];
      int y = figure[i][1];
      QRect cell(y * 16 + 110, x * 16 + 25, 16, 16);
      switch (color) {
        case 9:
        case 1:
          painter.fillRect(cell, Qt::red);
          break;
        case 10:
        case 2:
          painter.fillRect(cell, Qt::green);
          break;
        case 11:
        case 3:
          painter.fillRect(cell, Qt::yellow);
          break;
        case 12:
        case 4:
          painter.fillRect(cell, Qt::blue);
          break;
        case 13:
        case 5:
          painter.fillRect(cell, Qt::magenta);
          break;
        case 14:
        case 6:
          painter.fillRect(cell, Qt::cyan);
          break;
        case 15:
        case 7:
          painter.fillRect(cell, Qt::black);
          break;
      }
      painter.drawRect(cell);
    }
  }
}

void StatusWidget::clear() {
  for (int i = 0; i < FIGURE_PART; ++i) {
    delete[] figure[i];
  }
  delete[] figure;
  delete managment;
}

void StatusWidget::addConnections() {
  connect(TurnLeft, &QPushButton::clicked, this, &StatusWidget::LeftClicked);
  connect(TurnRight, &QPushButton::clicked, this, &StatusWidget::RightClicked);
  connect(Boost, &QPushButton::clicked, this, &StatusWidget::BoostClicked);
  connect(Pause, &QPushButton::clicked, this, &StatusWidget::PauseClicked);
  connect(ExitButton, &QPushButton::clicked, this, &StatusWidget::ExitClicked);
  connect(StartButton, &QPushButton::clicked, this,
          &StatusWidget::StartClicked);
  connect(DropButton, &QPushButton::clicked, this, &StatusWidget::DropClicked);
}
void StatusWidget::addButtons() {
  TurnLeft = new QPushButton("<-", this);
  TurnRight = new QPushButton("->", this);
  Boost = new QPushButton("boost", this);
  DropButton = new QPushButton("Drop", this);
  Pause = new QPushButton("P", this);
  ExitButton = new QPushButton("Q", this);
  StartButton = new QPushButton("Start", this);
}
}  // namespace s21
