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
    Engine::Point<double> _position;
    double _rotation;
    Engine::Point<double> _origin;
    Engine::Scale<double> _scale;
    Engine::Box<double> _rect;

public:
    DataSprite() : _position({0, 0}), _rotation(0), _scale({0, 0}), _origin({0, 0}), _rect({0, 0, 0, 0}), Engine::ASprite() {}
    explicit DataSprite(std::shared_ptr<Engine::ATexture> &texture, Engine::Box<double> rect = {0, 0, 0, 0})
    : _position({0, 0}), _rotation(0), _scale({0, 0}), _origin({0, 0}), _rect(rect), Engine::ASprite() {
        setTexture(texture);
    }
    explicit DataSprite(const std::string fileName, Engine::Box<double> rect = {0, 0, 0, 0})
    : _position({0, 0}), _rotation(0), _scale({0, 0}), _origin({0, 0}), _rect(rect), Engine::ASprite() {
        _texture = std::make_shared<DataTexture>(fileName);
        setTexture(_texture);
    }

    void setTexture(std::shared_ptr<Engine::ATexture> &texture) final;
    void setPosition(Engine::Point<double> position);
    [[nodiscard]] Engine::Point<double> getPosition() const override;
    void setRotation(double angle);
    [[nodiscard]] double getRotation();
    void setOrigin(Engine::Point<double> origin) override;
    [[nodiscard]] Engine::Point<double> getOrigin() const override;
    void setScale(Engine::Scale<double> scale) override;
    [[nodiscard]] Engine::Scale<double> getScale() const;
    void setRect(Engine::Box<double> rect) override;
    [[nodiscard]] Engine::Box<double> getRect() const override;
    [[nodiscard]] Engine::Size<double> getSize() const override;

    void draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<double> position, double angle) override;
};


#endif //RTYPE_DATASPRITE_HPP
