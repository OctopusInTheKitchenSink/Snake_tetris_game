#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "snakegame.h"
#include "tetrisgame.h"
#include "view.h"

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT
  QWidget *MainWidget;
  SnakeGame *snake{nullptr};
  TetrisGame *tetris{nullptr};
  MyLabel *text;
  QPushButton *SnakeButton{nullptr};
  QPushButton *TetrisButton{nullptr};
  QPushButton *ExitButton{nullptr};
 signals:
  void SnakeSignal();
  void TetrisSignal();
  void ExitSignal();

 private slots:
  void TetrisClicked();
  void SnakeClicked();
  void ExitClicked();

 public:
  /**
   * @brief Constructs the MainWindow and initializes the game launcher
   * interface
   *
   * Sets up the main application window with title and initializes the
   * menu interface with game selection buttons and instructions.
   *
   * @note Initialization process:
   *       - Sets window title to "BrickGame v2.0"
   *       - Calls addMenu() to create the UI layout
   *       - Calls addConnection() to set up button signals
   */
  MainWindow();
  /**
   * @brief Destructor for MainWindow - cleans up allocated resources
   *
   * Safely deallocates the main UI components created by the MainWindow.
   * This includes the central widget and the instruction text label.
   *
   * @note The destructor follows RAII principles by ensuring proper
   *       cleanup of dynamically allocated member objects.
   */
  ~MainWindow();
  /**
   * @brief Creates and arranges the main menu user interface
   *
   * Builds the complete menu layout with game selection buttons,
   * exit button, and instructional text using Qt layout managers.
   *
   * @note UI Structure:
   *       - MainWidget as central widget
   *       - QVBoxLayout as main vertical layout
   *       - QHBoxLayout for game buttons (horizontal arrangement)
   *       - MyLabel for instructional text
   *       - QPushButton for Tetris, Snake, and Exit actions
   */
  void addMenu();
  /**
   * @brief Establishes signal-slot connections for menu interactions
   *
   * Connects the menu buttons to their respective handler methods,
   * enabling the game selection and exit functionality.
   *
   * @note Signal Mappings:
   *       - SnakeButton clicked → SnakeClicked()
   *       - TetrisButton clicked → TetrisClicked()
   *       - ExitButton clicked → ExitClicked()
   */
  void addConnection();
};
}  // namespace s21

#endif  // MAINWINDOW_H
