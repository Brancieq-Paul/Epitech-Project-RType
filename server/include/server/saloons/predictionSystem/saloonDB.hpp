/*
** EPITECH PROJECT, 2021
** SaloonDB
** File description:
** SaloonDB
*/

#ifndef SALOON_DB_HPP_
#define SALOON_DB_HPP_

#include "../../../elems/entity.hpp"
#include "../../../elems/positionModifier/modifiers/controledByPlayer.hpp"
#include <vector>
#include "../../../elems/archetype.hpp"
#include <string>
#include "../../../constantsServer.hpp"
#include "../../../verbose.hpp"

class SaloonDB {
    public:
        SaloonDB();
        ~SaloonDB() {};

        void addEntity(int tid, int sid);
        std::vector<std::shared_ptr<Entity>> getEntities();
        void updateEntity(int tid, int sid, int vx, int vy);
        void updateOrCreateEntityArchetypeScripts(int type, int scripts, std::vector<uint8_t> data);
        void updateOrCreateEntityArchetypeDefaultPos(int type, int x, int y);
        void updateOrCreateEntityArchetypeCollBox(int type, int dimx, int dimy, int layers);
        bool addPseudo(std::string p);
        void createNewEntity(int id, int tid, int posx, int posy, int team);
        void removePseudo(std::string p);
        void aPlayerWantToPlay(std::string p, bool ready);
        std::vector<std::string> getPseudos();
        bool readyToPLay();
        int getArchetypesNB() { return (archetypes.size()); };

    private:
        std::vector<std::shared_ptr<Entity>> entities;
        std::vector<std::string> ps;
        std::vector<std::unique_ptr<Archetype>> archetypes;
        std::vector<bool> wannaPlay;
        int worldBoundaryX = -1;
        int worldBoundaryY = -1;
};

#endif