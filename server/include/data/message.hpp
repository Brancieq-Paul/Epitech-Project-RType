/*
** EPITECH PROJECT, 2021
** message
** File description:
** message
*/

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <vector>
#include <string>
#include <iostream>
#include "../verbose.hpp"
#include "../constantsServer.hpp"
#include "../verbose.hpp"

namespace message {
    static std::vector<uint8_t> stringToUint8(std::string s) {
        std::vector<uint8_t> d;
        for (int i = 0; i < 10; i++) {
            if (s.size() > i)
                d.emplace_back(s[i]);
            else
                d.emplace_back(0);
        }
        return (d);
    };

    static std::vector<uint8_t> intToUint8(int i) {
        std::vector<uint8_t> d;
        d.emplace_back((uint8_t) ((i & 0xff000000) >> 24));
        d.emplace_back((uint8_t) ((i & 0x00ff0000) >> 16));
        d.emplace_back((uint8_t) ((i & 0x0000ff00) >> 8));
        d.emplace_back((uint8_t) ((i & 0x000000ff)));
        return (d);
    };

    static int uint8ToInt(std::vector<uint8_t> nb) {
        int res;
        if (nb.size() != 4)
            return (-1);
        res = nb[0];
        res = (res << 8) + nb[1];
        res = (res << 8) + nb[2];
        res = (res << 8) + nb[3];
        return (res);
    };

    static int16_t uint82Toint16(uint8_t biggest, uint8_t smallest) {
        int16_t res = biggest;
        res = (res << 8) + smallest;
        return (res);
    };

    static int uint84ToInt(uint8_t biggest, uint8_t intermediateBig, uint8_t intermediateSmall, uint8_t smallest) {
        int res = biggest;
        res = (res << 8) + intermediateBig;
        res = (res << 8) + intermediateSmall;
        res = (res << 8) + smallest;
        return (res);
    };

    static uint uint84ToUint(uint8_t biggest, uint8_t intermediateBig, uint8_t intermediateSmall, uint8_t smallest) {
        uint res = biggest;
        res = (res << 8) + intermediateBig;
        res = (res << 8) + intermediateSmall;
        res = (res << 8) + smallest;
        return (res);
    };

    static int arrayToUint8(std::vector<uint8_t> a, int s, int e) {
        if (e - s == 3 && a.size() > e)
            return (uint84ToInt(a[s], a[s + 1], a[s + 2], a[s + 3]));
        Verbose::debugCriticalMessage("Invalid conversion from array to int!", __FILE__, __LINE__);
        return (0);
    };

    namespace UDP {

        typedef struct s_messageUDP {
            uint8_t id;
            std::vector<uint8_t> body;
        } messageUDP_t;

        typedef struct s_responseUDP {
            std::vector<std::string> to;
            messageUDP_t *message;
        } responseUDP_t;

        static int getLengthMessage() {
            return (LENGTH_UDP_MESSAGE);
        };

        static responseUDP_t *createResponse(messageUDP_t *msg) {
            responseUDP_t *res = new responseUDP_t();

            res->to = {"All"};
            res->message = msg;
            return (res);
        };

        static messageUDP_t *createMessage(uint8_t id_, std::vector<uint8_t> data) {
            messageUDP_t *res = new messageUDP_t();

            for (int i = 0; i < LENGTH_UDP_MESSAGE; i++) {
                if (i < data.size())
                    res->body.emplace_back(data[i]);
                else
                    res->body.emplace_back(0);
            }
            res->id = id_;
            return (res);
        };

        static messageUDP_t *messageFromData(uint8_t data[LENGTH_UDP_MESSAGE]) {
            messageUDP_t *res = new messageUDP_t();

            if (LENGTH_UDP_MESSAGE == 0) {
                res->id = 0;
                return (res);
            }
            res->id = data[0];
            for (int i = 1; i < LENGTH_UDP_MESSAGE; i++)
                res->body.emplace_back(data[i]);
            Verbose::simpleDebugMessageWithColor("The following raw UDP message was received:", Verbose::CYAN, true);
            for (int i = 0; i < LENGTH_UDP_MESSAGE; i++) {
                if (i != 0)
                    Verbose::simpleDebugMessageWithColor("|", Verbose::RED, false);
                Verbose::simpleDebugMessageWithColor(std::to_string((int) data[i]), Verbose::CYAN, false);
            }
            Verbose::simpleDebugMessageWithColor("", Verbose::CYAN, true);
            return (res);
        };

        static void loadData(messageUDP_t *message, uint8_t res[LENGTH_UDP_MESSAGE]) {
            if (LENGTH_UDP_MESSAGE == 0)
                return;
            res[0] = message->id;
            for (int i = 0; i < LENGTH_UDP_MESSAGE - 1; i++) {
                if (i < message->body.size())
                    res[i + 1] = message->body[i];
                else
                    res[i + 1] = 0;
            }
            Verbose::simpleDebugMessageWithColor("The following raw UDP message was sent:", Verbose::CYAN, true);
            for (int i = 0; i < LENGTH_UDP_MESSAGE; i++) {
                if (i != 0)
                    Verbose::simpleDebugMessageWithColor("|", Verbose::RED, false);
                Verbose::simpleDebugMessageWithColor(std::to_string((int) res[i]), Verbose::CYAN, false);
            }
            Verbose::simpleDebugMessageWithColor("", Verbose::CYAN, true);
        };
    };

    namespace TCP {

        typedef struct s_messageTCP {
            uint8_t id;
            std::vector<uint8_t> body;
        } messageTCP_t;

        typedef struct s_responseTCP {
            std::vector<std::string> to;
            messageTCP_t *message;
        } responseTCP_t;

        static int getLengthMessage() {
            return (LENGTH_TCP_MESSAGE);
        };

        static responseTCP_t *createResponse(messageTCP_t *msg, std::vector<std::string> to_) {
            responseTCP_t *res = new responseTCP_t();

            res->message = msg;
            res->to = to_;
            return (res);
        };

        static messageTCP_t *createMessage(uint8_t id_, std::vector<uint8_t> data) {
            messageTCP_t *res = new messageTCP_t();

            for (int i = 0; i < LENGTH_TCP_MESSAGE; i++) {
                if (i < data.size())
                    res->body.emplace_back(data[i]);
                else
                    res->body.emplace_back(0);
            }
            res->id = id_;
            return (res);
        };

        static messageTCP_t *messageFromData(uint8_t data[LENGTH_TCP_MESSAGE]) {
            messageTCP_t *res = new messageTCP_t();

            if (LENGTH_TCP_MESSAGE == 0) {
                res->id = 0;
                return (res);
            }
            res->id = data[0];
            for (int i = 1; i < LENGTH_TCP_MESSAGE; i++)
                res->body.emplace_back(data[i]);
            Verbose::simpleDebugMessageWithColor("The following raw TCP message was received:", Verbose::CYAN, true);
            for (int i = 0; i < LENGTH_TCP_MESSAGE; i++) {
                if (i != 0)
                    Verbose::simpleDebugMessageWithColor("|", Verbose::RED, false);
                Verbose::simpleDebugMessageWithColor(std::to_string((int) data[i]), Verbose::CYAN, false);
            }
            Verbose::simpleDebugMessageWithColor("", Verbose::CYAN, true);
            return (res);
        };

        static void loadData(messageTCP_t *message, uint8_t res[LENGTH_TCP_MESSAGE]) {
            if (LENGTH_TCP_MESSAGE == 0)
                return;
            res[0] = message->id;
            for (int i = 0; i < LENGTH_TCP_MESSAGE - 1; i++) {
                if (i < message->body.size())
                    res[i + 1] = message->body[i];
                else
                    res[i + 1] = 0;
            }
            Verbose::simpleDebugMessageWithColor("The following raw TCP message was sent:", Verbose::CYAN, true);
            for (int i = 0; i < LENGTH_TCP_MESSAGE; i++) {
                if (i != 0)
                    Verbose::simpleDebugMessageWithColor("|", Verbose::RED, false);
                Verbose::simpleDebugMessageWithColor(std::to_string((int) res[i]), Verbose::CYAN, false);
            }
            Verbose::simpleDebugMessageWithColor("", Verbose::CYAN, true);
        };
    };
};

#endif