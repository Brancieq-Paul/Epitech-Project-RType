/*
** EPITECH PROJECT, 2021
** generateResponses
** File description:
** generateResponses
*/

#ifndef GENERATE_RESPONSES_HPP_
#define GENERATE_RESPONSES_HPP_

#include "../../data/message.hpp"
#include "../commandFactory.hpp"

namespace Generator {
    namespace UDP {
        class ResponseGeneratorUDP {
            private:
                ResponseGeneratorUDP() {};
                ~ResponseGeneratorUDP() {};
            public:
                static message::UDP::responseUDP_t *generateServerPositionUpdate(int x, int y, int typeId, int spriteId);
                static message::UDP::responseUDP_t *generateServerEntityStatusUpdate(int life, int typeId, int spriteId, uint8_t status);
        };
    };
    namespace TCP {
        class ResponseGeneratorTCP {
            private:
                ResponseGeneratorTCP() {};
                ~ResponseGeneratorTCP() {};
            public:
                static message::TCP::responseTCP_t *generateServerGameLaunched();
                static message::TCP::responseTCP_t *generateServerSaloonCreated(uint8_t idSaloonCreated);
                static message::TCP::responseTCP_t *generateServerUpdateToSaloonComposition(std::vector<std::string> names);
                static message::TCP::responseTCP_t *generateServerDeconnexionOfClient(uint8_t posOfLeaver);
                static message::TCP::responseTCP_t *generateServerUDPPortToUse(int port);
                static message::TCP::responseTCP_t *generateServerSaloonFull(int idSession);
        };
    };
};

#endif