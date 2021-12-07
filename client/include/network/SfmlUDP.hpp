/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** SfmlUDP
*/

#ifndef SFMLUDP_HPP_
#define SFMLUDP_HPP_

#include <SFML/Network.hpp>
#include "message.hpp"
#include "processor.hpp"
#include "messageFactory.hpp"

namespace rtype
{
    namespace network
    {
        class ClientNetwork
        {
        public:
            inline ClientNetwork(){};
            inline ~ClientNetwork(){};
            static inline void setProcess(rtype::processor::MyProcess *process) { _myProcess = process; _messageFactory = new rtype::sendmfactory::messageFactory();};
            static inline rtype::processor::MyProcess *getProcess() { return _myProcess; };
            static inline rtype::sendmfactory::messageFactory *getFactory() { return _messageFactory; };

        protected:
            static inline rtype::processor::MyProcess *_myProcess = nullptr;
            static inline rtype::sendmfactory::messageFactory *_messageFactory = nullptr;

        };

        class SfmlUDP : public ClientNetwork
        {
        public:
            inline SfmlUDP(): ClientNetwork() {};
            ~SfmlUDP();

            static void init(unsigned short sendPort, unsigned short receivedPort, std::string ip);
            static void writeData(message::UDP::messageUDP_t *data);
            static void getUDPsocket(){_udpSocket;};
            inline static void setPort(unsigned short sendPort){_sendPort = sendPort;};
            inline static sf::IpAddress getIp(){return _ip;};
            inline static unsigned short getSendPort(){return _sendPort;};
            static void receivedData();

        protected:
            static inline sf::UdpSocket *_udpSocket = new sf::UdpSocket();
            static inline unsigned short _sendPort = 0;
            static inline unsigned short _receivedPort = 0;
            static inline sf::IpAddress _ip = "";
        };

        class SfmlTCP : public ClientNetwork
        {
        public:
            inline SfmlTCP(int port, std::string ip)
            {
                _tcpSocket->setBlocking(false);
                _port = port;
                _ip = ip;
            };
            inline ~SfmlTCP(){};
            inline static void init(unsigned short sendPort, std::string ip){_ip = ip, _port = sendPort;};
            static void writeData(message::TCP::messageTCP_t *data);
            static void receivedData();
            static inline sf::TcpSocket *_tcpSocket =  new sf::TcpSocket();

        protected:
            static inline int _port = 0;
            static inline sf::IpAddress _ip = "";
        };
    }
}

#endif /* !SFMLUDP_HPP_ */
