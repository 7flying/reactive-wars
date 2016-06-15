#include "Tile.hpp"
#include <iostream>


Tile::Tile() {}

Tile::Tile(const unsigned int tileSize, const unsigned int height,
           Texture &texture, const vector<Animation> &animations,
           const TileType tileType)
{
    this->tileType = tileType;
    this->tileVariant = 0;
    this->regions[0] = 0;
    switch (tileType) {
    case TileType::GRASS:
    case TileType::GRASS1:
        this->defence = 0;
        this->avoid = 0;
        this->movement = 1;
        break;
    case TileType::GRASS2:
    case TileType::GRASS3:
        this->defence = 0;
        this->avoid = 10;
        this->movement = 1;
        break;
    case TileType::MOUNTAIN:
        this->defence = 0;
        this->avoid = -10;
        this->movement = 1;
        break;
    case TileType::MOUNTAIN1:
        this->defence = 5;
        this->avoid = 10;
        this->movement = 1;
        break;
    case TileType::WATER:
    case TileType::WATER1:
    case TileType::WATER2:
        this->defence = 0;
        this->avoid = -15;
        this->movement = 1;
        break;
    default:
        this->defence = 0;
        this->avoid = 0;
        this->movement = 1;
        break;
    }

    this->sprite.setOrigin(Vector2f(0.0f, tileSize * (height - 1)));
    this->sprite.setTexture(texture);
    if (tileType == TileType::REDSOLDIER || tileType == TileType::BLACKSOLDIER) {
        this->animHandler.frameSize = IntRect(0, 0, tileSize, tileSize * 2);
    } else {
        this->animHandler.frameSize = IntRect(0, 0, tileSize * 2, tileSize * height);
    }
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
