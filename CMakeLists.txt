cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(Diameter)

set(Python_ADDITIONAL_VERSIONS "2.7")

find_package(PythonLibs REQUIRED)
find_package(SDL REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(SDL_image REQUIRED)
find_package(PNG REQUIRED)
find_package(OpenGL REQUIRED)

find_library(GUICHAN_LIBRARY guichan)
if(NOT GUICHAN_LIBRARY)
	message(ERROR "Not found guichan library")
endif()
find_library(GUICHAN_SDL_LIBRARY guichan_sdl)
find_library(GUICHAN_OPENGL_LIBRARY guichan_opengl)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID MATCHES "Clang")
 	set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall")
endif()

include_directories(
	${SDL_INCLUDE_DIR}
	${SDL_IMAGE_INCLUDE_DIRS}
	${SDL_MIXER_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIR}
	${PYTHON_INCLUDE_DIRS}
	${PNG_INCLUDE_DIRS}
)
add_executable(diameter
	src/main.cpp
	src/gra/mathlib.cpp
	src/gra/model.cpp
	src/gra/sprite.cpp
	src/gra/model_init.cpp
	src/gra/2d/gui.cpp
	src/gra/2d/image_button.cpp
	src/gra/2d/fonts_button.cpp
	src/gra/2d/text_checkbox.cpp
	src/gra/2d/simple2d.cpp
	src/gra/effect/cloud.cpp
	src/gra/effect/explosion.cpp
	src/gra/effect/particle.cpp
	src/gra/effect/stars.cpp
	src/res/3ds.cpp
	src/res/tga.c
	src/res/3dsloader.cpp
	src/res/texture.cpp
	src/res/loadworld.cpp
	src/res/xml/tinystr.cpp
	src/res/xml/tinyxml.cpp
	src/res/xml/tinyxmlerror.cpp
	src/res/xml/tinyxmlparser.cpp
	src/snd/snd.cpp
	src/wor/AI.cpp
	src/wor/fiz.cpp
	src/wor/object.cpp
	src/wor/decoration.cpp
	src/wor/pylevel.cpp
	src/wor/objects/gao.cpp
	src/wor/objects/pul.cpp
	src/wor/objects/roc.cpp
	src/wor/objects/tim.cpp
	src/wor/objects/sta.cpp
	src/wor/objects/nul.cpp
)

target_compile_definitions(diameter PRIVATE -DPKGDATADIR="${CMAKE_INSTALL_PREFIX}/share/gamediameter/")
target_compile_features(diameter PRIVATE cxx_range_for)

target_link_libraries(diameter
	${SDL_LIBRARY}
	${SDL_IMAGE_LIBRARIES}
	${SDL_MIXER_LIBRARIES}
	${OPENGL_LIBRARIES}
	${PNG_LIBRARIES}
	${PYTHON_LIBRARIES}
	${GUICHAN_LIBRARY}
	${GUICHAN_SDL_LIBRARY}
	${GUICHAN_OPENGL_LIBRARY}
)

install(TARGETS diameter
		RUNTIME DESTINATION bin)

install(DIRECTORY data/
		DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gamediameter")
