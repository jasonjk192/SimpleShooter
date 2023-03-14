project(simple-shooter)

cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS FALSE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

#FetchContent
include(FetchContent)

#--------------------------------------

# SDL
set(SDL_SHARED OFF)
set(SDL_STATIC ON)
FetchContent_Declare(sdl GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG release-2.26.0)
FetchContent_MakeAvailable(sdl)

# SDL2_Image
FetchContent_Declare(sdl2_image GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git  GIT_TAG release-2.6.0)
set(SDL2IMAGE_INSTALL OFF)
FetchContent_MakeAvailable(sdl2_image)

# SDL2_TTF
FetchContent_Declare(sdl2_ttf GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git  GIT_TAG release-2.20.0)
set(SDL2TTF_INSTALL OFF)
FetchContent_MakeAvailable(sdl2_ttf)

set(SDL2_INCLUDE_DIR "${FETCHCONTENT_BASE_DIR}/sdl-build/include")
set(SDL_LIBRARIES SDL2main SDL2-static SDL2_image SDL2_ttf)

#--------------------------------------

# Source files
set(PROJECT_SOURCES_WITHOUT_MAIN
	 "src/Assets/UIAsset.cpp"
	 "src/Assets/ShipAsset.cpp"
	 "src/Assets/SDLMaths.cpp"

	 "src/Entities/BaseEntity.cpp"
	 "src/Entities/AIShipEntity.cpp"
	 "src/Entities/DynamicEntity.cpp"
	 "src/Entities/StartStateShipEntity.cpp"
	
	 "src/States/BaseState.cpp;"
	 "src/States/GameLostState.cpp;"
	 "src/States/GameWonState.cpp;"
	 "src/States/StartState.cpp;"

	 "src/Drawer.cpp;"
	 "src/Menu.cpp;"
	 "src/StateMachine.cpp;"
	 "src/Texture.cpp;"
	)
add_executable(${PROJECT_NAME} src/main.cpp ${PROJECT_SOURCES_WITHOUT_MAIN})

# Include files
set(PROJECT_INCLUDES
	"include;"
	"fonts;"
 	"${SDL2_INCLUDE_DIR}" 
	)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDES})

# Libraries
set(PROJECT_LIBRARIES
	${SDL_LIBRARIES}
  )
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIBRARIES})