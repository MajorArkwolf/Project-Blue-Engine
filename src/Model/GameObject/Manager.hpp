#pragma once

	/// System Dependencies
#include <map>
#include <memory>

	/// Internal Dependencies
#include "Base.hpp"
#include "LuaHelper.hpp"

	//! A manager class for GameObject's creation and storage.
class GameObj_Manager {
public:
		/*!
		 * @brief Registers the GameObject Manager and LuaHelper classes into the engine's Lua VM.
		 * @note Only performs the registration once, even if called multiple times.
		 */
	static void lua_init();

		/*!
		 * @brief Adds a new GameObject to be managed.
		 * @param [in] object A smart pointer to the target GameObject.
		 * @note This is not registered with Lua.
		 * @warning Assigning a new GameObject with an existing identifier will overwrite the old GameObject!
		 */
	static void insert(std::shared_ptr<GameObj_Base> object);

		/*!
		 * @brief Gather a reference to a managed GameObject.
		 * @param [in] identifier A GameObject identifier.
		 * @return A pointer to the specified GameObject, or nullptr on error.
		 * @note Can be used to check if a GameObject is being managed.
		 * @note This is not registered with Lua.
		 */
	static std::shared_ptr<GameObj_Base> get(BlueEngine::ID identifier);

		/*!
		 * @brief Calls the addToDraw function on all managed GameObjects.
		 * @note No calls will occur if the Manager isn't managing any GameObjects.
		 */
	static void addAllToDraw();

		/*!
		 * @brief Calls for a specific GameObject to be removed from the manager.
		 * @param [in] identifier A GameObject identifier.
		 * @note No effect will occur if the requested GameObject is not managed.
		 * @warning The requested GameObject may remain in memory after this call due to smart pointers!
		 */
	static void remove(BlueEngine::ID identifier);

		/*!
		 * @brief Calls for all GameObjects to be removed from the manager.
		 * @see GameObj_Manager::remove()
		 */
	static void clear();

		/*!
		 * @brief Calls upon the Factory Methods to generate a new GameObject of a specific type.
		 * @param [in] type A GameObject Type Identifier to declare what form of GameObject to generate.
		 * @return The unique identifier for the newly created GameObject, or 0u on error.
		 */
	static BlueEngine::ID lua_add(GameObjType type);

		/*!
		 * @brief Gathers a non-smart pointer, which is actually compatible with Lua.
		 * @param [in] identifier A GameObject identifier.
		 * @return A pointer to 
		 */
	static GameObj_LuaHelper lua_get(BlueEngine::ID identifier);

private:
		//! Stores a collection of unique GameObjects, mapped to their identifier.
	static std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>> managedGameObjects;
};
