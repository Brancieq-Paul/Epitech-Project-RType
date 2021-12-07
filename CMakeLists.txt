cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CONAN_DISABLE_CHECK_COMPILER TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -luuid")
project(Babel VERSION 0.1)

include(${CMAKE_BINARY_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)

set(server_src
    server/src/clock/masterClock.cpp
    server/src/clock/masterClockSingleton.cpp
	server/src/command/commands/tcp/clientLeaveSaloon.cpp
	server/src/command/commands/tcp/clientReadyToPlay.cpp
	server/src/command/commands/tcp/clientWantJoinSaloon.cpp
	server/src/command/commands/tcp/creationSaloonAsked.cpp
	server/src/command/commands/udp/entityCreation.cpp
	server/src/command/commands/udp/velocityUpdate.cpp
	server/src/command/generator/generateResponses.cpp
	server/src/command/command.cpp
	server/src/command/commandFactory.cpp
	server/src/server/saloons/predictionSystem/predictor.cpp
	server/src/server/saloons/predictionSystem/saloonPhysicSystem.cpp
	server/src/server/saloons/saloon.cpp
	server/src/server/saloons/saloonManager.cpp
	server/src/server/sessions/asioTCPSession.cpp
	server/src/server/sessions/asioUDPSession.cpp
	server/src/server/asioServer.cpp
	server/src/main.cpp
	server/src/verbose.cpp
    server/src/command/commands/dataloading/collisionBox.cpp
    server/src/command/commands/dataloading/scripts.cpp
    server/src/command/commands/dataloading/worldBoundaries.cpp
    server/src/server/saloons/predictionSystem/saloonDB.cpp
)

# add the executable
add_executable(r-type_server ${server_src})

include_directories(r-type_server ${CONAN_INCLUDE_DIRS})

target_link_libraries(r-type_server PRIVATE ${CONAN_LIBS})


file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/client/*.cpp)

include(${CMAKE_BINARY_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()


add_executable(r-type_client ${SRC})
target_include_directories(r-type_client PRIVATE ${CONAN_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/client/include/ ${CMAKE_CURRENT_SOURCE_DIR}/client/include/database/ ${CONAN_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/client/include/clientErrors/ ${CONAN_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/client/include/ecs/ ${CMAKE_CURRENT_SOURCE_DIR}/errors/ ${CMAKE_CURRENT_SOURCE_DIR}/client/include/network/ ${CMAKE_CURRENT_SOURCE_DIR}/client/include/scene/)
target_link_libraries(r-type_client ${CONAN_LIBS} ${CONAN_LIBS_SFML})
