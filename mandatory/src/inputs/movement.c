/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:25:00 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/20 19:03:57 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#define WALL_SAYS ft_printf("\nYou touch the wall...\nIt's Cold.\n");
#include <X11/keysym.h>

double	move_rot(t_camera *cam, t_player *p, int dir)
{
	double	increment;

	if (dir == XK_Right)
		increment = -ROTATE_SPEED;
	else
		increment = ROTATE_SPEED;
	p->angle += increment;
	if (p->angle < 0)
		p->angle += 2 * PI;
	else if (p->angle > 2 * PI)
		p->angle -= 2 * PI;
	p->dir_x = cos(p->angle);
	p->dir_y = sin(p->angle);
	cam->plane_x = p->dir_y * cam->plane_multiplier;
	cam->plane_y = -p->dir_x * cam->plane_multiplier;
	return (p->angle);
}

void	move_up(t_player *p, double *dx, double *dy)
{
	*dx += player->dir_x * player->speed;
	*dy += player->dir_y * player->speed;
}

void	move_down(t_player *p, double *dx, double *dy)
{
	*dx -= player->dir_x * player->speed;
	*dy -= player->dir_y * player->speed;
}

void	move_left(t_player *p, double *dx, double *dy)
{
	dx -= player->dir_y * player->speed;
	dy += player->dir_x * player->speed;
}

void	move_right(t_player *p, double *dx, double *dy)
{
	dx += player->dir_y * player->speed;
	dy -= player->dir_x * player->speed;
}
