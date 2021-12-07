/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** SfmlUDP
*/

#include "SfmlUDP.hpp"
#include <iostream>
#include <cstring>
#include "verbose.hpp"

void rtype::network::SfmlUDP::init(unsigned short sendPort, unsigned short receivedPort, std::string ip)
{
    _udpSocket->setBlocking(false);
    _sendPort = sendPort;
    _receivedPort = receivedPort;
    _ip = ip;
}

rtype::network::SfmlUDP::SfmlUDP::~SfmlUDP()
{
}

void rtype::network::SfmlUDP::writeData(message::UDP::messageUDP_t *data)
{
    uint8_t dataS[LENGTH_UDP_MESSAGE];
    std::memset(dataS, 0, LENGTH_UDP_MESSAGE);
    message::UDP::loadData(data, dataS);

    std::cout << "sending UDP: ";
    for (int i = 0; i < LENGTH_UDP_MESSAGE; i++)
        std::cout << "|" << (int)dataS[i];
    std::cout << std::endl;
    std::cout << "IP = " << rtype::network::SfmlUDP::getIp() << std::endl;
    std::cout << "_sendPORT = " << rtype::network::SfmlUDP::getSendPort() << std::endl;

    _udpSocket->send(dataS, LENGTH_UDP_MESSAGE, rtype::network::SfmlUDP::getIp(), rtype::network::SfmlUDP::getSendPort());
}

void rtype::network::SfmlUDP::receivedData()
{
    uint8_t data[LENGTH_UDP_MESSAGE];
    std::size_t received = 0;
    bool trigger = false;
    sf::IpAddress tmp;
    _udpSocket->receive(data, LENGTH_UDP_MESSAGE, received, tmp, _receivedPort);
    if (received != 0) {
        std::cout << "received = ";
    }
    for (int i = 0; i != received; i++) {
        std::cout << "|" << (int)data[i];
        trigger = true;
    }
    if (trigger) {
        std::cout << std::endl;
         _myProcess->processUDP(data);
    }
}

void rtype::network::SfmlTCP::writeData(message::TCP::messageTCP_t *data)
{
    uint8_t dataS[LENGTH_TCP_MESSAGE];
    std::memset(dataS, 0, LENGTH_TCP_MESSAGE);
    message::TCP::loadData(data, dataS);

    std::cout << "sending TCP: ";
    for (int i = 0; i < LENGTH_TCP_MESSAGE; i++)
        std::cout << "|" << (int)dataS[i];
    std::cout << std::endl;
    rtype::network::SfmlTCP::_tcpSocket->send(dataS, LENGTH_TCP_MESSAGE);
    std::cout << " Now Wait for response " << std::endl;
    std::cout << " BLOCK =  " << rtype::network::SfmlTCP::_tcpSocket->isBlocking() << std::endl;
    // rtype::network::SfmlTCP::receivedData();
    // _tcpSocket->send(dataS, LENGTH_TCP_MESSAGE);
}

void rtype::network::SfmlTCP::receivedData()
{
    uint8_t data[LENGTH_TCP_MESSAGE];
    std::size_t received;
    bool trigger = false;

    rtype::network::SfmlTCP::_tcpSocket->receive(data, LENGTH_TCP_MESSAGE, received);

    for (int i = 0; i < received; i++) {
        std::cout << "|" << (int)data[i];
        trigger = true;
    }
    if (trigger) {
         _myProcess->processTCP(data);
        std::cout << std::endl;
    }
}