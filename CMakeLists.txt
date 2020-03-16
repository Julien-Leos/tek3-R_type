cmake_minimum_required(VERSION 3.10)
project(RType)

# Flags
if (UNIX)
    set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -std=c++14 -pthread -g3")
    set(CMAKE_CXX_STANDARD 14)
else (UNIX)
    if (WIN32)
        set(CMAKE_CXX_STANDARD 17)
    endif (WIN32)
endif (UNIX)

# Conan
include(build/conanbuildinfo.cmake)
conan_basic_setup()

# --------- NETWORK -----------
file(GLOB_RECURSE NETWORK_SRC "./src/Network/*.cpp")


# --------- SERVER -----------
file(GLOB_RECURSE SERVER_SRC "./src/Server/*.cpp" "./lua/*.c")
file(GLOB_RECURSE GAME_ENGINE_SRC "./src/GameEngine/*.cpp")
file(GLOB_RECURSE GAME_SRC "./src/Game/*.cpp")

################################# INCLUDE HEADER PROJECT TO THE EXECUTABLE #################################

add_executable(r-type_server WIN32 ${SERVER_SRC} ${GAME_ENGINE_SRC} ${NETWORK_SRC} ${GAME_SRC})


########## LINK LIBRARIES OF YOUR CURRENT PLATEFORM TO THE EXECUTABLE
target_link_libraries(r-type_server ${LINK_LIBRARIES})
##########  FUNC WHICH GET ALL HEADER AND ADD THEIR PATHS TO A LIST
set(HEADERS_PROJECT "")
MACRO(HEADER_DIRECTORIES return_list)
    if (WIN32)
        file(GLOB_RECURSE new_list "./src/*.hpp" "./lua/*.h")
    else (WIN32)
        file(GLOB_RECURSE new_list "./src/*.hpp" "./lua/*.h")
    endif(WIN32)
    set(dir_list "")
    FOREACH(file_path ${new_list})
        get_filename_component(dir_path ${file_path} PATH)

        set(dir_list ${dir_list} " " ${dir_path})

    ENDFOREACH()
    list(REMOVE_DUPLICATES dir_list)
    set(${return_list} ${dir_list})
ENDMACRO()
HEADER_DIRECTORIES(HEADERS_PROJECT)

##########  LINK ALL HEADERS TO THE EXECUTABLE
message(${HEADERS_PROJECT})
target_include_directories(r-type_server PRIVATE ${HEADERS_PROJECT})
target_link_libraries(r-type_server ${CONAN_LIBS} ${LINK_LIBRARIES})



# --------- CLIENT -----------
file(GLOB_RECURSE CLIENT_SRC "./src/Client/*.cpp")
file(GLOB_RECURSE GAME_ENGINE_SRC "./src/GameEngine/*.cpp")

add_executable(r-type_client WIN32 ${CLIENT_SRC} ${GAME_ENGINE_SRC} ${NETWORK_SRC})
target_include_directories(r-type_client PRIVATE  ${HEADERS_PROJECT})
target_link_libraries(r-type_client ${CONAN_LIBS} ${LINK_LIBRARIES})
