/*
** EPITECH PROJECT, 2021
** MovScripts
** File description:
** MovScripts
*/

#include "../../../../include/command/commands/tcp/dataLoading/scripts.hpp"
#include <sstream>

std::vector<message::TCP::responseTCP_t *> MovScripts::execute(Saloon *saloon, SaloonManager *manager)
{
    std::vector<message::TCP::responseTCP_t *> res;
    UNUSED(manager);
    if (saloon == NULL)
        return (res);
    saloon->getDB()->updateOrCreateEntityArchetypeScripts(type_, scripts, data);
    return (res);
};

MovScripts::MovScripts(std::vector<uint8_t> body) {
    type_ = message::uint84ToInt(body[0], body[1], body[2], body[3]);
    scripts = body[4];
    data.insert(data.begin(), body.begin() + 5, body.end());
    std::stringstream s;
    s << "Script '" << scripts << "' added to type '" << type_ << "'" << std::endl;
    for (int i = 5; i < body.size(); i++)
        s << ((int) body[i]) << "|";
    s << std::endl;
    Verbose::logInError(s.str());
};
