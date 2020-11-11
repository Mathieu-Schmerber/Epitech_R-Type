//
// Created by mathi on 07/11/2020.
//

#include "DataSprite.hpp"

void DataSprite::setTexture(std::shared_ptr<Engine::ATexture> &texture)
{
    ASprite::setTexture(texture);
}

void DataSprite::setScale(Engine::Scale<float> scale)
{
    _scale = scale;
}

Engine::Scale<float> DataSprite::getScale() const
{
    return _scale;
}

void DataSprite::setRect(Engine::Box<int> rect)
{
    _rect = rect;
}

Engine::Box<int> DataSprite::getRect() const
{
    return _rect;
}

void DataSprite::setPosition(Engine::Point<float> position)
{
    _position = position;
}

Engine::Point<float> DataSprite::getPosition() const
{
    return _position;
}

void DataSprite::setOrigin(Engine::Point<float> origin)
{
    _origin = origin;
}

Engine::Point<float> DataSprite::getOrigin() const
{
    return _origin;
}

void DataSprite::draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<int> position, float angle)
{}

void DataSprite::setRotation(float angle)
{
    _rotation = angle;
}

float DataSprite::getRotation()
{
    return _rotation;
}

Engine::Size<int> DataSprite::getSize() const {
    return {_rect.size.x, _rect.size.y};
}
