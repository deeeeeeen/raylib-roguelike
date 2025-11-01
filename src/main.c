#include "raylib.h"
#include "dungeon.h"
#include "game.h"
#include "player.h"

int main(void)
{
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, GAME_TITLE);
    SetTargetFPS(60);

    // Create a render texture for the game world
    RenderTexture2D target = LoadRenderTexture(GAME_WINDOW_SIZE, GAME_WINDOW_SIZE);

    dungeon_t dungeon;
    player_t player = { 
                        .pos = (vec2ui8_t) { (int)(GAME_WINDOW_SIZE/16), (int)(GAME_WINDOW_SIZE/16) },
                        .size = (vec2ui8_t) { TILE_SIZE, TILE_SIZE },
                        .sprite = LoadTexture("res/player.png")
                      };

    GenerateDungeonRooms(&dungeon);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_D)) player.pos.x += 1;
        if (IsKeyPressed(KEY_A)) player.pos.x -= 1;
        if (IsKeyPressed(KEY_W)) player.pos.y -= 1;
        if (IsKeyPressed(KEY_S)) player.pos.y += 1;

        // --- Draw to render texture (game space) ---
        BeginTextureMode(target);
            ClearBackground((Color){ 30, 30, 40, 255 });
            for (int roomidx = 0; roomidx < dungeon.roomcount; roomidx++) {
                DrawRectangle(dungeon.rooms[roomidx].pos.x*TILE_SIZE, 
                              dungeon.rooms[roomidx].pos.y*TILE_SIZE, 
                              dungeon.rooms[roomidx].size.x*TILE_SIZE, 
                              dungeon.rooms[roomidx].size.y*TILE_SIZE, 
                              RED);
            }
            DrawTexture(player.sprite, player.pos.x*TILE_SIZE, player.pos.y*TILE_SIZE, RAYWHITE);
        EndTextureMode();

        // --- Draw scaled to screen ---
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(
                target.texture,
                (Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height },
                (Rectangle){ 0, 0, WINDOW_SIZE, WINDOW_SIZE },
                (Vector2){ 0, 0 },
                0.0f,
                WHITE
            );
        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();
    return 0;
}
