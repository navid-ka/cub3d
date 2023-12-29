/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:25:00 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/30 00:03:23 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#define WALL_SAYS ft_printf("\nYou touch the wall...\nIt's Cold.\n");
#include <X11/keysym.h>

double	move_rot(t_player *p, char **map, int dir)
{
	(void)map;
	if (dir == XK_Left) // moving left
	{
		p->angle -= ROTATE_SPEED;
		if (p->angle < 0)
			p->angle += 2 * PI;
		return (ROTATE_SPEED);
	}
	else// if (dir == 0x64) // moving right
	{
		p->angle += ROTATE_SPEED;
		if (p->angle > 2 * PI)
			p->angle -= 2 * PI;
		return (ROTATE_SPEED);
	}
}

double	move_y(t_player *p, char **map, int dir)
{
	int x;
	int y;

	x = (int)p->pos_x;
	y = (int)p->pos_y;
	if (dir == XK_W) // moving up
	{
		if (map[y - 1][x] == '1') // if there is a wall in the
		{
			WALL_SAYS;
			return (0);
		}	
			
		return (MOVE_SPEED);		
	}
	else// if (dir == 0x73) // moving down
	{
		if (map[y + 1][x] == '1') // if there is a wall in the
		{
			WALL_SAYS;
			return (0);
		}
		return (MOVE_SPEED);
		
	}
}

double	move_x(t_player *p, char **map, int dir)
{
	int x;
	int y;

	x = (int)p->pos_x;
	y = (int)p->pos_y;
	if (dir == XK_A) // moving left
	{
		if (map[y][x - 1] == '1')
		{
			WALL_SAYS;
			return (0);
		}
		return (MOVE_SPEED);
	}
	else// if (dir == 0x64) // moving right
	{
		if (map[y][x + 1] == '1')
		{
			WALL_SAYS;
			return (0);
		}
		return (MOVE_SPEED);
	}
}