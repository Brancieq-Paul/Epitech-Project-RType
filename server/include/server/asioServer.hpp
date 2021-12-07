/*
** EPITECH PROJECT, 2021
** asioServer
** File description:
** asioServer
*/

#ifndef ASIO_SERVER_HPP_
#define ASIO_SERVER_HPP_

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "server.hpp"
#include "sessions/asioUDPSession.hpp"
#include "sessions/asioTCPSession.hpp"
#include "saloons/saloonManager.hpp"

class AsioServer : public server::AServer {
    public:
        AsioServer(boost::asio::io_service& io_service, short port);
        ~AsioServer() {};

        void start();

    private:
        void handleAccept(std::shared_ptr<AsioTCPSession> new_session, const boost::system::error_code& error);
        void startAccept();
        bool clean(std::vector<AsioTCPSession *> sessions);

        boost::asio::io_service &io_service_;
        boost::asio::ip::tcp::acceptor acceptor_;

        std::shared_ptr<SaloonManager> manager;
};

#endif