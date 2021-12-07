/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** eventHandler
*/

#ifndef EVENTHANDLER_HPP_
#define EVENTHANDLER_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <map>
#include <algorithm>
#include "utility.hpp"

namespace rtype
{
    namespace eventHandler
    {
        class EventHandler
        {
        protected:
            inline EventHandler(){};
            inline ~EventHandler(){};

            static bool _isMouseClicked;
            static std::string _text;

        public:
            static void pollEvents(sf::RenderWindow *window);
            static bool checkEventKey(rtype::utility::keyCode);
            static bool isMouseClicked();
            static std::pair<int, int> getMousePosition();
            static std::string getText();

            static std::map<sf::Keyboard::Key, utility::keyCode> _keys_map;
            static std::map<rtype::utility::keyCode, bool> _status_keys_map;
        };
    }
}

#endif /* !EVENTHANDLER_HPP_ */
