//
//  GridElement.hpp
//  SearchStragies
//
//  Created by David Stritzl on 08/11/15.
//
//

#ifndef GridElement_hpp
#define GridElement_hpp

#include "Direction.hpp"

class GridElement {
public:
	GridElement();

	void reset();
	void partialReset();

	void draw();
	void drawWall(Direction);

	void setWall(Direction, bool);

	int x, y, z;

	GridElement *neighbours[N_DIRECTIONS];
	bool walls[N_DIRECTIONS];

	// variables for maze generation and path finding
	bool visited;
	bool marked; //both marked and visited and finally checked --> partialReset();
	bool finally_checked;
	GridElement *parent;
	int length_of_path;
	int score;

	//some new vars for drawing and tracking of enemies and Human Player
	bool visited_human;
	
	//all flags underneat here: ONLY ONE AT MOST
	bool astar;
	bool greedy;
	bool bfs;
	bool dfs;
	bool human;
};

#endif /* GridElement_hpp */
