/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** RHoldData
*/

#include "ecs/component.hpp"
#include "errInexistantFile.hpp"
#include "window.hpp"
#include "eventHandler.hpp"

void rtype::component::RTextInput::eachFrame()
{
    std::string tmp;
    sf::FloatRect rectPos;

    RMouseHandler::eachFrame();
    if (getData("isHold"))
    {
        changeData("isSelected", 1);
    }
    else if (rtype::eventHandler::EventHandler::isMouseClicked())
    {
        changeData("isSelected", 0);
        _blink_state = false;
    }
    if (getData("isSelected") == 1)
    {
        tmp = rtype::eventHandler::EventHandler::getText();
        if (tmp != "\b")
            changeData("text", getDataTxt("text") + rtype::eventHandler::EventHandler::getText());
        else if (getDataTxt("text").size() >= 1)
            changeData("text", getDataTxt("text").erase(getDataTxt("text").size() - 1, 1));
    }
    if (getDataTxt("text").size() > _limit)
        changeData("text", getDataTxt("text").substr(0, _limit));

    _text.setString(getDataTxt("text"));
    rectPos = _text.getGlobalBounds();
    _rectangle.setPosition({float(_pos.first - 10), float(_pos.second)});
    _rectangle.setSize({float(27*_limit + 25), 45});
    _dims = {27*_limit + 25, 45};
    _offset = {-10, 0};
    rtype::graphique::RWindow::GetInstance()->draw(_rectangle);

    blinkHandler();
    if (_display != _text.getString())
        _text.setString(_display);
    _text.setPosition({float(_pos.first - 10 +_rectangle.getSize().x / 2 - rectPos.width / 2), float(_pos.second)});

    rtype::graphique::RWindow::GetInstance()->draw(_text);
}

void rtype::component::RTextInput::blinkHandler()
{
    _display = getDataTxt("text");
    if (getData("isSelected") == 1)
    {
        if (_blink_clock.deadLinePassed())
        {
            if (_blink_state == 1)
                _blink_state = 0;
            else
                _blink_state = 1;
            _blink_clock.reset();
        }
        if (_blink_state == 1)
            _display += "l";
    }
}