	/// Definition Include
#include "../GameObj_NPC.hpp"

GameObj_NPC::GameObj_NPC() {
	// GameObj_NPC has no unique attributes to initialise yet
}

GameObj_NPC::GameObj_NPC(std::string path, glm::vec3 position, glm::vec3 look_at, glm::vec3 look_up) {
	// GameObj_NPC has no unique attributes to initialise yet
}

GameObjectType GameObj_NPC::gameObj_getType() const {
	// Keep track of this class's identifier for its type
	static const GameObjectType classID = gameObj_getType();

	// Return a copy of the tracked id
	return classID;
}