//
// Created by mathi on 07/11/2020.
//

#ifndef RTYPE_DATASPRITE_HPP
#define RTYPE_DATASPRITE_HPP

#include "graphical/ASprite.hpp"
#include "dataHolders/DataTexture.hpp"

class DataSprite : public Engine::ASprite
{
private:
    Engine::Point<float> _position;
    float _rotation;
    Engine::Point<float> _origin;
    Engine::Scale<float> _scale;
    Engine::Box<int> _rect;

public:
    DataSprite() : _position({0, 0}), _rotation(0), _scale({0, 0}), _origin({0, 0}), _rect({0, 0, 0, 0}), Engine::ASprite() {}
    explicit DataSprite(std::shared_ptr<Engine::ATexture> &texture, Engine::Box<int> rect = {0, 0, 0, 0})
    : _position({0, 0}), _rotation(0), _scale({0, 0}), _origin({0, 0}), _rect(rect), Engine::ASprite() {
        setTexture(texture);
    }
    explicit DataSprite(const std::string fileName, Engine::Box<int> rect = {0, 0, 0, 0})
    : _position({0, 0}), _rotation(0), _scale({0, 0}), _origin({0, 0}), _rect(rect), Engine::ASprite() {
        _texture = std::make_shared<DataTexture>(fileName);
        setTexture(_texture);
    }

    void setTexture(std::shared_ptr<Engine::ATexture> &texture) final;
    void setPosition(Engine::Point<float> position);
    [[nodiscard]] Engine::Point<float> getPosition() const;
    void setRotation(float angle);
    [[nodiscard]] float getRotation();
    void setOrigin(Engine::Point<float> origin) override;
    [[nodiscard]] Engine::Point<float> getOrigin() const;
    void setScale(Engine::Scale<float> scale) override;
    [[nodiscard]] Engine::Scale<float> getScale() const;
    void setRect(Engine::Box<int> rect) override;
    [[nodiscard]] Engine::Box<int> getRect() const override;
    [[nodiscard]] Engine::Size<int> getSize() const override;

    void draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<int> position, float angle) override;
};


#endif //RTYPE_DATASPRITE_HPP
