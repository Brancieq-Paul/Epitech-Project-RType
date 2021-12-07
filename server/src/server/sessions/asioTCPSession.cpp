/*
** EPITECH PROJECT, 2021
** asioTCPSession
** File description:
** asioTCPSession
*/

#include "../../../include/server/sessions/asioTCPSession.hpp"
#include <iostream>
#include <cstring>
#include "../../../include/verbose.hpp"
#include "../../../include/server/saloons/saloon.hpp"
#include "../../../include/server/saloons/saloonManager.hpp"
#include "../../../include/command/commandFactory.hpp"

AsioTCPSession::AsioTCPSession(boost::asio::io_service &io_service, std::shared_ptr<SaloonManager> manager) : socket_(io_service), saloon_(nullptr), manager_(manager) {
    std::memset(wholeMessage, 0, LENGTH_TCP_MESSAGE);
};

AsioTCPSession::~AsioTCPSession() {};

void AsioTCPSession::start() {
    Verbose::simpleDebugMessage("A new client just connected to the server, Waiting for next message.");
    socket_.async_read_some(boost::asio::buffer(wholeMessage, sizeof(wholeMessage)),
                            boost::bind(&AsioTCPSession::handleRead,
                                        this,
                                        boost::asio::placeholders::error));
};

void AsioTCPSession::write(message::TCP::messageTCP_t *message) {
    if (message != nullptr)
        toWrite.emplace_back(message);
    handleWrite();
};

void AsioTCPSession::combineMessageAndProcess() {
    message::TCP::messageTCP_t *msg = message::TCP::messageFromData(wholeMessage);
    if (msg->id == CommandFactory::CLIENT_CREATION_SALOON_ASKED) {
        pseudo = "";
        for (int i = 0; i < 10; i++)
            pseudo.push_back(msg->body[i]);
    }
    if (msg->id == CommandFactory::CLIENT_WANT_JOIN_SALOON) {
        pseudo = "";
        for (int i = 1; i < 11; i++)
            pseudo.push_back(msg->body[i]);
    }
    command::TCP::ITCPCommand *com = CommandFactory::createTCPCommand(msg, id);
    if (com == nullptr)
        return;
    if (manager_ != nullptr)
        manager_->processTCP(com);
    else {
        if (saloon_ != nullptr)
            saloon_->processTCP(com);
        else
            Verbose::debugCriticalMessage("Neither the manager not the saloon are set for a tcp session", __FILE__, __LINE__);
    }
};

void AsioTCPSession::handleRead(const boost::system::error_code &error) {
    if (!error) {
        combineMessageAndProcess();
        std::memset(wholeMessage, 0, LENGTH_TCP_MESSAGE);
        socket_.async_read_some(boost::asio::buffer(wholeMessage, sizeof(wholeMessage)),
                                boost::bind(&AsioTCPSession::handleRead,
                                            this,
                                            boost::asio::placeholders::error));
    } else {
        destructor();
    }
}

void AsioTCPSession::handleWrite() {
    if (toWrite.size() > 0) {
        uint8_t data[LENGTH_TCP_MESSAGE];
        std::memset(data, 0, LENGTH_TCP_MESSAGE);
        Verbose::simpleDebugMessageWithColor(ConcatOnTheFly() << "Sending message '" << toWrite[0]->id << "' to client with pseudo : " << pseudo, Verbose::CYAN, true);
        message::TCP::loadData(toWrite[0], data);
        boost::asio::async_write(socket_,
                                boost::asio::buffer(data, sizeof(data)),
                                boost::bind(&AsioTCPSession::handleWrite2,
                                        this,
                                        boost::asio::placeholders::error));
        toWrite.erase(toWrite.begin());
        handleWrite();
    }
}

void AsioTCPSession::destructor() {
    if (manager_ != NULL)
        manager_->deathOfASession(this->id);
    if (saloon_ != NULL)
        saloon_->deathOfASession(this->id);
}

void AsioTCPSession::handleWrite2(const boost::system::error_code &error) {
}