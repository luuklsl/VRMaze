//
//  GridGreedySearch.cpp
//  SearchStragies
//
//  Created by David Stritzl on 08/11/2016.
//
//
//--Luuk Lenders				s1568892
//--Luc Schoot Uiterkamp		s1555537

#include "Grid.hpp"

#include <iostream>

#include "PriorityQueue.hpp"

// distance comparison class for priority queue
class DistanceCompare {
public:
	bool operator()(GridElement const *a, GridElement const *b) const {
		return MANHATTAN_DISTANCE_TO_END(a) > MANHATTAN_DISTANCE_TO_END(b);
	}
};

void Grid::greedySearch(GridElement* greedy_elem, GridElement* human_elem) {
	// priority queue which sorts elements based on its score (score is a member of GridElement)
	// for greedy search, this score could be the manhattan distance (from the current element) to the end
	PriorityQueue<GridElement *, DistanceCompare> queue; //creates a queue that already uses distancecompare
	if (greedy_elem == NULL) {
		GridElement* greedy_elem = &grid[0][0][0];
	}		//this is how we have to give the elem to queue due to mandist.
	queue.push(greedy_elem);//current start
	int n_visited = 0; //set in visited
	queue.top()->length_of_path = 0;
	while (!queue.empty()) {							//if queue is empty we haven't started yet (catch finish case)
		GridElement *current_element = queue.top();		//we get the current elem ([0][0]
		queue.pop();
		current_element->visited = true;				//set to true
		n_visited++;
		int x = current_element->x;						//try to get x and y values 
		int y = current_element->y;
		int z = current_element->z;
		if (x == human_elem->x && y == human_elem->y && z == human_elem->z)
		{
			//add element with shortes Manhattan distance
			std::cout << "Greedy	|	" << n_visited << "	|	" << current_element->length_of_path+1 << "	|	" <<
				((current_element->length_of_path+1) / (double)n_visited) << std::endl;// << z << std::endl;
			while (current_element->parent != NULL)
			{
				current_element->marked = true;
				current_element = current_element->parent;
			}
			current_element->marked = true;
			return;
		}

		//int n_unvisited_directions = 0;	//does this even do what I want?

		for (int direction = 0; direction < N_DIRECTIONS; direction++) {
			//for a queue we want to push all the elements that are on the 'frontier'
			if (current_element->neighbours[direction] != NULL
				&& !current_element->neighbours[direction]->visited
				&& current_element->walls[direction] != true)

			{

				//should push next elem on queue here
				current_element->neighbours[direction]->parent = current_element; //set parent of neighbouring unvisited to current elem
				current_element->neighbours[direction]->length_of_path = current_element->length_of_path + 1;
				queue.push(current_element->neighbours[direction]); //element that statisfies if-
				//above way is easiest change without changing the GridElement Class;

														//WE should also check if neighbour elem is already on queue.

			}
		}
	
	}
	std::cout << "Greedy	| No solution to be found. Are we Jailed?" << std::endl;

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
