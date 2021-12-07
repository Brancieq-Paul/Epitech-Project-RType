/*
** EPITECH PROJECT, 2021
** Verbose
** File description:
** Verbose
*/

#ifndef VERBOSE_HPP_
#define VERBOSE_HPP_

#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

#include <mutex>
#include <iostream>
#include <unordered_map>

namespace Verbose {

    enum COLOR {
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE
    };

    class Speaker;

    class SpeakerSingleton {
        private:
            static Speaker *instance;
            static std::mutex mutex_;

        protected:
            SpeakerSingleton() {};
            ~SpeakerSingleton() {};

        public:
            SpeakerSingleton(SpeakerSingleton &other) = delete;
            void operator=(const SpeakerSingleton &) = delete;
            static Speaker *getInstance();
    };

    class Speaker {
        friend Speaker *SpeakerSingleton::getInstance();
        protected:
            Speaker() {
                colorJunction = {
                    {RED, KRED},
                    {GREEN, KGRN},
                    {YELLOW, KYEL},
                    {BLUE, KBLU},
                    {MAGENTA, KMAG},
                    {CYAN, KCYN},
                    {WHITE, KWHT}
                };
            };
            ~Speaker() {};

        public:
            void showDebugMessage(bool verbose) {
                verbose_ = verbose;
            };
            void debugMessage(std::string msg, const char *file, int line) {
                if (verbose_)
                    std::cout << msg << " - " << file << " line:" << line << std::endl;
            };

            void debugCriticalMessage(std::string msg, const char *file, int line) {
                if (verbose_)
                    std::cout << "\x1B[31m" << msg << " - " << file << " l:" << line << RST << std::endl;
            };

            void debugMessageWithColor(std::string msg, const char *file, int line, COLOR c) {
                if (verbose_)
                    std::cout << colorJunction[c] << msg << " - " << file << " l:" << line << RST << std::endl;
            };

            void simpleDebugMessage(std::string msg) {
                if (verbose_)
                    std::cout << msg << std::endl;
            };

            void simpleDebugMessageWithColor(std::string msg, COLOR c, bool wLineBreak) {
                if (verbose_) {
                    std::cout << colorJunction[c] << msg << RST;
                    if (wLineBreak)
                        std::cout << std::endl;
                }
            };

            void logInError(std::string msg) {
                if (verbose_) {
                    std::cerr << msg << std::endl;
                }
            };

        private:
            bool verbose_ = false;
            std::unordered_map<COLOR, std::string> colorJunction;
    };

    static void debugMessage(std::string msg, const char *file, int line) {
        SpeakerSingleton::getInstance()->debugMessage(msg, file, line);
    };

    static void simpleDebugMessage(std::string msg) {
        SpeakerSingleton::getInstance()->simpleDebugMessage(msg);
    };

    static void debugCriticalMessage(std::string msg, const char *file, int line) {
        SpeakerSingleton::getInstance()->debugCriticalMessage(msg, file, line);
    };

    static void showDebugMessage(bool verbose) {
        SpeakerSingleton::getInstance()->showDebugMessage(verbose);
    };

    static void debugMessageWithColor(std::string msg, const char *file, int line, COLOR color) {
        SpeakerSingleton::getInstance()->debugMessageWithColor(msg, file, line, color);
    };

    static void simpleDebugMessageWithColor(std::string msg, COLOR color, bool wLineBreak) {
        SpeakerSingleton::getInstance()->simpleDebugMessageWithColor(msg, color, wLineBreak);
    };

    static void logInError(std::string msg) {
        SpeakerSingleton::getInstance()->logInError(msg);
    };
};

#endif