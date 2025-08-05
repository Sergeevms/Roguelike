#pragma once
#include <memory>
#include <vector>

#include "Labyrinth.h"
#include "Vector.h"

namespace Roguelike {
/** Class for generating Labyrinth
 * generation splits in to parts:
 * - describing Labyrinth by filling tileGrid, starting with Generate (fills
 * tileGrid with random tiles using Depth-first search algorithm)
 * or StartBuilding (filles tileGrid with specified TileType)
 * - editing tileGrid throw AddRect, AddFloorRect, SetWall, SetFloor
 * - constructing Labyrinth (creating exepmlar according tileGrid)
 * by calling ConstructLabyrinth */
class LabyrinthBuilder {
   public:
    /** Struct describing parameters for labirinth random
     * generation used in Generate
     */
    struct Parameters {
        int width;  /**< labyrinth width*/
        int heigth; /**< labyrinth heigth*/
        /** will be size and startPosition adjusted in Generate*/
        bool isAdjustingSizeAndStart;
        /** Seed for random. Using -1 as value will lead to using time(nullptr)
         * as seed in Generate*/
        int randSeed = -1;
        /** Position from where DFS algorithm starts. Using negative coordinates
         * as value will lead random startPosition in Generate*/
        MaxrEngine::Vector2Di startPosition = {-1, -1};
    };
    /** Enum class describing what kind of tile is it in tileGrid*/
    enum class TileType {
        Empty,
        Floor,
        Wall,
        Exit,
        VerticalWall,
        HorizontalWall
    };

    /** Struct describing parameters for AddRect */
    struct RectFillingParameters {
        MaxrEngine::Vector2Di
            bottomLeft;  //**< Coordinates of bottom left corder of rect*/
        MaxrEngine::Vector2Di size;  //**< Size of rect */
        TileType
            borderTileType;  //**< TileType used for filling border of rect*/
        TileType
            fillingTileType;  //**< TileType used for filling interior of rect*/
    };

    LabyrinthBuilder();

    /** Generate new labyrinth grid consisting TileType using DFS algorithm
     *Can be modified after generation using AddRect, SetWall, SetFloor*/
    void Generate(const Parameters& parameters);

    /** Resets current labyrinthGrid and create according newTileSize filled
     * with fillTileType tiles*/
    void StartBuilding(const MaxrEngine::Vector2Di& newTileSize,
                       const TileType fillTileType = TileType::Empty);

    /** Fill rectangle (clamp bottomLeft coordinates and sizeto predefined
     * labyrinth tileSize) in tileGrid according to RectFillingParameters If
     * cell of tileGrid on border of rect have fillingTileTypeOn value, it
     * doesn't change to borderTileType
     */
    void AddRect(const RectFillingParameters& parameters);

    /** Constructs Labyrinth according to current tileGrid */
    std::shared_ptr<Labyrinth> ConstructLabyrinth();

    /** Returns current labyrinth state grid, where true means that tile is
     * walkable throw, false othervise*/
    // std::vector<std::vector<bool>> GetIsWalkableGrid();
    /** Returns dead ends after labyrinth generation by Generate*/
    // std::vector<MaxrEngine::Vector2Di> GetGeneratedDeadEnds();
    /** Fill rectangle in tileGrid with TileType::Floor surronded with
     * TileType::Wall) converts previous placed walls to floor, but not floor to
     * wall
     */
    void AddFloorRect(MaxrEngine::Vector2Di bottomLeft,
                      MaxrEngine::Vector2Di size);

    /** Sets position tile to Wall*/
    void SetWall(MaxrEngine::Vector2Di position);
    /** Sets position tile to Wall*/
    void SetFloor(MaxrEngine::Vector2Di position);
    /** Get current labyrinth size in tiles*/
    MaxrEngine::Vector2Di GetTileSize() const;
    /** Set exitCell*/
    void SetExitCell(const MaxrEngine::Vector2Di& newExitCell);
    /** Get current exitCell. Return MaxrEngine::Vector2Di(-1, -1) if was not
     * setted*/
    const MaxrEngine::Vector2Di& GetExitCell() const;

   private:
    int labyrinthTileWidth = 0;  /**< Current labyrinth width*/
    int labyrinthTileHeight = 0; /**< Current labyrinth height*/
    /** Current labyrinth TileType's*/
    std::vector<std::vector<TileType>> tileGrid;
    std::vector<int> usableFloorTextureId;
    /** Return directions that are availiable to move in DFS at
                  Generate*/
    std::vector<MaxrEngine::Vector2Di> GetAvaliableDirections(
        const MaxrEngine::Vector2Di& currentCell,
        const std::vector<std::vector<bool>>& visitiedCells) const;
    MaxrEngine::Vector2Di startPosition; /**< Saved start position if labyrinth
                                            tileGrid filled by Generate*/
    /** Cell where exit from Labyrinth is positioned. Setted during Generate or
     * manually throw SetExitCell*/
    MaxrEngine::Vector2Di exitCell;
    void
    UpdateWallType(); /**< Changes wall TileType according to its position*/
    /** Checks if TileType at position is kind of wall*/
    bool IsWall(MaxrEngine::Vector2Di position) const;
    /** Adjust startPoint and Labyrinth size (make coordinates odd (increase on
     * one if needed) for DFS algorithm go throw all labyrinth)*/
    void AdjustStartPointAndSize();
    /** Make cell in middle of DFS step Floor and surrond it by Walls*/
    void ProcessMiddleCell(const MaxrEngine::Vector2Di& middleCell,
                           std::vector<std::vector<bool>>& visited,
                           const MaxrEngine::Vector2Di& selectedDirection);
    /** Get farthest deadEnd cell near the edge of Labyrinth and places Exit on
     * edge. If there's no such dead ends, emplace the exit on random cell on
     * edge*/
    void FindAndEmplaceExit();
    /** Emplace exit on random cell on edge of Labyrinth that is near the
     * floor*/
    void RandomlyEmplaceExit();
    MaxrEngine::Vector2Df GetCenterInTyles() const;
    MaxrEngine::Vector2Df GetTylePosition(MaxrEngine::Vector2Di tilePosition);
    std::vector<MaxrEngine::Vector2Di> deadEnds;
};
}  // namespace Roguelike
