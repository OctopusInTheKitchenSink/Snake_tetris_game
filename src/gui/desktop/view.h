#ifndef VIEW_H
#define VIEW_H

#include <QApplication>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>
#include <QRect>
#include <QSplitter>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <QWindow>
#include <iostream>

#include "../../brick_game/snake/snake_controller.h"
#include "../../brick_game/tetris/common.h"

namespace s21 {

class MyLabel : public QLabel {
  Q_OBJECT
  QString menu_instruction =
      "Brick Game Center<br>"
      "Welcome to classic games!<br><br>"
      "Controls:<br>"
      "• Snake: Arrow keys for movement<br>"
      "Please remember that the snake's head turns (right or left)<br><br>"
      "• Tetris: Arrow keys + Space for rotation<br>"
      "• Q to return to menu<br>"
      "• P to pause the game<br>"
      "<br><br>"
      "Below you can select a game by clicking<br>"
      "the corresponding button<br>"
      "Or press Exit to quit the game<br>";

  QString snake_managment =
      "Button Controls:\n"
      "<- - turn snake head left\n"
      "-> - turn snake head right\n"
      "P - pause game/resume from pause\n"
      "Q - return to game selection menu\n"
      "Drop is not active in this game";

  QString tetris_managment =
      "Button Controls:\n"
      "<- - move piece left\n"
      "-> - move piece right\n"
      "P - pause\n"
      "Q - return to game selection menu\n"
      "Down arrow - hard drop (instant placement)";

 public:
  /**
   * @brief Default constructor for MyLabel widget
   *
   * Initializes a MyLabel instance with optional parent widget for memory
   * management. The constructor uses the default QLabel behavior while
   * preparing the custom text content for game instructions and management.
   *
   * @note The constructor relies on the base QLabel constructor while
   *       the custom text content is managed through the getter methods.
   */
  MyLabel(QWidget *parent = nullptr) {}

  /**
   * @brief Retrieves the main menu instructional text
   *
   * Returns the formatted text containing instructions and information
   * for the main game launcher menu. This typically includes welcome
   * messages, game descriptions, and control overview.
   *
   * @return QString The main menu instructional text
   *
   * @note The text is pre-formatted with line breaks and sections
   *       for optimal display in the main menu layout.
   */
  QString get_menu_instruction() { return menu_instruction; }
  /**
   * @brief Retrieves Snake game-specific management instructions
   *
   * Returns the formatted text containing Snake game controls, rules,
   * and gameplay instructions. This is displayed in the status panel
   * when the Snake game is active.
   *
   * @return QString Snake game management and instruction text
   *
   * @note The content is tailored specifically for Snake gameplay
   *       mechanics and control schemes.
   */
  QString get_snake_managment() { return snake_managment; }

  /**
   * @brief Retrieves Tetris game-specific management instructions
   *
   * Returns the formatted text containing Tetris game controls, rules,
   * and gameplay instructions. This is displayed in the status panel
   * when the Tetris game is active.
   *
   * @return QString Tetris game management and instruction text
   *
   * @note The content is tailored specifically for Tetris gameplay
   *       mechanics and control schemes, including piece manipulation.
   */
  QString get_tetris_managment() { return tetris_managment; }
};

}  // namespace s21

#endif
