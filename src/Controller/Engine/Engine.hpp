#pragma once

#include <memory>
#include <string>

#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "GameStack.hpp"
#include "BaseState.hpp"
extern "C" {
	#include "lauxlib.h"
	#include "lua.h"
	#include "lualib.h"
}
#include "LuaBridge/LuaBridge.h"


namespace BlueEngine {
    class Engine {
      public:
        using Window  = std::shared_ptr<SDL_Window>;
        using Context = std::shared_ptr<void>;

        static constexpr auto FPS_UPDATE_INTERVAL = 0.5;

        /* Mouse movement. */
        glm::vec2 mouse = {};

        /* SDL handles. */
        Window window   = nullptr;
        Context context = nullptr;

        /**
         * @brief The current FPS
         */
        double fps           = 0.0;


        auto getTime() const -> double;
        
        auto getBasePath() -> std::string;

      private:
        lua_State *luaState = nullptr;
        GameStack<BaseState *> gameStack;
        bool isRunning = true;
        std::string basepath = "";


        Engine();

      public:
        Engine(Engine &&)      = default;
        Engine(const Engine &) = delete;
        ~Engine();

        lua_State *getLuaState();
        //This variable will hold the game stack
        //Game *thegame = nullptr;

        static auto get() -> Engine &;
        static auto run() -> void;

        /**
         * @brief Overloaded assignment operator, set to default overload
         */
        auto operator=(Engine &&) -> Engine & = default;

        /**
         * @brief Overloaded const assignment operator, set to delete overload
         */
        auto operator=(const Engine &) -> Engine & = delete;

        auto getIsRunning() const -> bool;

        auto endEngine() -> void;

        auto processInput() -> void;
    };
}
