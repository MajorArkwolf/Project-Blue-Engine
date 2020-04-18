#include "OpenGL.hpp"
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glad/glad.h>
#include "Controller/Engine/Engine.hpp"
#include "Controller/GUIManager.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <algorithm>

void View::OpenGL::Draw() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    auto &engine = BlueEngine::Engine::get();
    auto& guiManager = engine.getGuiManager();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    GUIManager::startWindowFrame();
    guiManager.displayInputRebindWindow();
    guiManager.displayEscapeMenu();
    guiManager.displayInstructionMenu();
    guiManager.displayQuitScreen();
    guiManager.displayDevScreen(*camera);
    guiManager.displayTextureManager();
    int width = 0, height = 0;
    glfwGetWindowSize(engine.window, &width, &height);
    // view/projection transformations
    glm::mat4 projection =
            glm::perspective(glm::radians(camera->Zoom),
                             static_cast<double>(width) / static_cast<double>(height), 0.1, 100000.0);
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 skyboxView = glm::mat4(glm::mat3(camera->GetViewMatrix()));
    glm::mat4 model = glm::mat4(1.0f);

//    shader->use();
//    shader->setMat4("model", model);
//    shader->setMat4("projection", projection);
//    shader->setMat4("view", view);
    sortDrawDistance();
    for (auto &m : drawQue) {
        m.drawPointer(projection, view, camera->Position);
    }
    skyBox.draw(skyboxView, projection);
    GUIManager::endWindowFrame();
    glfwSwapBuffers(engine.window);
    drawQue.clear();
}
void View::OpenGL::Init() {
    int width  = 0;
    int height = 0;

    auto &engine = BlueEngine::Engine::get();
    glfwGetWindowSize(engine.window, &width, &height);
    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    shader = std::make_unique<Shader>(Shader("./res/shader/vertshader.vs", "./res/shader/fragshader.fs"));
    skyBox.Init();

}
void View::OpenGL::DeInit() {

}

void View::OpenGL::DrawModel(Shader& shader, unsigned int &VAO, const std::vector<TextureB> &textures,
               const std::vector<unsigned int> &indices) {
    // bind appropriate textures
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number =
                    std::to_string(specularNr++); // transfer unsigned int to stream
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void View::OpenGL::SetupMesh(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO,
               std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) {
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, static_cast<unsigned int>(vertices.size()) * sizeof(Vertex),
                 &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<unsigned int>(indices.size()) * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(0));
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void*>(offsetof(Vertex, Normal)));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, TexCoords)));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, Tangent)));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, Bitangent)));

    glBindVertexArray(0);
}

void View::OpenGL::ResizeWindow() {
    auto &engine = BlueEngine::Engine::get();
    int width = 0, height = 0;
    glfwGetWindowSize(engine.window, &width, &height);
    glViewport(0, 0, width, height);
}

void View::OpenGL::AddToQue(View::Data::DrawItem drawItem) {
    drawQue.push_back(drawItem);
}

unsigned int View::OpenGL::TextureFromFile(const char *path, const std::string &directory,
                                                     [[maybe_unused]] bool gamma) {
    std::string filename = std::string(path);
    filename             = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data =
            stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format = 1;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Enable should you need alpha, this will clamp textures to the edge to
        // ensure that weird stuff doesnt happen.
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    return textureID;
}
void View::OpenGL::SetCameraOnRender(Camera &mainCamera) {
    camera = &mainCamera;
}

void View::OpenGL::sortDrawDistance() {
    glm::vec3 cpos = {camera->Position.x, static_cast<float>(camera->Position.y), static_cast<float>(camera->Position.z)};
    for (auto &e : drawQue) {
        e.distance = glm::distance(e.pos, cpos);
    }
    sort(drawQue.begin(), drawQue.end(),
         [](const View::Data::DrawItem& lhs, const View::Data::DrawItem& rhs)->bool {
             return lhs.distance > rhs.distance;
         });
}