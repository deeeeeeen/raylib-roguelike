#include "dungeon.h"

#define ROOM_PADDING 3  // space between rooms in tiles

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

void GenerateDungeonRooms(dungeon_t *dungeon) {
    SetRandomSeed(time(0));
    dungeon->roomcount = 0;

    for (int idx = 0; idx < MAX_ROOMS; idx++) {
        vec2ui8_t size = {
            GetRandomValue(MIN_ROOM_SIZE, MAX_ROOM_SIZE),
            GetRandomValue(MIN_ROOM_SIZE, MAX_ROOM_SIZE)
        };

        bool placed = false;

        for (int retry = 0; retry < 10 && !placed; retry++) {
            vec2ui8_t pos = {
                GetRandomValue(1, GAME_WINDOW_SIZE / TILE_SIZE - size.x - 1),
                GetRandomValue(1, GAME_WINDOW_SIZE / TILE_SIZE - size.y - 1)
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
                dungeon->rooms[dungeon->roomcount++] = candidate;
                placed = true;
            }
        }
    }
}
