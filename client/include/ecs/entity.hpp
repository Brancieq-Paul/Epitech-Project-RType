/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** entity
*/

#pragma once

#include <vector>
#include <map>
#include <iostream>
#include "ecs/Acomponent.hpp"
#include "myJson.hpp"

namespace rtype
{
    namespace entity
    {
        class REntity
        {
        public:
            inline REntity() {_data = nullptr; };
            inline ~REntity() {/*if (_data != nullptr) { delete _data; }*/ };

            void eachFrame();
            void init();
            void attach(rtype::component::IRComponent *component) { _components.push_back(component); };

            void changePos(std::pair<int, int> newPos);
            void unblockInput();

            inline void activate(){ _activated = true; };
            inline void deactivate(){ _activated = false; };

            void setData(nlohmann::json *j);
            inline nlohmann::json *getDataList() { return _data; };
            int getData(std::string _data_key);
            std::string getDataTxt(std::string _data_key);
            void changeData(std::string key, int data) { (*_data)["data"][key] = data; };
            void changeData(std::string key, std::string data) { (*_data)["data_txt"][key] = data; };

            bool _activated;
            int _handle_layer;
        private:
            nlohmann::json *_data;
            std::vector<rtype::component::IRComponent *> _components;

        };
    };
};