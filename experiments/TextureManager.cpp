#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "TextureManager.hpp"


TextureManager::TextureManager(){}

void TextureManager::loadTexture(const string &name, const string &filename)
{
    Texture tex;
    tex.loadFromFile(filename);
    this->textures[name] = tex;
}

Texture& TextureManager::getRef(const string &texture)
{
    // this will throw an exception if the given element does not exist
    return this->textures.at(texture);
}
