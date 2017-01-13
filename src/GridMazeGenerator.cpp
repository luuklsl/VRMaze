//
//  maze_generator.hpp
//  SearchStragies
//
//  Created by David Stritzl on 08/11/2016.
//
//

#include "Grid.hpp"

#include <cstdlib>
#include <stack>

void Grid::generateMaze() {
    std::stack<GridElement *> stack;
    
    // push first element (0, 0) on stack
    stack.push(&grid[0][0][0]);
	GridElement* e = (GridElement*)grid;
	for (int x = 0; x < GRID_SIZE*GRID_SIZE*GRID_SIZE; x++) {
		for (int i = 0; i < N_DIRECTIONS; i++) {
			e->reset();
		}
		e++;	// Advance the pointer by one
	}
    /*
    while(!stack.empty()) {
        // get next element
        GridElement *current_element = stack.top();
        
        current_element->visited = true;
        
        // find all unvisited directions
        int n_unvisited_directions = 0;
        Direction unvisited_directions[N_DIRECTIONS];
        for(int direction = 0; direction < N_DIRECTIONS; direction++) {
            if(current_element->neighbours[direction] != NULL
               && !current_element->neighbours[direction]->visited) {
                unvisited_directions[n_unvisited_directions++] = (Direction)direction;
            }
        }
        
        // backtrack if no possible directions are found
        if(n_unvisited_directions == 0) {
            stack.pop();
            continue;
        }
        
        // choose random direction from unvisited directions
        Direction next_direction = unvisited_directions[std::rand() % n_unvisited_directions];
        
        // remove wall in this direction
        current_element->setWall(next_direction, false);
        
        // push next element on stack
        GridElement *next_element = current_element->neighbours[next_direction];
        stack.push(next_element);
    }*/
    
    { // randomly remove some walls
        int n_walls_removed = 0;
		while(n_walls_removed < N_WALLS_TO_BE_REMOVED) {
            // choose random element and direction
            int x = std::rand() % GRID_SIZE;
            int y = std::rand() % GRID_SIZE;
			int z = std::rand() % GRID_SIZE;
            
            GridElement *current_element = &grid[x][y][z];
            
            Direction direction = (Direction)(std::rand() % N_DIRECTIONS);
            
            // remove wall if possible
            if(current_element->neighbours[direction] != NULL && current_element->walls[direction]) {//// <<dit werkt nu niet correct
                current_element->setWall(direction, false);
                n_walls_removed++;
            }
        }
    }
    
    { // reset visited flags
        for(int x = 0; x < GRID_SIZE; x++) {
            for(int y = 0; y < GRID_SIZE; y++) {
				for (int z = 0; z < GRID_SIZE; z++) {
					grid[x][y][z].visited = false;
				}
            }
        }
    }
}