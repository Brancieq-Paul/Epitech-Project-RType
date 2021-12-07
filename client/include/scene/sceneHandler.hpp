/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** sceneHandler
*/

#ifndef SCENEHANDLER_HPP_
#define SCENEHANDLER_HPP_

#include <vector>
#include "component.hpp"
#include "eventHandler.hpp"
#include "entityHandler.hpp"

namespace rtype
{
    namespace scene
    {

        class sceneScreen
        {
        public:
            sceneScreen(int id);
            inline ~sceneScreen(){};
            inline int getId() { return _id; };
            inline virtual void goScene(int *scene) {};

        protected:
            int _id;
            rtype::entity::REntityHandler entity_handler_;
            rtype::network::SfmlTCP *_sessionTCP;
        };

        class sceneMenu : public sceneScreen
        {
            public:
            sceneMenu(int id);
            inline ~sceneMenu(){};
            void goScene(int *scene) override;
        };

        class sceneSalon: public sceneScreen
        {
            public:
            sceneSalon(int id);
            inline ~sceneSalon(){};
            void goScene(int *scene) override;
            private:
                bool _triggerWindow;
        };

        class sceneName: public sceneScreen
        {
            public:
            sceneName(int id);
            inline ~sceneName(){};
            void goScene(int *scene) override;
        };

        class sceneJoin: public sceneScreen
        {
            public:
            sceneJoin(int id);
            inline ~sceneJoin(){};
            void goScene(int *scene) override;
        };

        class sceneGame: public sceneScreen
        {
            public:
            sceneGame(int id);
            inline ~sceneGame(){};
            void goScene(int *scene) override;
            private:
            inline static int _static_lol = 0;
        };



        class sceneHandler
        {
        public:
            inline sceneHandler(){};
            inline ~sceneHandler(){};
            void lauchScene(int *id);
            inline void addScene(sceneScreen *scene) { _AllScene.emplace_back(scene); }

        private:
            std::vector<sceneScreen *> _AllScene;
        };
    }
}

#endif /* !SCENEHANDLER_HPP_ */
