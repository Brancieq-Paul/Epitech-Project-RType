/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** RMouseHandler
*/

#include "component.hpp"
#include "eventHandler.hpp"

void rtype::component::RMouseHandler::init()
{
    changeData("isClicked", 0);
    changeData("isHovered", 0);
}

void rtype::component::RMouseHandler::eachFrame()
{
    std::pair<int, int> mousPos = rtype::eventHandler::EventHandler::getMousePosition();
    sf::FloatRect zone = {{float(_pos.first + _offset.first), float(_pos.second + _offset.second)}, {float(_dims.first), float(_dims.second)}};

    changeData("isClicked", 0);
    changeData("isReleased", 0);
    if (zone.contains(float(mousPos.first), float(mousPos.second)))
    {
        changeData("isHovered", 1);
        if (rtype::eventHandler::EventHandler::isMouseClicked()) {
            if (getData("isHold") != 1)
                changeData("isClicked", 1);
            changeData("isHold", 1);
        } else {
            if (getData("isHold") == 1)
                changeData("isReleased", 1);
            changeData("isHold", 0);
        }
    }
    else
    {
        changeData("isHovered", 0);
        changeData("isHold", 0);
    }
}
