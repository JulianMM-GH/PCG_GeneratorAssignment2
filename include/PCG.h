#pragma once
#include "raylib.h"

namespace PCG {
    // Screen & Map Dimensions
    constexpr int SCREEN_WIDTH = 1024;
    constexpr int SCREEN_HEIGHT = 1024;
    constexpr int TILE_SIZE = 4;
    constexpr int MAP_COLUMNS = (SCREEN_WIDTH / TILE_SIZE);
    constexpr int MAP_ROWS = (SCREEN_HEIGHT / TILE_SIZE);

    // Tile Types (Using Enum for readability)
    typedef enum {
        TILE_TYPE_GRASS = 0,
        TILE_TYPE_ROCK = 1,
        TILE_TYPE_WATER = 2,
        TILE_TYPE_SAND = 3,

        TILE_TYPE_DIRT = 4,

        TILE_COUNT  // Automatically counts total types
    } TileType;

    // Visual & Character settings
    constexpr char GRASS_CHAR = '.';
    constexpr char ROCK_CHAR = '#';
    constexpr char WATER_CHAR = '~';
    constexpr char SAND_CHAR = '*';

    constexpr char DIRT_CHAR = '=';

    constexpr Color GRASS_COLOR = {86, 206, 56, 255 };
    constexpr Color ROCK_COLOR = {118, 118, 118, 255 };
    constexpr Color WATER_COLOR = {51, 153, 255, 255 };
    constexpr Color SAND_COLOR = {239, 226, 130, 255 };

    constexpr Color DIRT_COLOR = { 156, 118, 83, 255 };

    constexpr Color UNKNOWN_COLOR = { 255, 255, 255, 255 };

    // UI variable defines used to position buttons on screen
    constexpr int BUTTON_WIDTH = 200;
    constexpr int BUTTON_HEIGHT = 50;
    constexpr int BUTTON_X = (SCREEN_WIDTH - BUTTON_WIDTH - 20);
    constexpr int BUTTON_Y = (SCREEN_HEIGHT - BUTTON_HEIGHT - 20);
    constexpr Rectangle RESET_BUTTON_BOUNDS = { BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT };

    // File Names
    constexpr char* MAP_TEXT_FILENAME = "pcg_map_data.txt";
    constexpr char* MAP_IMAGE_FILENAME = "pcg_map.png";

    // Pure Virtual Class
    class MapGenerator {
    public:
        virtual ~MapGenerator() = default; // virtual destructor
        // This enforces that every child class MUST write their own Generate function.
        virtual void Generate(TileType _tileArray[MAP_ROWS][MAP_COLUMNS]) = 0;
    };

    // Random Map Generator
    class RandomMapGenerator : public MapGenerator {
    public:
        RandomMapGenerator();
        ~RandomMapGenerator();
        void Generate(TileType _tileArray[MAP_ROWS][MAP_COLUMNS]) override;
    };

    // Noise Map Generator
    class NoiseMapGenerator : public MapGenerator {
    public:
        float scale = 2.5f;
        float grassThreshold = 0.70f;
        float sandThreshold = 0.45f;
        float waterThreshold = 0.35f;

        NoiseMapGenerator();
        ~NoiseMapGenerator();
        void Generate(TileType _tileArray[MAP_ROWS][MAP_COLUMNS]) override;
    };

    class TileMap {
    public:
        TileMap();  // constructor
        ~TileMap(); // destructor

        // Core Actions
        // Function Declarations
        void CreateMap();
        void Update();
        void DrawMap() const; // 'const' means this function won't change the map data
        void PrintMap() const;
        void DrawGUI();

        // I/O Functions
        void SaveMapData(const char* filename) const;
        void SaveMapImage(const char* filename) const;
        void LoadMapData(const char* filename);

        // Accessors (Getters/Setters)
        void SetTile(int x, int y, PCG::TileType tileType);
        Color GetTileColor(TileType tileType) const;
        char GetTileChar(TileType tileType) const;

        // getter /setter for map generator 
        void SetMapGenerator(MapGenerator* generator);
        MapGenerator* GetMapGenerator() const;

        // public tile array, for convenience but ideally hidden as private later
        TileType tileArray[MAP_ROWS][MAP_COLUMNS] = { PCG::TileType::TILE_TYPE_ROCK };  // 2D array to hold tile types for the map

        TileType activeBrushType = TILE_TYPE_GRASS;

        void SetBrushSize(int size) { brushSize = size; }

    private:
        MapGenerator* mapGenerator;
        int brushSize = 1;

    };
}