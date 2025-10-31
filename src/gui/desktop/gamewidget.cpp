#include "gamewidget.h"

namespace s21 {
GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
  setFixedSize(170, 370);
  DrawGame = new GameInfo_t;
  DrawGame->field = new int *[FIELD_HEIGHT] { 0 };
  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    DrawGame->field[i] = new int[FIELD_WIDTH]{0};
  }
}

void GameWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.drawRect(0, 15, 160, 322);
  if (DrawGame->pause == terminate || DrawGame->pause == game_over) {
    QRect finish_info(20, 166, 160, 30);
    if (DrawGame->score == 200) {
      QRect winner(20, 100, 160, 30);
      painter.drawText(winner, "You are winner!");
    }
    QString score = QString("Your score is %1").arg(DrawGame->score);
    if (DrawGame->score >= DrawGame->high_score) {
      QRect new_rec(20, 116, 160, 50);
      QString new_record = QString("You made a new record!");
      painter.drawText(new_rec, new_record);
    }
    painter.drawText(finish_info, score);
    return;
  }
  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    for (int j = 0; j < FIELD_WIDTH; ++j) {
      if (DrawGame->pause != ready_to_start && DrawGame->pause != game_pause) {
        // std::cout << DrawGame->field[i][j] << std::endl;
        QRect cell(j * 16, i * 16, 16, 16);
        switch (DrawGame->field[i][j]) {
          case 9:
          case 1:
            painter.fillRect(cell, Qt::red);
            painter.drawRect(cell);
            break;
          case 10:
          case 2:
            painter.fillRect(cell, Qt::green);
            painter.drawRect(cell);
            break;
          case 11:
          case 3:
            painter.fillRect(cell, Qt::yellow);
            painter.drawRect(cell);
            break;
          case 12:
          case 4:
            painter.fillRect(cell, Qt::blue);
            painter.drawRect(cell);
            break;
          case 13:
          case 5:
            painter.fillRect(cell, Qt::magenta);
            painter.drawRect(cell);
            break;
          case 14:
          case 6:
            painter.fillRect(cell, Qt::cyan);
            painter.drawRect(cell);
            break;
          case 15:
          case 7:
            painter.fillRect(cell, Qt::black);
            painter.drawRect(cell);
            break;
          default:
            break;
        }
      }
    }
  }
}
void GameWidget::updateGame(GameInfo_t *game) {
  if (game->field) {
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
      for (int j = 0; j < FIELD_WIDTH; ++j) {
        DrawGame->field[i][j] = game->field[i][j];
      }
    }
  }
  DrawGame->level = game->level;
  DrawGame->next = nullptr;
  DrawGame->pause = game->pause;
  DrawGame->score = game->score;
  DrawGame->speed = game->speed;
  DrawGame->high_score = game->high_score;

  update();
}

void GameWidget::clear() {
  if (DrawGame) {
    if (DrawGame->field) {
      for (int i = 0; i < FIELD_HEIGHT; ++i) {
        delete[] DrawGame->field[i];
        DrawGame->field[i] = nullptr;
      }
      delete[] DrawGame->field;
      DrawGame->field = nullptr;
    }
    delete DrawGame;
    DrawGame = nullptr;
  }
}
}  // namespace s21
