/*
** EPITECH PROJECT, 2021
** saloonDB
** File description:
** saloonDB
*/

#include "../../../../include/server/saloons/predictionSystem/saloonDB.hpp"

SaloonDB::SaloonDB()
{
    for (int i = 0; i < MAX_PLAYER_PER_SALOON; i++)
        wannaPlay.emplace_back(false);
};

void SaloonDB::addEntity(int tid, int sid)
{
    entities.emplace_back(std::shared_ptr<Entity>(new Entity(0, 0, sid, tid, std::shared_ptr<ColBox>(new ColBox(0, 0, 0)))));
};

std::vector<std::shared_ptr<Entity>> SaloonDB::getEntities() { return (entities); };

void SaloonDB::updateEntity(int tid, int sid, int vx, int vy)
{
    for (auto e : entities)
    {
        if (e->getId()->spriteId == sid && e->getId()->typeId == tid)
        {
            e->getVelocity()->setVx(vx);
            e->getVelocity()->setVy(vy);
            return;
        }
    }
    for (int i = 0; i < archetypes.size(); i++)
    {
        if (archetypes[i]->getType() == tid)
        {
            auto newE = archetypes[i]->convertToEntity(sid, 0, 0, 0);
            newE->getVelocity()->setVx(vx);
            newE->getVelocity()->setVy(vy);
            entities.emplace_back(newE);
            return;
        }
    }
    addEntity(tid, sid);
};

void SaloonDB::updateOrCreateEntityArchetypeScripts(int type, int scripts, std::vector<uint8_t> data)
{
    bool found = false;
    for (int i = 0; i < archetypes.size(); i++)
    {
        if (archetypes[i]->getType() == type)
        {
            archetypes[i]->setPosModifierScripts(scripts, data);
            found = true;
        }
    }
    if (!found)
    {
        archetypes.emplace_back(std::unique_ptr<Archetype>(new Archetype(type)));
        archetypes[archetypes.size() - 1]->setPosModifierScripts(scripts, data);
    }
};

void SaloonDB::updateOrCreateEntityArchetypeDefaultPos(int type, int x, int y)
{
    bool found = false;
    for (int i = 0; i < archetypes.size(); i++)
    {
        if (archetypes[i]->getType() == type)
        {
            archetypes[i]->defineDefaultPos(x, y);
            found = true;
        }
    }
    if (!found)
    {
        archetypes.emplace_back(std::unique_ptr<Archetype>(new Archetype(type)));
        archetypes[archetypes.size() - 1]->defineDefaultPos(x, y);
    }
};

void SaloonDB::updateOrCreateEntityArchetypeCollBox(int type, int dimx, int dimy, int layers)
{
    bool found = false;
    for (int i = 0; i < archetypes.size(); i++)
    {
        if (archetypes[i]->getType() == type)
        {
            archetypes[i]->setColBoxes(dimx, dimy, layers);
            found = true;
        }
    }
    if (!found)
    {
        archetypes.emplace_back(std::unique_ptr<Archetype>(new Archetype(type)));
        archetypes[archetypes.size() - 1]->setColBoxes(dimx, dimy, layers);
    }
};

bool SaloonDB::addPseudo(std::string p)
{
    if (ps.size() > 4)
        return (false);
    ps.emplace_back(p);
    return (true);
};

void SaloonDB::createNewEntity(int id, int tid, int posx, int posy, int team)
{
    for (int i = 0; i < archetypes.size(); i++)
    {
        if (archetypes[i]->getType() == tid)
        {
            auto e = archetypes[i]->convertToEntity(id, posx, posy, team);
            entities.emplace_back(e);
            return;
        }
    }
    archetypes.emplace_back(std::unique_ptr<Archetype>(new Archetype(tid)));
    entities.emplace_back(archetypes[archetypes.size() - 1]->convertToEntity(id, posx, posy, team));
};

void SaloonDB::removePseudo(std::string p)
{
    for (int i = 0; i < ps.size(); i++)
    {
        if (ps[i] == p)
        {
            ps.erase(ps.begin() + i);
            wannaPlay[i] = false;
            return;
        }
    }
};

void SaloonDB::aPlayerWantToPlay(std::string p, bool ready)
{
    int i = 0;
    for (; i < ps.size() && i < MAX_PLAYER_PER_SALOON; i++)
        if (ps[i] == p)
            wannaPlay[i] = ready;
};

std::vector<std::string> SaloonDB::getPseudos()
{
    std::vector<std::string> res;
    for (int i = 0; i < MAX_PLAYER_PER_SALOON; i++)
    {
        if (ps.size() > i)
            res.emplace_back(ps[i]);
        else
            res.emplace_back("");
    }
    return (res);
};

bool SaloonDB::readyToPLay()
{
    if (ps.size() == 0)
        return (false);
    bool res = true;
    for (int i = 0; i < ps.size(); i++)
        res = res && wannaPlay[i];
    return (res);
};