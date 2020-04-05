#include "Controller/InputManager.hpp"

#include <iostream>

#include "Controller/Engine/Engine.hpp"

namespace Controller::Input {
    InputManager &InputManager::getInstance() {
        static auto instance = InputManager{};

        return instance;
    }
    InputData InputManager::ProcessInput(SDL_Event &event) {
        // Handle input data from event
        InputData inputEvent;

        switch (event.type) {
            case SDL_KEYDOWN: {
                inputEvent.inputType = BLUE_InputType::KEY_PRESS;
            } break;
            case SDL_KEYUP: {
                inputEvent.inputType = BLUE_InputType::KEY_RELEASE;
            } break;
            case SDL_MOUSEMOTION: {
                inputEvent.inputType             = BLUE_InputType::MOUSE_MOTION;
                inputEvent.mouseMotionRelative.x = event.motion.xrel;
                inputEvent.mouseMotionRelative.y = event.motion.yrel;
                inputEvent.mouseMotionAbsolute.x = event.motion.x;
                inputEvent.mouseMotionAbsolute.y = event.motion.y;
            } break;
            case SDL_MOUSEBUTTONDOWN: {
                inputEvent.inputType = BLUE_InputType::MOUSE_BUTTONDOWN;
            } break;
            case SDL_MOUSEBUTTONUP: {
                inputEvent.inputType = BLUE_InputType::MOUSE_BUTTONUP;
            } break;
            case SDL_MOUSEWHEEL: {
                inputEvent.inputType        = BLUE_InputType::MOUSE_WHEEL;
                inputEvent.mouseWheelMotion = event.wheel.y;
            } break;
        }

        switch (inputEvent.inputType) {
            case BLUE_InputType::KEY_PRESS:
            case BLUE_InputType::KEY_RELEASE: {
                for (auto itr : InputMap) {
                    if (itr.second == event.key.keysym.scancode) {
                        inputEvent.inputAction = itr.first;
                    }
                }
            } break;

            case BLUE_InputType::MOUSE_BUTTONDOWN:
            case BLUE_InputType::MOUSE_BUTTONUP: {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    inputEvent.inputAction = BLUE_InputAction::INPUT_ACTION_1;
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    inputEvent.inputAction = BLUE_InputAction::INPUT_ACTION_2;
                } else if (event.button.button == SDL_BUTTON_MIDDLE) {
                    inputEvent.inputAction = BLUE_InputAction::INPUT_ACTION_3;
                }
            } break;
            default: {

            } break;
        }

        return inputEvent;

    }

    void InputManager::ReadBindings() {
        std::string basePath = "";

        char *base_path = SDL_GetBasePath();
        if (base_path) {
            basePath = std::string(base_path);
        } else {
            basePath = SDL_strdup("./");
        }

        SDL_free(base_path);
        auto &LuaManager = LuaManager::getInstance();

        auto luaState          = LuaManager.getLuaState();
        std::string scriptPath = basePath + "scripts//InputBindings.lua";
        if (luaL_dofile(luaState, scriptPath.c_str())) {
            std::cout << "No script file found at '" << scriptPath
                      << "', aborting input binding." << std::endl;
        }
        lua_pcall(luaState, 0, 0, 0);
        luaL_openlibs(luaState);
        luabridge::LuaRef table =
            luabridge::getGlobal(luaState, "InputBindings");
        if (!table.isNil()) {
            readLuaInputTable(table);
        }
    }

    SDL_Scancode InputManager::hashInputValue(const std::string &value) {
        if (value == "A") {
            return SDL_SCANCODE_A;
        }
        if (value == "B") {
            return SDL_SCANCODE_B;
        }
        if (value == "C") {
            return SDL_SCANCODE_C;
        }
        if (value == "D") {
            return SDL_SCANCODE_D;
        }
        if (value == "E") {
            return SDL_SCANCODE_E;
        }
        if (value == "F") {
            return SDL_SCANCODE_F;
        }
        if (value == "G") {
            return SDL_SCANCODE_G;
        }
        if (value == "H") {
            return SDL_SCANCODE_H;
        }
        if (value == "I") {
            return SDL_SCANCODE_I;
        }
        if (value == "J") {
            return SDL_SCANCODE_J;
        }
        if (value == "K") {
            return SDL_SCANCODE_K;
        }
        if (value == "L") {
            return SDL_SCANCODE_L;
        }
        if (value == "M") {
            return SDL_SCANCODE_M;
        }
        if (value == "N") {
            return SDL_SCANCODE_N;
        }
        if (value == "O") {
            return SDL_SCANCODE_O;
        }
        if (value == "P") {
            return SDL_SCANCODE_P;
        }
        if (value == "Q") {
            return SDL_SCANCODE_Q;
        }
        if (value == "R") {
            return SDL_SCANCODE_R;
        }
        if (value == "S") {
            return SDL_SCANCODE_S;
        }
        if (value == "T") {
            return SDL_SCANCODE_T;
        }
        if (value == "U") {
            return SDL_SCANCODE_U;
        }
        if (value == "V") {
            return SDL_SCANCODE_V;
        }
        if (value == "W") {
            return SDL_SCANCODE_W;
        }
        if (value == "X") {
            return SDL_SCANCODE_X;
        }
        if (value == "Y") {
            return SDL_SCANCODE_Y;
        }
        if (value == "Z") {
            return SDL_SCANCODE_Z;
        }
        if (value == "SPACE") {
            return SDL_SCANCODE_SPACE;
        }
        if (value == "LSHIFT") {
            return SDL_SCANCODE_LSHIFT;
        }
        if (value == "LCTRL") {
            return SDL_SCANCODE_LCTRL;
        }
        if (value == "TAB") {
            return SDL_SCANCODE_TAB;
        }
        if (value == "LALT") {
            return SDL_SCANCODE_LALT;
        }
        if (value == "ESCAPE") {
            return SDL_SCANCODE_ESCAPE;
        }
        return SDL_SCANCODE_UNKNOWN;

    }

    void InputManager::bindKey(BLUE_InputAction action,
                               luabridge::LuaRef &inputTable, std::string value) {

        luabridge::LuaRef inputRef = inputTable[value];

        if (inputRef.isString()) {
            std::string input = inputRef.cast<std::string>();
            std::cout << input << std::endl;
            InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
                action, hashInputValue(input)));
        }
    }

    void InputManager::bindKey(BLUE_InputAction, SDL_Scancode) {}

    void InputManager::readLuaInputTable(luabridge::LuaRef inputTable) {

        bindKey(BLUE_InputAction::INPUT_JUMP, inputTable, "JUMP");
        bindKey(BLUE_InputAction::INPUT_SPRINT, inputTable, "SPRINT");
        bindKey(BLUE_InputAction::INPUT_MOVE_FORWARD, inputTable, "MOVE_FORWARD");
        bindKey(BLUE_InputAction::INPUT_MOVE_LEFT, inputTable, "MOVE_LEFT");
        bindKey(BLUE_InputAction::INPUT_MOVE_RIGHT, inputTable, "MOVE_RIGHT");
        bindKey(BLUE_InputAction::INPUT_MOVE_BACKWARD, inputTable, "MOVE_BACKWARD");
    }

    void InputManager::DefaultInputMap() {
        InputMap.at(BLUE_InputAction::INPUT_JUMP)          = SDL_SCANCODE_SPACE;
        InputMap.at(BLUE_InputAction::INPUT_MOVE_FORWARD)  = SDL_SCANCODE_W;
        InputMap.at(BLUE_InputAction::INPUT_MOVE_BACKWARD) = SDL_SCANCODE_S;
        InputMap.at(BLUE_InputAction::INPUT_MOVE_LEFT)     = SDL_SCANCODE_A;
        InputMap.at(BLUE_InputAction::INPUT_MOVE_RIGHT)    = SDL_SCANCODE_D;
        InputMap.at(BLUE_InputAction::INPUT_ACTION_1)      = SDL_SCANCODE_E;
        InputMap.at(BLUE_InputAction::INPUT_ACTION_2)      = SDL_SCANCODE_R;
        InputMap.at(BLUE_InputAction::INPUT_SPRINT) = SDL_SCANCODE_LSHIFT;
        InputMap.at(BLUE_InputAction::INPUT_CROUCH) = SDL_SCANCODE_LCTRL;
        InputMap.at(BLUE_InputAction::INPUT_ESCAPE) = SDL_SCANCODE_ESCAPE;
    }

    InputManager::~InputManager() {}
    void InputManager::populateInputMap() { // Populates Input map with all actions to allow mapping inputs to them
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_DEFAULT, SDL_SCANCODE_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_JUMP, SDL_SCANCODE_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_MOVE_FORWARD, SDL_SCANCODE_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_MOVE_BACKWARD, SDL_SCANCODE_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_MOVE_LEFT, SDL_SCANCODE_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_MOVE_RIGHT, SDL_SCANCODE_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_SPRINT, SDL_SCANCODE_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_CROUCH, SDL_SCANCODE_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_LOOK_UP, SDL_SCANCODE_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_LOOK_DOWN, SDL_SCANCODE_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_LOOK_LEFT, SDL_SCANCODE_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_LOOK_RIGHT, SDL_SCANCODE_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_ACTION_1, SDL_SCANCODE_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_ACTION_2, SDL_SCANCODE_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_ACTION_3, SDL_SCANCODE_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_ACTION_4, SDL_SCANCODE_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
            BLUE_InputAction::INPUT_ESCAPE, SDL_SCANCODE_UNKNOWN));
    }

    InputManager::InputManager() {
        populateInputMap();
        DefaultInputMap();
    }
}