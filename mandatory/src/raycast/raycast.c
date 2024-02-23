/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:33:34 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/23 19:06:58 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// This function sets the camera position and direction

void	get_distance(t_camera *c, t_player *p)
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

void	init_dda(t_player *p, t_camera *c, char **map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (c->side_dist_x < c->side_dist_y)
		{
			c->side_dist_x += c->ddx;
			c->map_x += c->step_x;
			c->side = 0;
		}
		else
		{
			c->side_dist_y += c->ddy;
			c->map_y += c->step_y;
			c->side = 1;
		}
		if (map[c->map_y][c->map_x] == '1')
		{
			hit = 1;
			dda_aux(c);
		}
	}
	get_distance(c, p);
}

void	init_step(t_player *p, t_camera *c)
{
	if (c->ray_dir_x < 0)
	{
		c->step_x = -1;
		c->side_dist_x = (p->pos_x - c->map_x) * c->ddx;
	}
	else
	{
		c->step_x = 1;
		c->side_dist_x = (c->map_x + 1.0 - p->pos_x) * c->ddx;
	}
	if (c->ray_dir_y < 0)
	{
		c->step_y = -1;
		c->side_dist_y = (p->pos_y - c->map_y) * c->ddy;
	}
	else
	{
		c->step_y = 1;
		c->side_dist_y = (c->map_y + 1.0 - p->pos_y) * c->ddy;
	}
}

void	init_ray(t_player *p, t_camera *c, int i)
{
	double	fov_scale;

	fov_scale = p->fov / PI;
	c->camera_x = 2 * fov_scale * (i / (double) S_WIDTH) - fov_scale;
	c->ray_dir_x = p->dir_x + c->plane_x * c->camera_x;
	c->ray_dir_y = p->dir_y + c->plane_y * c->camera_x;
	c->map_x = (int)p->pos_x;
	c->map_y = (int)p->pos_y;
	if (c->ray_dir_x == 0)
		c->ddx = 1e30;
	else
		c->ddx = fabs(1 / c->ray_dir_x);
	if (c->ray_dir_y == 0)
		c->ddy = 1e30;
	else
		c->ddy = fabs(1 / c->ray_dir_y);
}

void	raycast(t_game *game)
{
	t_line		line;
	t_img		img;

	game->screen_x = 0;
	img = create_new_img(game->mlx_s, 1280, 720);
	while (game->screen_x < S_WIDTH)
	{
		init_ray(game->player_s, game->camera_s, game->screen_x);
		init_step(game->player_s, game->camera_s);
		init_dda(game->player_s, game->camera_s, game->map_s->map);
		init_line(&line, game->camera_s, game->screen_x);
		draw(game, game->camera_s, &img, &line);
		game->screen_x++;
	}
	put_img_to_img(game->mlx_s->buffer, &img, 0, 0);
	mlx_destroy_image(game->mlx_s->mlx_p, img.img);
}
