cmake_minimum_required (VERSION 3.2)

project (CommsFramework)

# Get the current compilation architecture
# From : https://github.com/tcbrindle/sdl2-cmake-scripts/blob/master/FindSDL2.cmake
if(CMAKE_SIZEOF_VOID_P EQUAL 8) 
    set(ARCH x64)
else() 
    set(ARCH x86)
endif() 

set (CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE ENGINE_HEADERS "CommsFramework/*.h")
file(GLOB_RECURSE ENGINE_SOURCES "CommsFramework/*.cpp")

file(GLOB_RECURSE BLACKJACK_HEADERS "Blackjack/*.h")
file(GLOB_RECURSE BLACKJACK_SOURCES "Blackjack/*.cpp")

file(GLOB_RECURSE PUZZLEGAME_HEADERS "PuzzleGame/*.h")
file(GLOB_RECURSE PUZZLEGAME_SOURCES "PuzzleGame/*.cpp")

file(GLOB_RECURSE FANTASYGAME_HEADERS "FantasyGame/*.h")
file(GLOB_RECURSE FANTASYGAME_SOURCES "FantasyGame/*.cpp")

IF(WIN32)
    add_definitions("-D_WINDOWS")
    add_definitions("-D_UNICODE")
    add_definitions("/Zc:strictStrings-")
ENDIF(WIN32)

IF(WIN32)
    include_directories("../libs/windows/rapidxml")
    include_directories("../libs/windows/SDL/include")
    include_directories("../libs/windows/SDL_Image/include")
    include_directories("../libs/windows/SDL_ttf/include")

    find_library(
        SDL2_LIB
        NAMES SDL2
        HINTS "../libs/windows/SDL/lib/${ARCH}"
    )
    find_library(
        SDL2_IMAGE_LIB
        NAMES SDL2_image
        HINTS "../libs/windows/SDL_Image/lib/${ARCH}"
    )
    find_library(
        SDL2_TTF_LIB
        NAMES SDL2_ttf
        HINTS "../libs/windows/SDL_ttf/lib/${ARCH}"
    )
    
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
ENDIF(WIN32)

IF(EMSCRIPTEN)

    INCLUDE(FindPkgConfig)

    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
    PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
    PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

    include_directories("../libs/windows/rapidxml")
    include_directories("../libs/windows/SDL/include")
    include_directories("../libs/windows/SDL_Image/include")
    include_directories("../libs/windows/SDL_ttf/include")

    set(SDL2_LIB ${SDL2_LIBRARIES})
    set(SDL2_IMAGE_LIB ${SDL2IMAGE_LIBRARIES})
    set(SDL2_TTF_LIB ${SDL2TTF_LIBRARIES})

ELSEIF(UNIX)
    include_directories("../libs/linux/rapidxml")
    include_directories("../libs/linux/SDL/include")
    include_directories("../libs/linux/SDL_Image/include")
    include_directories("../libs/linux/SDL_ttf/include")

    find_path(
        SDL2_INCLUDE
        SDL.h
        HINTS $ENV{SDL2DIR}
        PATH_SUFFIXES
            include/SDL2
            include
        PATHS ${SDL2_SEARCH_PATHS}
    )
    find_path(
        SDL2_IMAGE_INCLUDE
        SDL_image.h
        HINTS
            ENV SDL2IMAGEDIR
            ENV SDL2DIR
        PATH_SUFFIXES
            SDL2
            # path suffixes to search inside ENV{SDLDIR}
            include/SDL2 include
        PATHS ${SDL2_IMAGE_PATH}
    )
    find_path(
        SDL2_TTF_INCLUDE
        SDL_ttf.h
        HINTS
            ENV SDL2TTFDIR
            ENV SDL2DIR
        PATH_SUFFIXES
            SDL2
            # path suffixes to search inside ENV{SDLDIR}
            include/SDL2 include
        PATHS ${SDL2_TTF_PATH}
    )

    # Doesn't seem to work
    include_directories(${SDL2_INCLUDE})
    include_directories(${SDL2_IMAGE_INCLUDE})
    include_directories(${SDL2_TTF_INCLUDE})

    find_library(
        SDL2_LIB
        NAMES SDL2
#       HINTS "../libs/linux/SDL/lib/x86"
    )
    find_library(
        SDL2_IMAGE_LIB
        NAMES SDL2_image
#       HINTS "../libs/linux/SDL_Image/lib/x86"
    )
    find_library(
        SDL2_TTF_LIB
        NAMES SDL2_ttf
#       HINTS "../libs/linux/SDL_ttf/lib/x86"
    )
ENDIF(EMSCRIPTEN)



# Engine
add_library(engine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})
target_link_libraries(engine ${SDL2_LIB} ${SDL2_IMAGE_LIB} ${SDL2_TTF_LIB})

include_directories("CommsFramework")
include_directories("CommsFramework/Framework")


# Blackjack
add_executable(Blackjack ${BLACKJACK_HEADERS} ${BLACKJACK_SOURCES})
target_link_libraries(Blackjack engine)
target_link_libraries(Blackjack ${SDL2_LIB} ${SDL2_IMAGE_LIB} ${SDL2_TTF_LIB})


#PuzzleGame
add_executable(PuzzleGame ${PUZZLEGAME_HEADERS} ${PUZZLEGAME_SOURCES})
target_link_libraries(PuzzleGame engine)
target_link_libraries(PuzzleGame ${SDL2_LIB} ${SDL2_IMAGE_LIB} ${SDL2_TTF_LIB})

#FantasyGame
add_executable(FantasyGame ${FANTASYGAME_HEADERS} ${FANTASYGAME_SOURCES})
target_link_libraries(FantasyGame engine)
target_link_libraries(FantasyGame ${SDL2_LIB} ${SDL2_IMAGE_LIB} ${SDL2_TTF_LIB})

IF(EMSCRIPTEN)
    set_target_properties(engine PROPERTIES LINK_FLAGS "-s USE_SDL=2")
    set_target_properties(Blackjack PROPERTIES LINK_FLAGS "-s USE_SDL=2")
    set_target_properties(PuzzleGame PROPERTIES LINK_FLAGS "-s USE_SDL=2")
    set_target_properties(FantasyGame PROPERTIES LINK_FLAGS "-s USE_SDL=2")
ENDIF(EMSCRIPTEN)

IF(WIN32)

set_target_properties(engine PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
set_target_properties(Blackjack PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
set_target_properties(PuzzleGame PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
set_target_properties(FantasyGame PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")

# Copy dependencies DLL

#SDL2.dll
add_custom_command(
    TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/../libs/windows/SDL/lib/$(PlatformTarget)/SDL2.dll"
    $<TARGET_FILE_DIR:engine>
)

#SDL2_Image.dll
add_custom_command(
    TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/../libs/windows/SDL_Image/lib/$(PlatformTarget)/SDL2_image.dll"
    $<TARGET_FILE_DIR:engine>
)
#libjpeg-9.dll
add_custom_command(
    TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/../libs/windows/SDL_Image/lib/$(PlatformTarget)/libjpeg-9.dll"
    $<TARGET_FILE_DIR:engine>
)
#libpng16-16.dll
add_custom_command(
    TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/../libs/windows/SDL_Image/lib/$(PlatformTarget)/libpng16-16.dll"
    $<TARGET_FILE_DIR:engine>
)
#libtiff-5.dll
add_custom_command(
    TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/../libs/windows/SDL_Image/lib/$(PlatformTarget)/libtiff-5.dll"
    $<TARGET_FILE_DIR:engine>
)
#libwebp-4.dll
add_custom_command(
    TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/../libs/windows/SDL_Image/lib/$(PlatformTarget)/libwebp-4.dll"
    $<TARGET_FILE_DIR:engine>
)

#SDL2_ttf.dll
add_custom_command(
    TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/../libs/windows/SDL_ttf/lib/$(PlatformTarget)/SDL2_ttf.dll"
    $<TARGET_FILE_DIR:engine>
)
#libfreetype-6.dll
add_custom_command(
    TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/../libs/windows/SDL_ttf/lib/$(PlatformTarget)/libfreetype-6.dll"
    $<TARGET_FILE_DIR:engine>
)
#zlib1.dll
add_custom_command(
    TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/../libs/windows/SDL_ttf/lib/$(PlatformTarget)/zlib1.dll"
    $<TARGET_FILE_DIR:engine>
)

ENDIF(WIN32)

add_custom_command(
        TARGET engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/CommsFramework/Assets"
        $<TARGET_FILE_DIR:engine>/assets
)
add_custom_command(
        TARGET Blackjack POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/Blackjack/assets"
        $<TARGET_FILE_DIR:Blackjack>/assets
)
add_custom_command(
        TARGET FantasyGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/FantasyGame/assets"
        $<TARGET_FILE_DIR:FantasyGame>/assets
)
add_custom_command(
        TARGET FantasyGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${PROJECT_SOURCE_DIR}/FantasyGame/config.xml"
        $<TARGET_FILE_DIR:FantasyGame>/config.xml
)
