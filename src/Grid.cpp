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

void Grid::clearRect(int first_x, int first_y,int first_z, int width, int height, int depth) {
	int last_x = first_x + width - 1;
	int last_y = first_y + height - 1;
	int last_z = first_z + depth - 1;

	for (int y = first_y; y <= last_y; y++) {
		for (int x = first_x; x <= last_x; x++) {
			for (int z = first_z; z <= last_z; z++) {

				if (x != first_x) {
					grid[x][y][z].walls[DirectionWest] = false;
				}
				if (x != last_x) {
					grid[x][y][z].walls[DirectionEast] = false;
				}
				if (y != first_y) {
					grid[x][y][z].walls[DirectionUp] = false;
				}
				if (y != last_y) {
					grid[x][y][z].walls[DirectionDown] = false;
				}
				if (z != first_z) {
					grid[x][y][z].walls[DirectionNorth] = false;
				}
				if (z != last_z) {
					grid[x][y][z].walls[DirectionSouth] = false;
				}
			}
		}
	}
}

/*void Grid::drawArc(int x_center, int y_center, double radius, double first_alpha, double last_alpha) {
	assert(first_alpha >= 0.0 && first_alpha <= 2 * M_PI);
	assert(last_alpha >= 0.0 && last_alpha <= 2 * M_PI);

	for (int y_relative = -radius; y_relative <= radius; y_relative++) {
		int y = y_center + y_relative;

		// stop if outside of grid
		if (y < 0 || y >= GRID_SIZE) {
			continue;
		}

		for (int x_relative = -radius; x_relative <= radius; x_relative++) {
			int x = x_center + x_relative;

			// stop if outside of grid
			if (x < 0 || x >= GRID_SIZE) {
				continue;
			}

			double alpha = std::atan2(y_relative, x_relative);
			if (alpha < 0) {
				alpha += 2 * M_PI;
			}

			// stop if outside of arc angle range
			if (last_alpha >= first_alpha) {
				if (alpha < first_alpha || alpha > last_alpha) {
					continue;
				}
			}
			else {
				if (alpha < first_alpha && alpha > last_alpha) {
					continue;
				}
			}

			// stop if outside of arc radius
			double distance = std::sqrt(std::pow(x_relative, 2) + std::pow(y_relative, 2));
			if (distance >= radius) {
				continue;
			}

			for (int direction = 0; direction < N_DIRECTIONS; direction++) {
				GridElement *neighbour = grid[x][y][z].neighbours[direction];
				if (neighbour == NULL) {
					continue;
				}

				int x_neighbour_relative = neighbour->x - x_center;
				int y_neighbour_relative = neighbour->y - y_center;
				double neighbour_distance = std::sqrt(std::pow(x_neighbour_relative, 2) + std::pow(y_neighbour_relative, 2));

				// mark wall if neighbour is outside of arc radius
				if (neighbour_distance >= radius) {
					grid[x][y][z].setWall((Direction)direction, true);
				}
			}
		}
	}
	}*/
