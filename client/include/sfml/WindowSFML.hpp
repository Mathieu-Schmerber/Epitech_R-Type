/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_WINDOWSFML_HPP
#define RTYPE_WINDOWSFML_HPP

#include "tools/Geometry.hpp"
#include "graphical/AWindow.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Color.hpp"

class WindowSFML : public Engine::AWindow {
public:
    WindowSFML(const std::string &title, const Engine::Size<double> windowSize) : Engine::AWindow(title, windowSize),
    _titleSFML(title.data()) {}
    ~WindowSFML() = default;

    void open() override;
    bool isOpen() override;
    void display() override;
    void close() override;

    void setTitle(const std::string &title) override;
    void setFrameRate(int frameRate) override;
    void setVsync(bool sync) override;

    [[nodiscard]] int getFrameRate() const override;
    [[nodiscard]] bool getVsync() const override;
    [[nodiscard]] Engine::Size<double> getSize() const override;

    friend class SpriteSFML;
    friend class TextSFML;
    friend class EventsSFML;

private:
    std::unique_ptr<sf::RenderWindow> &getWindow();

    std::unique_ptr<sf::RenderWindow> _window = nullptr;
    sf::String _titleSFML;
};


#endif //RTYPE_WINDOWSFML_HPP
