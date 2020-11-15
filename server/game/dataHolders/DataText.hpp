/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_DATATEXT_HPP
#define RTYPE_DATATEXT_HPP


#include "graphical/AText.hpp"
#include "dataHolders/DataFont.hpp"
#include <memory>
#include <utility>

class DataText : public Engine::AText
{
private:
    Engine::Point<double> _position = {0, 0};
    double _rotation = 0;
    Engine::Point<double> _origin = {0, 0};
    Engine::Point<double> _scale = {0, 0};
    std::string _text = "../../client/assets/textsEdt/Basic.txt";
    int _characterSize = 30;
    Engine::Color _fillColor = {0, 0, 0, 255};
    Engine::Color _outLineColor = {0, 0, 0, 255};
    double _letterSpacing = 30;
    double _lineSpacing = 10;

public:
    DataText() = default;
    DataText(std::string text, std::shared_ptr<DataFont> &font, Engine::Point<double> position) : _text(std::move(text)), _position(position), Engine::AText() {
        setFont(font);
    }
    DataText(std::shared_ptr<DataFont> font, Engine::Point<double> position) : _position(position), Engine::AText() {
        setFont(font);
    }

    std::shared_ptr<DataFont> getFont() {return std::dynamic_pointer_cast<DataFont>(_font);}
    void setFont(std::shared_ptr<DataFont> &font) {_font = font;}
    [[nodiscard]] Engine::Point<double> getPosition() const override {return _position;}
    void setPosition(Engine::Point<double> position) override {_position = position;}
    [[nodiscard]] Engine::Point<double> getOrigin() const  {return _origin;}
    void setOrigin(const Engine::Point<double> origin) final {_origin  = origin;}
    void setScale(Engine::Size<double> scale) final {_scale = scale;}
    void setFillColor(Engine::Color color) final {_fillColor = color;}
    void setOutlineColor(Engine::Color color) final {_outLineColor = color;}
    void setString(std::string text) final {_text = text;}
    void setRotation(double angle) final {_rotation = angle;}
    void setCharacterSize(unsigned int size) final {_characterSize = size;}
    void setLetterSpacing(double spacingFactor) final {_letterSpacing = spacingFactor;}
    void setLineSpacing(double spacingFactor) final {_lineSpacing = spacingFactor;}
    [[nodiscard]] Engine::Size<int> getSize() const final {return Engine::Size<int>{0, 0};}
    [[nodiscard]] double getRotation() const final {return _rotation;}
    [[nodiscard]] std::string toStdString() const final {return _text;}
    [[nodiscard]] int getCharacterSize() const final {return _characterSize;}
    [[nodiscard]] int getLetterSpacing() const final {return static_cast<int>(_letterSpacing);}
    [[nodiscard]] Engine::Color getFillColor() const final {return _fillColor;}

    void draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<double> position, double angle) final {}

};

#endif //RTYPE_DATATEXT_HPP
