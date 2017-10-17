cmake_minimum_required (VERSION 3.6)

project (CommsFramework)

# Get the current compilation architecture
# From : https://github.com/tcbrindle/sdl2-cmake-scripts/blob/master/FindSDL2.cmake
if(CMAKE_SIZEOF_VOID_P EQUAL 8) 
	set(ARCH x64)
else() 
	set(ARCH x86)
endif() 


file(GLOB ENGINE_HEADERS "CommsFramework/*.h")
file(GLOB ENGINE_SOURCES "CommsFramework/*.cpp")

file(GLOB BLACKJACK_HEADERS "Blackjack/*.h")
file(GLOB BLACKJACK_SOURCES "Blackjack/*.cpp")

file(GLOB PUZZLEGAME_HEADERS "PuzzleGame/*.h")
file(GLOB PUZZLEGAME_SOURCES "PuzzleGame/*.cpp")

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
	
ENDIF(WIN32)

IF(UNIX)
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
	
	include_directories(${SDL2_INCLUDE})
	include_directories(${SDL2_IMAGE_INCLUDE})
	include_directories(${SDL2_TTF_INCLUDE})

	find_library(
		SDL2_LIB
		NAMES SDL2
#		HINTS "../libs/linux/SDL/lib/x86"
	)
	find_library(
		SDL2_IMAGE_LIB
		NAMES SDL2_image
#		HINTS "../libs/linux/SDL_Image/lib/x86"
	)
	find_library(
		SDL2_TTF_LIB
		NAMES SDL2_ttf
#		HINTS "../libs/linux/SDL_ttf/lib/x86"
	)
ENDIF(UNIX)



# Engine
add_library(engine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})
target_link_libraries(engine ${SDL2_LIB} ${SDL2_IMAGE_LIB} ${SDL2_TTF_LIB})
target_compile_features(engine PUBLIC cxx_std_11)

include_directories("CommsFramework")

# Blackjack
add_executable(Blackjack ${BLACKJACK_HEADERS} ${BLACKJACK_SOURCES})
target_link_libraries(Blackjack engine)
target_link_libraries(Blackjack ${SDL2_LIB} ${SDL2_IMAGE_LIB} ${SDL2_TTF_LIB})
target_compile_features(Blackjack PUBLIC cxx_std_11)

#PuzzleGame
add_executable(PuzzleGame ${PUZZLEGAME_HEADERS} ${PUZZLEGAME_SOURCES})
target_link_libraries(PuzzleGame engine)
target_link_libraries(PuzzleGame ${SDL2_LIB} ${SDL2_IMAGE_LIB} ${SDL2_TTF_LIB})
target_compile_features(PuzzleGame PUBLIC cxx_std_11)

IF(WIN32)
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