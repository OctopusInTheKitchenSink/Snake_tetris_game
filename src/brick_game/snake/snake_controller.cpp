#include "snake_controller.h"

namespace s21 {
void Controller::userInput(UserAction_t action, bool hold) {
  (void)hold;
  int status = model.get_pause();
  if (status != game_over && status != game_pause) {
    switch (action) {
      case Start:
        if (status == ready_to_start) model.set_status(shift);
        break;
      case Pause:
        model.set_status(game_pause);
        break;
      case Terminate:
        model.set_status(game_over);
        break;
      case Left:
        model.set_status(move_left);
        break;
      case Right:
        model.set_status(move_right);
        break;
      case Action:
        model.set_status(rotation);
        break;
      default:
        break;  // GCOVR_EXCL_LINE
    }
  }
  if (action == Start && status == game_pause) {
    model.set_status(shift);
  }
  if (action == Terminate && status == game_pause) {
    model.set_status(game_over);
  }
}
GameInfo_t Controller::updateCurrentState() {
  bool action_flag = model.check_flag();
  if (action_flag &&
      model.get_time_nanos() - model.get_time() > model.get_delay()) {
    model.set_time(model.get_time_nanos());
    switch (model.get_pause()) {
      case move_left:  // turn left
        model.turn_left();
        model.set_status(shift);
        model.snake_turn();
        break;
      case move_right:  // turn right
        model.turn_right();
        model.set_status(shift);
        model.snake_turn();
        break;
      case rotation:  // boost = 2x shift
        model.snake_turn();
        model.set_status(shift);
        model.snake_turn();
        break;
      case shift:
        model.set_status(shift);
        model.snake_turn();
        break;
    }

    // model.snake_turn();
  }
  if (model.get_pause() == game_over) {
    model.fin_game();
  }
  return model.get_game();
}
}  // namespace s21
