#include "raylib.h"
#include "resource_dir.h"
#include "PCG.h"

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(PCG::SCREEN_WIDTH, PCG::SCREEN_HEIGHT, "Construct Map Editor");

    PCG::TileMap tileMap;

    tileMap.SetMapGenerator(new PCG::NoiseMapGenerator());
    tileMap.GetMapGenerator()->Generate(tileMap.tileArray); // Generate the map using the selected generator

    while (!WindowShouldClose()) {
        tileMap.Update();

        BeginDrawing();
        ClearBackground(BLACK);
        tileMap.DrawMap();
        DrawText("Construct Map Editor", 20, 20, 20, WHITE);
        tileMap.DrawGUI();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}