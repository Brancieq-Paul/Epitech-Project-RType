/*
** EPITECH PROJECT, 2021
** Saloon
** File description:
** Saloon
*/

#ifndef SALOON_HPP_
#define SALOON_HPP_

#include "predictionSystem/saloonPhysicSystem.hpp"
#include "../../data/message.hpp"
#include "../sessions/asioUDPSession.hpp"
#include "../../command/command.hpp"
#include "../../constantsServer.hpp"

class AsioTCPSession;

class AsioTCPSession;

class SaloonManager;

namespace command {
    namespace UDP {
        class IUDPCommand;
    };
    namespace TCP {
        class ITCPCommand;
    };
};

class Saloon {
    public:
        enum playerAcceptedStatus {
            PLAYER_ACCEPTED,
            PLAYER_REFUSED
        };

        Saloon(int max_player_, std::shared_ptr<AsioTCPSession> host_, int idSaloon_, boost::asio::io_service& io_service, SaloonManager *manager);
        ~Saloon() {physicSystem->deactivate();};

        playerAcceptedStatus acceptPlayer(std::shared_ptr<AsioTCPSession> session, std::shared_ptr<Saloon> thisSaloon);
        int getIDSaloon() { return (idSaloon); };
        void processData(std::vector<message::TCP::responseTCP_t *> respTCP, std::vector<message::UDP::responseUDP_t *> respUDP);
        void processUDP(command::UDP::IUDPCommand *msg);
        void processTCP(command::TCP::ITCPCommand *msg);
        int getUDPPort() { return (udpPort); };
        void aPlayerWantToPLay(int idSession, bool want);
        bool isGameLaunched() { return (gameLaunched); };
        inline void launchGame() {
            gameLaunched = true;
            physicSystem->startClock();
            Verbose::logInError("Nb of archetypes created : " + std::to_string(physicSystem->getDB()->getArchetypesNB()));
            Verbose::logInError("------------------A GAME HAS BEEN LAUNCHED WITH THE PREVIOUS definitions of scripts and such------------------");
        };
        void respondTCP(std::vector<message::TCP::responseTCP_t *> responses);
        void deathOfASession(int idSession);
        std::shared_ptr<SaloonDB> getDB() { return (physicSystem->getDB()); };
        void setWroldBoundaries(int x, int y) {
            physicSystem->setBoundaries(x, y);
        };

        boost::asio::io_service &io_service;

    private:
        void createUDPSession();
        void notifyAllThatSomebodyJoinedTheSaloon();
        void respondUDP(std::vector<message::UDP::responseUDP_t *> responses);
        void notifyThatSomebodyLeft();

        std::unique_ptr<SaloonPhysicSystem> physicSystem;
        int idSaloon;
        int max_player;
        bool gameLaunched = false;
        std::vector<std::shared_ptr<AsioTCPSession>> managedSessions;
        std::unique_ptr<AsioUDPSession> udpSession;
        int counter;
        int udpPort;
        SaloonManager *manager_;
};

#endif