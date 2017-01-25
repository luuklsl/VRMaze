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



class Grid {
public:
	Grid();
	void reset();
	void partialReset();

	void draw();
	void generateMaze();

	bool aStarCheck();

	bool playerInput(int key_id);
	bool humanPlayer(GridElement* human_elem,int key_id);
	GridElement* getHumanElement();

	int gridEnemy();

	GridElement grid[GRID_SIZE][GRID_SIZE][GRID_SIZE];


	void depthFirstSearch(GridElement* dfs_elem, GridElement* human_elem);
	void breadthFirstSearch(GridElement* bfs_elem, GridElement* human_elem);
	void greedySearch(GridElement* greedy_elem, GridElement* human_elem);
	int aStarSearch(GridElement* astar_elem, GridElement* human_elem);
	GridElement* astar_elem;
	GridElement* greedy_elem;
	GridElement* bfs_elem;
	GridElement* dfs_elem;
	GridElement* human_elem;

};

#endif /* Grid_hpp */
