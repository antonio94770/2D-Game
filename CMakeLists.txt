cmake_minimum_required (VERSION 2.6)
set(Game_CMAKE_BUILD_TYPE Release)
set (Game_VERSION_MAJOR 1)
set (Game_VERSION_MINOR 0)
project (Game)
add_executable(Game Main.cpp Bullet.cpp Collisione.cpp Enemy.cpp Gioco.cpp Player.cpp Sfondo.cpp Shield.cpp)
INCLUDE_DIRECTORIES( /usr/include )

LINK_DIRECTORIES( /usr/lib )

TARGET_LINK_LIBRARIES(Game liballegro.so liballegro_dialog.so liballegro_audio.so liballegro_acodec.so liballegro_color.so liballegro_font.so liballegro_image.so liballegro_primitives.so liballegro_ttf.so)

set_target_properties(Game
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/.."
)
 
