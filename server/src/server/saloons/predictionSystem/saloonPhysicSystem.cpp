/*
** EPITECH PROJECT, 2021
** SaloonPhysicSystem
** File description:
** SaloonPhysicSystem
*/

#include "../../../../include/server/saloons/predictionSystem/saloonPhysicSystem.hpp"
#include "../../../../include/server/saloons/saloon.hpp"
#include "../../../../include/verbose.hpp"
#include "../../../../include/command/commandFactory.hpp"

void SaloonPhysicSystem::prepareData()
{
    std::vector<message::UDP::responseUDP_t *> repsUDP;
    std::vector<message::TCP::responseTCP_t *> repsTCP;
    if (saloon_->isGameLaunched()) {
        auto es = db->getEntities();
        for (int i = 1; i < es.size(); i++) {
            if (es[i - 1]->collideWith(es[i])) {
                es[i - 1]->removeHP(1);
                es[i]->removeHP(1);
                if (es[i - 1]->isAlive())
                    es[i - 1]->setStatus(Entity::HIT);
                else
                    es[i - 1]->setStatus(Entity::DEAD);
                if (es[i]->isAlive())
                    es[i]->setStatus(Entity::HIT);
                else
                    es[i]->setStatus(Entity::DEAD);
            }
        }
        Verbose::simpleDebugMessageWithColor("There are '" + std::to_string(db->getEntities().size()) + "' entities", Verbose::RED, true);
        for (auto e : db->getEntities())
        {
            repsUDP.emplace_back(Generator::UDP::ResponseGeneratorUDP::generateServerEntityStatusUpdate(e->getLife(), e->getId()->typeId, e->getId()->spriteId, e->getStatus()));
            repsUDP.emplace_back(Generator::UDP::ResponseGeneratorUDP::generateServerPositionUpdate(e->getPos()->getX(), e->getPos()->getY(), e->getId()->typeId, e->getId()->spriteId));
        }
    }  else {
        repsTCP.emplace_back(Generator::TCP::ResponseGeneratorTCP::generateServerUDPPortToUse(saloon_->getUDPPort()));
        repsTCP.emplace_back(Generator::TCP::ResponseGeneratorTCP::generateServerUpdateToSaloonComposition(db->getPseudos()));
        if (db->readyToPLay())
        {
            repsTCP.emplace_back(Generator::TCP::ResponseGeneratorTCP::generateServerGameLaunched());
            saloon_->launchGame();
        }
    }
    saloon_->processData(repsTCP, repsUDP);
};

SaloonPhysicSystem::SaloonPhysicSystem(Saloon *saloon) : saloon_(saloon)
{
    db = std::shared_ptr<SaloonDB>(new SaloonDB());
    predictor = std::unique_ptr<Predictor>(new Predictor(db));
    clock = new Clock::BasicClock((PHYSIC_SYSTEM_CLOCK_FREQUENCY > 0 ? PHYSIC_SYSTEM_CLOCK_FREQUENCY : 1), this);
    Clock::MasterClockSingleton::getInstance(saloon->io_service)->addClock(clock);
};

void SaloonPhysicSystem::notifiedByClock()
{
    prepareData();
};