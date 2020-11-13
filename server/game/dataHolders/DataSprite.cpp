//
// Created by mathi on 07/11/2020.
//

#include "DataSprite.hpp"

void DataSprite::setTexture(std::shared_ptr<Engine::ATexture> &texture)
{
    ASprite::setTexture(texture);
}

void DataSprite::setScale(Engine::Scale<double> scale)
{
    _scale = scale;
}

Engine::Scale<double> DataSprite::getScale() const
{
    return _scale;
}

void DataSprite::setRect(Engine::Box<double> rect)
{
    _rect = rect;
}

Engine::Box<double> DataSprite::getRect() const
{
    return _rect;
}

void DataSprite::setPosition(Engine::Point<double> position)
{
    _position = position;
}

Engine::Point<double> DataSprite::getPosition() const
{
    return _position;
}

void DataSprite::setOrigin(Engine::Point<double> origin)
{
    _origin = origin;
}

Engine::Point<double> DataSprite::getOrigin() const
{
    return _origin;
}

void DataSprite::draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<double> position, double angle)
{}

void DataSprite::setRotation(double angle)
{
    _rotation = angle;
}

double DataSprite::getRotation()
{
    return _rotation;
}

Engine::Size<double> DataSprite::getSize() const {
    return {_rect.size.x, _rect.size.y};
}
