/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** window
*/

#include <SFML/Graphics/RenderWindow.hpp>

#pragma once

namespace rtype
{
    namespace graphique
    {
        class RWindow : public sf::RenderWindow
        {
            protected:
                RWindow(sf::VideoMode mode, std::string name): sf::RenderWindow(mode, name) {};

                static RWindow * window_;

            public:
                RWindow(RWindow &other) = delete;
                ~RWindow();

                void operator=(const RWindow &) = delete;

                static RWindow *GetInstance();
                static void init(std::string pathFile);
                static void sendWindowSize();
        };
    };
};