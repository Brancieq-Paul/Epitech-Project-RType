/*
** EPITECH PROJECT, 2021
** SaloonPhysicSystem
** File description:
** SaloonPhysicSystem
*/

#include "../../../include/server/saloons/saloon.hpp"
#include "../../../include/server/sessions/asioTCPSession.hpp"
#include "../../../include/server/sessions/asioUDPSession.hpp"
#include "../../../include/verbose.hpp"
#include "../../../include/server/saloons/saloonManager.hpp"
#include "../../../include/command/generator/generateResponses.hpp"
#include "../../../include/error.hpp"

Saloon::Saloon(int max_player_, std::shared_ptr<AsioTCPSession> host, int idSaloon_, boost::asio::io_service& io, SaloonManager *manager) : physicSystem(std::unique_ptr<SaloonPhysicSystem>(new SaloonPhysicSystem(this))), io_service(io), manager_(manager)
{
    Verbose::logInError("------------------A saloon is been created------------------");
    Verbose::simpleDebugMessageWithColor(ConcatOnTheFly() << "ID OF SALOON TO USE :'" << std::to_string(idSaloon_) << "'", Verbose::RED, true);
    counter = 1;
    idSaloon = idSaloon_;
    max_player = max_player_;
    managedSessions.emplace_back(host);
    host->setID(counter);
    counter++;
    createUDPSession();
};

Saloon::playerAcceptedStatus Saloon::acceptPlayer(std::shared_ptr<AsioTCPSession> session, std::shared_ptr<Saloon> thisSaloon)
{
    if (!gameLaunched && managedSessions.size() < max_player)
    {
        session->setSaloon(thisSaloon);
        session->detachManager();
        session->setID(counter);
        counter++;
        managedSessions.emplace_back(session);
        return (PLAYER_ACCEPTED);
    }
    return (PLAYER_REFUSED);
};

void Saloon::notifyAllThatSomebodyJoinedTheSaloon() {
    std::vector<std::string> pseudos;
    for (int i = 0; i < managedSessions.size(); i++) {
        pseudos.emplace_back(managedSessions[i]->getPseudo());
    }
    std::vector<message::TCP::responseTCP_t *> res = {Generator::TCP::ResponseGeneratorTCP::generateServerUpdateToSaloonComposition(pseudos)};
    respondTCP(res);
};

void Saloon::respondTCP(std::vector<message::TCP::responseTCP_t *> responses) {
    for (auto rep : responses) {
        if (rep->to[0] == "All") {
            for (auto ses : managedSessions) {
                ses->write(rep->message);
            }
        } else {
            for (std::string stringID : rep->to) {
                int id = std::atoi(stringID.c_str());
                for (auto ses : managedSessions) {
                    if (ses->getID() == id)
                        ses->write(rep->message);
                }
            }
        }
    }
};

void Saloon::deathOfASession(int idSession) {
    int i = 0;
    bool sesFound = false;
    for (; i < managedSessions.size(); i++) {
        if (managedSessions[i]->getID() == idSession) {
            sesFound = true;
            break;
        }
    }
    if (sesFound) {
        physicSystem->getDB()->removePseudo(managedSessions[i]->getPseudo());
        managedSessions.erase(managedSessions.begin() + i);
        if(managedSessions.size() == 0)
            manager_->deathOfASaloon(this->idSaloon);
    } else
        Verbose::debugCriticalMessage("A Session died but wasn't in the saloon it was supoossed to be in", __FILE__, __LINE__);
};

void Saloon::respondUDP(std::vector<message::UDP::responseUDP_t *> responses) {
    std::vector<message::UDP::messageUDP_t *> msgs;
    for (auto rep : responses)
        msgs.emplace_back(rep->message);
    if (msgs.size() != 0)
        udpSession->write(msgs);
};

void Saloon::aPlayerWantToPLay(int idSession, bool want) {
    int i = 0;
    bool found = false;
    for (; i < managedSessions.size(); i++) {
        if (managedSessions[i]->getID() == idSession) {
            found = true;
            break;
        }
    }
    if (found) {
        Verbose::simpleDebugMessage("in a player want to play");
        physicSystem->getDB()->aPlayerWantToPlay(managedSessions[i]->getPseudo(), want);
    } else
        Verbose::debugCriticalMessage("A session was not found.", __FILE__, __LINE__);
};

void Saloon::processData(std::vector<message::TCP::responseTCP_t *> repTCP, std::vector<message::UDP::responseUDP_t *> repUDP)
{
    respondTCP(repTCP);
    respondUDP(repUDP);
};

void Saloon::processUDP(command::UDP::IUDPCommand *com)
{
    com->execute(physicSystem->getDB());
};

void Saloon::processTCP(command::TCP::ITCPCommand *com) {
    respondTCP(com->execute(this, nullptr));
};

void Saloon::createUDPSession()
{
    if (udpSession == nullptr)
    {
        udpSession = std::unique_ptr<AsioUDPSession>(new AsioUDPSession(io_service, DEFAULT_UDP_PORT, this));
        udpPort = udpSession->getPort();
        udpSession->start();
    }
};