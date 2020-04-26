#pragma once

	/// System Dependencies
#include <memory>

	/// Internal Dependencies
#include "View/Renderer/Shader.hpp"
#include "Base.hpp"

	/*!
	 * @brief A non-moving Gameobject.
	 * @note Used for populating a scene with furnishings.
	 */
class GameObj_Static : public GameObj_Base {
public:
		/*!
		 * @brief Initialses class contents and calls the inherited class constructor.
		 * @see GameObj_Base
		 */
	GameObj_Static();

		/*!
		 * @brief Sets initial class contents and calls the inherited class constructor.
		 * @param [in] path The path to a target external model file for this GameObject.
		 * @param [in] physBody The identifier for the physical body for this GameObject.
		 * @param [in] position The position of the GameObject in the 3D environment.
		 * @param [in] rotation The GameObject's rotation, in degrees, for the pitch, yaw, and roll.
		 * @param [in] scale The scale of the GameObject for its x, y, and z co-ordinates.
		 */
	GameObj_Static(std::string path, unsigned long int physBody, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

		//! GameObj_Static destructor
	~GameObj_Static();

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return GAMEOBJ_STATIC, always.
		 */
	GameObjType gameObj_getTypeID() const;

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return GAMEOBJ_STATIC, always.
		 */
	static GameObjType _gameObj_getTypeID();

		//! Adds the GameObject to the draw queue.
	void gameObj_addToDraw();

		//! Stores the GameObject's shader for use in rendering.
	std::shared_ptr<Shader> gameObj_shader = nullptr;

		/*!
		 * @brief The draw call for a GameObj_Static.
		 * @param [in] projection The rendering projection for rendering.
		 * @param [in] view The rendering view for rendering.
		 * @param [in] cameraPos The position of the camera for rendering.
		 * @note Only used by gameObj_addToDraw()!
		 */
	void Draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos);
};
