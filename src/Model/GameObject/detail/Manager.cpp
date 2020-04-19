	/// Declaration Include
#include "../Manager.hpp"

	/// Internal Dependencies
#include "Controller/Engine/LuaManager.hpp"
#include "Controller/Factory/GameAssetFactory.hpp"

void GameObj_Manager::insert(std::shared_ptr<GameObj_Base> object) {
	// Catch and stop processing nullptr
	if (!object)
		return;
	
	// Assign the new object for management into the map
	managedGameObjects[object.get()->gameObj_getUniqueID()] = object;
}

std::shared_ptr<GameObj_Base> GameObj_Manager::get(BlueEngine::ID identifier)
{
	// Catch any errors thrown
	try {
		// Attempt to find and return a copy of the requested GameObject
		return managedGameObjects.at(identifier);
	}
	catch (...) {
		// Indicate no element with specified found
		return nullptr;
	}
}

void GameObj_Manager::addAllToDraw() {
	// Process all of the stored GameObjects
	for (auto i = managedGameObjects.begin(); i != managedGameObjects.end(); ++i)
	{
		// Call the addToDraw function
		i->second.get()->gameObj_addToDraw();
	}
}

void GameObj_Manager::remove(BlueEngine::ID identifier) {
	// Just remove the specified GameObject from the manager, don't directly call for it to be removed from memory
	managedGameObjects.erase(identifier);
}

void GameObj_Manager::clear() {
	// Just remove the GameObjects from the manager, don't directly call for it to be removed from memory
	managedGameObjects.clear();
}

BlueEngine::ID GameObj_Manager::lua_add(GameObjType type) {
	// Call the Factory Constructor to generate and insert a new GameObject
	std::shared_ptr<GameObj_Base> temp = Controller::Factory::get().GameObject(type);

	// Catch any error from the Factory output
	if (temp.get() == nullptr)
	{
		// Don't store anything, just return an indicator of failure
		return 0u;
	}

	// On success, store the factory output and return the GameObject's identifier
	insert(temp);
	return temp.get()->gameObj_getUniqueID();
}

GameObj_LuaHelper GameObj_Manager::lua_get(BlueEngine::ID identifier) {
	//Return the outcome from get() encapsulated in a LuaHelper GameObject
	return GameObj_LuaHelper(get(identifier));
}

void GameObj_Manager::lua_init() {
	// Prevent registering multiple times
	static bool is_registered = false;
	if (is_registered)
		return;

	// Register the LuaHelper class
	auto vm = LuaManager::getInstance().getLuaState();
	luabridge::getGlobalNamespace(vm)
		.beginClass<GameObj_LuaHelper>("GameObject")
			.addFunction("getUniqueID", &GameObj_LuaHelper::gameObj_getUniqueID)
			.addFunction("getTypeID", &GameObj_LuaHelper::gameObj_getTypeID)
			.addFunction("setModel", &GameObj_LuaHelper::gameObj_setModel)
			.addFunction("getModelID", &GameObj_LuaHelper::gameObj_getModelID)
			.addFunction("getModelPath", &GameObj_LuaHelper::gameObj_getModelPath)
			.addFunction("getPos_X", &GameObj_LuaHelper::gameObj_getPos_X)
			.addFunction("setPos_X", &GameObj_LuaHelper::gameObj_setPos_X)
			.addFunction("getPos_Y", &GameObj_LuaHelper::gameObj_getPos_Y)
			.addFunction("setPos_Y", &GameObj_LuaHelper::gameObj_setPos_Y)
			.addFunction("getPos_Z", &GameObj_LuaHelper::gameObj_getPos_Z)
			.addFunction("setPos_Z", &GameObj_LuaHelper::gameObj_setPos_Z)
			.addFunction("getYaw", &GameObj_LuaHelper::gameObj_getYaw)
			.addFunction("setYaw", &GameObj_LuaHelper::gameObj_setYaw)
			.addFunction("getPitch", &GameObj_LuaHelper::gameObj_getPitch)
			.addFunction("setPitch", &GameObj_LuaHelper::gameObj_setPitch)
			.addFunction("getRoll", &GameObj_LuaHelper::gameObj_getRoll)
			.addFunction("setRoll", &GameObj_LuaHelper::gameObj_setRoll)
			.addFunction("getPhysBody", &GameObj_LuaHelper::gameObj_getPhysBody)
			.addFunction("setPhysBody", &GameObj_LuaHelper::gameObj_setPhysBody)
		.endClass();

	// Register the Manager class
	luabridge::getGlobalNamespace(vm)
		.beginClass<GameObj_Manager>("GameObject_Manager")
			.addStaticFunction("add", &GameObj_Manager::lua_add)
			.addStaticFunction("get", &GameObj_Manager::lua_get)
			.addStaticFunction("remove", &GameObj_Manager::remove)
			.addStaticFunction("clear", &GameObj_Manager::clear)
		.endClass();

	// Prevent the registration with lua occuring multiple times
	is_registered = true;
}

	/// Static Initialisation
std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>> GameObj_Manager::managedGameObjects = std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>>();