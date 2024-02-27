/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:15:59 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/27 19:22:12 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_ray(t_player *p, t_camera *c, int i)
{
	double	fov_scale;

	fov_scale = p->fov / PI;
	c->camera_x = 2 * fov_scale * (i / (double)S_WIDTH) - fov_scale;
	c->ray_dir_x = p->dir_x + c->plane_x * c->camera_x;
	c->ray_dir_y = p->dir_y + c->plane_y * c->camera_x;
	c->map_x = (int)p->pos_x;
	c->map_y = (int)p->pos_y;
	if (c->ray_dir_x == 0)
		c->delta_dist_x = 1e30;
	else
		c->delta_dist_x = fabs(1 / c->ray_dir_x);
	if (c->ray_dir_y == 0)
		c->delta_dist_y = 1e30;
	else
		c->delta_dist_y = fabs(1 / c->ray_dir_y);
}

void	init_step(t_player *p, t_camera *c)
{
	if (c->ray_dir_x < 0)
	{
		c->step_x = -1;
		c->side_dist_x = (p->pos_x - c->map_x) * c->delta_dist_x;
	}
	else
	{
		c->step_x = 1;
		c->side_dist_x = (c->map_x + 1.0 - p->pos_x) * c->delta_dist_x;
	}
	if (c->ray_dir_y < 0)
	{
		c->step_y = -1;
		c->side_dist_y = (p->pos_y - c->map_y) * c->delta_dist_y;
	}
	else
	{
		c->step_y = 1;
		c->side_dist_y = (c->map_y + 1.0 - p->pos_y) * c->delta_dist_y;
	}
}
