#include "dungeon.h"

bool CheckCollisionRooms(room_t a, room_t b) {
    // expand each room by ROOM_PADDING in all directions for spacing
    int ax1 = a.pos.x - ROOM_PADDING;
    int ay1 = a.pos.y - ROOM_PADDING;
    int ax2 = a.pos.x + a.size.x + ROOM_PADDING;
    int ay2 = a.pos.y + a.size.y + ROOM_PADDING;

    int bx1 = b.pos.x;
    int by1 = b.pos.y;
    int bx2 = b.pos.x + b.size.x;
    int by2 = b.pos.y + b.size.y;

    // AABB collision
    return (ax1 < bx2 && ax2 > bx1 && ay1 < by2 && ay2 > by1);
}

void DrawWalls(room_t room, Texture *htexture, Texture *vtexture) {

    Texture *p1 = htexture;
    Texture *p2 = vtexture;
    int counter = 0;
    // top and bottom row
    for (int i = 0; i < room.size.x; i++) {
        if (i == 0) {
            DrawTexture(*(p1+1), 8*room.pos.x+8*i, 8*room.pos.y, RAYWHITE);
            DrawTexture(*(p1+3), 8*room.pos.x+8*i, 8*room.pos.y+8*(room.size.y-1), RAYWHITE);
        }
        else if (i == room.size.x-1) {
            DrawTexture(*(p1+2), 8*room.pos.x+8*i, 8*room.pos.y, RAYWHITE);
            DrawTexture(*(p1+4), 8*room.pos.x+8*i, 8*room.pos.y+8*(room.size.y-1), RAYWHITE);
        }
        else {
            DrawTexture(*p1, 8*room.pos.x+8*i, 8*room.pos.y, RAYWHITE);
            DrawTexture(*p1, 8*room.pos.x+8*i, 8*room.pos.y+8*(room.size.y-1), RAYWHITE);
        }
    }

    for (int i = 1; i < room.size.y-1; i++) {
        DrawTexture(*p2, 8*room.pos.x, 8*room.pos.y+8*i, RAYWHITE);
        DrawTexture(*(p2+1), 8*room.pos.x+8*(room.size.x-1), 8*room.pos.y+8*i, RAYWHITE);
    }
}

void GenerateDoors(room_t *room) {
    SetRandomSeed((int)(room->pos.x+room->pos.y));

    const int TOP = 0;
    const int RIGHT = 1;
    const int BOTTOM = 2;
    const int LEFT = 3;

    // clockwise 0 1 2 3
    int randwall1 = GetRandomValue(0, 1);
    int randwall2 = GetRandomValue(2, 3);
    vec2ui8_t doorpos1;
    vec2ui8_t doorpos2;

    if (randwall1 == TOP) {
        doorpos1.y = room->pos.y;
        doorpos1.x = GetRandomValue(room->pos.x+2, room->pos.x+room->size.x-2);
    }
    if (randwall2 == BOTTOM) {
        doorpos2.y = room->pos.y + room->size.y-1;
        doorpos2.x = GetRandomValue(room->pos.x+2, room->pos.x+room->size.x-2);
    }
    if (randwall1 == RIGHT) {
        doorpos1.y = GetRandomValue(room->pos.y+2, room->pos.y+room->size.y-2);
        doorpos1.x = room->pos.x + room->size.x-1;
    }
    if (randwall2 == LEFT) {
        doorpos2.y = GetRandomValue(room->pos.y+2, room->pos.y+room->size.y-2);
        doorpos2.x = room->pos.x;
    }

    room->doorpos[0] = doorpos1;
    room->doorpos[1] = doorpos2;
}

void GenerateDungeonRooms(dungeon_t *dungeon) {
    SetRandomSeed(time(0));
    dungeon->roomcount = 0;

    for (int idx = 0; idx < MAX_ROOMS; idx++) {
        vec2ui8_t size = {
            GetRandomValue(MIN_ROOM_SIZE, MAX_ROOM_SIZE),
            GetRandomValue(MIN_ROOM_SIZE, MAX_ROOM_SIZE)
        };

        bool placed = false;

        for (int retry = 0; retry < 100 && !placed; retry++) {
            vec2ui8_t pos = {
                GetRandomValue(3, GAME_WINDOW_SIZE / TILE_SIZE - size.x - 3),
                GetRandomValue(3, GAME_WINDOW_SIZE / TILE_SIZE - size.y - 3)
            };

            room_t candidate = { .pos = pos, .size = size };

            bool collides = false;
            for (int i = 0; i < dungeon->roomcount; i++) {
                if (CheckCollisionRooms(candidate, dungeon->rooms[i])) {
                    collides = true;
                    break;
                }
            }

            if (!collides) {
                GenerateDoors(&candidate);
                dungeon->rooms[dungeon->roomcount++] = candidate;
                placed = true;

            }
        }
    }
}
