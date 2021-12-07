/*
** EPITECH PROJECT, 2021
** collisionBox
** File description:
** collisionBox
*/

#include "../../../../include/command/commands/tcp/dataLoading/collisionbox.hpp"
#include <sstream>

std::vector<message::TCP::responseTCP_t *> CollisionBox::execute(Saloon *saloon, SaloonManager *manager)
{
    UNUSED(manager);
    std::vector<message::TCP::responseTCP_t *> res;
    if (saloon == NULL)
        return (res);
    auto db = saloon->getDB();
    db->updateOrCreateEntityArchetypeCollBox(typeSprite, dimx, dimy, layers);
    return (res);
};

std::string toBinary(int n)
{
    std::string r = "00000000000000000000000000000000";
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
}

CollisionBox::CollisionBox(std::vector<uint8_t> body){
    typeSprite = message::arrayToUint8(body, 0, 3);
    dimx = message::arrayToUint8(body, 4, 7);
    dimy = message::arrayToUint8(body, 8, 11);
    layers = message::arrayToUint8(body, 12, 15);
    std::stringstream s;
    s << "Collision box of '" << typeSprite << "' of dim x '" << dimx << "' and dim y '" << dimy << "' on layers '" << layers << "'" << std::endl;
    Verbose::logInError(s.str());
};
