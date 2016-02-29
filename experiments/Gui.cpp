#include "Gui.hpp"


GuiStyle::GuiStyle(Font *font, float borderSize, Color bodyCol, Color borderCol,
                   Color textCol, Color bodyHighCol, Color borderHighCol,
                   Color textHighCol)
{
    this->font = font;
    this->borderSize = borderSize;
    this->bodyCol = bodyCol;
    this->borderCol = borderCol;
    this->textCol = textCol;
    this->bodyHighCol = bodyHighCol;
    this->borderHighCol = borderHighCol;
    this->textHighCol = textHighCol;
}

GuiEntry::GuiEntry(const string &message, RectangleShape shape, Text text)
{
    this->message = message;
    this->shape = shape;
    this->text = text;
}

Gui::Gui(Vector2f dimensions, int padding, bool horizontal,
         GuiStyle &style, vector<pair<string, string>> entries)
{
    this->visible = false;
    this->style = style;
    this->dimensions = dimensions;
    this->padding = padding;
    // construct the background shape
    RectangleShape shape;
    shape.setSize(this->dimensions);
    shape.setFillColor(this->style.bodyCol);
    shape.setOutlineThickness(-this->style.borderSize);
    shape.setOutlineColor(this->style.borderCol);
    // construct each gui entry
    for (auto entry : entries) {
        Text text;
        text.setString(entry.first);
        text.setFont(*this->style.font);
        text.setColor(this->style.textCol);
        text.setCharacterSize(this->dimensions.y - this->style.borderSize
                              - padding);
        this->entries.push_back(GuiEntry(entry.second, shape, text));
    }
}
