/*
** EPITECH PROJECT, 2021
** asioUDPSession
** File description:
** asioUDPSession
*/

#include "../../../include/server/sessions/asioUDPSession.hpp"
#include "../../../include/server/saloons/saloon.hpp"
#include <iostream>
#include <cstring>
#include "../../../include/verbose.hpp"
#include "../../../include/command/commandFactory.hpp"
#include "../../../include/error.hpp"

AsioUDPSession::AsioUDPSession(boost::asio::io_service &io_service, int port, Saloon *saloon) : socket_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), saloon_(saloon) {
    std::memset(wholeMessage, 0, LENGTH_UDP_MESSAGE);
};

void AsioUDPSession::start() {
    Verbose::simpleDebugMessage("A new UDP link has been created with that address : " + socket_.local_endpoint().address().to_string() + " on port : " + std::to_string(socket_.local_endpoint().port()));
    socket_.async_receive_from(boost::asio::buffer(wholeMessage, sizeof(wholeMessage)),
                                remote_endpoint_,
                                boost::bind(&AsioUDPSession::handleRead,
                                            this,
                                            boost::asio::placeholders::error));
};

void AsioUDPSession::write(std::vector<message::UDP::messageUDP_t *> messages) {
    if (messages.size() != 0)
        toWrite.insert(toWrite.end(), messages.begin(), messages.end());
    handleWrite();
};

void AsioUDPSession::combineMessageAndProcess() {
    message::UDP::messageUDP_t *msg = message::UDP::messageFromData(wholeMessage);
    command::UDP::IUDPCommand *com = CommandFactory::createUDPCommand(msg);
    if(com == nullptr)
        return;
    saloon_->processUDP(com);
};

void AsioUDPSession::rememberEndpoint(boost::asio::ip::udp::endpoint e) {
    for (auto ee : endpoints) {
        if (ee.address() == e.address() && ee.port() == e.port())
            return;
    }
    endpoints.emplace_back(e);
}

void AsioUDPSession::handleRead(const boost::system::error_code &error) {
    if (!error) {
        rememberEndpoint(remote_endpoint_);
        combineMessageAndProcess();
        std::memset(wholeMessage, 0, LENGTH_UDP_MESSAGE);
        socket_.async_receive_from(boost::asio::buffer(wholeMessage, sizeof(wholeMessage)),
                                remote_endpoint_,
                                boost::bind(&AsioUDPSession::handleRead,
                                            this,
                                            boost::asio::placeholders::error));
    }
}

void AsioUDPSession::handleWrite() {
    if (toWrite.size() > 0) {
        uint8_t data[LENGTH_UDP_MESSAGE];
        std::memset(data, 0, LENGTH_UDP_MESSAGE);
        message::UDP::loadData(toWrite[0], data);
        Verbose::simpleDebugMessage(ConcatOnTheFly() << "The udp session of a saloon is trying to send packages to : " << endpoints.size() << " !");
        for (auto e : endpoints) {
            socket_.async_send_to(boost::asio::buffer(data, sizeof(data)),
                            e,
                            boost::bind(&AsioUDPSession::handleWrite2,
                            this,
                            boost::asio::placeholders::error));
            e.address().to_string();
        }
        toWrite.erase(toWrite.begin());
        handleWrite();
    }
}

void AsioUDPSession::handleWrite2(const boost::system::error_code &error) {}