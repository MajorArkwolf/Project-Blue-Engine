#pragma once

#include <SDL.h>
#include <imgui.h>
#include <map>
#include <string>

#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_sdl.h>

class GUIManager {
  public:
    /**
     * @brief GUIManager default constructor
     */
    GUIManager();

    /**
     * @brief Default destructor, uninitialises imgui stuff
     */
    ~GUIManager();

    /**
     * @brief Initialises ImGUI stuff
     * @param window The SDL window to draw the gui in
     * @param context The SDL context to draw the window in
     */
    void initialiseImGUI(SDL_Window *window, void *context);

    /**
     * @brief Displays the input rebind menu that allows inputs to be rebound on the fly
     */
    void displayInputRebindWindow();

    /**
     * @brief Displays the escape menu
     */
    void displayEscapeMenu();

    /**
     * @brief Starts an Imgui Window frame, must be called at the beginning of a display loop
     */
    void startWindowFrame();

    /**
     * @brief Ends an Imgui window frame, must be called at the end of a display loop before swapping window
     */
    void endWindowFrame();

    /**
     * @brief Toggles a window given its name in the map
     */
    void toggleWindow(std::string windowName);

  private:
    /// The max number of windwows possible
    static constexpr int windowMax = 30;

    /// An array of booleans telling each window whether to display or not
    bool windowOpen[windowMax];

    /// A mapping of a window name to a location in the window open array
    std::map<std::string, bool> windowOpenMap;

    /// Initialises the window open map
    void initialiseWindowOpenMap();
};