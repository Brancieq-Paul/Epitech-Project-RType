/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** entiry
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>

namespace rtype
{
    namespace component
    {
        class IRComponent
        {
        public:
            inline IRComponent(){};
            inline ~IRComponent(){};

            inline virtual void eachFrame(){};
            inline virtual void init(){};
            static inline void initServerType(int type, nlohmann::json json){};
        };
    };
};

#endif /* !COMPONENT_HPP_ */
