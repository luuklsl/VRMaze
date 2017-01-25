//
//  constants.h
//  SearchStragies
//
//  Created by David Stritzl on 08/11/15.
//
//

#ifndef config_h
#define config_h

#define APP_VERSION_MAJOR   1
#define APP_VERSION_MINOR   0

#define WINDOW_WIDTH        700 /50
#define WINDOW_HEIGHT       700 /50
#define GRID_SIZE           5

#define GRID_ELEMENT_WIDTH  ((float)WINDOW_HEIGHT  / GRID_SIZE)//Might be in need of Change
#define GRID_ELEMENT_HEIGHT ((float)WINDOW_HEIGHT / GRID_SIZE)



#define N_WALLS_TO_BE_REMOVED 175


// simple macro to compute the manhattan distance to the end
// USAGE for a GridElement el: MANHATTAN_DISTANCE_TO_END(el)
#define MANHATTAN_DISTANCE_TO_END(el, h_el) ((abs((h_el->x) - el->x)) + abs(((h_el->y) - el->y)) + abs(((h_el->z) - el->z)))



#endif /* config_h */
