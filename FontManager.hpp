#ifndef FONT_MANAGER_HPP
#define FONT_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

using namespace std;
using namespace sf;


class FontManager {
private:
    map<string, Font> fonts;

public:
    FontManager();

    /** Adds a font from a file.**/
    void loadFont(const string &name, const string &filename);
    /** Gets a font given its id.**/
    Font &getRef(const string &font);
};


#endif // FONT_MANAGER_HPP
