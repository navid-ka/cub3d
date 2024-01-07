/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:33:34 by plinscho          #+#    #+#             */
/*   Updated: 2024/01/07 20:15:25 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    draw_line(t_game *game, t_line *line, int color)
{
	/*
	double	delta_x;
	double	delta_y;
	double 	pixel_x;
	double 	pixel_y;
	int 	pixels;

	delta_x = line->x_end - line->x_start;
	delta_y = line->y_end - line->y_start;
	pixels = sqrt((pow(delta_x, 2)) + pow(delta_y, 2));
	pixel_x = line->x_start * 32;
	pixel_y = line->y_start * 32;
	*/
	while (line->draw_start < line->draw_end)
	{
		mlx_pixel_put(game->mlx_s->mlx_p, game->mlx_s->pov, line->x_start, line->draw_start, color);
		line->draw_start++;
	}
}

// This function sets the camera position and direction
void	init_ray(t_player *p, t_camera *c, int i)
{
	
	// the ray direction is the player direction + the camera plane
	c->camera_x = 2 * i / (double)S_WIDTH - 1;	// x-coordinate in camera space
	c->ray_dir_x = p->dir_x + c->plane_x * c->camera_x;
	c->ray_dir_y = p->dir_y + c->plane_y * c->camera_x;
	
	c->map_x = (int)p->pos_x;
	c->map_y = (int)p->pos_y;
	
	// distance the ray has to travel to go from 1 x-side to the next x-side
	c->delta_dist_x = fabs(1 / c->ray_dir_x);
	c->delta_dist_y = fabs(1 / c->ray_dir_y);	
}

void	init_step(t_player *p, t_camera *c)
{
	// what direction to step in x or y-direction (either +1 or -1)
	// Basically, if angle is bigger than 180, the ray is pointing left, so we need to step in the negative x-direction
	// If the angle is smaller than 180, the ray is pointing right, so we need to step in the positive x-direction
	// Same logic for the y-direction
	
	if (c->ray_dir_x < 0)	// if the ray is pointing left
	{
		c->step_x = -1;	// step in the negative x-direction
		c->side_dist_x = (p->pos_x - c->map_x) * c->delta_dist_x;	// calculate the distance to the next x-side
	}
	else
	{
		c->step_x = 1;	// step in the positive x-direction
		c->side_dist_x = (c->map_x + 1.0 - p->pos_x) * c->delta_dist_x;	// calculate the distance to the next x-side
	}
	if (c->ray_dir_y < 0)	// if the ray is pointing up
	{
		c->step_y = -1;
		c->side_dist_y = (p->pos_y - c->map_y) * c->delta_dist_y;
	}
	else					// if the ray is pointing down
	{
		c->step_y = 1;	
		c->side_dist_y = (c->map_y + 1.0 - p->pos_y) * c->delta_dist_y;
	}
}

void	init_dda(t_player *p, t_camera *c, char **map)
{
	int hit;
	
	hit = 0;
	while (hit == 0)
	{
		if (c->side_dist_x < c->side_dist_y)	// if the next x-side is closer than the next y-side
		{
			c->side_dist_x += c->delta_dist_x;	
			c->map_x += c->step_x;				// move to the next x-side
			c->side = 0;						// set the side to 0 (NS)
		}
		else
		{
			c->side_dist_y += c->delta_dist_y;
			c->map_y += c->step_y;
			c->side = 1;						// set the side to 1 (EW)
		}
		if (map[c->map_y][c->map_x] == '1')
			hit = 1;
	}
	// Calculations avoiding "fish eye" effect NOTE: I don't understand this part
	if (c->side == 0)	// if the NS side was hit
		c->perp_wall_dist = (c->map_x - p->pos_x + (1 - c->step_x) / 2) / c->ray_dir_x;	// calculate the distance to the point of impact
	else
		c->perp_wall_dist = (c->map_y - p->pos_y + (1 - c->step_y) / 2) / c->ray_dir_y;
}

void	init_line(t_line *line, t_camera *c, int i)
{
	// Calculate the height of the line
	line->line_height = (int)(S_HEIGHT / c->perp_wall_dist);
	
	// Calculate the lowest and highest pixel to fill in current stripe
	line->draw_start = -line->line_height / 2 + S_HEIGHT / 2;
	if (line->draw_start < 0)
		line->draw_start = 0;
	line->draw_end = line->line_height / 2 + S_HEIGHT / 2;
	if (line->draw_end >= S_HEIGHT)
		line->draw_end = S_HEIGHT - 1;

	// Calculate the color of the line
	line->x_start = i;
	line->x_end = i;
	// color depends on the distance to the wall
	line->color = 0xFFFF00;
}

void    raycast(t_game *game)
{
	t_line		line;
	int			i;
	
	i = 0;
	while (i < S_WIDTH)
	{
		// 1. Get player position and get the structs needef for the raycasting
		init_ray(game->player_s, game->camera_s, i);	// Gets the position from player and sets the direction vector
		init_step(game->player_s, game->camera_s);	// Sets the step and the side distance
		init_dda(game->player_s, game->camera_s, game->map_s->map);	// Performs the DDA algorithm		
		// 2. Get the height of the wall
		init_line(&line, game->camera_s, i);		
		draw_line(game, &line, line.color);
		i++;
	}
}

/*
// PSEUDOCODE
void	raycast(t_game *g)
{
	// 1. get the player position and direction, using cos and sin
	
	// 2. get the angle of the first ray, using the fov and the player direction
	// 3. for each ray, do the following:
	// 3.1. get the first intersection with a wall
	// 3.2. get the distance to the wall
	// 3.3. get the height of the wall
	// 3.4. get the color of the wall
	// 3.5. draw the wall
	// 4. draw the minimap
}

*/