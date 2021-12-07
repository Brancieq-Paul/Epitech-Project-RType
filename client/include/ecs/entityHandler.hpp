/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** entity
*/

#pragma once

#include "entity.hpp"
#include <map>
#include "compoFactory.hpp"

namespace rtype
{
    namespace entity
    {
        class REntityHandler
        {
        public:
            REntityHandler(std::string dirPath, bool serverHandle = false);
            inline REntityHandler() {};
            inline ~REntityHandler(){};


            void init(std::string dirpath, bool serverHandle = false);
            void createEntity(int type, int id);
            void destroyEntity(int type, int id);

            rtype::entity::REntity *getEntity(int type, int id);

            void eachFrame();

            std::vector<rtype::entity::REntity> *getTab() { return &entity_tab_; };

            void initServerTypes();

        private:
            std::vector<rtype::entity::REntity> entity_tab_;
            std::map<int, std::string> entity_def_json_tab_;
        };
    };
};