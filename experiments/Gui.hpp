#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <string>

using namespace std;
using namespace sf;


class GuiStyle
{
public:
    Color bodyCol, bodyHighCol, borderCol, borderHighCol, textCol,
        textHighCol;
    // Fonts are large stuff, we load them once and reference to it
    Font *font;

    float borderSize;

    GuiStyle(){}
    GuiStyle(Font *fong, float borderSize, Color bodyCol, Color borderCol,
             Color textCol, Color bodyHighCol, Color borderHighCol,
             Color textHighCol);
};


class GuiEntry
{
public:
    // Appearance of the entry
    RectangleShape shape;
    // String returned when the entry is activated
    string message;
    // Text displayed on the entry
    Text text;

    GuiEntry(const string &message, RectangleShape shape, Text text);
};


class Gui : public Transformable, public Drawable
{
private:
    // true if the menu entries will be horizontally adjacent
    bool horizontal;
    GuiStyle style;
    Vector2f dimensions;
    int padding;

public:
    vector<GuiEntry> entries;
    bool visible;

    Gui(Vector2f dimensions, int padding, bool horizontal,
        GuiStyle &style, vector<pair<string, string>> entries);
    Vector2f getSize();
    /** Return the entry that the mouse is hovering over, returns -1 if the
     *  mouse is outside of the Gui **/
    int getEntry(const Vector2f mousePos);
    /** Change the text of an entry. **/
    void setEntryText(int enty, string text);
    /** Change the entry dimensions **/
    void setDimensions(Vector2f dimensions);
    /** Draw the menu **/
    // note-> const at the end means that 'this' is not modified
    virtual void draw(RenderTarget &target, RenderStates states) const;
    void show();
    void hide();
    /** Highlights an entry of the menu **/
    void highlight(const int entry);
    /** Return the message bound to the entry **/
    string activate(const int entry);
    string activate(const Vector2f mousePos);
    
};

#endif // GUI_HPP
