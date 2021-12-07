/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** userDatabase
*/

#ifndef USERDATABASE_HPP_
#define USERDATABASE_HPP_

#include <string>
#include <map>
#include "entityHandler.hpp"

namespace rtype
{
    namespace database
    {
        class userDatabase
        {
            protected:
            inline userDatabase(){ _goSalon = false; _game = false; _isFull = false; _nbReady = 0; _imReady = false; _nbPlayer = 1; _myPos = 1;};
            inline static userDatabase * userDatabase_;
            inline static std::map<std::string, std::string> _playersNames;
            inline static uint8_t _idSalon;
            inline static int _port;
            inline static std::string _ip;
            inline static bool _game;
            inline static bool _isFull;
            inline static bool _goSalon;
            inline static bool _imReady;
            inline static int _nbReady;
            inline static int _nbPlayer;
            inline static int _myPos;

            public:
            userDatabase(userDatabase &other) = delete;
            inline ~userDatabase(){delete userDatabase_;};
            void operator=(const userDatabase &) = delete;
            static void init();

            static userDatabase *GetInstance();
            static std::string getPlayerName(std::string search);
            static void setPlayerName(std::string key, std::string value);
            inline static uint8_t getIdSalon(){return _idSalon;};
            inline static void setIdSalon(uint8_t id){_idSalon = id;};
            inline static int getPort(){return _port;};
            inline static void setPort(int port){_port = port;};
            inline static std::string getIp(){return _ip;};
            inline static void setIp(std::string ip){_ip = ip;};
            inline static void setGame(bool bo){_game = bo;};
            inline static bool getGame(){return _game;};
            inline static void setFull(bool bo){_isFull = bo;};
            inline static bool getFull(){return _isFull;};
            inline static void setGoSalon(bool bo){_goSalon = bo;};
            inline static bool getGoSalon(){return _goSalon;};
            inline static void setReady(bool bo){_imReady = bo;};
            inline static bool getReady(){return _imReady;};
            inline static void changeNbReady(int i){_nbReady += i;};
            inline static int getNbReady(){return _nbReady;};
            inline static void changeNbPlayer(int i){_nbPlayer += i;};
            inline static int getNbPlayer(){return _nbPlayer;};
            inline static void setMyPos(int i){_myPos = i;};
            inline static int getMyPos(){return _myPos;};
            inline static rtype::entity::REntityHandler *_gameHandler;
        };
    }
}

#endif /* !USERDATABASE_HPP_ */
