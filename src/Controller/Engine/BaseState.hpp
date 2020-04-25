#pragma once

#include "Controller/InputManager.hpp"

/**
 * @class BaseState
 * @brief Pure virtual class for a game state
 */
class BaseState {
  public:
    /**
     * @brief Virtual destructor for BaseState
     */
    virtual ~BaseState() = default;

    /// Whether mouse is set to relative mode (reset to center of window each frame)
    bool relativeMouse = 1;

    /**
     * @brief Virtual initialisation function for a game state
     * Used separately from a hard init to reset variables needed for game state function
     */
    virtual void Init() = 0;

    /**
     * @brief Virtual soft initialisation function for a game state
     * Used separately from a hard init to reset variables needed for games tate function
     */
    virtual void display() = 0;

    /**
     * @brief Virtual un-initialisation function for a game state
     * Used to free memory from the game state, called right before popping the game stack
     */
    virtual void unInit() = 0;

    /**
     * @brief Virtual function for handling input events encased within a a custom Input Event
     * All input events will be sent to the current game state at the top of the stack
     * @param inputData The InputData event that contains the user input
     */
    virtual void handleInputData(Controller::Input::InputData inputData) = 0;

    /**
     * @brief Virtual update function for updating physics within a game state
     * @param dt Delta time since last frame
     */
    virtual void update(double t, double dt) = 0;

    /**
     * @brief to delete update function
     */
    virtual void updateWorld(double ts) = 0;

    /**
     * @brief to delete function to test physics
     */
    virtual void updatePhysics(double f) = 0;


};
