#include "gamewindow.h"

namespace s21 {
void GameWindow::keyPressEvent(QKeyEvent *pe) {
  switch (pe->key()) {
    case Qt::Key_Left:
      LeftClicked();
      break;
    case Qt::Key_Right:
      RightClicked();
      break;
    case Qt::Key_P:
      PauseClicked();
      break;
    case Qt::Key_Q:
      ExitClicked();
      break;
    case Qt::Key_Space:
      BoostClicked();
      break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
      StartClicked();
      break;
    case Qt::Key_Down:
      DropClicked();
      break;
  }
}

void GameWindow::updateField(GameInfo_t *game) {
  gameWidget->updateGame(game);
  managmentWidget->updateGame(game);
}

void GameWindow::addConnections() {
  connect(managmentWidget, &StatusWidget::LeftSignal, this,
          &GameWindow::LeftClicked);
  connect(managmentWidget, &StatusWidget::BoostSignal, this,
          &GameWindow::BoostClicked);
  connect(managmentWidget, &StatusWidget::PauseSignal, this,
          &GameWindow::PauseClicked);
  connect(managmentWidget, &StatusWidget::ExitSignal, this,
          &GameWindow::ExitClicked);
  connect(managmentWidget, &StatusWidget::RightSignal, this,
          &GameWindow::RightClicked);
  connect(managmentWidget, &StatusWidget::StartSignal, this,
          &GameWindow::StartClicked);
  connect(managmentWidget, &StatusWidget::DropSignal, this,
          &GameWindow::DropClicked);
}
}  // namespace s21
