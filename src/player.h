#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "mathlib.h"

typedef struct player_s {
    vec2ui8_t pos;
    vec2ui8_t size;
    Texture2D  sprite;
} player_t;

#endif