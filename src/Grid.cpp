//
//  Grid.cpp
//  SearchStragies
//
//  Created by David Stritzl on 08/11/15.
//
//

#define _USE_MATH_DEFINES

#include "Grid.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include "Direction.hpp"

Grid::Grid() {
	// set positions and neighbours of all elements
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			for (int z = 0; z < GRID_SIZE; z++)
			{

				grid[x][y][z].x = x;
				grid[x][y][z].y = y;
				grid[x][y][z].z = z;

				if (x > 0) { grid[x][y][z].neighbours[DirectionWest] = &grid[x - 1][y][z]; }
				if (x < GRID_SIZE - 1) { grid[x][y][z].neighbours[DirectionEast] = &grid[x + 1][y][z]; }
				if (y > 0) { grid[x][y][z].neighbours[DirectionDown] = &grid[x][y - 1][z]; }
				if (y < GRID_SIZE - 1) { grid[x][y][z].neighbours[DirectionUp] = &grid[x][y + 1][z]; }
				if (z > 0) { grid[x][y][z].neighbours[DirectionSouth] = &grid[x][y][z - 1]; }
				if (z < GRID_SIZE - 1) { grid[x][y][z].neighbours[DirectionNorth] = &grid[x][y][z + 1]; }
			}
		}
	}
}



void Grid::reset() {
	// reset all elements
	for (int y = 0; y < GRID_SIZE; y++) {
		for (int x = 0; x < GRID_SIZE; x++) {
			for (int z = 0; z < GRID_SIZE; z++) {
				grid[x][y][z].reset();
			}
		}
	}
}


void Grid::partialReset() {
	for (int y = 0; y < GRID_SIZE; y++) {
		for (int x = 0; x < GRID_SIZE; x++) {
			for (int z = 0; z < GRID_SIZE; z++) {
				grid[x][y][z].partialReset();
			}
		}
	}

}


void Grid::draw() {
	// draw all elements
	for (int y = 0; y < GRID_SIZE; y++) {
		for (int x = 0; x < GRID_SIZE; x++) {
			for (int z = 0; z < GRID_SIZE; z++) {

				grid[x][y][z].draw();
				//std::cout << x<<", "<< y<<", "<< z << std::endl;
			}
		}
	}
}

void Grid::gridEnemy() {
	GridElement* e = (GridElement*)grid; //e is apointer to the grid array of GridElements
	int human_visted = 0;
	for (int x = 0; x < GRID_SIZE*GRID_SIZE*GRID_SIZE; x++) {

			if (e->astar)
			{
				astar_elem = e;
			}
			if (e->greedy)
			{
				greedy_elem = e;

			}if (e->dfs)
			{
				dfs_elem = e;

			}if (e->bfs)
			{
				bfs_elem = e;
			}
			if (e->human)
			{
				human_elem = e;
			}
			if (e->visited_human)
			{
				human_visted++;
			}
			e++;	// Advance the pointer by one
		}
	if (bfs_elem == NULL)
	{
		bfs_elem = &grid[2][2][2];
	}
	//if (human_elem == NULL)
	//{
	//	human_elem = &grid[0][0][0];
	//}
	if (bfs_elem == human_elem)
	{
		std::cout << "You died" << std::endl;
	}
		breadthFirstSearch(bfs_elem,human_elem);	
	}