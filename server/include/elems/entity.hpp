/*
** EPITECH PROJECT, 2021
** Entity
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "pos.hpp"
#include "velocity.hpp"
#include "positionModifier/aPositionModifier.hpp"
#include "positionModifier/modifiers/stationary.hpp"
#include <memory>
#include <vector>
#include "../data/id.hpp"
#include "colBox.hpp"
#include "../clock/notifiableByClock.hpp"
#include "../clock/clock.hpp"
#include "../verbose.hpp"
#include "../error.hpp"

class Entity : public NotifiableByClock {

    public:
        Entity(int x, int y, int sid, int tid, std::shared_ptr<ColBox> colBox) : pos(std::shared_ptr<Pos>(new Pos(x, y))),
                                            velocity(std::shared_ptr<Velocity>(new Velocity(0, 0))),
                                            id_(new id::id_t()), lifeLeft(1), colBox_(colBox)
        {
            counter = 0;
            id_->spriteId = sid;
            id_->typeId = tid;
            hasMoved_ = false;
            posModifiers.emplace_back(std::shared_ptr<APositionModifier>(new Stationary()));
            clock = new Clock::StartableClock(20, this);
            auto a = Clock::MasterClockSingleton::getInstance2();
            if (a != NULL)
                a->addClock(clock);
        };

        ~Entity() {};

        enum statusEntity {
            ALIVE = 1,
            DEAD = 3,
            HIT = 2
        };

        void notifiedByClock() {
            if (statusE == HIT)
                statusE = ALIVE;
        };

        id::id_t *getId() { return (id_); };
        std::shared_ptr<Pos> getPos() { return (pos); };
        std::shared_ptr<Velocity> getVelocity() { return (velocity); };
        void addPositionModifier(std::shared_ptr<APositionModifier> newposModifier) {posModifiers.emplace_back(newposModifier); };
        void simulate(int bx, int by) {
            hasMoved_ = false;
            for (int i = 0; i < posModifiers.size(); i++) {
                hasMoved_ = hasMoved_ || posModifiers[i]->modifyPos(pos, velocity);
            }
            if (bx > 0) {
                pos->setX(pos->getX() > bx ? bx : pos->getX());
                pos->setX(pos->getX() < -bx ? -bx : pos->getX());
            }
            if (by > 0)
                pos->setY(pos->getY() > by ? by : pos->getY());
                pos->setY(pos->getY() < -by ? -by : pos->getY());
        };
        bool resetMove() {
            bool res = hasMoved_;
            hasMoved_ = false;
            return (res);
        };

        statusEntity getStatus() { return (statusE); };
        void setLIfe(int life) { lifeLeft = life; };
        int getLife() { return (lifeLeft); };
        void setTeam(int team_) { team = team_; };
        std::shared_ptr<ColBox> getColBox() { return (colBox_); };
        bool collideWith(std::shared_ptr<Entity> other) {
            if (other->getId()->typeId == getId()->typeId)
                return (false);
            if (!other->isAlive() || !isAlive())
                return (false);
            auto c1 = colBox_;
            auto c2 = other->getColBox();
            auto p1 = pos;
            auto p2 = other->getPos();
            if (isOnSameLayer(c1->getLayers(), c2->getLayers())) {
                bool xOver = valueInRange(p1->getX(), p2->getX(), p2->getX() + c2->getX()) || valueInRange(p2->getX(), p1->getX(), p1->getX() + c1->getX());
                bool yOver = valueInRange(p1->getY(), p2->getY(), p2->getY() + c2->getY()) || valueInRange(p2->getY(), p1->getY(), p1->getY() + c1->getY());
                return (xOver && yOver);
            }
            return (false);
        };

        void setStatus(statusEntity s) {
            statusE = s;
            if (s == HIT)
                clock->startClock();
        };
        void removeHP(int nb) {
            if (statusE != ALIVE)
                return;
            lifeLeft -= nb;
            if (lifeLeft <= 0) {
                posModifiers.clear();
                posModifiers.emplace_back(std::shared_ptr<APositionModifier>(new Stationary()));
                colBox_->killColBox();
            }
        };
        bool isAlive() { return (lifeLeft > 0); };

    private:
        bool isOnSameLayer(int l1, int l2) {
            if((l1 & l2) > 0)
                return (true);
            return (false);
        };

        bool valueInRange(int value, int min, int max) {
            return ((value >= min) && (value <= max));
        };

        std::shared_ptr<Pos> pos;
        std::shared_ptr<Velocity> velocity;
        std::vector<std::shared_ptr<APositionModifier>> posModifiers;
        id::id_t *id_;
        bool hasMoved_;
        int lifeLeft;
        int team;
        statusEntity statusE = ALIVE;
        std::shared_ptr<ColBox> colBox_;
        int counter;
        Clock::StartableClock *clock;
};

#endif