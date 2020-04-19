#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Renderer.hpp"
#include "Shader.hpp"
#include "DrawStruct.hpp"
#include "Model/Models/DataTypes.hpp"
#include "Skybox.hpp"
#include "View/EulerCamera.hpp"
#include "Model/Models/Model.hpp"
#include "Model/Vertix.hpp"
namespace View {
    class OpenGL: public View::Renderer {
      public:
        /**
         * Default Constructor
         */
        OpenGL() = default;
        /**
         * Default Destructor
         */
        ~OpenGL() = default;
        /**
         * Draw call for the renderer.
         */
        void Draw() override;
        /**
         * Initialises the OpenGL renderer.
         */
        void Init() override;
        /**
         * Deinitialises the renderer.
         */
        void DeInit() override;
        /**
         * Toggles wireframe on and off.
         */
        void ToggleWireFrame() override;
        /**
         * Adds an item to the draw que.
         * @param drawItem Passes DrawItem into the que to be used for rendering purposes.
         */
        void AddToQue(View::Data::DrawItem drawItem);
        /**
         * Setups a general mesh for the renderer in the OpenGL Context.
         * @param VAO buffer identity
         * @param VBO buffer identity
         * @param EBO buffer identity
         * @param vertices the verticies to be passed into OpenGL
         * @param indices the indicies to be passed into OpenGl.
         */
        static void SetupMesh(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO,
                       std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
        /**
         * The Resize window function for OpenGL
         */
        static void ResizeWindow();
        /**
         * Load a texture from file and store it.
         * @param path The path to the image.
         * @param directory The basepath to ensure that no funny operating filesystem stuff happens.
         * @param gamma A flag to set if there is gamma present.
         * @return A texture ID to avoid loading duplicates.
         */
        static unsigned int TextureFromFile(const char *path, const std::string &directory,
                                                   [[maybe_unused]] bool gamma);
        /**
         * Draws a generic OpenGL Model.
         * @param shader the shader used to draw the model.
         * @param VAO index to the VAO buffer.
         * @param textures required to draw the model
         * @param indices how many indicies are needed to draw the model.
         */
        static void DrawModel(Shader& shader, unsigned int &VAO, const std::vector<TextureB> &textures,
                              const std::vector<unsigned int> &indices);
        /**
         * Sets the camera to the renderer for the render pass. Required for lighting.
         * @param mainCamera the active camera in the scene.
         */
        void SetCameraOnRender(Camera &mainCamera);
        /**
         * Setup the terrain models
         * @param VAO index of buffer.
         * @param VBO index of buffer.
         * @param EBO index of buffer.
         * @param verticies to load into the buffers.
         * @param indicies to load into the buffers.
         */
        void SetupTerrainModel(unsigned int &VAO, unsigned &VBO, unsigned int &EBO, std::vector<Blue::Vertex>& verticies, std::vector<unsigned int>& indicies);

    private:
        /// Decides if the renderer should be in wireframe mode or not.
        bool wireframe = true;
        /// Sorts the objects based on the view distance, helps solve alpha issues.
        void sortDrawDistance();
        /// DrawQue of objects that need to be rendered by the renderer.
        std::vector<View::Data::DrawItem> drawQue = {};
        /// The active camera on the draw pass.
        Camera *camera = nullptr;
        /// The skybox for the scene.
        Skybox skyBox = {};
    };
}