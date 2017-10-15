cmake_minimum_required (VERSION 3.10)

project (CommsFramework)


file(GLOB ENGINE_SOURCES "CommsFramework/*.cpp")
file(GLOB GAME_SOURCES "Blackjack/*.cpp")

add_definitions("-D_WINDOWS")
add_definitions("-D_UNICODE")
add_definitions("/Zc:strictStrings-")

#find_library(SDL2 "E:/Prog/CommsFramework/libs/SDL/lib/win32/SDL2.lib")

include_directories("E:/Prog/CommsFramework/libs/rapidxml")
include_directories("E:/Prog/CommsFramework/libs/SDL/include")
include_directories("E:/Prog/CommsFramework/libs/SDL_Image/include")
include_directories("E:/Prog/CommsFramework/libs/SDL_ttf/include")

add_library(SDL2 SHARED IMPORTED)
set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION "E:/Prog/CommsFramework/libs/SDL/lib/win32/SDL2.dll")

add_library(engine STATIC ${ENGINE_SOURCES})
target_link_libraries(engine SDL2)

include_directories("E:/Prog/CommsFramework/src/CommsFramework")

add_executable(Blackjack ${GAME_SOURCES})
target_link_libraries(Blackjack engine)

target_link_libraries(Blackjack SDL2)

