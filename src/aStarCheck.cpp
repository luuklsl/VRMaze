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


bool Grid::aStarCheck() {
	// priority queue which sorts elements based on its score (score is a member of GridElement)
	// for a star search, the score partially consists of the length of the path from the start to the current_element element
	// for this purpose, GridElement has a member length_of_path, whose calculation is left to the user
	PriorityQueue<GridElement *, FScoreCompare> queue;
	GridElement* element = &grid[0][0][0];		//this is how we have to give the elem to queue due to mandist.
	queue.push(element);//current_element start
	int n_visited = 0;
	queue.top()->length_of_path = 0;
	human_elem = &grid[GRID_SIZE - 1][GRID_SIZE - 1][GRID_SIZE - 1];
	while (!queue.empty()) {							//if queue is empty we haven't started yet (catch finish case)
		GridElement *current_element = queue.top();		//we get the current elem ([0][0]
		queue.pop();

		//current_element->visited = true;				//set to true
		current_element->finally_checked = true;

		int x = current_element->x;						//try to get x and y values 
		int y = current_element->y;
		int z = current_element->z;
		if (x == (GRID_SIZE - 1) && y == (GRID_SIZE - 1) && z == (GRID_SIZE - 1))
		{
			std::cout << "A*	|	" << n_visited << "	|	" << current_element->length_of_path + 1 << "	|	" <<
				((current_element->length_of_path + 1) / (double)n_visited) << std::endl;// << z << std::endl;
			while (current_element->parent != NULL)
			{
				current_element->marked = true;
				current_element = current_element->parent;
			}
			current_element->marked = true;
			return false; //set the thingy to false so we end the generateMaze loop
		}

		int n_unvisited_directions = 0;	//does this even do what I want?

		for (int direction = 0; direction < N_DIRECTIONS; direction++) {
			if (current_element->neighbours[direction] != NULL
				&& !current_element->neighbours[direction]->visited
				&& !current_element->walls[direction]) {
				current_element->neighbours[direction]->length_of_path = current_element->length_of_path + 1;


				//check for shorter distance
				if ((current_element->neighbours[direction]->visited = true) && (current_element->neighbours[direction]->score >(current_element->neighbours[direction]->length_of_path +
					MANHATTAN_DISTANCE_TO_END(current_element->neighbours[direction],human_elem))) && current_element->finally_checked != true) {
					std::cout << "higher costs";
					queue.erase(current_element->neighbours[direction]);		//update costs
				}
				//add to queue on given place
				current_element->neighbours[direction]->score = current_element->neighbours[direction]->length_of_path +
					MANHATTAN_DISTANCE_TO_END(current_element->neighbours[direction],human_elem);
				current_element->neighbours[direction]->parent = current_element;
				queue.push(current_element->neighbours[direction]);
				n_visited++;
				current_element->visited = true;
				//unvisited_directions[n_unvisited_directions++] = (Direction)direction;
				//current_element->neighbours[direction]->visited = true;
			}
		}

	}
	std::cout << "A*	| No solution to be found. Are we Jailed?" << std::endl;
	return true;
}
