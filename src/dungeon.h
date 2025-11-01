#ifndef DUNGEON_H
#define DUNGEON_H
#include "raylib.h"
#include "mathlib.h"
#include "entity.h"
#include "game.h"
#include <time.h>

#define MAX_ROOMS 10
#define MIN_ROOM_SIZE 4
#define MAX_ROOM_SIZE 8

typedef struct room_s {
    vec2ui8_t pos;
    vec2ui8_t size;
} room_t;

typedef struct {
    room_t rooms[MAX_ROOMS];
    int roomcount;
} dungeon_t;

void GenerateDungeonRooms(dungeon_t *dungeon);

#endif