#pragma once
#include <map>

#include "Model/Texture.hpp"
#include "stb_image.h"

/**
 * @class TextureManager
 * @brief A class used to manager textures within the program
 */
class TextureManager {

  public:
    /**
     * @brief Loads a texture from file and stores it as an openGL texture
     * @param filePath The filepath to load the image from
     * @param texName The key to give to the texture for later access
     * @return True if succeeded
     */
    bool loadTextureFromFile(std::string filePath, std::string texName);

    /**
     * @brief Returns a texture with the given name/key
     * @param texName The key/name to look for in the texture map
     * @return The texture at the given key location
     */
    Texture &getTexture(std::string texName);

    /**
     * @brief Returns a texture with the given OpenGL ID
     * @param id The id to search for
     * @return The texture with the given ID
     */
    Texture &getTexture(unsigned int id);

    /**
     * @brief Returns a static instance of the texture manager
     * @return  A static instance of the texture manager
     */
    static TextureManager &getInstance();

    /// A map containing pairs of keys and textures
    std::map<std::string, Texture> textureMap;

  private:
    TextureManager();
};
