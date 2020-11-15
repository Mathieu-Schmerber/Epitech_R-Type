/*!
 * @file WindowSFML.hpp
 * @brief Manage SFML's window
 * @authors Cyprien.R
 * @version 1.0
 * @date 14/11/2020
 *
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
    /*!
     * \brief Window SFML constructor with title and size
     * \param title window's title to be set
     * \param windowSize X and Y size (in pixels)
     *
     * Create a window with the above parameters
    */
    WindowSFML(const std::string &title, const Engine::Size<double> windowSize) : Engine::AWindow(title, windowSize),
    _titleSFML(title.data()) {}
    /*!
     * \brief Window SFML default destructor
     *
     *
    */
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
