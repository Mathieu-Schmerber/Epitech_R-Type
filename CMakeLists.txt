project(RType)
cmake_minimum_required(VERSION 3.17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

if (UNIX)
    add_definitions("-fPIC")
endif()
if(WIN32)
    add_compile_options("/std:c++latest")
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(
        client/include
        server/include
        engine/include/ecs
)

set(ENGINE_SOURCES
        engine/src/ecs/System.cpp engine/src/ecs/Entity.cpp)

set(ENGINE_INCLUDES
        engine/include/ecs/Entity.hpp
        engine/include/ecs/System.hpp
        engine/include/ecs/Component.hpp)

set(CLIENT_SOURCES
        client/src/main.cpp)

set(CLIENT_INCLUDES
        client/include/Client.hpp)

set(SERVER_SOURCES
        server/src/main.cpp)

set(SERVER_INCLUDES
        server/include/Server.hpp)

add_executable(r-type_client ${ENGINE_SOURCES} ${ENGINE_INCLUDES} ${CLIENT_SOURCES} ${CLIENT_INCLUDES})

add_executable(r-type_server ${ENGINE_SOURCES} ${ENGINE_INCLUDES} ${SERVER_SOURCES} ${SERVER_INCLUDES})

target_link_libraries(r-type_server ${CONAN_LIBS})
target_link_libraries(r-type_client ${CONAN_LIBS})

if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/DWIN32 /D_WINDOWS /EHsc /WX /wd4355 /wd4251 /wd4250 /wd4996" CACHE STRING "Debug compiler flags" FORCE)
    set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
    set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
    set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
    set(Boost_USE_MULTITHREADED      ON)
    set(Boost_USE_STATIC_RUNTIME     OFF)
    find_package(Boost 1.71.0 COMPONENTS serialization)
    if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        target_link_libraries(r-type_client ${Boost_LIBRARIES})
        target_link_libraries(r-type_server ${Boost_LIBRARIES})
    endif()
endif()
