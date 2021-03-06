////////////////////////////////////////////////////////////
//
// Copyright (C) 2014 Maximilian Wagenbach (aka. Foaly) (foaly.f@web.de)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
//
// Modified by 7flying, June 2016
///////////////////////////////////////////////////////////

#include "SpriteAnimation.hpp"

SpriteAnimation::SpriteAnimation() : m_texture(NULL)
{

}

void SpriteAnimation::addFrame(sf::IntRect rect)
{
    m_frames.push_back(rect);
}

void SpriteAnimation::setSpriteSheet(const sf::Texture& texture)
{
    m_texture = &texture;
}

const sf::Texture* SpriteAnimation::getSpriteSheet() const
{
    return m_texture;
}

std::size_t SpriteAnimation::getSize() const
{
    return m_frames.size();
}

const sf::IntRect& SpriteAnimation::getFrame(std::size_t n) const
{
    return m_frames[n];
}
