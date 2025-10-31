#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "gamewindow.h"
#include "view.h"

namespace s21 {
class SnakeGame : public QObject {
  Q_OBJECT
  Controller *controller{nullptr};
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
  void GameUpdate();
 signals:
  void ExitSignal();

 public:
  /**
   * @brief Constructs a SnakeGame instance and initializes game components
   *
   * Sets up the complete Snake game environment including:
   * - Game controller for logic handling
   * - Game window for UI presentation
   * - Game field memory allocation
   * - Signal connections for user input
   * - Game loop timer for updates
   *
   * @param parent The parent QObject for memory management
   */
  SnakeGame(QObject *parent = nullptr);
  /**
   * @brief Cleans up all allocated resources for the Snake game
   *
   * Safely deallocates all dynamically allocated game components
   * including controller, timer, and game window.
   *
   * @note Cleanup process:
   *       - Deletes controller and sets to nullptr
   *       - Deletes game timer and sets to nullptr
   *       - Deletes game window and sets to nullptr
   */
  void clear();
  /**
   * @brief Retrieves the game window instance for external access
   *
   * Provides access to the GameWindow instance, allowing external code
   * to manipulate the game window (show, hide, modify properties) without
   * exposing the entire SnakeGame implementation.
   *
   * @note This function enables the Model-View-Controller pattern by
   *       providing controlled access to the view component while
   *       maintaining encapsulation of the game logic.
   */
  GameWindow *get_window() { return gameWindow; }
  /**
   * @brief Provides external interface for simulating user input
   *
   * Allows external systems (e.g., automated tests, AI players, replay systems)
   * to programmatically inject user actions into the game without requiring
   * actual user interaction.
   *
   * @note This function is particularly useful for:
   *       - Automated testing of game functionality
   *       - Implementing demo/replay modes
   *       - AI-controlled gameplay
   *       - Keyboard macro systems
   */
  void SetUserInput(UserAction_t act) { controller->userInput(act, 0); }
  /**
   * @brief Initializes and starts the game loop timer
   *
   * Creates a QTimer that triggers game state updates at approximately
   * 30 FPS (33ms intervals). Connects the timer timeout signal to the
   * GameUpdate slot.
   *
   * @note Timer configuration:
   *       - Interval: 33 milliseconds (~30 updates per second)
   *       - Single-shot: false (repeating timer)
   *       - Parent: this (auto-managed cleanup)
   */
  void gameLoop();
  /**
   * @brief Establishes signal-slot connections between UI and game logic
   *
   * Connects signals from the game window to corresponding game action
   * handlers, enabling user input from both keyboard and UI buttons.
   *
   * @note Signal mappings:
   *       - BoostSignal → BoostClicked()
   *       - PauseSignal → PauseClicked()
   *       - ExitSignal → ExitClicked()
   *       - LeftSignal → LeftClicked()
   *       - RightSignal → RightClicked()
   *       - StartSignal → StartClicked()
   */
  void addConnections();
  /**
   * @brief Destructor for SnakeGame - ensures proper resource cleanup
   *
   * Automatically calls the clear() method when the SnakeGame instance
   * is destroyed, ensuring all dynamically allocated resources are
   * properly released and preventing memory leaks.
   *
   * @note The destructor follows RAII (Resource Acquisition Is Initialization)
   *       principles by tying resource cleanup to object lifetime.
   */
  ~SnakeGame() { clear(); }
};
}  // namespace s21

#endif  // SNAKEGAME_H
