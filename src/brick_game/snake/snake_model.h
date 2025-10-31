#ifndef H_SNAKE_MODEL
#define H_SNAKE_MODEL

#include <sys/time.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include "./../../tetris.h"
namespace s21 {

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

enum { empty, apple, snake, start_speed = 700000 };

typedef struct {
  int **field{nullptr};
  int **next{nullptr};
  int score{0};
  int high_score{0};
  int level{1};
  int speed{0};
  int pause{ready_to_start};
} GameInfo_t;

class Model {
 private:
  GameInfo_t game{.field = nullptr,
                  .next = nullptr,
                  .score = 0,
                  .high_score = 0,
                  .level = 0,
                  .speed = 0,
                  .pause = 0};  // snake - 2 (green), apple - 1 (red)
  std::vector<std::pair<int, int>> snake_dir{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  int dir_num{3};
  long delay = start_speed;
  long now_time;
  std::list<std::pair<int, int>> snake_elements;
  unsigned int count_of_elements{4};

 public:
  /**
   * @brief Constructs a new Model object and initializes the game state.
   *
   * This constructor performs the complete initialization of the game model:
   * - Allocates and initializes the game field matrix
   * - Sets up the initial snake position
   * - Places the first apple on the field
   * - Loads the high score from persistent storage
   * - Initializes the game timing system
   *
   * @note Memory allocation for the game field follows a two-dimensional array
   * pattern where each row is individually allocated and initialized to zero.
   */
  Model();
  /**
   * @brief Finalizes the game session and performs cleanup operations.
   *
   * This function is called when the game ends, either normally or due to
   * termination. It handles proper resource deallocation and persistent
   * data management.
   *
   * @note The function performs two main operations:
   *       1. Memory cleanup of the dynamically allocated game field
   *       2. High score preservation if the current score exceeds the record
   */
  void fin_game();
  // void show(QPaintEvent *event){
  //     for(int i = 0; i < FIELD_HEIGHT; ++i){
  //         for(int j = 0; j < FIELD_WIDTH; ++j){
  //             std::cout << game.field[i][j];
  //         }
  //         std::cout << std::endl;
  //     }
  // };
  /**
   * @brief Retrieves the current monotonic time in microseconds.
   *
   * This function provides high-resolution timing information using the
   * system's monotonic clock, which is ideal for measuring time intervals
   * and game loop timing.
   *
   * @return long Current time in microseconds since an arbitrary point
   *
   * @note The monotonic clock is used to prevent issues with system time
   *       adjustments (NTP, daylight saving, manual changes) that could
   *       affect game timing consistency.
   * @note The precision is limited to microseconds (10^-6 seconds) even though
   *       the underlying clock provides nanosecond resolution. This is
   * typically sufficient for game loop timing requirements.
   */
  long get_time_nanos() const;
  /**
   * @brief Retrieves the timestamp of the last game state update.
   *
   * This function provides access to the internal timestamp tracking
   * when the last game update occurred. Used for calculating time
   * intervals between game state updates.
   *
   * @return long The timestamp in microseconds of the last game update
   */
  long get_time() const { return now_time; }
  /**
   * @brief Retrieves the current delay between game state updates.
   *
   * This function returns the current time interval (in microseconds)
   * that must elapse between consecutive game state updates. The delay
   * typically decreases as game level increases to create difficulty
   * progression.
   *
   * @return long The current update delay in microseconds
   */
  long get_delay() const { return delay; }
  /**
   * @brief Updates the timestamp of the last game state update.
   *
   * This function sets the internal timestamp to mark when a game
   * state update occurred. It is typically called after processing
   * game logic to track the timing for the next update cycle.
   */
  void set_time(long t) { now_time = t; }
  /**
   * @brief Rotates the snake's movement direction counterclockwise.
   *
   * This function changes the snake's current direction by decrementing
   * the direction index, effectively turning the snake 90 degrees to the left.
   * The direction system uses a circular numbering scheme to maintain
   * consistent rotation behavior.
   *
   * @note The direction system typically follows this convention:
   *       - 0: Right (east)
   *       - 1: Down (south)
   *       - 2: Left (west)
   *       - 3: Up (north)
   */
  void turn_left();
  /**
   * @brief Rotates the snake's movement direction clockwise.
   *
   * This function changes the snake's current direction by incrementing
   * the direction index, effectively turning the snake 90 degrees to the right.
   * The direction system uses a circular numbering scheme to maintain
   * consistent rotation behavior.
   *
   * @note The direction system typically follows this convention:
   *       - 0: Right (east)
   *       - 1: Down (south)
   *       - 2: Left (west)
   *       - 3: Up (north)
   */
  void turn_right();
  /**
   * @brief Retrieves the current game state information.
   *
   * This function provides read-only access to the complete game state,
   * allowing external systems to query the current game status without
   * modifying the internal model state.
   *
   * @return GameInfo_t A copy of the current game state structure containing:
   *         - field: 2D array representing the game board state
   *         - next: Preview of the next piece (if applicable)
   *         - level: Current game level
   *         - score: Current player score
   *         - high_score: All-time best score
   *         - speed: Current game speed setting
   *         - pause: Current game status (running, paused, game over, etc.)
   *
   * @note The function returns a copy of the game state rather than a reference
   *       to ensure encapsulation and prevent external modification of the
   *       model's internal state.
   */
  int get_pause() const { return game.pause; }
  /**
   * @brief Sets the game status with special handling for pause state toggle.
   *
   * This function updates the game's current status, implementing special
   * logic for the pause state. When the game is already paused and a pause
   * command is received, it toggles back to the shift (running) state.
   *
   * @note The function implements pause toggle behavior:
   *       - If current status is game_pause AND new status is Pause,
   *         then toggle to shift state (resume game)
   *       - Otherwise, set to the specified new status
   */
  void set_status(int st);
  /**
   * @brief Retrieves the current game state information.
   *
   * This function provides read-only access to the complete game state,
   * allowing external systems to query the current game status without
   * modifying the internal model state.
   *
   * @return GameInfo_t A copy of the current game state structure containing:
   *         - field: 2D array representing the game board state
   *         - next: Preview of the next piece (if applicable)
   *         - level: Current game level
   *         - score: Current player score
   *         - high_score: All-time best score
   *         - speed: Current game speed setting
   *         - pause: Current game status (running, paused, game over, etc.)
   *
   * @note The function returns a copy of the game state rather than a reference
   *       to ensure encapsulation and prevent external modification of the
   *       model's internal state.
   */
  GameInfo_t get_game() const { return game; }
  /**
   * @brief Advances the snake movement by one step in the current direction.
   *
   * This function processes a single movement step for the snake, including:
   * - Calculating the new head position based on current direction
   * - Checking for collisions with walls or self
   * - Handling apple consumption and growth
   * - Updating the snake's body segments
   *
   * @note The function implements the core snake movement logic:
   *       - Uses direction vector to calculate new head position
   *       - Checks if new position is valid (no collisions)
   *       - Processes apple consumption if applicable
   *       - Updates snake body and redraws the head
   */
  void snake_turn();
  /**
   * @brief Checks if the game is in an active state where actions can be
   * processed.
   *
   * This function determines whether the game is currently in a state that
   * allows game logic updates and snake movement. It identifies states where
   * the game simulation should be running versus states where it should be
   * paused or terminated.
   *
   * @return bool true if the game is active and can process updates,
   *         false if the game is in a passive state (paused, not started, or
   * ended)
   *
   * @note The function returns true only for active gameplay states:
   *       - shift: Normal game progression
   *       - move_left: Left movement state
   *       - move_right: Right movement state
   *       - rotation: Special action state
   */
  bool check_flag() const {
    return (game.pause != game_pause && game.pause != ready_to_start &&
            game.pause != terminate && game.pause != game_over);
  }
  friend class test_class;

 private:
  /**
   * @brief Draws a snake segment at the specified coordinates on the game
   * field.
   *
   * This function updates the game field to place a snake segment at the
   * given coordinates. It is used to render both new head positions during
   * movement and existing snake body segments during initialization.
   * @note This function performs a simple field update operation:
   *       - Sets the specified cell value to 'snake'
   *       - Does not modify the snake_elements container
   *       - Does not perform any validation on the coordinates
   */
  void draw_snake_part(std::pair<int, int> coord) {
    game.field[coord.first][coord.second] = snake;
  }
  /**
   * @brief Reads the high score from persistent storage file.
   *
   * This function attempts to read the snake game high score from a text file.
   * If the file does not exist or cannot be opened, it creates a new file
   * with a default high score of 0 and returns that value.
   *
   * @return int The high score value read from file, or 0 if file doesn't exist
   *
   * @note The function implements a fail-safe mechanism:
   *       - Attempts to open "snake_high_score.txt" for reading
   *       - If file exists and opens successfully, reads the first line as
   * score
   *       - If file doesn't exist, creates it with default value "0"
   *       - Returns 0 as default score in case of file creation
   *
   */
  int read_from_file();
  /**
   * @brief Generates a new apple at a random valid position on the game field.
   *
   * This function places an apple at a random empty cell within the playable
   * area of the game field, ensuring it doesn't overlap with existing game
   * elements like snake segments.
   *
   * @note The function uses a trial-and-error approach to find a valid
   * position:
   *       - Generates random coordinates within field boundaries
   *       - Checks if the position is empty (value 0)
   *       - Repeats until a valid empty cell is found
   */
  void make_apple();
  /**
   * @brief Checks if a cell position would cause a collision.
   *
   * This function determines whether moving to the specified cell would
   * result in a game-ending collision. It checks for both wall collisions
   * and self-collisions with the snake's body.
   *
   * @return bool true if the move is safe (no collision), false if collision
   *         would occur (game over condition)
   *
   * @note The function checks three collision conditions:
   *       - Wall collision: Cell outside playable area boundaries
   *       - Self-collision: Cell contains existing snake segment
   *       - Sets game state to game_over if collision detected
   */
  bool check_crash(std::pair<int, int> cell);
  /**
   * @brief Handles apple consumption and snake growth mechanics.
   *
   * This function checks if the snake's head has reached an apple cell
   * and processes the consequences. It manages score incrementation,
   * apple regeneration, level progression, and snake growth.
   *
   * @note The function implements the core apple consumption logic:
   *       - If cell contains apple: increment score, generate new apple, update
   * level
   *       - If cell doesn't contain apple: remove tail segment (normal
   * movement)
   */
  void check_apple(std::pair<int, int> cell);
  /**
   * @brief Updates the game level and difficulty based on current score.
   *
   * This function handles the game's progression system by calculating
   * the current level from the player's score and adjusting the game
   * speed accordingly. It also updates the high score if necessary.
   *
   * @note The function performs three main operations:
   *       - Calculates current level based on score (1 level per 5 points)
   *       - Updates high score if current score exceeds it
   *       - Adjusts game speed (delay) based on current level
   */
  void update_lvl();
  /**
   * @brief Removes the tail segment of the snake during movement.
   *
   * This function handles the removal of the snake's last segment when
   * the snake moves without consuming an apple. It updates both the
   * game field and the snake's internal representation.
   *
   * @note The function performs two main operations:
   *       - Clears the tail position on the game field (sets to empty)
   *       - Removes the last element from the snake_elements container
   */
  void erase_snake_part();
};
}  // namespace s21

#endif
