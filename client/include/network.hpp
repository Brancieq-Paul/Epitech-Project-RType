/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** network
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

namespace rtype
{
    namespace client
    {
        namespace network
        {
            class serverBoost
            {
            public:
                inline serverBoost(){};
                inline ~serverBoost(){};

            private:
                socketTCP _myTCP;
                socketUDP _myUDP;
            };

            class socketTCP
            {
            public:
                inline socketTCP(){};
                inline ~socketTCP(){};
            };

            class socketUDP
            {
            public:
                inline socketUDP(){};
                inline ~socketUDP(){};
            };
        }
    }
}

#endif /* !NETWORK_HPP_ */
