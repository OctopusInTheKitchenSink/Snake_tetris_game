#ifndef TETRISGAME_H
#define TETRISGAME_H

#include "gamewindow.h"
#include "view.h"

namespace s21 {
class TetrisGame : public QObject {
  Q_OBJECT
  GameWindow *gameWindow{nullptr};
  QTimer *gameTimer{nullptr};
  GameInfo_t game{0};
 private slots:
  void LeftClicked();
  void RightClicked();
  void BoostClicked();
  void PauseClicked();
  void ExitClicked();
  void StartClicked();
  void DropClicked();
  void gameUpdate();
 signals:
  void ExitSignal();

 public:
  /**
   * @brief Constructs a TetrisGame instance and initializes game state
   *
   * Sets up the complete Tetris game environment including:
   * - Game window with 't' identifier for Tetris
   * - Game field and next piece preview memory allocation
   * - Initial game state values (score, level, speed)
   * - Signal connections for user input
   * @note Initial game state:
   *       - Score: 0
   *       - Level: 1
   *       - Pause state: ready_to_start
   *       - Speed: START_SPEED
   *       - Field: Allocated and zero-initialized
   *       - Next piece: Allocated for preview
   */
  TetrisGame(QObject *parent = nullptr);
  /**
   * @brief Retrieves the game window instance for external access
   *
   * Provides controlled access to the GameWindow instance, allowing external
   * code to manipulate the game window properties and visibility without
   * exposing the internal TetrisGame implementation details.
   *
   * @note This accessor method enables the View component of the MVC pattern
   *       to be accessed while maintaining encapsulation of the game logic
   *       and state management.
   */
  GameWindow *get_window() { return gameWindow; }
  /**
   * @brief Establishes signal-slot connections for Tetris controls
   *
   * Connects all game window signals to their corresponding Tetris game
   * handlers, enabling both keyboard and button-based control of the Tetris
   * game.
   *
   * @note Signal mappings specific to Tetris:
   *       - DropSignal → DropClicked() (accelerated descent)
   *       - BoostSignal → BoostClicked() (piece rotation)
   */
  void addConnection();
  /**
   * @brief Establishes signal-slot connections for Tetris controls
   *
   * Connects all game window signals to their corresponding Tetris game
   * handlers, enabling both keyboard and button-based control of the Tetris
   * game.
   *
   * @note Signal mappings specific to Tetris:
   *       - DropSignal → DropClicked() (accelerated descent)
   *       - BoostSignal → BoostClicked() (piece rotation)
   */
  void gameLoop();
  /**
   * @brief Converts backend game state to frontend representation
   *
   * Copies and converts game state information from the backend C-style
   * structure to the frontend Qt-friendly structure for rendering.
   *
   * @note Conversion process:
   *       - Copies field data for active game states
   *       - Copies next piece preview data
   *       - Copies game metadata (score, level, etc.)
   *       - Skips field copying for terminal states
   */
  void converter(::GameInfo_t s21_info);
  /**
   * @brief Destructor for TetrisGame - performs comprehensive resource cleanup
   *
   * Safely deallocates all dynamically allocated resources associated with
   * the Tetris game instance, including:
   * - Game window and its child widgets
   * - 2D game field array (FIELD_HEIGHT x FIELD_WIDTH)
   * - Next piece preview array (FIGURE_PART x 3)
   *
   * @note The destructor implements a thorough cleanup process:
   *       1. Deletes the main game window and all its child widgets
   *       2. Deletes each row of the game field 2D array
   *       3. Deletes the game field pointer array
   *       4. Deletes each row of the next piece preview array
   *       5. Deletes the next piece pointer array
   *       6. Sets all pointers to nullptr to prevent dangling references
   */
  ~TetrisGame() {
    delete gameWindow;
    gameWindow = nullptr;
    if (game.field) {
      for (int i = 0; i < FIELD_HEIGHT; ++i) {
        delete[] game.field[i];
      }
      delete[] game.field;
    }
    game.field = nullptr;
    if (game.next) {
      for (int i = 0; i < FIGURE_PART; ++i) {
        delete[] game.next[i];
      }
      delete[] game.next;
    }
    game.next = nullptr;
  }
};
}  // namespace s21
#endif  // TETRISGAME_H
