/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** entiry
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <vector>
#include <utility>
#include <iostream>
#include "window.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "ecs/clock.hpp"
#include "SfmlUDP.hpp"
#include "ecs/Acomponent.hpp"
#include "myJson.hpp"

namespace rtype
{
    namespace component
    {
        class RHoldData : public virtual IRComponent
        {
        public:
            inline RHoldData() : IRComponent(){};
            inline ~RHoldData(){};

            virtual void eachFrame() override{};

            inline void setData(nlohmann::json *dataSet) { _data = dataSet; };
            inline nlohmann::json *getDataList() const { return _data; };
            int getData(std::string _data_key);
            std::string getDataTxt(std::string _data_key);
            void changeData(std::string key, int dataint) { (*_data)["data"][key] = dataint; };
            void changeData(std::string key, std::string datatxt)
            {
                (*_data)["data_txt"][key] = datatxt;
            };

            static inline void initServerType(int type, nlohmann::json json){};

        protected:
            nlohmann::json *_data;
        };

        class RPlaceable : public virtual RHoldData
        {
        public:
            inline RPlaceable() : RHoldData(), _pos(std::pair<int, int>(0, 0)){};
            inline ~RPlaceable(){};

            virtual inline void changePos(std::pair<int, int> pos) {_pos = pos; };
            virtual inline std::pair<int, int> getPos() const { return _pos; };

            virtual void eachFrame() override{};

            static inline void initServerType(int type, nlohmann::json json){};

        protected:
            std::pair<int, int> _pos;
        };

        class RCollider : public virtual RPlaceable
        {
        public:
            inline RCollider() : RPlaceable(), _dims(std::pair<int, int>(0, 0)), _offset(std::pair<int, int>(0, 0)){};
            inline ~RCollider(){};

            virtual inline void changeDims(std::pair<int, int> dims) { _dims = dims; };
            virtual inline std::pair<int, int> getDims() const { return _dims; };

            virtual inline void changeOffset(std::pair<int, int> offset) { _offset = offset; };
            virtual inline std::pair<int, int> getOffset() const { return _offset; };

            virtual void eachFrame() override{};

            static void initServerType(int type, nlohmann::json json);

        protected:
            std::pair<int, int> _dims;
            std::pair<int, int> _offset;
        };

        class RDrawable : public virtual RPlaceable
        {
        public:
            inline RDrawable() : RPlaceable(), _isHidden(false), _window(rtype::graphique::RWindow::GetInstance()){};
            inline ~RDrawable(){};

            virtual inline void hide() { _isHidden = true; };
            virtual inline void show() { _isHidden = false; };

            void loadFromFile(std::string filepath, bool isRepeated = false);
            void draw();

            virtual void eachFrame() override;

            static inline void initServerType(int type, nlohmann::json json){};

            virtual void changePos(std::pair<int, int> pos) override;
            inline void setParaVel(int vel) { para_vel = vel; };

        private:
            bool _isHidden;
            int para_vel;

            rtype::graphique::RWindow *_window;

            sf::Texture _texture;
            sf::Sprite _sprite;
        };

        class RMovable : public virtual RHoldData
        {
        public:
            RMovable();
            inline ~RMovable(){};

            inline void block() { _is_blocked = true; };
            inline void unBlock() { _is_blocked = false; };

            virtual void eachFrame() override;

            inline void setVelocity(int x, int y) { _velocity = std::pair<int, int>(x, y); };

            static void initServerType(int type, nlohmann::json json);

        private:
            bool _is_blocked;
            rtype::clock::RClock _clock;
            std::pair<int, int> _velocity;
        };

        class RMouseHandler : public virtual RCollider
        {
        public:
            inline RMouseHandler() : RCollider(){};

            virtual void init() override;
            virtual void eachFrame() override;

            static inline void initServerType(int type, nlohmann::json json){};
        };

        class RText : public virtual RPlaceable, public virtual RMouseHandler
        {
        public:
            inline RText() : RPlaceable(), RMouseHandler(){};

            virtual void eachFrame() override;
            virtual void init() override
            {
                RMouseHandler::init();
                changeData("text", _tempo);
                _text.setPosition({0, 0});
            };

            virtual inline void setText(std::string newText) { changeData("text", newText); };
            virtual void setFont(std::string pathFile);
            inline void setColor(sf::Color color) { _text.setFillColor(color); };

            static inline void initServerType(int type, nlohmann::json json){};

            std::string _tempo;

        protected:
            sf::Text _text;
            sf::Font _font;
        };

        class RTextInput : public virtual RText
        {
        public:
            inline RTextInput() : RText(), _blink_clock(rtype::clock::RClock(500)){};

            virtual void eachFrame() override;

            void blinkHandler();

            inline void setLimit(int limit) { _limit = limit; };
            inline sf::RectangleShape *getRect(){ return(&_rectangle); };
            inline sf::Text *getText(){ return(&_text); };

            static inline void initServerType(int type, nlohmann::json json){};

        protected:
            rtype::clock::RClock _blink_clock;
            bool _blink_state;
            std::string _display;
            int _limit;
            sf::RectangleShape _rectangle;
        };
    };
};

#endif /* !COMPONENT_HPP_ */
