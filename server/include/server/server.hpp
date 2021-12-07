/*
** EPITECH PROJECT, 2021
** server
** File description:
** server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <vector>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

namespace server {

    class IServer {
        public:
            virtual ~IServer() = default;

            virtual void start() = 0;
    };

    class AServer : public IServer {
        protected:
            inline AServer(short port) : port_(port) {};

            short port_;
    };
};

#endif