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
	if (visited) {
		ofSetColor(145, 187, 255);
		ofFill();
		//ofDrawRectangle((x * GRID_ELEMENT_WIDTH), (y * GRID_ELEMENT_HEIGHT), GRID_ELEMENT_WIDTH / 2, GRID_ELEMENT_HEIGHT / 2);
		ofDrawBox((x + 0.5)*GRID_ELEMENT_HEIGHT, (y + 0.5)*GRID_ELEMENT_HEIGHT, (z + 0.5)*GRID_ELEMENT_HEIGHT, GRID_ELEMENT_HEIGHT / 1.5);
	}


	// draw circle if marked
	if (marked) {
		ofNoFill();
		ofSetColor(249, 77, 42);
		//ofDrawEllipse((x + 0.5) * GRID_ELEMENT_WIDTH, (y + 0.5) * GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH * 0.95, GRID_ELEMENT_HEIGHT * 0.95);
		ofDrawSphere((x + 0.5) * GRID_ELEMENT_HEIGHT, (y + 0.5) * GRID_ELEMENT_HEIGHT, (z + 0.5)*GRID_ELEMENT_HEIGHT,GRID_ELEMENT_HEIGHT/2);
		
	}


	// draw all walls
	for (int direction = 0; direction < N_DIRECTIONS; direction++) {
		if (walls[direction]) {
			ofNoFill();
			drawWall((Direction)direction);
		}
	}

}

void GridElement::drawWall(Direction direction) {
	ofSetColor(0);
	
	ofNoFill();
	switch (direction) {
	case DirectionSouth:
		//ofNoFill();
		ofSetColor(255, 0, 0, 150); //red
		ofDrawBox( //x,y,z, width, height, depth
			float((x+0.5) *GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y+0.5) *GRID_ELEMENT_HEIGHT), //this is for all the directions
			float((z) *GRID_ELEMENT_HEIGHT), //
			float(GRID_ELEMENT_HEIGHT),
			float(GRID_ELEMENT_HEIGHT),
			float(10)
		);
		break;
	
	case DirectionNorth:
		ofSetColor(255, 0, 255, 150); //purple
		ofDrawBox( //x,y,z, width, height, depth
			float((x + 0.5) *GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y + 0.5) *GRID_ELEMENT_HEIGHT), //this is for all the directions
			float((z + 1) *GRID_ELEMENT_HEIGHT), //
			float(GRID_ELEMENT_HEIGHT),
			float(GRID_ELEMENT_HEIGHT),
			float(10)
		);
		break;

	case DirectionEast:
		ofSetColor(255, 255, 0, 150); //yellow
		//ofDrawLine((x + 1) * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT, z*GRID_ELEMENT_HEIGHT,(x + 1) * GRID_ELEMENT_WIDTH, (y + 1) * GRID_ELEMENT_HEIGHT, z *GRID_ELEMENT_HEIGHT);
		ofDrawBox( //x,y,z, width, height, depth
			float((x +1) *GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y + 0.5) *GRID_ELEMENT_HEIGHT), //this is for all the directions
			float((z + 0.5) *GRID_ELEMENT_HEIGHT), //
			float(10),
			float(GRID_ELEMENT_HEIGHT),
			float(GRID_ELEMENT_HEIGHT)
		);
		break;	
	case DirectionWest:
		ofSetColor(0, 0, 255, 150); //white
		ofDrawBox( //x,y,z, width, height, depth
			float((x) *GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y + 0.5) *GRID_ELEMENT_HEIGHT), //this is for all the directions
			float((z + 0.5) *GRID_ELEMENT_HEIGHT), //
			float(10),
			float(GRID_ELEMENT_HEIGHT),
			float(GRID_ELEMENT_HEIGHT)
		); 
		break;

	case DirectionUp:
		ofSetColor(0, 0, 0, 150); //black
		ofDrawBox( //x,y,z, width, height, depth
			float((x + 0.5) *GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y + 1) *GRID_ELEMENT_HEIGHT), //this is for all the directions
			float((z + 0.5) *GRID_ELEMENT_HEIGHT), //
			float(GRID_ELEMENT_HEIGHT),
			float(30),
			float(GRID_ELEMENT_HEIGHT));
		break;
	case DirectionDown:
		ofSetColor(255, 200, 200, 150); //pink
		ofDrawBox( //x,y,z, width, height, depth
			float((x + 0.5) *GRID_ELEMENT_HEIGHT), //relative location based on coordinates
			float((y) *GRID_ELEMENT_HEIGHT), //this is for all the directions
			float((z + 0.5) *GRID_ELEMENT_HEIGHT), //
			float(GRID_ELEMENT_HEIGHT),
			float(10),
			float(GRID_ELEMENT_HEIGHT));
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
