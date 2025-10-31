#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "view.h"

namespace s21 {
class GameWidget : public QWidget {
  Q_OBJECT
  GameInfo_t *DrawGame;

 public:
  /**
   * @brief Constructs a GameWidget with the specified parent
   *
   * Initializes the game widget with a fixed size and allocates memory
   * for the drawing buffer used to render the game field.
   * @note The constructor:
   *       - Sets fixed widget dimensions to 170x370 pixels
   *       - Allocates a GameInfo_t structure for drawing buffer
   *       - Initializes the 2D field array with zeros
   */
  GameWidget(QWidget *parent = nullptr);
  /**
   * @brief Handles paint events and renders the game visualization
   *
   * This function is called automatically by Qt when the widget needs
   * repainting. It renders the game field, including:
   * - Game border and layout
   * - Game over/termination screens with score display
   * - Colored cells representing game pieces based on their values
   *
   * @note The rendering logic:
   *       - Draws a main game area rectangle
   *       - For terminal states (game_over/terminate): shows score and records
   *       - For active states: renders colored cells based on field values
   *       - Uses a color mapping system for different piece types (1-15)
   */
  void paintEvent(QPaintEvent *);

  /**
   * @brief Cleans up allocated resources and resets the widget state
   *
   * Safely deallocates all dynamically allocated memory used by the
   * drawing buffer, including the 2D field array and GameInfo_t structure.
   *
   * @note Memory cleanup process:
   *       - Deletes each row of the field array
   *       - Deletes the field pointer array
   *       - Deletes the main GameInfo_t structure
   *       - Sets all pointers to nullptr to prevent dangling references
   */
  void clear();
  /**
   * @brief Updates the widget with new game state information
   *
   * Copies the current game state from the provided GameInfo_t structure
   * into the internal drawing buffer and triggers a widget repaint.
   *
   * @note This function:
   *       - Deep copies the field data if the source field exists
   *       - Copies all other game state members (score, level, etc.)
   *       - Calls update() to schedule a repaint with the new data
   */
  void updateGame(GameInfo_t *game);
  ~GameWidget() { clear(); }
};
}  // namespace s21

#endif  // GAMEWIDGET_H
