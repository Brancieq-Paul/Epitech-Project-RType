/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** sceneHandler
*/

#include "sceneHandler.hpp"
#include "window.hpp"
#include "userDatabase.hpp"

rtype::scene::sceneScreen::sceneScreen(int id)
{
    _id = id;
    // _sessionTCP = new rtype::network::SfmlTCP(9999, rtype::database::userDatabase::getIp());
    // _sessionTCP->_tcpSocket->connect(rtype::database::userDatabase::getIp(), 9999);
}

void rtype::scene::sceneHandler::lauchScene(int *id)
{
    for (auto elem : _AllScene)
    {
        if (elem->getId() == *id)
            elem->goScene(id);
    }
}

rtype::scene::sceneGame::sceneGame(int id) : sceneScreen(id)
{
    entity_handler_ = rtype::entity::REntityHandler("client/rsrc/entities", true);
    entity_handler_.createEntity(1, 1);
    entity_handler_.createEntity(1, 2);
    entity_handler_.createEntity(1, 3);
    entity_handler_.createEntity(1, 4);
    entity_handler_.createEntity(2, 1);
    entity_handler_.createEntity(3, 1);
    entity_handler_.getEntity(1, 1)->changePos(std::pair<int, int>(-100, -100));
    entity_handler_.getEntity(1, 2)->changePos(std::pair<int, int>(-100, -100));
    entity_handler_.getEntity(1, 3)->changePos(std::pair<int, int>(-100, -100));
    entity_handler_.getEntity(1, 4)->changePos(std::pair<int, int>(-100, -100));
    entity_handler_.getEntity(3, 1)->changePos(std::pair<int, int>(-100, -100));

    entity_handler_.getEntity(1, 1)->changeData("color", "blue");
    entity_handler_.getEntity(1, 2)->changeData("color", "red");
    entity_handler_.getEntity(1, 3)->changeData("color", "yellow");
    entity_handler_.getEntity(1, 4)->changeData("color", "green");
    database::userDatabase::_gameHandler = &entity_handler_;
    rtype::network::SfmlUDP::getProcess()->setEntityList(entity_handler_.getTab());
}

rtype::scene::sceneMenu::sceneMenu(int id) : sceneScreen(id)
{
    entity_handler_ = rtype::entity::REntityHandler("./client/rsrc/menu");
    entity_handler_.createEntity(1, 1);
    entity_handler_.createEntity(3, 1);
    entity_handler_.createEntity(2, 1);
    entity_handler_.createEntity(2, 2);
    entity_handler_.createEntity(2, 3);
    entity_handler_.createEntity(6, 1);

    entity_handler_.getEntity(2, 1)->changeData("text", "YOUR NAME IS : ");
    entity_handler_.getEntity(2, 1)->changeData("text", "SCENE = MENU");
    entity_handler_.getEntity(2, 1)->changePos(std::pair<int, int>(600, 100));
    entity_handler_.getEntity(2, 2)->changePos(std::pair<int, int>(200, 100));
    entity_handler_.getEntity(2, 3)->changePos(std::pair<int, int>(500, 0));
    entity_handler_.getEntity(3, 1)->changePos(std::pair<int, int>(400, 400));
    // entity_handler_.getEntity(3, 1)->changeData("color", "white");
}

rtype::scene::sceneJoin::sceneJoin(int id) : sceneScreen(id)
{
entity_handler_ = rtype::entity::REntityHandler("./client/rsrc/join");
    entity_handler_.createEntity(1, 1);
    entity_handler_.createEntity(2, 1);
    entity_handler_.createEntity(2, 3);
    entity_handler_.createEntity(4, 1);
    entity_handler_.createEntity(6, 1);

    entity_handler_.getEntity(2, 1)->changeData("text", "ENTER ID : ");
    entity_handler_.getEntity(2, 3)->changeData("text", "SCENE = JOIN");
    entity_handler_.getEntity(2, 1)->changePos(std::pair<int, int>(50, 400));
    entity_handler_.getEntity(1, 1)->changePos(std::pair<int, int>(300, 400));
    entity_handler_.getEntity(4, 1)->changePos(std::pair<int, int>(100, 500));
}

rtype::scene::sceneName::sceneName(int id) : sceneScreen(id)
{
    entity_handler_ = rtype::entity::REntityHandler("./client/rsrc/name");
    // entity_handler_.createEntity(1, 1);
    entity_handler_.createEntity(1, 2);
    entity_handler_.createEntity(1, 3);
    entity_handler_.createEntity(2, 1);
    entity_handler_.createEntity(4, 1);
    entity_handler_.createEntity(6, 1);

    // entity_handler_.getEntity(1, 1)->changePos(std::pair<int, int>(100, 100));
    entity_handler_.getEntity(1, 2)->changeData("text", "NEW NAME");
    entity_handler_.getEntity(1, 2)->changeData("text", "SCENE = NAME");
    entity_handler_.getEntity(2, 1)->changePos(std::pair<int, int>(200, 200));
    entity_handler_.getEntity(1, 2)->changePos(std::pair<int, int>(500, 100));
    entity_handler_.getEntity(1, 3)->changePos(std::pair<int, int>(500, 500));
    entity_handler_.getEntity(4, 1)->changePos(std::pair<int, int>(500, 550));
}

rtype::scene::sceneSalon::sceneSalon(int id) : sceneScreen(id)
{
    entity_handler_ = rtype::entity::REntityHandler("./client/rsrc/salon");
    entity_handler_.createEntity(1, 1);
    entity_handler_.createEntity(1, 2);
    entity_handler_.createEntity(1, 3);
    entity_handler_.createEntity(1, 4);
    entity_handler_.createEntity(1, 5);
    entity_handler_.createEntity(1, 6);
    entity_handler_.createEntity(1, 7);
    entity_handler_.createEntity(2, 1);
    entity_handler_.createEntity(3, 1);
    entity_handler_.createEntity(6, 1);

    _triggerWindow = false;

    entity_handler_.getEntity(3, 1)->changePos(std::pair<int, int>(-200, -200));
    entity_handler_.getEntity(1, 1)->changeData("text", database::userDatabase::getPlayerName("USER"));
    entity_handler_.getEntity(1, 2)->changeData("text", database::userDatabase::getPlayerName("POne"));
    entity_handler_.getEntity(1, 3)->changeData("text", database::userDatabase::getPlayerName("PTwo"));
    entity_handler_.getEntity(1, 4)->changeData("text", database::userDatabase::getPlayerName("PThree"));
    entity_handler_.getEntity(1, 5)->changeData("text", database::userDatabase::getPlayerName("PFour"));
    entity_handler_.getEntity(1, 6)->changeData("text", "SCENE = SALON");
    entity_handler_.getEntity(1, 7)->changeData("text", std::to_string(database::userDatabase::getIdSalon()));
    entity_handler_.getEntity(1, 1)->changePos(std::pair<int, int>(100, 100));
    entity_handler_.getEntity(1, 2)->changePos(std::pair<int, int>(100, 300));
    entity_handler_.getEntity(1, 3)->changePos(std::pair<int, int>(100, 500));
    entity_handler_.getEntity(1, 4)->changePos(std::pair<int, int>(100, 600));
    entity_handler_.getEntity(1, 5)->changePos(std::pair<int, int>(100, 700));
    entity_handler_.getEntity(1, 6)->changePos(std::pair<int, int>(100, 0));
    entity_handler_.getEntity(1, 7)->changePos(std::pair<int, int>(700, 0));
    entity_handler_.getEntity(2, 1)->changePos(std::pair<int, int>(500, 500));
}

void rtype::scene::sceneJoin::goScene(int *scene)
{
    entity_handler_.eachFrame();
    if (entity_handler_.getEntity(1, 1)->getData("isClicked") == 1)
    {
        std::vector<uint8_t> _byteBody;
        std::vector<std::string> _stringBody;
        uint8_t id = 0;
        if (!entity_handler_.getEntity(4, 1)->getDataTxt("text").empty())
        {
            id = static_cast<uint8_t>(entity_handler_.getEntity(4, 1)->getDataTxt("text").at(0));
            id -= 48;
        }
        _byteBody.emplace_back(id);
        // _byteBody.emplace_back(database::userDatabase::getIdSalon());
        _stringBody.emplace_back(rtype::database::userDatabase::getPlayerName("USER"));
        rtype::sendmfactory::Imessage *message = rtype::network::SfmlUDP::getFactory()->createTCPMessage(rtype::sendmfactory::JoinSalon, _byteBody, _stringBody);
        rtype::network::SfmlTCP::writeData(message->getMessageTCP());
        // _sessionTCP->writeData(message->getMessageTCP());
    }
    if (database::userDatabase::getGoSalon())
        *scene = 1;
}

void rtype::scene::sceneName::goScene(int *scene)
{
    entity_handler_.eachFrame();
    if (entity_handler_.getEntity(2, 1)->getData("isClicked") == 1)
    {
        // std::string name = "";
        if (!entity_handler_.getEntity(4, 1)->getDataTxt("text").empty())
        {
            std::string name = entity_handler_.getEntity(4, 1)->getDataTxt("text");
            rtype::database::userDatabase::GetInstance()->setPlayerName("USER", name);
            *scene = 0;
        }
        // std::string name = entity_handler_.getEntity(1, 2)->getDataTxt("text");
    }
}

void rtype::scene::sceneMenu::goScene(int *scene)
{
    entity_handler_.eachFrame();
    std::string name = rtype::database::userDatabase::getPlayerName("POne");

    entity_handler_.getEntity(2, 2)->changeData("text", name);
    if (entity_handler_.getEntity(1, 1)->getData("isClicked") == 1)
    {
        std::vector<uint8_t> _byteBody;
        std::vector<std::string> _stringBody;
        _stringBody.emplace_back(rtype::database::userDatabase::getPlayerName("USER"));
        rtype::sendmfactory::Imessage *message = rtype::network::SfmlUDP::getFactory()->createTCPMessage(rtype::sendmfactory::CreateSalon, _byteBody, _stringBody);
        rtype::network::SfmlTCP::writeData(message->getMessageTCP());
    }

    if (entity_handler_.getEntity(3, 1)->getData("isClicked") == 1)
    {
        *scene = 4;
    }
    if (!database::userDatabase::getFull() && database::userDatabase::getGoSalon())
        *scene = 1;
}

void rtype::scene::sceneSalon::goScene(int *scene)
{
    entity_handler_.eachFrame();
    if (_triggerWindow == false)
    {
        database::userDatabase::_gameHandler->initServerTypes();
        rtype::graphique::RWindow::sendWindowSize();
        _triggerWindow = true;
    }
    entity_handler_.getEntity(1, 7)->changeData("text", std::to_string(database::userDatabase::getIdSalon()));
    entity_handler_.getEntity(1, 1)->changeData("text", database::userDatabase::getPlayerName("USER"));
    entity_handler_.getEntity(1, 2)->changeData("text", database::userDatabase::getPlayerName("POne"));
    entity_handler_.getEntity(1, 3)->changeData("text", database::userDatabase::getPlayerName("PTwo"));
    entity_handler_.getEntity(1, 4)->changeData("text", database::userDatabase::getPlayerName("PThree"));
    entity_handler_.getEntity(1, 5)->changeData("text", database::userDatabase::getPlayerName("PFour"));
    if (entity_handler_.getEntity(2, 1)->getData("isClicked") == 1)
    {
        std::vector<std::string> _stringBody;
        std::vector<uint8_t> _byteBody;
        if (!database::userDatabase::getReady())
        {
            _byteBody.emplace_back(true);
            entity_handler_.getEntity(3, 1)->changePos(std::pair<int, int>(100, 100));
            database::userDatabase::setReady(true);
        }
        else
        {
            _byteBody.emplace_back(false);
            entity_handler_.getEntity(3, 1)->changePos(std::pair<int, int>(-200, -200));
            database::userDatabase::setReady(false);
        }
        rtype::sendmfactory::Imessage *message = rtype::network::SfmlUDP::getFactory()->createTCPMessage(rtype::sendmfactory::ReadySalon, _byteBody, _stringBody);
        rtype::network::SfmlTCP::writeData(message->getMessageTCP());
    }

    if (database::userDatabase::getGame())
        *scene = 2;
}

void rtype::scene::sceneGame::goScene(int *scene)
{
    while (_static_lol != 1 && database::userDatabase::getMyPos() == 1)
    {
        std::vector<uint8_t> _byteBody;
        std::vector<uint8_t> _tmpType = message::intToUint8(3);
        std::vector<uint8_t> _tmpId = message::intToUint8(1);
        std::vector<uint8_t> _tmpX = message::intToUint8(500);
        std::vector<uint8_t> _tmpY = message::intToUint8(500);

        for (int i = 0; i != _tmpType.size(); i++)
            _byteBody.emplace_back(_tmpType[i]);
        for (int i = 0; i != _tmpId.size(); i++)
            _byteBody.emplace_back(_tmpId[i]);
        for (int i = 0; i != _tmpX.size(); i++)
            _byteBody.emplace_back(_tmpX[i]);
        for (int i = 0; i != _tmpY.size(); i++)
            _byteBody.emplace_back(_tmpY[i]);
        rtype::sendmfactory::Imessage *message = rtype::network::SfmlUDP::getFactory()->createUDPMessage(rtype::sendmfactory::CreateEntity, _byteBody);
        rtype::network::SfmlUDP::writeData(message->getMessageUDP());
        _static_lol++;
    }

    entity_handler_.getEntity(1, database::userDatabase::getMyPos())->unblockInput();
    entity_handler_.eachFrame();
}