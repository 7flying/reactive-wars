#include "TextureManager.hpp"


TextureManager::TextureManager(){}

void TextureManager::loadTexture(const string &name, const string &filename)
{
    Texture texture;
    texture.loadFromFile(filename);
    this->textures[name] = texture;
}

Texture &TextureManager::getRef(const string &texture)
{
    return this->textures.at(texture);
}
