#ifndef H_SNAKE_CONTROLLER
#define H_SNAKE_CONTROLLER

#include "snake_model.h"

namespace s21 {
class Controller {
  Model model;
  int i = 0;

 public:
  friend class test_class;
  /**
   * @brief Processes user input and updates the game state accordingly.
   *
   * This function handles various user actions and translates them into
   * corresponding game state changes. It manages game flow controls
   * (start, pause, terminate) and in-game actions (movement, rotation).
   */

  void userInput(UserAction_t action, bool hold);
  /**
   * @brief Updates the current game state based on elapsed time and game
   * status.
   *
   * This function is the main game loop processor that handles game state
   * updates at regular intervals. It checks if enough time has passed since the
   * last update and performs the appropriate game actions based on the current
   * game status.
   *
   * @return GameInfo_t Current game state information containing field data,
   *         score, level, and other game parameters
   *
   * @note The function uses a time-based update system:
   *       - Updates occur only when the elapsed time exceeds the current game
   * delay
   *       - Different actions are performed based on current movement direction
   *       - Automatically handles game termination when appropriate
   */
  GameInfo_t updateCurrentState();
};
}  // namespace s21

#endif
