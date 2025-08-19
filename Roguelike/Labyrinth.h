#pragma once
#include <memory>
#include <vector>

#include "Floor.h"
#include "GameObjectContainer.h"
#include "LabyrinthElement.h"
#include "LabyrinthExit.h"
#include "Rect.h"
#include "Vector.h"
#include "Wall.h"

namespace Roguelike {
/** GameObject containing Wall and Floor
 * Constructed by LabyrinthBuilder
 */
class Labyrinth : public GameObjectContainer {
   public:
    /** LabyrinthBuilder class for constructing Labyrinth objects*/
    friend class LabyrinthBuilder;
    /** Return Wall objects of Labytinth*/
    std::vector<std::weak_ptr<Wall>> GetWalls() const;
    /** Return Floor objects of Labytinth*/
    std::vector<std::weak_ptr<Floor>> GetFloors() const;
    /** Return LabyrinthExit from Labyrinth*/
    std::shared_ptr<LabyrinthExit>& GetExit();
    /** Get all Labyrinth elements*/
    const std::vector<std::vector<std::shared_ptr<LabyrinthElement>>>&
    GetElements() const;
    /** Get startCell*/
    const MaxrEngine::Vector2Di& GetStartCell() const;
    /** Move center of Labytinth to newPosition*/
    void SetCenterPosition(const MaxrEngine::Vector2Df newPosition);
    /** Get points where DFS algorithm in LabyrinthBuilder::Generate() met dead
     * ends*/
    const std::vector<MaxrEngine::Vector2Di>& GetGenerationDeadEnds() const;
    /** Get tile grid marking is tile walkable or not*/
    const std::vector<std::vector<bool>>& GetIsTileWalkable() const;
    /**
     * Returns world coordinates of cell
     */
    const MaxrEngine::Vector2Df GetCellCoordinates(
        const MaxrEngine::Vector2Di& cell);
    /**
     * @brief Method to get information about labyrinth borders
     * @returns rectangle in which labyrinths elements are, TopLeft is top left
     * wall coordinate, bottomRigth is bottom rigth wall coordinate
     */
    const MaxrEngine::FloatRect GetLabyrinthCoodinatesRect();

   private:
    /** Constructor*/
    explicit Labyrinth(const MaxrEngine::Vector2Di& size);
    /** Labyrinth ssize in cells*/
    MaxrEngine::Vector2Di size;
    /** Stores elements of Labyrinth (Wall, Floor, LabyrinthExit)*/
    std::vector<std::vector<std::shared_ptr<LabyrinthElement>>> elements;
    /** Stores cell marked as Labyrinth exit*/
    std::shared_ptr<LabyrinthExit> exit;
    /** Stores points where DFS algorithm in LabyrinthBuilder::Generate() met
     * dead ends*/
    std::vector<MaxrEngine::Vector2Di> generationDeadEnd;
    /** Stores tile grid marking is tile walkable or not*/
    std::vector<std::vector<bool>> isTileWalkable;
    /** Stores start cell for Labyrinth::Generate() */
    MaxrEngine::Vector2Di startCell;
};
}  // namespace Roguelike
