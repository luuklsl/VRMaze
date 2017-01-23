#include "Grid.hpp"

#include <iostream>

bool Grid::humanPlayer(GridElement* human_elem, int key_id)
{
	//left right up down: 356, 357, 358, 359
	//also the only key id we should EVER get in here
	bool notmoved = true;
	int x = human_elem->x;
	int y = human_elem->y;
	int z = human_elem->z;

	switch (key_id)
	{
	case 356: //left = west
		if (human_elem->neighbours[3] != NULL
			&& !human_elem->walls[3])
		{
			human_elem->human = false;
			human_elem->visited_human = true;
			human_elem =&grid[x-1][y][z];
			human_elem->human = true;
			notmoved = false;
		}
		break;
	case 357: //up = north
		if (human_elem->neighbours[0] != NULL
			&& !human_elem->walls[0])
		{
			human_elem->human = false;
			human_elem->visited_human = true;
			human_elem = &grid[x][y][z+1];
			human_elem->human = true;
			notmoved = false;
		}
		break;
	case 358: // right = east
		if (human_elem->neighbours[1] != NULL
			&& !human_elem->walls[1])
		{
			human_elem->human = false;
			human_elem->visited_human = true;
			human_elem = &grid[x + 1][y][z];
			human_elem->human = true;
			notmoved = false;
		}
		break;
	case 359: // down = south
		if (human_elem->neighbours[2] != NULL
			&& !human_elem->walls[2])
		{
			human_elem->human = false;
			human_elem->visited_human = true;
			human_elem = &grid[x][y][z-1];
			human_elem->human = true;
			notmoved = false;
		}
		break;
	case 'j': // up = up
		if (human_elem->neighbours[4] != NULL
			&& !human_elem->walls[4])
		{
			human_elem->human = false;
			human_elem->visited_human = true;
			human_elem = &grid[x][y+1][z];
			human_elem->human = true;
			notmoved = false;
		}
		break;
	case 'n': // downward = down
		if (human_elem->neighbours[5] != NULL
			&& !human_elem->walls[5])
		{
			human_elem->human = false;
			human_elem->visited_human = true;
			human_elem = &grid[x][y-1][z];
			human_elem->human = true;
			notmoved = false;
		}
		break;
	}
	//check if move is valid, if so, switch the bool
	
	//also move the character's flag (bool human in GridElem)




	//move according to way player is facing

	return notmoved;
}