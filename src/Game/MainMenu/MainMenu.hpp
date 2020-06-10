#pragma once
#include "Model/BaseState.hpp"
#include "Controller/InputManager.hpp"
#include "View/EulerCamera.hpp"
#include "Game/MainMenu/StaticModel.hpp"

class MainMenu : public BaseState {
public:
    /**
     * Main Menu Scene
     */
    MainMenu();

    /**
     * Destructor for main menu.
     */
    ~MainMenu() override;

    /**
     * Display method for the scene.
     */
    auto display() -> void override;

    /**
     * Update function for main menu.
     * @param t time since start.
     * @param dt time since last frame.
     */
    auto update(double t, double dt) -> void override;

    /**
     * Init function to setup any variables outside of the constructor.
     */
    void Init() override;

    /**
     * Deinits before the destructor.
     */
    void unInit() override;

    /**
     * Input to be handled inside of the scene.
     * @param inputData
     * @param deltaTime
     */
    void handleInputData(Controller::Input::InputData inputData, double deltaTime) override;

    /**
     * Function to start our game.
     */
    void startGame();

    /**
     * Starts the GUI
     */
    void GUIStart() override;

    /**
     * ends the GUI
     */
    void GUIEnd() override;

private:
    /**
     * Handles window events.
     */
    void handleWindowEvent();

    /// Camera for the scene
    View::Camera camera;

    /// models used inside of the scene.
    std::vector<MainMenuObject::StaticModel> sModels = {};
};


