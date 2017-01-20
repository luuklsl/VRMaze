//
//  Grid.hpp
//  SearchStragies
//
//  Created by David Stritzl on 08/11/15.
//
//

#ifndef Grid_hpp
#define Grid_hpp

#include "GridElement.hpp"
#include "constants.h"

#define N_WALLS_TO_BE_REMOVED 220

// simple macro to compute the manhattan distance to the end
// USAGE for a GridElement el: MANHATTAN_DISTANCE_TO_END(el)
#define MANHATTAN_DISTANCE_TO_END(el) ((GRID_SIZE - 1) - el->x) + ((GRID_SIZE - 1) - el->y) + ((GRID_SIZE - 1) - el->z)

class Grid {
public:
	Grid();
	void reset();
	void partialReset();

	void draw();
	void generateMaze();

	bool aStarCheck();

	void gridEnemy();

	GridElement grid[GRID_SIZE][GRID_SIZE][GRID_SIZE];


	void depthFirstSearch(GridElement* dfs_elem, GridElement* human_elem);
	void breadthFirstSearch(GridElement* bfs_elem, GridElement* human_elem);
	void greedySearch(GridElement* greedy_elem, GridElement* human_elem);
	void aStarSearch(GridElement* astar_elem, GridElement* human_elem);
	GridElement* astar_elem;
	GridElement* greedy_elem;
	GridElement* bfs_elem;
	GridElement* dfs_elem;
	GridElement* human_elem;

};

#endif /* Grid_hpp */
