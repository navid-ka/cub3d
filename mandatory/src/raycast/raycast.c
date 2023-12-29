/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:33:34 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/30 00:06:29 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// to start, we need the player position and the player direction
void    ray_init(t_game *game)
{
	game->player_s->dir_x = cos(game->player_s->angle);
	game->player_s->dir_y = sin(game->player_s->angle);
	return ;
}

void    raycast(t_game *game)
{
	ray_init(game);	
	return ;
}

/*
CODE I STOLE FROM CHAT GPT

#include <stdio.h>
#include <math.h>

#define PI 3.14159265359

// Define the player structure with position and viewing angle
typedef struct {
    double x, y;  // Player position
    double angle; // Viewing angle
} Player;

// Function to cast rays in the map
void castRays(Player* player, char** map, int mapRows, int mapCols, int screenWidth, int screenHeight) {
    // Constants for raycasting calculations
    double fov = PI / 3.0;  // Field of view
    double rayAngleDelta = fov / screenWidth;  // Angle between rays

    // Iterate through each column of the screen
    for (int col = 0; col < screenWidth; ++col) {
        // Calculate the current ray angle
        double rayAngle = player->angle - (fov / 2.0) + col * rayAngleDelta;

        // Initialize ray variables
        double rayX = cos(rayAngle);
        double rayY = sin(rayAngle);

        // Initialize ray position to player's position
        double rayPosX = player->x;
        double rayPosY = player->y;

        // Variables to store the distance to the closest wall
        double distanceToWall = 0;
        int hitWall = 0;

        // Raycasting loop
        while (!hitWall && rayPosX >= 0 && rayPosX < mapCols && rayPosY >= 0 && rayPosY < mapRows) {
            // Check if the current position in the map is a wall
            if (map[(int)rayPosY][(int)rayPosX] == '#') {
                hitWall = 1;
            } else {
                // Move the ray to the next position
                rayPosX += rayX;
                rayPosY += rayY;
                distanceToWall += 1.0;  // Increment distance for each step
            }
        }

        // Draw the column based on the distance to the wall
        // (You can customize this based on your visualization method)
        int wallHeight = screenHeight / distanceToWall; // Simple height calculation
        // Draw the column (e.g., print characters or draw pixels)
        for (int row = 0; row < screenHeight; ++row) {
            if (row < screenHeight / 2 - wallHeight / 2 || row >= screenHeight / 2 + wallHeight / 2) {
                printf(" ");  // Empty space
            } else {
                printf("#");  // Wall segment
            }
        }
    }
}

// Function to print the map
void printMap(char** map, int mapRows, int mapCols) {
    for (int row = 0; row < mapRows; ++row) {
        for (int col = 0; col < mapCols; ++col) {
            printf("%c ", map[row][col]);
        }
        printf("\n");
    }
}

int main() {
    // Initialize a map and a player
    char* myMap[] = {
        "##########",
        "#........#",
        "#........#",
        "#........#",
        "#........#",
        "#........#",
        "#........#",
        "#........#",
        "##########"
    };
    int mapRows = sizeof(myMap) / sizeof(myMap[0]);
    int mapCols = strlen(myMap[0]);

    Player myPlayer = {1.5, 1.5, PI / 4.0}; // Player starts at position (1.5, 1.5) with a 45-degree viewing angle

    // Print the initial map
    printf("Initial map:\n");
    printMap(myMap, mapRows, mapCols);

    // Cast rays and visualize the scene
    printf("\nRaycasting result:\n");
    castRays(&myPlayer, myMap, mapRows, mapCols, 80, 20); // Adjust screen dimensions as needed

    return 0;
}



*/