/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** window
*/

#include "window.hpp"
#include "myJson.hpp"
#include "message.hpp"
#include "SfmlUDP.hpp"
#include "clientErrors/errWindowNotInitialized.hpp"

rtype::graphique::RWindow *rtype::graphique::RWindow::window_ = nullptr;

rtype::graphique::RWindow *rtype::graphique::RWindow::GetInstance()
{
    if (window_ == nullptr) {
        throw ErrorWindowNotInitialized(__FILE__, __LINE__);
    }
    return window_;
}

rtype::graphique::RWindow::~RWindow()
{
    delete window_;
}

void rtype::graphique::RWindow::init(std::string pathFile)
{
    rtype::Json *j = rtype::Json::parseFromFile(pathFile);
    int x_size = j->value("/size/x"_json_pointer, 800);
    int y_size = j->value("/size/y"_json_pointer, 600);

    if (window_ == nullptr) {
        std::cout << "Start windows with config: " << x_size << "/" << y_size << std::endl;
        window_ = new rtype::graphique::RWindow(sf::VideoMode(x_size, y_size), "My window");
        window_->setFramerateLimit(120);
        window_->setKeyRepeatEnabled(false);
    }
    delete j;
}

void rtype::graphique::RWindow::sendWindowSize()
{
    sf::Vector2u size = window_->getSize();
    std::cout << "send size" << std::endl;

    std::vector<uint8_t> _byteBody;
    std::vector<std::string> _stringBody;
    std::vector<uint8_t> tmpSizeX = message::intToUint8(size.x);
    std::vector<uint8_t> tmpSizeY = message::intToUint8(size.y);

    for(int i = 0; i != tmpSizeX.size(); i++)
        _byteBody.emplace_back(tmpSizeX[i]);
    for(int i = 0; i != tmpSizeY.size(); i++)
        _byteBody.emplace_back(tmpSizeY[i]);

    rtype::sendmfactory::Imessage *message = rtype::network::SfmlUDP::getFactory()->createTCPMessage(rtype::sendmfactory::SendWindowSize, _byteBody, _stringBody);
    rtype::network::SfmlTCP::writeData(message->getMessageTCP());
    //send here
}