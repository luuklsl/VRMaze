//
//  obstacle_generator.cpp
//  SearchStragies
//
//  Created by David Stritzl on 08/11/2016.
//
//

#define _USE_MATH_DEFINES

#include "Grid.hpp"

#include <cmath>
#include <cstdlib>
#include <vector>

#define N_OBSTACLES 5
#define MIN_OBSTACLE_RADIUS 2
#define MAX_OBSTACLE_RADIUS 10

void Grid::generateObstacles() {
    // NOTE: this algorithm is not deterministic
    
    clearRect(0, 0, GRID_SIZE, GRID_SIZE);
    
    // helper structure to save obstacles in a vector
    struct Obstacle {
        int center_x, center_y;
        int radius;
    };
    
    std::vector<Obstacle> obstacles;
    
    while(obstacles.size() < N_OBSTACLES) {
        int center_x = std::rand() % GRID_SIZE;
        int center_y = std::rand() % GRID_SIZE;
        
        int radius = std::rand() % (MAX_OBSTACLE_RADIUS - MIN_OBSTACLE_RADIUS) + MIN_OBSTACLE_RADIUS;
        
        bool too_close = false;
        for(Obstacle obstacle : obstacles) {
            int distance = (int)std::sqrt(std::pow(obstacle.center_x - center_x, 2) + std::pow(obstacle.center_y - center_y, 2));
            if(distance < obstacle.radius + radius) {
                too_close = true;
                break;
            }
        }
        
        if(too_close) {
            continue;
        }
        
        double first_alpha = std::rand() % (int)(2 * M_PI * 1000) / 1000.0;
        double last_alpha = first_alpha + std::rand() % (int)(M_PI * 1000) / 1000.0 + M_PI;
        if(last_alpha > 2 * M_PI) {
            last_alpha -= 2 * M_PI;
        }
        
        drawArc(center_x, center_y, radius, first_alpha, last_alpha);
        obstacles.push_back({center_x, center_y, radius});
    }
}
