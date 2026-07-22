//
// Created by Jkurt on 7/21/2026.
//

#ifndef RAYLIBGAME_OPTIONS_H
#define RAYLIBGAME_OPTIONS_H
#include <raylib.h>
inline Vector2 BASE_RESOLUTION = {640, 360};
inline int RENDER_SCALE = 2;
inline Vector2 VIRTUAL_RESOLUTION = {BASE_RESOLUTION.x * RENDER_SCALE, BASE_RESOLUTION.y * RENDER_SCALE};
inline bool FULLSCREEN = true;
#endif //RAYLIBGAME_OPTIONS_H