/*
** EPITECH PROJECT, 2021
** SaloonManager
** File description:
** SaloonManager
*/

#ifndef SALOON_MANAGER_HPP_
#define SALOON_MANAGER_HPP_

#include <vector>
#include <memory>
#include "saloon.hpp"
#include "../../command/command.hpp"
#include "../sessions/asioTCPSession.hpp"

class SaloonManager {
    public:
        SaloonManager(boost::asio::io_service &io_service);
        ~SaloonManager() {};

        void manageTCPSession(std::shared_ptr<AsioTCPSession> session);
        void processTCP(command::TCP::ITCPCommand *com);
        std::shared_ptr<Saloon> createNewSaloon(int idSession);
        std::shared_ptr<Saloon> giveTCPSessionToSaloon(int idSaloon, int idTCPSession);
        void deathOfASession(int session);
        void deathOfASaloon(int idSaloon);
        void respondTCP(std::vector<message::TCP::responseTCP_t *> responses);

    private:
        boost::asio::io_service &io_service_;
        int idManagerSaloons;
        std::vector<std::shared_ptr<Saloon>> saloons;
        int idManagerSessions;
        std::vector<std::shared_ptr<AsioTCPSession>> sessions;
};

#endif