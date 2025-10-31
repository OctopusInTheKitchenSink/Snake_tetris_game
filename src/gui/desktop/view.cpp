#include "gamewidget.h"
#include "gamewindow.h"
#include "mainwindow.h"
#include "statuswidget.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  s21::MainWindow new_win;
  return app.exec();
}
