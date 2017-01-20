//
//  GridBreadthFirstSearch.cpp
//  SearchStragies
//
//  Created by David Stritzl on 08/11/2016.
//
//
//--Luuk Lenders				s1568892
//--Luc Schoot Uiterkamp		s1555537

#include "Grid.hpp"

#include <iostream>
#include <queue>

void Grid::breadthFirstSearch(GridElement * bfs_elem, GridElement * human_elem) {
	std::queue<GridElement *> queue; //create a queue called 'queue' that will contain Gridelement pointers
	if (bfs_elem == NULL) {
		queue.push(&grid[0][0][0]);
	}
	else { queue.push(bfs_elem); }
	queue.front()->length_of_path = 0;
	int n_visited = 1;
	while (!queue.empty()) {							//if queue is empty we haven't started yet (catch finish case)
		GridElement *current_element = queue.front();		//we get the current elem ([0][0]
		current_element->visited = true;				//set to true
		int x = current_element->x;						//try to get x and y values (not yet working correctly)
		int y = current_element->y;
		int z = current_element->z;
		if (x == human_elem->x && y == human_elem->y && z == human_elem->z)
		{
			//add all possible frontiers to queue
			std::cout << "BFS	|	" << n_visited << "	|	" << current_element->length_of_path+1 << "	|	" << 
				((current_element->length_of_path+1)/(double)n_visited)  << std::endl;// << z << std::endl;
			while (current_element->parent != NULL)
			{
				current_element->marked = true;
				current_element = current_element->parent;
			}
			current_element->marked = true;
			return;
		}

		int n_unvisited_directions = 0;	//does this even do what I want?
		Direction unvisited_directions[N_DIRECTIONS]; //setup an array of possible directions
		for (int direction = 0; direction < N_DIRECTIONS; direction++) {
			//for a queue we want to push all the elements that are on the 'frontier'
			if (current_element->neighbours[direction] != NULL
				&& !current_element->neighbours[direction]->visited
				&& current_element->walls[direction] != true)

			{

				//should push next elem on queue here
				unvisited_directions[n_unvisited_directions++] = (Direction)direction;
				current_element->neighbours[direction]->parent = current_element;
				current_element->neighbours[direction]->length_of_path = current_element->length_of_path + 1;
				queue.push(current_element->neighbours[direction]); //element that statisfies if-
				queue.back()->visited = true;		//sets the visited on true so there is no dubble addition
				n_visited++;
				//above way is easiest change without changing the GridElement Class;
				//queue.back()->parent=current_element; //element that was just pushed is last elem and has current elem as parent

				//WE should also check if neighbour elem is already on queue.
			}
		}
		queue.pop();

		// backtrack if no possible directions are found


	}
	std::cout << "BFS	| No solution to be found. Are we Jailed?" << std::endl;
	//
	// USAGE
	//
	// - add element (of type GridElement *) to the end of the queue:
	// queue.push(element)
	//
	// - remove element from the front of the queue: (note: this will crash the program if the queue is empty)
	// queue.pop()
	//
	// - get element from the front of the queue: (note: this will crash the program if the queue is empty)
	// queue.front()
	//   example:
	// GridElement *element = queue.front();
	//
	// - check if the queue is empty:
	// queue.empty()
	//   example:
	// bool is_empty = queue.empty();
	//
	// for more information refer to the documentation:
	// http://en.cppreference.com/w/cpp/container/queue
	//
}
