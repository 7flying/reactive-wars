#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

using namespace std;
using namespace sf;


class TextureManager {
private:
    map<string, Texture> textures;

public:
    TextureManager();

    /** Adds a texture from a file.**/
    void loadTexture(const string &name, const string &filename);
    /** Gets a texture given its id.**/
    Texture &getRef(const string &texture);
};


#endif // TEXTURE_MANAGER_HPP
