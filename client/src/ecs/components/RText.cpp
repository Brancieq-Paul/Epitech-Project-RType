/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** RHoldData
*/

#include "ecs/component.hpp"
#include "errInexistantFile.hpp"
#include "window.hpp"

void rtype::component::RText::setFont(std::string pathFile)
{
    if (!_font.loadFromFile(pathFile))
    {
        throw ErrorInexistantFile(pathFile, __FILE__, __LINE__);
    }
    _text.setFont(_font);
}

void rtype::component::RText::eachFrame()
{
    std::string txt = getDataTxt("text");
    if (txt != _text.getString())
        _text.setString(getDataTxt("text"));
    _text.setPosition({float(_pos.first), float(_pos.second)});
    rtype::graphique::RWindow::GetInstance()->draw(_text);
}