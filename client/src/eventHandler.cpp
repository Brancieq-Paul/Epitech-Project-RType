/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** eventHandler
*/

#include "eventHandler.hpp"
#include <SFML/Window/Mouse.hpp>
#include "window.hpp"

std::map<rtype::utility::keyCode, bool> rtype::eventHandler::EventHandler::_status_keys_map = std::map<rtype::utility::keyCode, bool>();
bool rtype::eventHandler::EventHandler::_isMouseClicked = false;
std::string rtype::eventHandler::EventHandler::_text = "";

std::map<sf::Keyboard::Key, rtype::utility::keyCode> rtype::eventHandler::EventHandler::_keys_map = {
    {sf::Keyboard::Up, rtype::utility::UP},
    {sf::Keyboard::Down, rtype::utility::DOWN},
    {sf::Keyboard::Left, rtype::utility::LEFT},
    {sf::Keyboard::Right, rtype::utility::RIGHT},
    {sf::Keyboard::Escape, rtype::utility::EXIT_ALL},
    {sf::Keyboard::Space, rtype::utility::SPACE}};

void rtype::eventHandler::EventHandler::pollEvents(sf::RenderWindow *window)
{
    sf::Event event;

    _text = "";
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window->close();
            _status_keys_map[rtype::utility::EXIT_ALL] = true;
            break;
        case ::sf::Event::KeyPressed:
            if (_keys_map.find(event.key.code) != _keys_map.end())
            {
                _status_keys_map[_keys_map[event.key.code]] = true;
            }
            break;
        case ::sf::Event::KeyReleased:
            if (_keys_map.find(event.key.code) != _keys_map.end())
            {
                _status_keys_map[_keys_map[event.key.code]] = false;
            }
            break;
        case sf::Event::MouseButtonPressed:
            _isMouseClicked = true;
            break;
        case sf::Event::MouseButtonReleased:
            _isMouseClicked = false;
            break;
        case sf::Event::TextEntered:
            if (event.text.unicode == '\b') {
                _text = "\b";
            } else if (event.text.unicode < 128 && _text != "\b")
                _text += static_cast<char>(event.text.unicode);
            break;
        default:
            break;
        }
    }
}

bool rtype::eventHandler::EventHandler::checkEventKey(rtype::utility::keyCode keycode)
{
    return (_status_keys_map.find(keycode) != _status_keys_map.end() && _status_keys_map[keycode]);
}

bool rtype::eventHandler::EventHandler::isMouseClicked()
{
    return (_isMouseClicked);
}

std::pair<int, int> rtype::eventHandler::EventHandler::getMousePosition()
{
    sf::Vector2i position = sf::Mouse::getPosition(*static_cast<sf::Window *>(rtype::graphique::RWindow::GetInstance()));
    return {position.x, position.y};
}

std::string rtype::eventHandler::EventHandler::getText()
{
    return _text;
}