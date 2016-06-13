#include "FontManager.hpp"
#include <SFML/Graphics.hpp>


FontManager::FontManager(){}

void FontManager::loadFont(const string &name, const string &filename)
{
    Font font;
    font.loadFromFile(filename);
    this->fonts[name] = font;
}

Font& FontManager::getRef(const string &font)
{
    return this->fonts.at(font);
}
