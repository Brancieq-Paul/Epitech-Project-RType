/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** userDatabase
*/

#include "userDatabase.hpp"
#include "../clientErrors/errWindowNotInitialized.hpp"

rtype::database::userDatabase *rtype::database::userDatabase::GetInstance()
{
    if (userDatabase_ == nullptr) {
        throw ErrorWindowNotInitialized(__FILE__, __LINE__);
    }
    return userDatabase_;
}

void rtype::database::userDatabase::init()
{
    if (userDatabase_ == nullptr)
    {
        userDatabase_ = new rtype::database::userDatabase();
        userDatabase_->_playersNames["USER"] = "PLAYER";
        userDatabase_->_playersNames["POne"] = "";
        userDatabase_->_playersNames["PTwo"] = "";
        userDatabase_->_playersNames["PThree"] = "";
        userDatabase_->_playersNames["PFour"] = "";
        userDatabase_->_ip = "127.0.0.1";
        userDatabase_->_port = 4242;
        userDatabase_->_idSalon = 1;
    }
}

std::string rtype::database::userDatabase::getPlayerName(std::string search)
{
    auto pos = _playersNames.find(search);
    if (pos == _playersNames.end())
        return ("NONE");
    else {
        std::string res = _playersNames.at(search);
        return res;
    }
}

void rtype::database::userDatabase::setPlayerName(std::string key, std::string value)
{
    if (value.empty())
        return;
    userDatabase_->_playersNames[key] = value;
    std::cout << "IN FONCTION : " << userDatabase_->_playersNames[key] << std::endl;
    // std::cout << "IN FONCTION KEY : " << key << std::endl;
    // std::cout << "IN FONCTION VALUE : " << value << std::endl;
}
