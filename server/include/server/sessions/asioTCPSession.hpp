/*
** EPITECH PROJECT, 2021
** AsioTCPSession
** File description:
** AsioTCPSession
*/

#ifndef ASIO_TCP_SESSION_HPP_
#define ASIO_TCP_SESSION_HPP_

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "../../data/message.hpp"
#include "../server.hpp"

class SaloonManager;
class Saloon;

class AsioTCPSession {
    public:
        AsioTCPSession(boost::asio::io_service &io_service, std::shared_ptr<SaloonManager> manager);
        ~AsioTCPSession();

        void destructor();

        void start();
        void write(message::TCP::messageTCP_t *message);
        int getID() { return (id); };
        void setID(int id_) { id = id_; };
        void setSaloon(std::shared_ptr<Saloon> saloon) { saloon_ = saloon; };
        void detachManager() { manager_ = NULL; };
        std::string getPseudo() { return (pseudo); };
        boost::asio::ip::tcp::socket &socket() { return (socket_);};

    private:

        void handleRead(const boost::system::error_code& error);
        void handleWrite();
        void handleWrite2(const boost::system::error_code &error);
        void combineMessageAndProcess();

        boost::asio::ip::tcp::socket socket_;
        std::string pseudo = "";
        int id;
        std::shared_ptr<Saloon> saloon_ = NULL;
        std::vector<message::TCP::messageTCP_t *> toWrite;
        uint8_t wholeMessage[LENGTH_TCP_MESSAGE];
        std::shared_ptr<SaloonManager> manager_;
};

#endif