/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** compoFactory
*/

#include "ecs/compoFactory.hpp"
#include "clientErrors/errJsonData.hpp"

std::map<std::string, rtype::component::builder> rtype::component::CompoFactory::_builders{
    {"drawable", &rtype::component::CompoFactory::makeDrawable},
    {"movable", &rtype::component::CompoFactory::makeMovable},
    {"MouseHandler", &rtype::component::CompoFactory::makeMouseHandler},
    {"text", &rtype::component::CompoFactory::makeText},
    {"textInput", &rtype::component::CompoFactory::makeTextInput},
    {"collider", &rtype::component::CompoFactory::makeCollider}};

rtype::Json rtype::component::CompoFactory::getDef(rtype::Json json)
{
    return json["def"];
}

std::string rtype::component::CompoFactory::getType(rtype::Json json)
{
    return json.value("/type"_json_pointer, "");
}

rtype::component::IRComponent *rtype::component::CompoFactory::makeComponent(rtype::Json json)
{
    IRComponent *res = nullptr;
    std::string type = getType(json);
    if (type == "")
    {
        throw ErrorJsonData("Type of component non specified.", __FILE__, __LINE__);
    }
    if (_builders.find(type) == _builders.end())
    {
        throw ErrorJsonData("Invalid type of component: " + type, __FILE__, __LINE__);
    }
    res = (*_builders[type])(json);
    return (res);
}

rtype::component::IRComponent *rtype::component::CompoFactory::makeDrawable(rtype::Json json)
{
    rtype::component::RDrawable *compo = new rtype::component::RDrawable();
    rtype::Json def = getDef(json);
    bool isRepeated;
    int paralax_vel;

    std::string texture = def.value("/texture"_json_pointer, "");
    if (texture == "")
    {
        throw ErrorJsonData("Path to texture invalid.", __FILE__, __LINE__);
    }
    paralax_vel = def.value("/para_vel"_json_pointer, 0);
    isRepeated = def.value("/repeated"_json_pointer, false);
    compo->setParaVel(paralax_vel);
    compo->loadFromFile("client/rsrc/images/" + texture, isRepeated);
    return compo;
}

rtype::component::IRComponent *rtype::component::CompoFactory::makeMovable(rtype::Json json)
{
    rtype::component::RMovable *compo = new rtype::component::RMovable();
    rtype::Json def = getDef(json);
    int vel_x;
    int vel_y;

    vel_x = def.value("/vel_x"_json_pointer, 0);
    vel_y = def.value("/vel_y"_json_pointer, 0);
    compo->setVelocity(vel_x, vel_y);
    return compo;
}

rtype::component::IRComponent *rtype::component::CompoFactory::makeMouseHandler(rtype::Json json)
{
    rtype::component::RMouseHandler *compo = new rtype::component::RMouseHandler();
    rtype::Json def = getDef(json);
    int dim_x;
    int dim_y;
    int offset_x;
    int offset_y;

    dim_x = def.value("/dim_x"_json_pointer, -1);
    if (dim_x == -1)
    {
        throw ErrorJsonData("Path to dim_x invalid.", __FILE__, __LINE__);
    }
    dim_y = def.value("/dim_y"_json_pointer, -1);
    if (dim_y == -1)
    {
        throw ErrorJsonData("Path to dim_y invalid.", __FILE__, __LINE__);
    }
    offset_x = def.value("/offset_x"_json_pointer, -1);
    if (offset_x == -1)
    {
        throw ErrorJsonData("Path to offset_x invalid.", __FILE__, __LINE__);
    }
    offset_y = def.value("/offset_y"_json_pointer, -1);
    if (offset_y == -1)
    {
        throw ErrorJsonData("Path to offset_y invalid.", __FILE__, __LINE__);
    }
    compo->changeDims({dim_x, dim_y});
    compo->changeOffset({offset_x, offset_y});
    return compo;
}

rtype::component::IRComponent *rtype::component::CompoFactory::makeCollider(rtype::Json json)
{
    rtype::component::RCollider *compo = new rtype::component::RCollider();
    rtype::Json def = getDef(json);
    int dim_x;
    int dim_y;
    int offset_x;
    int offset_y;

    dim_x = def.value("/dim_x"_json_pointer, -1);
    if (dim_x == -1)
    {
        throw ErrorJsonData("Path to dim_x invalid.", __FILE__, __LINE__);
    }
    dim_y = def.value("/dim_y"_json_pointer, -1);
    if (dim_y == -1)
    {
        throw ErrorJsonData("Path to dim_y invalid.", __FILE__, __LINE__);
    }
    offset_x = def.value("/offset_x"_json_pointer, -1);
    if (offset_x == -1)
    {
        throw ErrorJsonData("Path to offset_x invalid.", __FILE__, __LINE__);
    }
    offset_y = def.value("/offset_y"_json_pointer, -1);
    if (offset_y == -1)
    {
        throw ErrorJsonData("Path to offset_y invalid.", __FILE__, __LINE__);
    }
    compo->changeDims({dim_x, dim_y});
    compo->changeOffset({offset_x, offset_y});
    return compo;
}

rtype::component::IRComponent *rtype::component::CompoFactory::makeText(rtype::Json json)
{
    rtype::component::RText *compo = new rtype::component::RText();
    rtype::Json def = getDef(json);
    std::string text;
    std::string font;
    std::string color;
    std::map<std::string, sf::Color> _color_map = {{"black", sf::Color::Black},
                                                   {"blue", sf::Color::Blue},
                                                   {"green", sf::Color::Green},
                                                   {"red", sf::Color::Red},
                                                   {"white", sf::Color::White},
                                                   {"yellow", sf::Color::Yellow},
                                                   {"magenta", sf::Color::Magenta}
                                                   };

    text = def.value("/text"_json_pointer, "&");
    if (text == "&")
    {
        throw ErrorJsonData("Path to text invalid.", __FILE__, __LINE__);
    }
    font = def.value("/font"_json_pointer, "&");
    if (font == "&")
    {
        throw ErrorJsonData("Path to font invalid.", __FILE__, __LINE__);
    }
    color = def.value("/color"_json_pointer, "white");
    if (_color_map.find(color) == _color_map.end())
        throw ErrorJsonData("Color '" + color + "' invalid.", __FILE__, __LINE__);
    compo->_tempo = text;
    compo->setFont("./client/rsrc/fonts/" + font);
    compo->setColor(_color_map[color]);
    return compo;
}

rtype::component::IRComponent *rtype::component::CompoFactory::makeTextInput(rtype::Json json)
{
    rtype::component::RTextInput *compo = new rtype::component::RTextInput();
    rtype::Json def = getDef(json);
    std::string text;
    std::string font;
    std::string rectColor;
    std::string rectBorderColor;
    std::string color;
    std::map<std::string, sf::Color> _color_map = {{"black", sf::Color::Black},
                                                   {"blue", sf::Color::Blue},
                                                   {"green", sf::Color::Green},
                                                   {"red", sf::Color::Red},
                                                   {"white", sf::Color::White},
                                                   {"yellow", sf::Color::Yellow},
                                                   {"magenta", sf::Color::Magenta}
                                                   };
    int limit;

    text = def.value("/text"_json_pointer, "&");
    if (text == "&")
        throw ErrorJsonData("Path to text invalid.", __FILE__, __LINE__);
    font = def.value("/font"_json_pointer, "&");
    if (font == "&")
        throw ErrorJsonData("Path to font invalid.", __FILE__, __LINE__);

    rectColor = def.value("/rectColor"_json_pointer, "&");
    if (rectColor == "&")
        throw ErrorJsonData("Path to rectColor invalid.", __FILE__, __LINE__);
    if (_color_map.find(rectColor) == _color_map.end())
        throw ErrorJsonData("Color '" + rectColor + "' invalid.", __FILE__, __LINE__);

    rectBorderColor = def.value("/rectBorderColor"_json_pointer, "&");
    if (rectBorderColor == "&")
        throw ErrorJsonData("Path to rectBorderColor invalid.", __FILE__, __LINE__);
    if (_color_map.find(rectBorderColor) == _color_map.end())
        throw ErrorJsonData("Color '" + rectBorderColor + "' invalid.", __FILE__, __LINE__);

    color = def.value("/color"_json_pointer, "&");
    if (color == "&")
        throw ErrorJsonData("Path to color invalid.", __FILE__, __LINE__);
    if (_color_map.find(color) == _color_map.end())
        throw ErrorJsonData("Color '" + color + "' invalid.", __FILE__, __LINE__);

    limit = def.value("/limit"_json_pointer, 0);
    if (font == "&")
        throw ErrorJsonData("Path to font invalid.", __FILE__, __LINE__);
    compo->setLimit(limit);
    compo->_tempo = text;
    compo->setFont("./client/rsrc/fonts/" + font);
    compo->getRect()->setFillColor(_color_map[rectColor]);
    compo->getRect()->setOutlineColor(_color_map[rectBorderColor]);
    compo->getRect()->setOutlineThickness(5);
    compo->getText()->setFillColor(_color_map[color]);
    return compo;
}