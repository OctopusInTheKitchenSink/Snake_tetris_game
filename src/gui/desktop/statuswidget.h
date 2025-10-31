#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include "view.h"

namespace s21 {
class StatusWidget : public QWidget {
  Q_OBJECT
  int high_score{0}, score{0}, level{0}, pause{0};
  int **figure{nullptr};
  MyLabel *managment{nullptr};
  QPushButton *TurnLeft{nullptr};
  QPushButton *TurnRight{nullptr};
  QPushButton *Boost{nullptr};
  QPushButton *Pause{nullptr};
  QPushButton *ExitButton{nullptr};
  QPushButton *StartButton{nullptr};
  QPushButton *DropButton{nullptr};

 private slots:
  void LeftClicked() { emit LeftSignal(); }
  void RightClicked() { emit RightSignal(); }
  void BoostClicked() { emit BoostSignal(); }
  void PauseClicked() { emit PauseSignal(); }
  void ExitClicked() { emit ExitSignal(); }
  void StartClicked() { emit StartSignal(); }
  void DropClicked() { emit DropSignal(); }

 signals:
  void LeftSignal();
  void RightSignal();
  void BoostSignal();
  void PauseSignal();
  void ExitSignal();
  void StartSignal();
  void DropSignal();

 public:
  /**
   * @brief Constructs a StatusWidget with game controls and status display
   *
   * Initializes the status panel with control buttons, game information
   * display, and next figure preview for Tetris. Sets up the UI layout and
   * connections.
   *
   * @note Initialization process:
   *       - Allocates figure array for next piece preview (Tetris)
   *       - Creates control buttons
   *       - Establishes signal connections
   *       - Sets up multi-layout UI structure
   */
  StatusWidget(QWidget *parent = nullptr);
  /**
   * @brief Updates the status display with current game state information
   *
   * Refreshes the status panel with the latest game data including score,
   * level, high score, and next piece preview for Tetris.
   */
  void updateGame(GameInfo_t *game);
  /**
   * @brief Renders the status panel with game information and controls
   *
   * Paints the status widget with:
   * - Game statistics (score, high score, level)
   * - Game-specific instructions (Snake vs Tetris)
   * - Next piece preview for Tetris games
   * - Control button labels
   *
   * @note Rendering logic:
   *       - Skips rendering for terminal states (game_over/terminate)
   *       - Displays Tetris instructions when next piece data exists
   *       - Displays Snake instructions otherwise
   *       - Shows colored next piece preview for Tetris
   *       - Uses consistent color mapping with GameWidget
   */
  void paintEvent(QPaintEvent *);
  /**
   * @brief Cleans up allocated resources for the status widget
   *
   * Safely deallocates all dynamically allocated members including
   * the figure array for next piece preview and management label.
   *
   * @note Cleanup process:
   *       - Deletes each row of the figure array
   *       - Deletes the figure pointer array
   *       - Deletes the management text label
   */
  void clear();
  /**
   * @brief Creates and initializes all control buttons
   *
   * Instantiates the push buttons for game controls with appropriate
   * labels and parent widget assignment.
   *
   * @note Button labels:
   *       - TurnLeft: "<-" (Left arrow)
   *       - TurnRight: "->" (Right arrow)
   *       - Boost: "boost"
   *       - DropButton: "Drop"
   *       - Pause: "P" (Pause)
   *       - ExitButton: "Q" (Quit)
   *       - StartButton: "Start"
   */
  void addButtons();
  /** @brief Establishes signal-slot connections for control buttons
   *
   * Connects all control buttons to their respective signal emitters,
   * enabling user interaction with the game through the status panel.
   *
   * @note Signal mappings:
   *       - TurnLeft → LeftClicked()
   *       - TurnRight → RightClicked()
   *       - Boost → BoostClicked()
   *       - Pause → PauseClicked()
   *       - ExitButton → ExitClicked()
   *       - StartButton → StartClicked()
   *       - DropButton → DropClicked()
   */
  void addConnections();
  ~StatusWidget() {
    delete managment;
    if (figure) {
      for (int i = 0; i < FIGURE_PART; ++i) {
        delete[] figure[i];
      }
      delete[] figure;
    }
  }
};
}  // namespace s21
#endif  // STATUSWIDGET_H
