/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:33:34 by plinscho          #+#    #+#             */
/*   Updated: 2024/01/06 18:19:03 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
int	check_wall(t_game *game, double x0, double y0);

// to start, we need the player position and the player direction
double    draw_line(t_game *game, double x0, double y0, double angle)
{
	double	x_inc;
	double	y_inc;

	x_inc = x0;
	y_inc = y0;
	for (int i = 0 ; i < RENDER_DIST ; i++)
	{
		// check if it hits a wall. Will need the map.
		x_inc += 1 * cos(angle);
		y_inc -= 1 * sin(angle);
		if (check_wall(game, x0, y0))
		{
			//return (sqrt((pow(x_inc - x0, 2)) + pow(y_inc - y0, 2)));
			break;
		}
		mlx_pixel_put(game->mlx_s->mlx_p, game->mlx_s->win, (x_inc), (y_inc), 0x00AAFF00);
	}
	return (RENDER_DIST);
}

int	check_wall(t_game *game, double x0, double y0)
{
	int i;
	int j;
	
	i = (int)(x0 / 32);
	j = (int)(y0 / 32);
	if (game->map_s->map[j][i] == '1')
		return (1);
	return (0);
}

void    raycast(t_game *game)
{
	double  orientation;
	double	distance;
	double	x0;
	double	y0;
	
	y0 = game->player_s->pos_y * 32 + 16;
	x0 = game->player_s->pos_x * 32 + 16;
	orientation = game->player_s->angle;
	while (orientation == game->player_s->angle)//< game->player_s->fov + game->player_s->angle)
	{
		distance = draw_line(game, x0, y0, orientation) - 16;
		distance /= 32;

//		draw the points in the screen using the distance.
/*
		(distance > 0) 
		draw_camera()		
*/		
		orientation += 1;
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