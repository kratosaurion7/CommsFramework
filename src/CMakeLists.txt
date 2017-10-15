cmake_minimum_required (VERSION 3.7)

project (CommsFramework)

file(GLOB ENGINE_HEADERS "CommsFramework/*.h")
file(GLOB ENGINE_SOURCES "CommsFramework/*.cpp")
file(GLOB GAME_SOURCES "Blackjack/*.cpp")
file(GLOB GAME_SOURCES "PuzzleGame/*.cpp")

#add_definitions("-D_WINDOWS")
#add_definitions("-D_UNICODE")
#add_definitions("/Zc:strictStrings-")

#find_library(SDL2 "E:/Prog/CommsFramework/libs/SDL/lib/win32/SDL2.lib")

include_directories("../libs/rapidxml")
include_directories("../libs/SDL/include")
include_directories("../libs/SDL_Image/include")
include_directories("../libs/SDL_ttf/include")

#add_library(SDL2 SHARED IMPORTED)
#set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION "SDL2")

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)


add_library(engine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})
target_link_libraries(engine ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

include_directories("CommsFramework")

add_executable(Blackjack ${GAME_SOURCES})
target_link_libraries(Blackjack engine)
target_link_libraries(Blackjack ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

add_executable(PuzzleGame ${GAME_SOURCES})
target_link_libraries(PuzzleGame engine)
target_link_libraries(PuzzleGame ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

