/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** RDrawable
*/

#include "ecs/component.hpp"
#include "clientErrors/errInexistantFile.hpp"

void rtype::component::RDrawable::loadFromFile(std::string filepath, bool isRepeated)
{
    sf::Vector2u _vector;
    if (!_texture.loadFromFile(filepath))
    {
        throw ErrorInexistantFile(filepath, __FILE__, __LINE__);
    }
    if (isRepeated)
    {
        _texture.setRepeated(true);
        _vector = rtype::graphique::RWindow::GetInstance()->getSize();
        _sprite.setTextureRect({0, 0, int(_vector.x), int(_vector.y)});
    }
    _sprite.setTexture(_texture);
}

void rtype::component::RDrawable::draw()
{
    std::pair<int, int> pos = getPos();
    _sprite.setPosition(sf::Vector2f(pos.first, pos.second));
    _window->draw(_sprite);
}

void rtype::component::RDrawable::eachFrame()
{
    std::map<std::string, sf::Color> _color_map = {{"black", sf::Color::Black},
                                                   {"blue", sf::Color::Blue},
                                                   {"green", sf::Color::Green},
                                                   {"red", sf::Color::Red},
                                                   {"white", sf::Color::White},
                                                   {"yellow", sf::Color::Yellow},
                                                   {"magenta", sf::Color::Magenta}};
    std::string color;

    if (_texture.isRepeated())
    {
        changePos({_sprite.getTextureRect().left + para_vel, _sprite.getTextureRect().top});
    }
    color = getDataTxt("color");
    if (color == "" || _color_map.find(color) == _color_map.end())
        color = "white";
    _sprite.setColor(_color_map[color]);
    draw();
}

void rtype::component::RDrawable::changePos(std::pair<int, int> pos)
{
    if (!_texture.isRepeated())
        _pos = pos;
    else
    {
        _sprite.setTextureRect({pos.first, pos.second, _sprite.getTextureRect().width, _sprite.getTextureRect().height});
    }
}
