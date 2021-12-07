/*
** EPITECH PROJECT, 2021
** Archetype
** File description:
** Archetype
*/

#ifndef ARCHETYPE_HPP_
#define ARCHETYPE_HPP_

#include "positionModifier/factoryPosModifier.hpp"
#include "positionModifier/aPositionModifier.hpp"
#include "positionModifier/modifiers/stationary.hpp"
#include "entity.hpp"
#include "colBox.hpp"

class Archetype {
    public:
        Archetype(int type) :type_(type), defx(0), defy(0), colBox_(std::shared_ptr<ColBox>(new ColBox(0, 0, 0))), pv(1), invincibilityFrames(0) {
            scripts.emplace_back(new Stationary());
        };
        ~Archetype() {};
        void defineDefaultPos(int x, int y) {
            defx = x;
            defy = y;
        };

        std::shared_ptr<Entity> convertToEntity(int spriteID, int posx, int posy, int team) {
            std::shared_ptr<Entity> res = std::shared_ptr<Entity>(new Entity(posx, posy, spriteID, type_, colBox_));
            res->setLIfe(pv);
            res->setTeam(team);
            for (int i = 0; i < scripts.size(); i++)
                res->addPositionModifier(scripts[i]);
            return (res);
        }

        void setColBoxes(int x, int y, int layers) {
            colBox_ = std::shared_ptr<ColBox>(new ColBox(x, y, layers));
        };

        void setLife(int life, int invincFrames) { pv = life; invincibilityFrames = invincFrames; };

        void setPosModifierScripts(int type, std::vector<uint8_t> data) {
            scripts.emplace_back(FactoryPosModifier::createAPosModifier(FactoryPosModifier::getType(type), data));
        };

        int getType() { return (type_); };
        int getPosX() { return (defx); };
        int getPosY() { return (defy); };
        std::shared_ptr<ColBox> getColBox() { return (colBox_); };

    private:
        int type_;
        int defx;
        int defy;
        std::vector<std::shared_ptr<APositionModifier>> scripts;
        std::shared_ptr<ColBox> colBox_;
        int pv;
        int invincibilityFrames;
};

#endif