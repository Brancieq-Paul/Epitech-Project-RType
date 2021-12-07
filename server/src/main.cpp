/*
** EPITECH PROJECT, 2021
** main
** File description:
** babel
*/

#include <iostream>

#include "../include/error.hpp"
#include "../include/errors/errUsage.hpp"
#include "../include/server/server.hpp"
#include "../include/server/asioServer.hpp"
#include "../include/verbose.hpp"

int main(int ac, char *av[]) {
    try {
        if (ac > 3)
            throw (ErrorUsage());
        if(ac == 2) {
            std::string tmp = av[1];
            if (tmp == "verbose==true")
                Verbose::showDebugMessage(true);
            else
                throw (ErrorUsage());
            Verbose::simpleDebugMessage("Waiting for clients...");
        }

        boost::asio::io_service io_service;
        Clock::MasterClock *masterClock = Clock::MasterClockSingleton::getInstance(io_service);
        masterClock->run();
        server::IServer *serv = new AsioServer(io_service, 9999);
        serv->start();
        io_service.run();
        Verbose::debugCriticalMessage("Should not happen!", __FILE__, __LINE__);
    } catch (ErrorUsage &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    } catch (Error &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << e.where() << " ligne: " << e.on() << std::endl;
        return (84);
    } catch (std::logic_error &e) {
        std::cerr << "atoi: " << e.what() << std::endl;
        return (84);
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return (84);
    }
    return (0);
}