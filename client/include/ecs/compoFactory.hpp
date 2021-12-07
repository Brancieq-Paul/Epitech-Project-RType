/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** compoFactory
*/

#pragma once

#include "myJson.hpp"
#include "ecs/component.hpp"
#include <map>

namespace rtype
{
    namespace component
    {
        using builder = rtype::component::IRComponent *(*) (rtype::Json);
        class CompoFactory
        {
            public:
                static IRComponent *makeComponent(rtype::Json json);

            private:
                static std::map<std::string, builder> _builders;

                static rtype::Json getDef(rtype::Json json);
                static std::string getType(rtype::Json json);


                static rtype::component::IRComponent *makeDrawable(rtype::Json);
                static rtype::component::IRComponent *makeMovable(rtype::Json);
                static rtype::component::IRComponent *makeMouseHandler(rtype::Json);
                static rtype::component::IRComponent *makeText(rtype::Json);
                static rtype::component::IRComponent *makeTextInput(rtype::Json);
                static rtype::component::IRComponent *makeCollider(rtype::Json);
        };
    };
};