/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** engine
*/

#pragma once

#include "utility.hpp"
#include "eventHandler.hpp"
#include "window.hpp"
#include "ecs/component.hpp"
#include "entityHandler.hpp"

namespace rtype
{
    namespace engine
    {
        class Engine
        {
            public:
                Engine() {};
                inline ~Engine() {};

                void init(std::string ip);
                void run(std::string ip);

            private:
                rtype::graphique::RWindow *_window;
                rtype::utility::keyCode _event;
                rtype::entity::REntityHandler _entity_handler;
        };
    };
};