/*
** EPITECH PROJECT, 2021
** AsioUDPSession
** File description:
** AsioUDPSession
*/

#ifndef ASIO_UDP_SESSION_HPP_
#define ASIO_UDP_SESSION_HPP_

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "../server.hpp"
#include "../../data/message.hpp"

class Saloon;

class AsioUDPSession {
    public:
        AsioUDPSession(boost::asio::io_service &io_service, int port, Saloon *saloon);
        ~AsioUDPSession() {};

        void start();

        void write(std::vector<message::UDP::messageUDP_t *> messages);
        int getPort() {
            return (socket_.local_endpoint().port());
        };
        boost::asio::ip::udp::socket &socket() { return (socket_);};
        void startGame() { gameStarted = true; };

    private:

        void handleRead(const boost::system::error_code &error);
        void handleWrite();
        void handleWrite2(const boost::system::error_code &error);
        void combineMessageAndProcess();
        void rememberEndpoint(boost::asio::ip::udp::endpoint e);

        boost::asio::ip::udp::socket socket_;
        Saloon *saloon_;
        std::vector<boost::asio::ip::udp::endpoint> endpoints;
        boost::asio::ip::udp::endpoint remote_endpoint_;
        std::vector<message::UDP::messageUDP_t *> toWrite;
        uint8_t wholeMessage[LENGTH_UDP_MESSAGE];
        bool gameStarted = false;
};

#endif