/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:33:34 by plinscho          #+#    #+#             */
/*   Updated: 2024/03/21 19:18:42 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	dda_aux(t_camera *c)
{
	if (c->side == 0)
	{
		if (c->step_x > 0)
			c->hit_direction = SOUTH;
		else
			c->hit_direction = NORTH;
	}
	else
	{
		if (c->step_y > 0)
			c->hit_direction = EAST;
		else
			c->hit_direction = WEST;
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
	int	hit;

	hit = 0;
	(void)line;
	while (hit == 0)
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
		if (map[c->map_y][c->map_x] == '1')
		{
			hit = 1;
			dda_aux(c);
		}
	}
	wall_persepective(c, p);
}

void	init_line(t_line *line, t_camera *c, int i)
{
	line->line_height = (int)(S_HEIGHT / c->perp_wall_dist);
	line->draw_start = -line->line_height / 2 + S_HEIGHT / 2;
	if (line->draw_start < 0)
		line->draw_start = 0;
	line->draw_end = line->line_height / 2 + S_HEIGHT / 2;
	if (line->draw_end >= S_HEIGHT)
		line->draw_end = S_HEIGHT - 1;
	line->x_start = i;
	line->x_end = i;
}

void	raycast(t_game *game)
{
	t_line		line;
	int			i;
	t_img		img;

	i = 0;
	img = create_new_img(game->mlx_s, 1280, 720);
	while (i < S_WIDTH)
	{
		init_ray(game->player_s, game->camera_s, i);
		init_step(game->player_s, game->camera_s);
		init_dda(&line, game->player_s, game->camera_s, game->map_s->map);
		init_line(&line, game->camera_s, i);
		draw(game, game->camera_s, &img, &line);
		i++;
	}
	put_img_to_img(game->mlx_s->buffer, &img, 0, 0);
	mlx_destroy_image(game->mlx_s->mlx_p, img.img);
}
