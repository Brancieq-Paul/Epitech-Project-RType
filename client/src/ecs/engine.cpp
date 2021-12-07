/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** engine
*/

#include "ecs/engine.hpp"
#include "ecs/entity.hpp"
#include "ecs/clock.hpp"
#include "myJson.hpp"
#include "ecs/compoFactory.hpp"
#include "sceneHandler.hpp"
#include "userDatabase.hpp"

void rtype::engine::Engine::init(std::string ip)
{
    rtype::graphique::RWindow::init("client/rsrc/window.json");
    _window = rtype::graphique::RWindow::GetInstance();
    _event = rtype::utility::UNKNOWN;
    std::cout << "IP =" << ip << std::endl;
    rtype::network::SfmlUDP::init(9999, 1553, ip);
    rtype::network::SfmlUDP::setProcess(new rtype::processor::MyProcess());
}

void rtype::engine::Engine::run(std::string ip)
{
    int scene = 3;
    rtype::database::userDatabase::init();
    rtype::database::userDatabase::setIp(ip);
    rtype::network::SfmlTCP::init(9999, ip);
    rtype::network::SfmlTCP::_tcpSocket->connect(ip, 9999);
    rtype::network::SfmlTCP::_tcpSocket->setBlocking(false);
    rtype::scene::sceneHandler sceneHandler;
    rtype::scene::sceneMenu menu(0);
    rtype::scene::sceneSalon salon(1);
    rtype::scene::sceneName name(3);
    rtype::scene::sceneJoin join(4);
    rtype::scene::sceneGame game(2);

    sceneHandler.addScene(&menu);
    sceneHandler.addScene(&salon);
    sceneHandler.addScene(&name);
    sceneHandler.addScene(&join);
    sceneHandler.addScene(&game);
    // rtype::network::SfmlUDP::getProcess()->setEntityList(_entity_handler.getTab());
    while (!(rtype::eventHandler::EventHandler::checkEventKey(rtype::utility::EXIT_ALL)))
    {
        rtype::eventHandler::EventHandler::pollEvents(_window);
        _window->clear(sf::Color::Magenta);
        rtype::network::SfmlUDP::receivedData();
        rtype::network::SfmlTCP::receivedData();
        sceneHandler.lauchScene(&scene);
        // if (scene == 2) {
        //     _entity_handler.getEntity(1, database::userDatabase::getMyPos())->unblockInput();
        //     _entity_handler.getEntity(2, 1)->changePos(std::pair<int, int>(x, 0));
        //     x++;
        //     _entity_handler.eachFrame();
        // }
        _window->display();
        rtype::clock::RClock::restartCount();
    }
}