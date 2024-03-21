/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:06:43 by bifrost           #+#    #+#             */
/*   Updated: 2024/03/21 19:41:18 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// This function sets the camera position and direction
void	init_ray(t_player *p, t_camera *c, int i)
{
	double	fov_scale;

	fov_scale = p->fov / PI;
	c->camera_x = 2 * fov_scale * (i / (double)S_WIDTH) - fov_scale;
	c->ray_dir_x = -p->dir_x + c->plane_x * c->camera_x;
	c->ray_dir_y = -p->dir_y + c->plane_y * c->camera_x;
	c->map_x = (int)p->pos_x;
	c->map_y = (int)p->pos_y;
	if (c->ray_dir_x == 0)
		c->delta_dist_x = 1e30;
	else
		c->delta_dist_x = fabsl(1 / c->ray_dir_x);
	if (c->ray_dir_y == 0)
		c->delta_dist_y = 1e30;
	else
		c->delta_dist_y = fabsl(1 / c->ray_dir_y);
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

void	wall_persepective(t_camera *c, t_player *p)
{
	if (c->side == 0)
		c->perp_wall_dist = (c->map_x - p->pos_x + (1 - c->step_x) / 2) \
				/ c->ray_dir_x;
	else
		c->perp_wall_dist = (c->map_y - p->pos_y + (1 - c->step_y) / 2) \
				/ c->ray_dir_y;
	if (c->side == 0)
		c->wall_x = p->pos_y + c->perp_wall_dist * c->ray_dir_y;
	else
		c->wall_x = p->pos_x + c->perp_wall_dist * c->ray_dir_x;
	c->wall_x -= floor((c->wall_x));
}

void	init_dda(t_line *line, t_player *p, t_camera *c, char **map)
{
	c->hit = 0;
	(void)line;
	while (c->hit == 0)
	{
		if (c->side_dist_x < c->side_dist_y)
		{
			c->side_dist_x += c->delta_dist_x;
			c->map_x += c->step_x;
			c->side = 0;
		}
		else
		{
			c->side_dist_y += c->delta_dist_y;
			c->map_y += c->step_y;
			c->side = 1;
		}
		if ((map[c->map_y][c->map_x] == '1' || map[c->map_y][c->map_x] == '2'
			|| map[c->map_y][c->map_x] == '3' || map[c->map_y][c->map_x] == '4')
			|| (map[c->map_y][c->map_x] == 'D' && c->door_state == CLOSE))
		{
			c->hit = 1;
			c->type = map[c->map_y][c->map_x];
		}
	}
	wall_persepective(c, p);
}

void	init_line(t_line *line, t_camera *c, int i)
{
	line->line_height = (int)(S_HEIGHT / c->perp_wall_dist) * 2;
	line->draw_start = -line->line_height / 2 + S_HEIGHT / 2;
	if (line->draw_start < 0)
		line->draw_start = 0;
	line->draw_end = line->line_height / 2 + S_HEIGHT / 2;
	if (line->draw_end >= S_HEIGHT)
		line->draw_end = S_HEIGHT - 1;
	line->x_start = i;
	line->x_end = i;
}
