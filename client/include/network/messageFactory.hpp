/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** messageFactory
*/

#ifndef MESSAGEFACTORY_HPP_
#define MESSAGEFACTORY_HPP_

#include <map>
#include "message.hpp"

namespace rtype
{
    namespace sendmfactory
    {

        enum TypeMessage
        {
            SpeedEntity,
            CreateEntity,
            NONE_UDP
        };

        enum TypeMessageTCP
        {
            CreateSalon,
            JoinSalon,
            QuitSalon,
            ReadySalon,
            SendConfigType,
            SendScriptType,
            SendWindowSize,
            NONE_TCP
        };


        class Imessage
        {
        public:
            virtual message::UDP::messageUDP_t *getMessageUDP() = 0;
            virtual message::TCP::messageTCP_t *getMessageTCP() = 0;
        };

        class Amessage : public Imessage
        {
        public:
            inline Amessage(){};
            inline ~Amessage(){};
            inline message::UDP::messageUDP_t *getMessageUDP() { return _messageUDP; };
            inline message::TCP::messageTCP_t *getMessageTCP() { return _messageTCP; };

        protected:
            message::UDP::messageUDP_t *_messageUDP;
            message::TCP::messageTCP_t *_messageTCP;
        };

        class messageSpeed : public Amessage
        {
        public:
            messageSpeed(std::vector<uint8_t> data);
            inline ~messageSpeed(){};
        };

        class messageCreate : public Amessage
        {
        public:
            messageCreate(std::vector<uint8_t> data);
            inline ~messageCreate(){};
        };

        class messageFactory
        {
        public:
            inline messageFactory(){};
            inline ~messageFactory(){};
            virtual rtype::sendmfactory::Imessage *createUDPMessage(TypeMessage type, std::vector<uint8_t> data);
            virtual rtype::sendmfactory::Imessage *createTCPMessage(TypeMessageTCP type, std::vector<uint8_t> dataNb, std::vector<std::string> dataStr);
        };

        namespace TCP
        {
            class messageCreateSalon : public Amessage
            {
                public:
                messageCreateSalon(std::vector<std::string> dataStr);
                inline ~messageCreateSalon(){};
            };

            class messageJoinSalon : public Amessage
            {
                public:
                messageJoinSalon(std::vector<uint8_t> dataNb, std::vector<std::string> dataStr);
                inline ~messageJoinSalon(){};
            };

            class messageQuitSalon : public Amessage
            {
                public:
                messageQuitSalon();
                inline ~messageQuitSalon(){};
            };

            class messageSendConfigType : public Amessage
            {
                public:
                messageSendConfigType(std::vector<uint8_t> dataNb);
                inline ~messageSendConfigType(){};
            };


            class messageReadySalon : public Amessage
            {
                public:
                messageReadySalon(std::vector<uint8_t> dataNb);
                inline ~messageReadySalon(){};
            };

            class messageSendScriptType : public Amessage
            {
                public:
                messageSendScriptType(std::vector<uint8_t> dataNb);
                inline ~messageSendScriptType(){};
            };

            class messageWindowSize : public Amessage
            {
                public:
                messageWindowSize(std::vector<uint8_t> dataNb);
                inline ~messageWindowSize(){};
            };
        }

    }
}

#endif /* !MESSAGEFACTORY_HPP_ */
