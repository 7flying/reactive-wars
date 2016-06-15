#include "Tile.hpp"


Tile::Tile() {}

Tile::Tile(const unsigned int tileSize, const unsigned int height,
           Texture &texture, const vector<Animation> &animations,
           const TileType tileType, int defence, int avoid, int movement)
{
    this->tileType = tileType;
    this->tileVariant = 0;
    this->regions[0] = 0;
    this->defence = defence;
    this->avoid = avoid;
    this->movement = movement;

    this->sprite.setOrigin(Vector2f(0.0f, tileSize * (height - 1)));
    this->sprite.setTexture(texture);
    this->animHandler.frameSize = IntRect(0, 0, tileSize * 2, tileSize * height);
    for (auto animation : animations)
        this->animHandler.addAnim(animation);
    this->animHandler.update(0.0f);
}

void Tile::draw(RenderWindow &window, float dt)
{
    // change the sprite to reflect the tile variant
    this->animHandler.changeAnim(this->tileVariant);
    // update animation
    this->animHandler.update(dt);
    // update the sprite
    this->sprite.setTextureRect(this->animHandler.bounds);
    // Draw tile
    window.draw(this->sprite);
}

void Tile::update()
{
    /*
    // -- here the tutorial 'evolutionates' the tiles depending on the
    // population level
    if ((this->tileType == TileType::RESIDENTIAL ||
         this->tileType == TileType::COMMERCIAL ||
         this->tileType == TileType::INDUSTRIAL) &&
        this->population == this->maxPopPerLevel * (this->tileVariant + 1) &&
        this->tileVariant < (int) this->maxLevels)
    {
        if (rand() % int(1e4) < 1e2 / (this->tileVariant + 1))
            ++this->tileVariant;
    }
    */
}

string tileTypeToStr(TileType type)
{
    switch (type) {
    default:
    case TileType::VOID:            return "Void";
    case TileType::GRASS:           return "Plain";
    case TileType::GRASS1:          return "Plain";
    case TileType::GRASS2:          return "Forest";
    case TileType::GRASS3:          return "Forest";
    case TileType::MOUNTAIN:        return "Sand";
    case TileType::MOUNTAIN1:       return "Mountain";
    case TileType::WATER:           return "Water";
    case TileType::WATER1:          return "Water";
    case TileType::WATER2:          return "Deep Water";
   
    case TileType::FOREST:          return "Forest";
    case TileType::RESIDENTIAL:     return "Residential Zone";
    case TileType::COMMERCIAL:      return "Commercial Zone";
    case TileType::INDUSTRIAL:      return "Industrial Zone";
    }
}
