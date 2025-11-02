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

    Texture vwall[2] = { LoadTexture("res/vwall1.png"), LoadTexture("res/vwall2.png") };
    Texture hwall[5] = { LoadTexture("res/hwall1.png"), LoadTexture("res/hwall2.png"), LoadTexture("res/hwall3.png"), LoadTexture("res/hwall4.png"), LoadTexture("res/hwall5.png") };
    GenerateDungeonRooms(&dungeon);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_D)) player.pos.x += 1;
        if (IsKeyPressed(KEY_A)) player.pos.x -= 1;
        if (IsKeyPressed(KEY_W)) player.pos.y -= 1;
        if (IsKeyPressed(KEY_S)) player.pos.y += 1;

        // --- Draw to render texture (game space) ---
        BeginTextureMode(target);
            ClearBackground(BLACK);
            for (int idx = 0; idx < dungeon.roomcount; idx++) {
                DrawWalls(dungeon.rooms[idx], &hwall[0], &vwall[0]);
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
