/*
** EPITECH PROJECT, 2021
** asioServer
** File description:
** asioServer
*/

#include "../../include/server/asioServer.hpp"
#include "../../include/verbose.hpp"

AsioServer::AsioServer(boost::asio::io_service& io_service, short port) : server::AServer(port),
                                                                        io_service_(io_service),
                                                                        acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    manager = std::unique_ptr<SaloonManager>(new SaloonManager(io_service));
};

void AsioServer::start() {
    startAccept();
};

void AsioServer::startAccept() {
    std::shared_ptr<AsioTCPSession> newTCPSession = std::shared_ptr<AsioTCPSession>(new AsioTCPSession(io_service_, manager));
    acceptor_.async_accept(newTCPSession->socket(),
                            boost::bind(&AsioServer::handleAccept,
                                        this,
                                        newTCPSession,
                                        boost::asio::placeholders::error));
};

bool AsioServer::clean(std::vector<AsioTCPSession *> s) {
    for (int i = 0; i < s.size(); i++)
        if (s[i] == NULL)
            return (false);
    return (true);
}

void AsioServer::handleAccept(std::shared_ptr<AsioTCPSession> newSession, const boost::system::error_code& error) {
    if (!error) {
        newSession->start();
        manager->manageTCPSession(newSession);
    } else {
        newSession->~AsioTCPSession();
    }
    startAccept();
};