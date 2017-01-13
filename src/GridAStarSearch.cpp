////
////  GridAStartSearch.cpp
////  SearchStragies
////
////  Created by David Stritzl on 08/11/2016.
////
////
////--Luuk Lenders				s1568892
////--Luc Schoot Uiterkamp		s1555537
//
#include "Grid.hpp"

#include <iostream>

#include "PriorityQueue.hpp"



// score comparison class for priority queue
class FScoreCompare {
public:
	bool operator()(GridElement const *a, GridElement const *b) const {
		return a->score > b->score;
	}
};


void Grid::aStarSearch() {
	// priority queue which sorts elements based on its score (score is a member of GridElement)
	// for a star search, the score partially consists of the length of the path from the start to the current_element element
	// for this purpose, GridElement has a member length_of_path, whose calculation is left to the user
	PriorityQueue<GridElement *, FScoreCompare> queue;
	GridElement* element = &grid[0][0][0];		//this is how we have to give the elem to queue due to mandist.
	queue.push(element);//current_element start
	int n_visited = 0;
	queue.top()->length_of_path = 0;
	while (!queue.empty()) {							//if queue is empty we haven't started yet (catch finish case)
		GridElement *current_element = queue.top();		//we get the current elem ([0][0]
		queue.pop();
		
		//current_element->visited = true;				//set to true
		current_element->finally_checked = true;

		int x = current_element->x;						//try to get x and y values 
		int y = current_element->y;
		int z = current_element->z;
		if (x == (GRID_SIZE - 1) && y == (GRID_SIZE - 1) && z==(GRID_SIZE-1))
		{
			std::cout << "A*	|	" << n_visited << "	|	" << current_element->length_of_path + 1 << "	|	" <<
				((current_element->length_of_path + 1) / (double)n_visited) << std::endl;// << z << std::endl;
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
			if (current_element->neighbours[direction] != NULL
				&& !current_element->neighbours[direction]->visited
				&& !current_element->walls[direction]) {
				current_element->neighbours[direction]->length_of_path = current_element->length_of_path + 1;
				

				//check for shorter distance
				if ((current_element->neighbours[direction]->visited = true) && (current_element->neighbours[direction]->score > (current_element->neighbours[direction]->length_of_path +
					MANHATTAN_DISTANCE_TO_END(current_element->neighbours[direction]))) && current_element ->finally_checked != true) {
					std::cout << "higher costs";
					queue.erase(current_element->neighbours[direction]);		//update costs
				}
				//add to queue on given place
				current_element->neighbours[direction]->score = current_element->neighbours[direction]->length_of_path +
					MANHATTAN_DISTANCE_TO_END(current_element->neighbours[direction]);
				current_element->neighbours[direction]->parent = current_element;
				queue.push(current_element->neighbours[direction]);
				n_visited++;				
				current_element->visited = true;
				//unvisited_directions[n_unvisited_directions++] = (Direction)direction;
				//current_element->neighbours[direction]->visited = true;
			}
		}


		//
		// USAGE
		//
		// - add element (of type GridElement *) to the the queue:
		// queue.push(element)
		//
		// - remove the element with the lowest score from the queue: (note: this will crash the program if the queue is empty)
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
		// - remove a given element (of type GridElement *) (at any position) from the queue:
		// queue.erase(element)
		//   example: (updating the score of an element in the queue (and therefore its position))
		// queue.erase(element);
		// element->score = new_score; // the calculation of the value new_score is left to the user
		// queue.push(element);
		//
	}
	std::cout << "A*	| No solution to be found. Are we Jailed?" << std::endl;
}
