project(RType)
cmake_minimum_required(VERSION 3.14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

if (UNIX)
    add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)
    set(CMAKE_CXX_STANDARD 17)
    add_definitions("-fPIC")
endif()
if(WIN32)
    add_compile_options("/std:c++latest")
    add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
    set(CMAKE_CXX_FLAGS_DEBUG "/DWIN32 /D_WINDOWS /EHsc /WX /wd4355 /wd4251 /wd4250 /wd4996" CACHE STRING "Debug compiler flags" FORCE)
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

set(ENGINE_SOURCES
        engine/src/networking/AServer.cpp
        engine/src/sceneManagement/SceneManager.cpp
        engine/src/sceneManagement/AScene.cpp
        engine/src/graphical/ASprite.cpp
        engine/src/graphical/AEvents.cpp
        engine/src/graphical/ASound.cpp
        engine/src/graphical/AGraphical.cpp
        engine/src/graphical/AWindow.cpp
        engine/src/systems/DrawSystem.cpp
        engine/src/systems/DrawSystem.cpp
        engine/src/systems/MouseSystem.cpp
        engine/src/systems/InputSystem.cpp
        engine/src/systems/PhysicSystem.cpp
        engine/src/systems/ParallaxSystem.cpp
        engine/src/systems/AnimationSystem.cpp
        engine/src/sceneManagement/AEntityGroup.cpp
        engine/src/Timer.cpp
        engine/src/systems/AnimationSystem.cpp
        engine/src/graphical/AMusic.cpp
        engine/src/systems/MusicSystem.cpp)

set(ENGINE_INCLUDES
        engine/include/ecs/Entity.hpp
        engine/include/ecs/System.hpp
        engine/include/ecs/Component.hpp
        engine/include/networking/AServer.hpp
        engine/include/sceneManagement/SceneManager.hpp
        engine/include/sceneManagement/AScene.hpp
        engine/include/networking/AUdpSocketIO.hpp
        engine/include/networking/ATcpSocket.hpp
        engine/include/components/TransformComponent.hpp
        engine/include/components/SpriteComponent.hpp
        engine/include/systems/DrawSystem.hpp
        engine/include/graphical/ASprite.hpp
        engine/include/graphical/AGraphical.hpp
        engine/include/graphical/ASound.hpp
        engine/include/graphical/AEvents.hpp
        engine/include/graphical/AWindow.hpp
        engine/include/systems/DrawSystem.hpp
        engine/include/entities/Button.hpp
        engine/include/components/ClickableComponent.hpp
        engine/include/components/NetworkComponent.hpp
        engine/include/components/ControllerComponent.hpp
        engine/include/enumerations/Inputs.hpp
        engine/include/components/ColliderComponent.hpp
        engine/include/components/ChildrenComponent.hpp
        engine/include/components/VelocityComponent.hpp
        engine/include/components/MusicComponent.hpp
        engine/include/components/SoundComponent.hpp
        engine/include/systems/MouseSystem.hpp
        engine/include/tools/Geometry.hpp
        engine/include/systems/InputSystem.hpp
        engine/include/systems/PhysicSystem.hpp
        engine/include/entities/Drawable.hpp
        engine/include/tools/Utils.hpp
        engine/include/components/ParallaxComponent.hpp
        engine/include/systems/ParallaxSystem.hpp
        engine/include/entities/ParallaxSlide.hpp
        engine/include/Timer.hpp
        engine/include/components/AnimationComponent.hpp
        engine/include/systems/AnimationSystem.hpp
        engine/include/sceneManagement/AEntityGroup.hpp
        engine/include/sceneManagement/SceneRequest.hpp
        engine/include/enumerations/QueryType.hpp)
        engine/include/graphical/AMusic.hpp
        engine/include/graphical/IAudio.hpp
        engine/include/components/AudioComponent.hpp
        engine/include/tools/Time.hpp
        engine/include/entities/Music.hpp
        engine/include/tools/ATime.hpp
        engine/include/tools/TimeUnits.hpp 
		engine/include/systems/MusicSystem.hpp)

set(CLIENT_SOURCES
        client/src/main.cpp
        client/src/Core.cpp
        client/src/scenes/MainMenu.cpp
        client/src/sfml/WindowSFML.cpp
        client/src/sfml/SoundSFML.cpp
        client/src/sfml/EventsSFML.cpp
        client/src/sfml/GraphicalSFML.cpp
        client/src/scenes/Settings.cpp
        client/src/sfml/MusicSFML.cpp
)

set(CLIENT_INCLUDES
        client/include/Core.hpp
        client/include/scenes/MainMenu.hpp
        client/include/scenes/SceneType.hpp

        client/include/sfml/GraphicalSFML.hpp
        client/include/sfml/WindowSFML.hpp
        client/include/sfml/EventsSFML.hpp
        client/include/sfml/SoundSFML.hpp

        client/src/sfml/SpriteSfml.cpp
        client/include/sfml/SpriteSfml.hpp
        client/include/scenes/SceneType.hpp
        client/include/scenes/Settings.hpp 
		client/include/scenes/GroupId.hpp 
		client/include/scenes/Groups.hpp 
		client/include/Layer.hpp)
        client/include/scenes/Settings.hpp
        client/include/sfml/MusicSFML.hpp
        )

set(SERVER_SOURCES
        server/main.cpp
        server/core/Core.cpp
        server/client/Client.cpp
        server/lobby/lobbyManager/LobbyManager.cpp
        server/lobby/lobby/Lobby.cpp
        )

set(SERVER_INCLUDES
        server/core/Core.hpp
        server/client/Client.hpp
        server/lobby/lobbyManager/LobbyManager.hpp
        server/lobby/lobby/Lobby.hpp
        )

add_executable(r-type_client ${ENGINE_SOURCES} ${ENGINE_INCLUDES} ${CLIENT_SOURCES} ${CLIENT_INCLUDES})
add_executable(r-type_server ${ENGINE_SOURCES} ${ENGINE_INCLUDES} ${SERVER_SOURCES} ${SERVER_INCLUDES})

target_include_directories(r-type_server PRIVATE
        server/core
        engine/include
        server/client
        server/lobby/lobbyManager
        server/lobby/lobby)
target_include_directories(r-type_client PRIVATE
        client/include
        engine/include)

message("===========================================")
message(${CONAN_LIBS})
message("===========================================")

target_link_libraries(r-type_client ${CONAN_LIBS})
target_link_libraries(r-type_server ${CONAN_LIBS})

#if(MSVC)
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
