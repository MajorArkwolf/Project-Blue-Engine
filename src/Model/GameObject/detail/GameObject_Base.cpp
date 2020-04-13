	/// Definition Include
#include "../GameObject_Base.hpp"

	/// External Dependencies
#include <limits>

	/// Internal Dependencies
#include "../../Models/ModelManager.hpp"

GameObject_Base::GameObject_Base() {
	// Set the initial values of the GameObject's 3D position attributes
	gameObj_pos  = {0.0f, 0.0f, 0.0f};
	gameObj_lookAt = {0.0f, 0.0f, 1.0f};
	gameObj_lookUp = {0.0f, 1.0f, 0.0f};

	// Set the initial stored identifiers
	gameObj_modelId = std::numeric_limits<std::size_t>::min();
	gameObj_modelPath = "";
	gameObj_physBody = 0ul;
}

GameObject_Base::GameObject_Base(std::string path, unsigned long int physBody, glm::vec3 position, glm::vec3 look_at,
 glm::vec3 look_up) {
	// Set the initial values of the GameObject's 3D position attributes
	gameObj_pos  = position;
	gameObj_lookAt = look_at;
	gameObj_lookUp = look_up;

	// Set the initial stored identifiers
	gameObj_setModel(path);
	gameObj_physBody = physBody;
}

GameObject_Base::~GameObject_Base() {
	// GameObj_Base has no unique destruction procedure yet.
}

GameObjectType GameObject_Base::gameObj_getType() const {
	// Always return error indicator 0, never return anything else.
	return 0u;
}

void GameObject_Base::gameObj_setModel(std::string path) {
	// Call the Model Loader and keep track of what it spits out
	gameObj_modelId = ModelManager::GetModelID(path);

	// Store the path
	gameObj_modelPath = path;
}

GameObjectType GameObject_Base::gameObj_registerTypeID() {
	// Keep track of the IDs already assigned
	static GameObjectType idCount = 0u;

	// Catch the overflow of the tracked IDs
	if (idCount == std::numeric_limits<GameObjectType>::max())
	{
		// Return the minimum ID value to indicate an error
		return 0u;
	}

	// Generate the ID
	return ++idCount;
}

std::size_t GameObject_Base::gameObj_getModelID() {
	// Return a copy of the stored model identifier
	return gameObj_modelId;
}

std::string GameObject_Base::gameObj_getModelPath() {
	// return a copy of the stored model path
	return gameObj_modelPath;
}
