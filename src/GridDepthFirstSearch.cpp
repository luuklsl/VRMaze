//
//  GridDepthFirstSearch.cpp
//  SearchStragies
//
//  Created by David Stritzl on 08/11/2016.
//
//
//--Luuk Lenders				s1568892
//--Luc Schoot Uiterkamp		s1555537

#include <cstdlib>
#include <iostream>
#include <stack>

#include "Grid.hpp"

void Grid::depthFirstSearch(GridElement * dfs_elem, GridElement * human_elem) {
	std::stack<GridElement *> stack;
	//create a stack called 'stack' that will contain Gridelement pointers
	if (dfs_elem == NULL) {
		stack.push(&grid[0][0][0]);
	}
	else
	{
		stack.push(dfs_elem);
	}
	int n_visited = 1;
	while (!stack.empty()) {							//if stack is empty we haven't started yet (catch finish case)
		GridElement *current_element = stack.top();		//we get the current elem ([0][0]
		current_element->visited = true;				//set to true

		int x = current_element->x;						//try to get x and y values (not yet working correctly)
		int y = current_element->y;
		int z = current_element->z;
		if (x == human_elem->x && y == human_elem->y && z == human_elem->z)
		{
			//add o
			//int z = stack.size();
			if (x == human_elem->x && y == human_elem->y && z == human_elem->z)
				while (!stack.empty())
			{
				stack.top()->marked = true;
				stack.pop();
			}
			return;
		}

		int n_unvisited_directions = 0;	//does this even do what I want?
		Direction unvisited_directions[N_DIRECTIONS]; //setup an array of possible directions
		for (int direction = 0; direction < N_DIRECTIONS; direction++) {
			if (current_element->neighbours[direction] != NULL
				&& !current_element->neighbours[direction]->visited
				&& current_element->walls[direction] != true)
			{
				//should push next elem on stack here
				unvisited_directions[n_unvisited_directions++] = (Direction)direction;
				stack.push(current_element->neighbours[direction]);
				n_visited++;
				break; //break the for loop if we added something to the stack
			}
		}
		// backtrack if no possible directions are found

		if (n_unvisited_directions == 0) {
			stack.pop();
		}
	}
	std::cout << "DFS	| No solution to be found. Are we Jailed?"<<std::endl;


	//
	// USAGE
	//
	// - add element (of type GridElement *) to the top of the stack:
	// stack.push(element)
	//
	// - remove element from the top of the stack: (note: this will crash the program if the stack is empty)
	// stack.pop()
	//
	// - get element from the top of the stack: (note: this will crash the program if the stack is empty)
	// stack.top()
	//   example:
	// GridElement *element = stack.top();
	//
	// - check if the stack is empty:
	// stack.empty()
	//   example:
	// bool is_empty = stack.empty();
	//
	// for more information refer to the documentation:
	// http://en.cppreference.com/w/cpp/container/stack
	//
}
