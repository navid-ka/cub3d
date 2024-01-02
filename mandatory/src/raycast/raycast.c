/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:33:34 by plinscho          #+#    #+#             */
/*   Updated: 2024/01/02 20:37:10 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// to start, we need the player position and the player direction
void    draw_line(t_game *game, double x0, double y0, double angle)
{
	for (int i = 0 ; i < RENDER_DIST ; i++)
	{
		// check if it hits a wall. Will need the map.
		mlx_pixel_put(game->mlx_s->mlx_p, game->mlx_s->win, (x0), (y0), 0x00FFFF00);
		x0 += 1 * cos(angle);
		y0 += 1 * sin(angle);
	}
	return ;
}

void    raycast(t_game *game)
{
	double  ray_angle;
	double	x0;
	double	y0;
	
	y0 = game->player_s->pos_y * 32 + 16;
	x0 = game->player_s->pos_x * 32 + 16;
	ray_angle = game->player_s->angle;
	while (ray_angle < game->player_s->fov + game->player_s->angle)
	{
		draw_line(game, x0, y0, ray_angle);
		ray_angle += 0.025;
	}
	return ;
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