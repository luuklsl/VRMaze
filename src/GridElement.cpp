//
//  GridElement.cpp
//  SearchStragies
//
//  Created by David Stritzl on 08/11/15.
//
//

#include "GridElement.hpp"

#include <cstdio>
#include <cstdlib>
#include "ofMain.h"
#include "constants.h"

GridElement::GridElement() {  //constructor thingy
	// reset all neighbours
	for (int direction = 0; direction < N_DIRECTIONS; direction++) {
		neighbours[direction] = NULL;
	}
	reset();
}

void GridElement::reset() {
	// reset all walls
	for (int direction = 0; direction < N_DIRECTIONS; direction++) {
		walls[direction] = true;
	}

	visited = false;
	marked = false;
	finally_checked = false;
	parent = NULL;
	length_of_path = -1;
	score = 0;
	bfs = false;
	dfs = false;
	astar = false;
	greedy = false;
	human = false;
	visited_human = false;
}

void GridElement::partialReset() { //this makes that you can run multiple searches on the same maze (better for 3D vizualisation of effeiciency)
	visited = false;
	marked = false;
	finally_checked = false;
	parent = NULL;
	length_of_path = -1;
	score = 0;
}

void GridElement::draw() {
	// draw background if visited
	//if (visited) {
	//	ofSetColor(145, 187, 255);
	//	ofFill();
	//	//ofDrawRectangle((x * GRID_ELEMENT_WIDTH), (y * GRID_ELEMENT_HEIGHT), GRID_ELEMENT_WIDTH / 2, GRID_ELEMENT_HEIGHT / 2);
	//	ofDrawBox((x + 0.5)*GRID_ELEMENT_HEIGHT, (y + 0.1)*GRID_ELEMENT_HEIGHT, -(z + 0.5)*GRID_ELEMENT_HEIGHT, (GRID_ELEMENT_HEIGHT*0.01));
	//}

	if (bfs) {
		ofSetColor(255, 152, 0); //orange
		ofFill();
		//ofDrawRectangle((x * GRID_ELEMENT_WIDTH), (y * GRID_ELEMENT_HEIGHT), GRID_ELEMENT_WIDTH / 2, GRID_ELEMENT_HEIGHT / 2);
		ofDrawBox((x + 0.5)*GRID_ELEMENT_HEIGHT, (y + 0.1)*GRID_ELEMENT_HEIGHT, -(z + 0.5)*GRID_ELEMENT_HEIGHT, (GRID_ELEMENT_HEIGHT*0.15));
	}
	if (astar) {
		ofSetColor(0, 115, 100); //dark teal
		ofFill();
		//ofDrawRectangle((x * GRID_ELEMENT_WIDTH), (y * GRID_ELEMENT_HEIGHT), GRID_ELEMENT_WIDTH / 2, GRID_ELEMENT_HEIGHT / 2);
		ofDrawBox((x + 0.5)*GRID_ELEMENT_HEIGHT, (y + 0.3)*GRID_ELEMENT_HEIGHT, -(z + 0.5)*GRID_ELEMENT_HEIGHT, (GRID_ELEMENT_HEIGHT*0.3));
	}
	if (greedy) {
		ofSetColor(76, 175, 80); //Google Green
		ofFill();
		//ofDrawRectangle((x * GRID_ELEMENT_WIDTH), (y * GRID_ELEMENT_HEIGHT), GRID_ELEMENT_WIDTH / 2, GRID_ELEMENT_HEIGHT / 2);
		ofDrawBox((x + 0.5)*GRID_ELEMENT_HEIGHT, (y + 0.1)*GRID_ELEMENT_HEIGHT, -(z + 0.5)*GRID_ELEMENT_HEIGHT, (GRID_ELEMENT_HEIGHT*0.15));
	}
	if (dfs) {
		ofSetColor(175, 180, 43); //dark teal
		ofFill();
		//ofDrawRectangle((x * GRID_ELEMENT_WIDTH), (y * GRID_ELEMENT_HEIGHT), GRID_ELEMENT_WIDTH / 2, GRID_ELEMENT_HEIGHT / 2);
		ofDrawBox((x + 0.5)*GRID_ELEMENT_HEIGHT, (y + 0.1)*GRID_ELEMENT_HEIGHT, -(z + 0.5)*GRID_ELEMENT_HEIGHT, (GRID_ELEMENT_HEIGHT*0.15));
	}
	if (visited_human) {
		ofSetColor(200); //dark teal
		ofFill();
		//ofDrawRectangle((x * GRID_ELEMENT_WIDTH), (y * GRID_ELEMENT_HEIGHT), GRID_ELEMENT_WIDTH / 2, GRID_ELEMENT_HEIGHT / 2);
		ofDrawBox((x + 0.5)*GRID_ELEMENT_HEIGHT, (y + 0.2)*GRID_ELEMENT_HEIGHT, -(z + 0.5)*GRID_ELEMENT_HEIGHT, (GRID_ELEMENT_HEIGHT*0.20));
	}
	if (human) {
		ofSetColor(255); //dark teal
		ofFill();
		//ofDrawRectangle((x * GRID_ELEMENT_WIDTH), (y * GRID_ELEMENT_HEIGHT), GRID_ELEMENT_WIDTH / 2, GRID_ELEMENT_HEIGHT / 2);
		ofDrawBox((x + 0.5)*GRID_ELEMENT_HEIGHT, (y + 0.1)*GRID_ELEMENT_HEIGHT, -(z + 0.5)*GRID_ELEMENT_HEIGHT, (GRID_ELEMENT_HEIGHT*0.25));
	}

	// draw circle if marked
	//if (marked) {
	//	ofNoFill();
	//	ofSetColor(249, 77, 42);
	//	//ofDrawEllipse((x + 0.5) * GRID_ELEMENT_WIDTH, (y + 0.5) * GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH * 0.95, GRID_ELEMENT_HEIGHT * 0.95);
	//	ofDrawSphere((x + 0.5) * GRID_ELEMENT_HEIGHT, (y + 0.5) * GRID_ELEMENT_HEIGHT, -(z + 0.5)*GRID_ELEMENT_HEIGHT, GRID_ELEMENT_HEIGHT / 2);

	//}


	// draw all walls
	if (x == (GRID_SIZE - 1) && y == (GRID_SIZE - 1) && z == (GRID_SIZE - 1)) {
		for (int direction = 0; direction < N_DIRECTIONS; direction++) {
			if (walls[direction]) {
				drawEndWall((Direction)direction);
			}
		}
	}
	else {
		for (int direction = 0; direction < N_DIRECTIONS; direction++) {
			if (walls[direction]) {
				ofNoFill();
				drawWall((Direction)direction);
			}
		}
	}
}

void GridElement::drawWall(Direction direction) {
	ofSetColor(0);

	ofFill();
	switch (direction) {
	case DirectionSouth:
		//ofNoFill();
		ofSetColor(48, 63, 159); //blue
		ofDrawBox( //x,y,z, width, height, depth
			float((x + 0.5) *GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y + 0.5) *GRID_ELEMENT_HEIGHT), //this is for all the directions
			float(-(z)*GRID_ELEMENT_HEIGHT), //
			float(GRID_ELEMENT_HEIGHT),
			float(GRID_ELEMENT_HEIGHT),
			float(0)
		);
		break;

	case DirectionNorth:
		ofSetColor(48, 63, 159); //purple
		ofDrawBox( //x,y,z, width, height, depth
			float((x + 0.5) *GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y + 0.5) *GRID_ELEMENT_HEIGHT), //this is for all the directions
			float(-(z + 1) *GRID_ELEMENT_HEIGHT), //
			float(GRID_ELEMENT_HEIGHT),
			float(GRID_ELEMENT_HEIGHT),
			float(0)
		);
		break;

	case DirectionEast:
		ofSetColor(25, 32, 71); //yellow
		//ofDrawLine((x + 1) * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT, z*GRID_ELEMENT_HEIGHT,(x + 1) * GRID_ELEMENT_WIDTH, (y + 1) * GRID_ELEMENT_HEIGHT, z *GRID_ELEMENT_HEIGHT);
		ofDrawBox( //x,y,z, width, height, depth
			float((x + 1) *GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y + 0.5) *GRID_ELEMENT_HEIGHT), //this is for all the directions
			float(-(z + 0.5) *GRID_ELEMENT_HEIGHT), //
			float(0),
			float(GRID_ELEMENT_HEIGHT),
			float(-GRID_ELEMENT_HEIGHT)
		);
		break;
	case DirectionWest:
		ofSetColor(25, 32, 71); //white
		ofDrawBox( //x,y,z, width, height, depth
			float((x)*GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y + 0.5) *GRID_ELEMENT_HEIGHT), //this is for all the directions
			float(-(z + 0.5) *GRID_ELEMENT_HEIGHT), //
			float(0),
			float(GRID_ELEMENT_HEIGHT),
			float(-GRID_ELEMENT_HEIGHT)
		);
		break;

	case DirectionUp:
		ofSetColor(120, 195, 120); //black
		ofDrawBox( //x,y,z, width, height, depth
			float((x + 0.5) *GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y + 1) *GRID_ELEMENT_HEIGHT), //this is for all the directions
			float(-(z + 0.5) *GRID_ELEMENT_HEIGHT), //
			float(GRID_ELEMENT_HEIGHT),
			float(0),
			float(-GRID_ELEMENT_HEIGHT));
		break;
	case DirectionDown:
		ofSetColor(139, 195, 120); //pink
		ofDrawBox( //x,y,z, width, height, depth
			float((x + 0.5) *GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y)*GRID_ELEMENT_HEIGHT), //this is for all the directions
			float(-(z + 0.5) *GRID_ELEMENT_HEIGHT), //
			float(GRID_ELEMENT_HEIGHT),
			float(0),
			float(-GRID_ELEMENT_HEIGHT));
		break;
	}
}

void GridElement::drawEndWall(Direction direction) {
	ofSetColor(0);

	ofFill();
	switch (direction) {
	case DirectionSouth:
		//ofNoFill();
		ofSetColor(248, 187, 208); //blue
		ofDrawBox( //x,y,z, width, height, depth
			float((x + 0.5) *GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y + 0.5) *GRID_ELEMENT_HEIGHT), //this is for all the directions
			float(-(z)*GRID_ELEMENT_HEIGHT), //
			float(GRID_ELEMENT_HEIGHT),
			float(GRID_ELEMENT_HEIGHT),
			float(0)
		);
		break;

	case DirectionNorth:
		ofSetColor(248, 187, 208); //purple
		ofDrawBox( //x,y,z, width, height, depth
			float((x + 0.5) *GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y + 0.5) *GRID_ELEMENT_HEIGHT), //this is for all the directions
			float(-(z + 1) *GRID_ELEMENT_HEIGHT), //
			float(GRID_ELEMENT_HEIGHT),
			float(GRID_ELEMENT_HEIGHT),
			float(0)
		);
		break;

	case DirectionEast:
		ofSetColor(248, 187, 208); //yellow
								//ofDrawLine((x + 1) * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT, z*GRID_ELEMENT_HEIGHT,(x + 1) * GRID_ELEMENT_WIDTH, (y + 1) * GRID_ELEMENT_HEIGHT, z *GRID_ELEMENT_HEIGHT);
		ofDrawBox( //x,y,z, width, height, depth
			float((x + 1) *GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y + 0.5) *GRID_ELEMENT_HEIGHT), //this is for all the directions
			float(-(z + 0.5) *GRID_ELEMENT_HEIGHT), //
			float(0),
			float(GRID_ELEMENT_HEIGHT),
			float(-GRID_ELEMENT_HEIGHT)
		);
		break;
	case DirectionWest:
		ofSetColor(248, 187, 208); //white
		ofDrawBox( //x,y,z, width, height, depth
			float((x)*GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y + 0.5) *GRID_ELEMENT_HEIGHT), //this is for all the directions
			float(-(z + 0.5) *GRID_ELEMENT_HEIGHT), //
			float(0),
			float(GRID_ELEMENT_HEIGHT),
			float(-GRID_ELEMENT_HEIGHT)
		);
		break;

	case DirectionUp:
		ofSetColor(194,24,91); //black
		ofDrawBox( //x,y,z, width, height, depth
			float((x + 0.5) *GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y + 1) *GRID_ELEMENT_HEIGHT), //this is for all the directions
			float(-(z + 0.5) *GRID_ELEMENT_HEIGHT), //
			float(GRID_ELEMENT_HEIGHT),
			float(0),
			float(-GRID_ELEMENT_HEIGHT));
		break;
	case DirectionDown:
		ofSetColor(139, 195, 120); //pink
		ofDrawBox( //x,y,z, width, height, depth
			float((x + 0.5) *GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y)*GRID_ELEMENT_HEIGHT), //this is for all the directions
			float(-(z + 0.5) *GRID_ELEMENT_HEIGHT), //
			float(GRID_ELEMENT_HEIGHT),
			float(0),
			float(-GRID_ELEMENT_HEIGHT));
		break;
	}
}

void GridElement::setWall(Direction direction, bool is_solid) {
	walls[direction] = is_solid;

	// set opposite wall if it exists
	if (neighbours[direction] != NULL) {
		neighbours[direction]->walls[oppositeDirection(direction)] = is_solid;
	}
}
