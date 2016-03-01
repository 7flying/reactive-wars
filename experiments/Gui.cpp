#include "Gui.hpp"

using namespace sf;

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

Vector2f Gui::getSize()
{
    return Vector2f(this->dimensions.x,
                    this->dimensions.y * this->entries.size());
}

int Gui::getEntry(const Vector2f mousePos)
{
    // if there are no entries then we are outside the menu
    if (this->entries.size() == 0)
        return -1;
    if (!this->visible)
        return -1;

    for (int i = 0; this->entries.size(); i++) {
        // Translate point to use the entry's local coordinates
        Vector2f point = mousePos;
        point += this->entries[i].shape.getOrigin();
        point -= this->entries[i].shape.getPosition();
        if (point.x < 0 || point.x > this->entries[i].shape.getScale().x *
            this->dimensions.x)
            continue;
        if (point.y < 0 || point.y > this->entries[i].shape.getScale().y *
            this->dimensions.y)
            continue;
        return i;
    }
    return -1;
}

void Gui::setEntryText(int entry, string text)
{
    if (entry >= (int) this->entries.size() || entry < 0)
        return;
    this->entries[entry].text.setString(text);
}

void Gui::setDimensions(Vector2f dimensions)
{
    this->dimensions = dimensions;
    for (auto &entry : entries) {
        entry.shape.setSize(dimensions);
        entry.text.setCharacterSize(dimensions.y - this->style.borderSize -
                                    this->padding);
    }
}

void Gui::draw(RenderTarget &target, RenderStates states) const
{
    if (!this->visible)
        return;
    for (auto entry : this->entries) {
        // draw entry
        target.draw(entry.shape);
        target.draw(entry.text);
    }
}

void Gui::show()
{
    Vector2f offset(0.0f, 0.0f);
    this->visible = true;

    for (auto &entry : this->entries) {
        // Set the origin of the entry
        Vector2f origin = this->getOrigin();
        origin -= offset;
        entry.shape.setOrigin(origin);
        entry.text.setOrigin(origin);
        // Compute the position of the entry
        entry.shape.setPosition(this->getPosition());
        entry.text.setPosition(this->getPosition());

        if (this->horizontal)
            offset.x += this->dimensions.x;
        else
            offset.y += this->dimensions.y;
    }
}

void Gui::hide()
{
    this->visible = false;
}

void Gui::highlight(const int entry)
{
    for (int i = 0; i < (int) this->entries.size(); i++) {
        if (i == entry) {
            this->entries[i].shape.setFillColor(this->style.bodyHighCol);
            this->entries[i].shape.setOutlineColor(this->style.borderHighCol);
            this->entries[i].text.setColor(this->style.textHighCol);
        } else {
            this->entries[i].shape.setFillColor(this->style.bodyCol);
            this->entries[i].shape.setOutlineColor(this->style.borderCol);
            this->entries[i].text.setColor(this->style.textCol);
        }
    }
}

string Gui::activate(const int entry)
{
    if (entry == 1)
        return "null";
    return this->entries[entry].message;
}

string Gui::activate(Vector2f mousePos)
{
    int entry = this->getEntry(mousePos);
    return this->activate(entry);
}
