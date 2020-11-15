project(RType)
cmake_minimum_required(VERSION 3.14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

if (UNIX)
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
        engine/src/tools/Timer.cpp
		engine/src/graphical/AMusic.cpp
        engine/src/graphical/ATexture.cpp
		engine/src/graphical/AText.cpp
		engine/src/graphical/AFont.cpp
		engine/src/networking/AUdpSocketIO.cpp
		engine/src/systems/MoveSystem.cpp
		engine/src/systems/MoveSystem.cpp
		engine/src/networking/ATcpSocket.cpp
		engine/src/networking/UDP/UdpSocketInput.cpp
		engine/src/networking/UDP/UdpSocketOutput.cpp
		engine/src/systems/WindowResizeSystem.cpp
		engine/src/systems/TextSystem.cpp
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
        engine/src/tools/Timer.cpp
        engine/src/graphical/AMusic.cpp
        engine/src/graphical/ASoundBuffer.cpp
		engine/src/systems/WindowResizeSystem.cpp
		engine/src/systems/TextSystem.cpp
		engine/src/systems/ButtonSystem.cpp
		engine/src/graphical/ASoundBuffer.cpp
		engine/src/systems/ButtonSystem.cpp
		engine/src/tools/AssetPool.cpp
		engine/src/systems/ChildrenSystem.cpp 
		engine/src/systems/TargetSystem.cpp
		engine/src/systems/SoundSystem.cpp engine/include/systems/SoundSystem.hpp engine/src/systems/MusicSystem.cpp engine/include/systems/MusicSystem.hpp)

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
		engine/include/components/ClickableComponent.hpp
		engine/include/components/NetworkComponent.hpp
		engine/include/components/ControllerComponent.hpp
		engine/include/components/ColliderComponent.hpp
		engine/include/components/ChildrenComponent.hpp
		engine/include/components/VelocityComponent.hpp
		engine/include/components/MusicComponent.hpp
		engine/include/components/SoundComponent.hpp
		engine/include/components/ParallaxComponent.hpp
		engine/include/components/AnimationComponent.hpp
		engine/include/components/TextComponent.hpp
		engine/include/components/ButtonComponent.hpp
		engine/include/components/TextComponent.hpp
		engine/include/components/AudioComponent.hpp
		engine/include/systems/DrawSystem.hpp
		engine/include/graphical/ASprite.hpp
		engine/include/graphical/AGraphical.hpp
		engine/include/graphical/ASound.hpp
		engine/include/graphical/AEvents.hpp
		engine/include/graphical/AWindow.hpp
		engine/include/systems/DrawSystem.hpp
		engine/include/entities/Button.hpp
		engine/include/enumerations/Inputs.hpp
		engine/include/systems/MouseSystem.hpp
		engine/include/tools/Geometry.hpp
		engine/include/systems/InputSystem.hpp
		engine/include/systems/PhysicSystem.hpp
		engine/include/entities/Drawable.hpp
		engine/include/tools/Utils.hpp
		engine/include/systems/ParallaxSystem.hpp
		engine/include/entities/ParallaxSlide.hpp
		engine/include/tools/Timer.hpp
		engine/include/systems/AnimationSystem.hpp
		engine/include/sceneManagement/AEntityGroup.hpp
		engine/include/sceneManagement/SceneRequest.hpp
		engine/include/enumerations/QueryType.hpp
		engine/include/graphical/AMusic.hpp
		engine/include/graphical/IAudio.hpp
		engine/include/tools/Time.hpp
		engine/include/entities/Music.hpp
		engine/include/tools/ATime.hpp
		engine/include/tools/TimeUnits.hpp
        engine/include/graphical/ATexture.hpp
        engine/include/graphical/AText.hpp
		engine/include/graphical/AFont.hpp
		engine/include/tools/Color.hpp
		engine/include/networking/AUdpSocketIO.hpp
		engine/include/systems/MoveSystem.hpp
		engine/include/networking/AUdpSocketIO.hpp
		engine/include/networking/UDP/UdpSocketInput.hpp
		engine/include/networking/UDP/UdpSocketOutput.hpp
		engine/include/systems/MoveSystem.hpp
		engine/include/systems/WindowResizeSystem.hpp
		engine/include/systems/MoveSystem.hpp
		engine/include/systems/TextSystem.hpp
		engine/include/systems/ButtonSystem.hpp
		engine/include/systems/MoveSystem.hpp
        engine/include/graphical/AText.hpp
        engine/include/graphical/AFont.hpp
        engine/include/tools/Color.hpp
        engine/include/graphical/ASoundBuffer.hpp
        engine/include/components/TextComponent.hpp
        engine/include/graphical/ASoundBuffer.hpp
		engine/include/components/ButtonComponent.hpp
		engine/include/systems/ButtonSystem.hpp
		engine/include/tools/AssetPool.hpp
		engine/include/tools/DLLoader.hpp
		engine/include/tools/ADLLoader.hpp
		engine/include/entities/Text.hpp
		engine/include/tools/DynamicLibManager.hpp
		engine/include/systems/ChildrenSystem.hpp
		engine/include/tools/RandomETU.hpp
		engine/include/components/TargetComponent.hpp
		engine/include/systems/TargetSystem.hpp engine/include/tools/EngineExceptions.hpp engine/src/systems/SoundSystem.cpp engine/include/systems/SoundSystem.hpp engine/src/systems/MusicSystem.cpp engine/include/systems/MusicSystem.hpp)

set(CLIENT_SOURCES
		client/src/main.cpp
		client/src/Core.cpp
		client/src/scenes/MainMenu.cpp
		client/src/scenes/LobbyList.cpp
		client/src/sfml/WindowSFML.cpp
		client/src/sfml/SoundSFML.cpp
		client/src/sfml/EventsSFML.cpp
		client/src/sfml/GraphicalSFML.cpp
		client/src/scenes/Settings.cpp
		client/src/sfml/MusicSFML.cpp
		client/src/sfml/TextureSFML.cpp
		client/src/sfml/TextureSFML.cpp
		client/src/scenes/HowToPlay.cpp
		client/src/sfml/TextSFML.cpp
		client/src/sfml/FontSFML.cpp
		client/src/sfml/GraphicalSFML.cpp
		client/src/SocketParser.cpp
		client/src/systems/ClientNetworkSystem.cpp
		client/src/sfml/SpriteSfml.cpp
		client/src/scenes/InGame.cpp
		client/src/scenes/InGame.cpp
		client/src/systems/LobbySystem.cpp
		client/src/scenes/InGame.cpp
		client/src/systems/LobbySystem.cpp
		client/src/scenes/CreateLobby.cpp
        client/src/main.cpp
        client/src/Core.cpp
        client/src/scenes/MainMenu.cpp
        client/src/sfml/WindowSFML.cpp
        client/src/sfml/SoundSFML.cpp
        client/src/sfml/EventsSFML.cpp
        client/src/sfml/GraphicalSFML.cpp
        client/src/scenes/Settings.cpp
        client/src/sfml/MusicSFML.cpp
        client/src/sfml/TextureSFML.cpp
        client/src/sfml/TextureSFML.cpp
        client/src/scenes/HowToPlay.cpp
        client/src/sfml/TextSFML.cpp
        client/src/sfml/FontSFML.cpp
        client/src/sfml/SoundBufferSFML.cpp
		client/src/systems/LobbySystem.cpp
		client/src/scenes/LobbyWaiting.cpp
		client/src/systems/PlayerAndStarshipSystem.cpp)

set(CLIENT_INCLUDES
		client/include/Core.hpp
		client/include/scenes/MainMenu.hpp
		client/include/scenes/LobbyList.hpp
		client/include/scenes/SceneType.hpp
		client/include/sfml/GraphicalSFML.hpp
		client/include/sfml/WindowSFML.hpp
		client/include/sfml/EventsSFML.hpp
		client/include/sfml/SoundSFML.hpp
		client/include/sfml/SpriteSfml.hpp
		client/include/scenes/Settings.hpp
		client/include/scenes/GroupId.hpp
		client/include/scenes/Groups.hpp
		client/include/Layer.hpp
		client/include/scenes/Settings.hpp
		client/include/sfml/MusicSFML.hpp
		client/include/sfml/TextureSFML.hpp
		client/include/scenes/HowToPlay.hpp
		client/include/sfml/TextSFML.hpp
		client/include/sfml/FontSFML.hpp
		client/include/scenes/SceneEnum.hpp
		client/include/SocketParser.hpp
		client/include/systems/ClientNetworkSystem.hpp
		client/include/scenes/InGame.hpp
		client/include/NetworkAccess.hpp
		client/include/systems/ClientNetworkSystem.hpp
		client/include/components/LobbyComponent.hpp
		client/include/entities/LobbyCard.hpp
		client/include/systems/LobbySystem.hpp
		client/include/components/LobbyComponent.hpp
		client/include/systems/LobbySystem.hpp
		client/include/scenes/CreateLobby.hpp
		client/include/scenes/LobbyWaiting.hpp
        client/include/entities/PlayerAndStarshipEntity.hpp
		client/include/systems/PlayerAndStarshipSystem.hpp
		client/include/components/LobbyComponent.hpp
        client/include/scenes/Settings.hpp
        client/include/sfml/MusicSFML.hpp
		client/include/sfml/SoundBufferSFML.hpp
		client/include/systems/LobbySystem.hpp
		client/src/systems/LobbyWaitingSystem.cpp
		client/include/systems/LobbyWaitingSystem.hpp
		client/include/systems/QuitSystemInGame.hpp
		client/src/systems/QuitSystemInGame.cpp)

set(SERVER_SOURCES
        server/main.cpp
        server/client/Client.cpp
        server/lobby/lobbyManager/LobbyManager.cpp
        server/lobby/lobby/Lobby.cpp
        server/client/TCP/TcpSocket.cpp
		server/client/SocketParser.cpp
        server/client/TCP/TcpSocket.cpp
		server/game/systems/ServerNetworkSystem.cpp
        server/game/Game.cpp
		server/game/dataHolders/DataSprite.cpp
		server/game/dataHolders/DataTexture.cpp
		server/game/systems/PlayerMovementSystem.cpp
		server/game/systems/ProjectileSystem.cpp
		server/game/systems/GroundSystem.cpp
		server/game/systems/AutomaticWeaponSystem.cpp
		server/game/systems/EnemySystem.cpp
		server/game/systems/ProjectileSystem.cpp 
		server/game/systems/LifetimeSystem.cpp
		server/game/systems/ProjectileSystem.cpp
		server/game/systems/SpawnerSystem.cpp
		server/game/systems/HealthSystem.cpp
        server/game/systems/PlayerWeaponSystem.cpp
		server/game/systems/PlayerCollisionSystem.cpp
		server/game/systems/BorderLimitSystem.cpp server/game/systems/BorderLimitSystem.hpp server/game/dataHolders/DataMusic.cpp server/game/dataHolders/DataMusic.hpp server/game/dataHolders/DataSound.cpp server/game/dataHolders/DataSound.hpp)

set(SERVER_INCLUDES
		server/client/Client.hpp
		server/lobby/lobbyManager/LobbyManager.hpp
		server/lobby/lobby/Lobby.hpp
		server/client/TCP/TcpSocket.hpp
		server/client/SocketParser.hpp
		server/game/systems/ServerNetworkSystem.hpp
		server/client/TCP/TcpSocket.hpp
		server/game/systems/ServerNetworkSystem.hpp
		server/game/Game.hpp
		server/game/entities/Enemy.hpp
		server/game/Game.hpp
		server/game/dataHolders/DataSprite.hpp
		server/game/dataHolders/DataTexture.hpp
		server/game/entities/Player.hpp
		server/game/systems/PlayerMovementSystem.hpp
		server/game/components/ManualWeaponComponent.hpp
		server/game/components/ProjectileComponent.hpp
		server/game/entities/Projectile.hpp
		server/game/systems/ProjectileSystem.hpp
		server/game/systems/ProjectileSystem.hpp
		server/game/systems/EnemySystem.hpp
		server/game/components/PatternComponent.hpp
		server/game/systems/AutomaticWeaponSystem.hpp
		server/game/components/AutomaticWeaponComponent.hpp
		server/game/Game.hpp
		server/game/systems/PlayerMovementSystem.hpp
		server/game/components/ProjectileComponent.hpp
		server/game/entities/Projectile.hpp
		server/game/systems/ProjectileSystem.hpp
		server/game/systems/GroundSystem.hpp
		server/game/entities/Ground.hpp
		server/game/CollisionMasks.hpp
		server/game/entities/Spawner.hpp
		server/game/components/LifetimeComponent.hpp
		server/game/systems/LifetimeSystem.hpp
		server/game/entities/Particle.hpp
		server/game/components/EnemySpawnerComponent.hpp
		server/game/systems/SpawnerSystem.hpp
		server/game/components/HealthComponent.hpp
		server/game/systems/HealthSystem.hpp
		server/game/components/CollectibleComponent.hpp
		server/game/entities/Collectible.hpp
		server/game/entities/Sentinel.hpp
        server/game/systems/PlayerWeaponSystem.hpp
		server/game/systems/PlayerCollisionSystem.hpp
        server/game/GameData.hpp
		server/game/components/WaveComponent.hpp
		server/game/dataHolders/DataText.cpp server/game/dataHolders/DataText.hpp server/game/dataHolders/DataFont.cpp server/game/dataHolders/DataFont.hpp server/game/systems/BorderLimitSystem.cpp server/game/systems/BorderLimitSystem.hpp server/game/dataHolders/DataMusic.cpp server/game/dataHolders/DataMusic.hpp server/game/dataHolders/DataSound.cpp server/game/dataHolders/DataSound.hpp)


set(ENEMIES_INCLUDES
	${ENGINE_INCLUDES} ${SERVER_INCLUDES}
)
set(ENEMIES_SOURCES
		server/game/dataHolders/DataSprite.cpp
		server/game/dataHolders/DataTexture.cpp
		engine/src/graphical/ASprite.cpp
		engine/src/graphical/ATexture.cpp
		)

add_executable(r-type_client ${ENGINE_SOURCES} ${ENGINE_INCLUDES} ${CLIENT_SOURCES} ${CLIENT_INCLUDES})
add_executable(r-type_server ${ENGINE_SOURCES} ${ENGINE_INCLUDES} ${SERVER_SOURCES} ${SERVER_INCLUDES})

include(GNUInstallDirs)

### Dynamic libs

# Floating Robot
add_library(floatingRobot SHARED
		dynamic_libs/FloatingRobot.cpp
		dynamic_libs/FloatingRobot.hpp

		${ENEMIES_SOURCES}
		)
set_target_properties(floatingRobot PROPERTIES SOVERSION 1)
set_target_properties(floatingRobot PROPERTIES
		PUBLIC_HEADER "${ENEMIES_INCLUDES}")
target_include_directories(floatingRobot PUBLIC
		dynamic_libs
		engine/include
		server/game
		client/include
		)
install(TARGETS floatingRobot
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/floatingRobot.pc
		DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)


# Flapping Robot
add_library(flappingRobot SHARED
		dynamic_libs/FlappingRobot.cpp
		dynamic_libs/FlappingRobot.hpp

		${ENEMIES_SOURCES}
		)
set_target_properties(flappingRobot PROPERTIES SOVERSION 1)
set_target_properties(flappingRobot PROPERTIES
		PUBLIC_HEADER "${ENEMIES_INCLUDES}")
target_include_directories(flappingRobot PUBLIC
		dynamic_libs
		engine/include
		server/game
		client/include
		)
install(TARGETS flappingRobot
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/flappingRobot.pc
		DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

# BW Robot
add_library(bwRobot SHARED
		dynamic_libs/BWRobot.cpp
		dynamic_libs/BWRobot.hpp

		${ENEMIES_SOURCES}
		)
set_target_properties(bwRobot PROPERTIES SOVERSION 1)
set_target_properties(bwRobot PROPERTIES
		PUBLIC_HEADER "${ENEMIES_INCLUDES}")
target_include_directories(bwRobot PUBLIC
		dynamic_libs
		engine/include
		server/game
		client/include
		)
install(TARGETS bwRobot
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/bwRobot.pc
		DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

###############

target_include_directories(r-type_server PRIVATE
        server/core
        engine/include
        server/client
        server/lobby/lobbyManager
        server/lobby/lobby
        server/Client/TCP
		server/game
        engine/src/networking/UDP)
target_include_directories(r-type_client PRIVATE
        client/include
        engine/include
		)

message("===========================================")
message(${CONAN_LIBS})
message("===========================================")

target_link_libraries(r-type_client ${CONAN_LIBS})
target_link_libraries(r-type_server ${CONAN_LIBS})

if(MSVC)
    set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
    set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
    set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
    set(Boost_USE_MULTITHREADED      ON)
    set(Boost_USE_STATIC_RUNTIME     OFF)
    if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        target_link_libraries(r-type_client ${Boost_LIBRARIES})
        target_link_libraries(r-type_server ${Boost_LIBRARIES})
    endif()
endif()
