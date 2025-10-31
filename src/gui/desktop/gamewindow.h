#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "gamewidget.h"
#include "statuswidget.h"
#include "view.h"

namespace s21 {
class GameWindow : public QMainWindow {
  Q_OBJECT
  GameWidget *gameWidget{nullptr};
  StatusWidget *managmentWidget{nullptr};
 private slots:
  void LeftClicked() { emit LeftSignal(); }
  void RightClicked() { emit RightSignal(); }
  void BoostClicked() { emit BoostSignal(); }
  void PauseClicked() {
    // StartButton -> show();
    emit PauseSignal();
  }
  void ExitClicked() {
    // gameWidget -> clear();
    emit ExitSignal();
  }
  void StartClicked() {
    // StartButton->hide();
    emit StartSignal();
  }
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
   * @brief Constructs a GameWindow with specified game type and parent
   *
   * Initializes the main game window with a splitter layout containing
   * both the game visualization and status management panels. Sets up
   * the UI connections and focus policy for keyboard input.
   *
   * @note Window configuration:
   *       - Fixed size of 480x370 pixels
   *       - Horizontal splitter layout
   *       - Left: GameWidget (170x370) for game visualization
   *       - Right: StatusWidget (300x370) for controls and status
   */
  GameWindow(char gameType, QWidget *parent = nullptr) {
    setFixedSize(480, 370);
    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal, this);
    setCentralWidget(mainSplitter);
    gameWidget = new GameWidget(mainSplitter);
    managmentWidget = new StatusWidget(mainSplitter);
    managmentWidget->setFixedSize(300, 370);
    mainSplitter->addWidget(gameWidget);
    mainSplitter->addWidget(managmentWidget);
    addConnections();

    show();
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
  }
  /**
   * @brief Handles keyboard input events for game controls
   *
   * Processes key press events and maps them to corresponding game actions.
   * This provides keyboard-based control as an alternative to on-screen
   * buttons.
   *
   * @note The function uses Qt key codes to provide cross-platform
   *       keyboard input handling. The same actions are available
   *       via both keyboard and on-screen UI buttons.
   */
  void keyPressEvent(QKeyEvent *pe);
  /**
   * @brief Destructor for GameWindow - cleans up allocated resources
   *
   * Safely deallocates the UI components created by the GameWindow.
   * This includes both the game visualization widget and the status
   * management widget.
   *
   * @note The destructor follows RAII principles by ensuring proper
   *       cleanup of dynamically allocated member objects.
   */
  ~GameWindow() {
    delete gameWidget;
    delete managmentWidget;
  }
  /**
   * @brief Updates both game visualization and status display with new game
   * state
   *
   * Propagates game state updates to both the game field widget and the
   * management/status widget simultaneously to ensure consistent UI state.
   *
   * @note This function serves as a synchronization point between the
   *       game model and the user interface, ensuring both visual
   *       components display the same game state.
   */
  void updateField(GameInfo_t *game);
  /**
   * @brief Establishes signal-slot connections between UI components
   *
   * Connects signals from the status management widget to corresponding
   * slot methods in the game window, enabling button-based game control.
   *
   * @note The connections map UI button signals to the same handler methods
   *       used by keyboard input, providing consistent behavior regardless
   *       of input method.
   */
  void addConnections();
};

}  // namespace s21

#endif  // GAMEWINDOW_H
