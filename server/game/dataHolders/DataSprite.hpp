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
    Engine::Box<float> _rect;

public:
    DataSprite() : _position({0, 0}), _rotation(0), _scale({0, 0}), _origin({0, 0}), _rect({0, 0, 0, 0}), Engine::ASprite() {}
    explicit DataSprite(std::shared_ptr<Engine::ATexture> &texture, Engine::Box<float> rect = {0, 0, 0, 0})
    : _position({0, 0}), _rotation(0), _scale({0, 0}), _origin({0, 0}), _rect(rect), Engine::ASprite() {
        setTexture(texture);
    }
    explicit DataSprite(const std::string fileName, Engine::Box<float> rect = {0, 0, 0, 0})
    : _position({0, 0}), _rotation(0), _scale({0, 0}), _origin({0, 0}), _rect(rect), Engine::ASprite() {
        _texture = std::make_shared<DataTexture>(fileName);
        setTexture(_texture);
    }

    void setTexture(std::shared_ptr<Engine::ATexture> &texture) final;
    void setPosition(Engine::Point<float> position);
    [[nodiscard]] Engine::Point<float> getPosition() const override;
    void setRotation(float angle);
    [[nodiscard]] float getRotation();
    void setOrigin(Engine::Point<float> origin) override;
    [[nodiscard]] Engine::Point<float> getOrigin() const override;
    void setScale(Engine::Scale<float> scale) override;
    [[nodiscard]] Engine::Scale<float> getScale() const;
    void setRect(Engine::Box<float> rect) override;
    [[nodiscard]] Engine::Box<float> getRect() const override;
    [[nodiscard]] Engine::Size<float> getSize() const override;

    void draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<float> position, float angle) override;
};


#endif //RTYPE_DATASPRITE_HPP
