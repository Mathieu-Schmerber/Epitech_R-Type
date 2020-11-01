project(RType)
cmake_minimum_required(VERSION 3.14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

if (UNIX)
    set(CMAKE_CXX_STANDARD 17)
    add_definitions("-fPIC")
endif()
if(WIN32)
    add_compile_options("/std:c++latest")
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

set(ENGINE_SOURCES
        engine/src/AServer.cpp
        engine/src/SceneManager.cpp
        engine/src/AScene.cpp
        engine/src/components/TransformComponent.cpp
        engine/src/components/SpriteComponent.cpp
        engine/src/Graphical/ASprite.cpp
        engine/src/systems/DrawSystem.cpp
        engine/src/Graphical/AEvents.cpp
        engine/src/Graphical/ASound.cpp
        engine/src/Graphical/AGraphical.cpp
        engine/src/Graphical/AWindow.cpp

        )

set(ENGINE_INCLUDES
        engine/include/ecs/Entity.hpp
        engine/include/ecs/System.hpp
        engine/include/ecs/Component.hpp
        engine/include/AServer.hpp
        engine/include/SceneManager.hpp
        engine/include/AScene.hpp
        engine/include/AUdpSocket.hpp
        engine/include/ATcpSocket.hpp
        engine/include/components/TransformComponent.hpp
        engine/include/components/SpriteComponent.hpp
        engine/include/Graphical/ASprite.hpp
        engine/include/systems/DrawSystem.hpp
        engine/include/Graphical/AGraphical.hpp
        engine/include/Graphical/ASound.hpp
        engine/include/Graphical/AEvents.hpp
        engine/include/Graphical/AWindow.hpp

        )

set(CLIENT_SOURCES
        client/src/main.cpp
        client/src/Core.cpp
        client/src/scenes/MainMenu.cpp
        client/src/sfml/WindowSFML.cpp
        client/src/sfml/SoundSFML.cpp
        client/src/sfml/EventsSFML.cpp
        client/src/sfml/GraphicalSFML.cpp
        )

set(CLIENT_INCLUDES
        client/include/Core.hpp
        client/include/scenes/MainMenu.hpp
        client/include/scenes/SceneType.hpp
        client/include/entities/Button.hpp
        client/include/sfml/GraphicalSFML.hpp
        client/include/sfml/WindowSFML.hpp
        client/include/sfml/EventsSFML.hpp
        client/include/sfml/SoundSFML.hpp

        engine/include/Graphical/SpriteSfml.cpp engine/include/Graphical/SpriteSfml.hpp)

set(SERVER_SOURCES
        server/main.cpp
        server/Core/Core.cpp
        server/Client/Client.cpp
        server/Lobby/LobbyManager/LobbyManager.cpp
        server/Lobby/Lobby/Lobby.cpp)

set(SERVER_INCLUDES
        server/Core/Core.hpp
        server/Client/Client.hpp
        server/Lobby/LobbyManager/LobbyManager.hpp
        server/Lobby/Lobby/Lobby.hpp)

add_executable(r-type_client ${ENGINE_SOURCES} ${ENGINE_INCLUDES} ${CLIENT_SOURCES} ${CLIENT_INCLUDES})
add_executable(r-type_server ${ENGINE_SOURCES} ${ENGINE_INCLUDES} ${SERVER_SOURCES} ${SERVER_INCLUDES})

target_include_directories(r-type_server PRIVATE
        server/Core
        engine/include
        server/Client
        server/Lobby/LobbyManager
        server/Lobby/Lobby)
target_include_directories(r-type_client PRIVATE
        client/include
        engine/include)

message("===========================================")
message(${CONAN_LIBS})
message("===========================================")

target_link_libraries(r-type_server ${CONAN_LIBS})
target_link_libraries(r-type_client ${CONAN_LIBS})

#if(MSVC)
#    set(CMAKE_CXX_FLAGS_DEBUG "/DWIN32 /D_WINDOWS /EHsc /WX /wd4355 /wd4251 /wd4250 /wd4996" CACHE STRING "Debug compiler flags" FORCE)
#    set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
#    set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
#    set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
#    set(Boost_USE_MULTITHREADED      ON)
#    set(Boost_USE_STATIC_RUNTIME     OFF)
#    find_package(Boost 1.71.0 COMPONENTS serialization)
#    if(Boost_FOUND)
#        include_directories(${Boost_INCLUDE_DIRS})
#        target_link_libraries(r-type_client ${Boost_LIBRARIES})
#        target_link_libraries(r-type_server ${Boost_LIBRARIES})
#    endif()
#endif()
