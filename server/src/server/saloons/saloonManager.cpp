/*
** EPITECH PROJECT, 2021
** SaloonManager
** File description:
** SaloonManager
*/
#include "../../../include/server/saloons/saloonManager.hpp"

SaloonManager::SaloonManager(boost::asio::io_service &io_service) : idManagerSaloons(1),
                                                                    io_service_(io_service),
                                                                    idManagerSessions(1)
{
};

void SaloonManager::manageTCPSession(std::shared_ptr<AsioTCPSession> session)
{
    session->setID(idManagerSessions);
    idManagerSessions++;
    sessions.emplace_back(session);
};

void SaloonManager::processTCP(command::TCP::ITCPCommand *com)
{
    respondTCP(com->execute(nullptr, this));
};

void SaloonManager::respondTCP(std::vector<message::TCP::responseTCP_t *> responses) {
    for (auto rep : responses) {
        if (rep->to[0] == "All") {
            for (auto ses : sessions) {
                ses->write(rep->message);
            }
        } else {
            for (std::string stringID : rep->to) {
                int id = std::atoi(stringID.c_str());
                for (auto ses : sessions) {
                    if (ses->getID() == id)
                        ses->write(rep->message);
                }
            }
        }
    }
};

std::shared_ptr<Saloon> SaloonManager::createNewSaloon(int idSession)
{
    int i = 0;
    bool sesFound = false;
    for (; i < sessions.size(); i++)
    {
        if (sessions[i]->getID() == idSession)
        {
            sesFound = true;
            break;
        }
    }
    if (sesFound)
    {
        int idSaloon = idManagerSaloons;
        idManagerSaloons++;
        auto saloon = std::shared_ptr<Saloon>(new Saloon(MAX_PLAYER_PER_SALOON, sessions[i], idSaloon, io_service_, this));
        saloons.emplace_back(saloon);
        sessions[i]->setSaloon(saloon);
        sessions[i]->detachManager();
        sessions.erase(sessions.begin() + i);
        return (saloon);
    }
    return (NULL);
};

void SaloonManager::deathOfASession(int id) {
    int i = 0;
    bool b = false;
    for (; i < sessions.size(); i++) {
        if (sessions[i]->getID() == id) {
            b = true;
            break;
        }
    }
    if (b)
        sessions.erase(sessions.begin() + i);
}

void SaloonManager::deathOfASaloon(int idSaloon) {
    for (int i = 0; i < saloons.size(); i++) {
        if(saloons[i]->getIDSaloon() == idSaloon)
            saloons.erase(saloons.begin() + i);
            return;
    }
}

std::shared_ptr<Saloon> SaloonManager::giveTCPSessionToSaloon(int idSaloon, int idTCPSession)
{
    int i = 0;
    int k = 0;
    bool sessionFound = false;
    bool saloonFound = false;
    for (; i < sessions.size(); i++)
    {
        if (sessions[i]->getID() == idTCPSession)
        {
            sessionFound = true;
            break;
        }
    }
    for (; k < saloons.size(); k++)
    {
        if (saloons[k]->getIDSaloon() == idSaloon)
        {
            saloonFound = true;
            break;
        }
    }

    if (saloonFound && sessionFound)
    {
        if (Saloon::PLAYER_ACCEPTED == saloons[k]->acceptPlayer(sessions[i], saloons[k]))
        {
            sessions.erase(sessions.begin() + i);
            return (saloons[k]);
        }
        else
        {
            return (nullptr);
        }
    }
    else
    {
        if (!saloonFound)
        {
            Verbose::simpleDebugMessageWithColor("A client tried to connect to a non-existant saloon!", Verbose::RED, true);
        }
        else
        {
            Verbose::simpleDebugMessageWithColor("The id of a TCP session seems to be lost...", Verbose::RED, true);
        }
    }

    return (nullptr);
};
