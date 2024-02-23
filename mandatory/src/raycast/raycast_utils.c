/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:33:30 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/23 19:11:13 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	plane_mult(int fov)
{
	double	plane_multiplier;

	plane_multiplier = deg_to_rad(fov);
	plane_multiplier = tan(plane_multiplier / 2);
	plane_multiplier = 2 / plane_multiplier;
	return (plane_multiplier);
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
	line->color_fader = 0;
	line->x_end = i;
	line->color = 0xFF0F00;
}

void	dda_aux(t_camera *c)
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

double	deg_to_rad(int dg_angle)
{
	return (dg_angle * PI / 180);
}

int		rad_to_dg(double angle)
{
	return ((int)(angle * 180 / PI));
}

/*

void	dda_step(t_game *game, int map_x, int map_y)
{
	double	x0;
	double	y0;

	x0 = game->player_s->pos_x;
	y0 = game->player_s->pos_y;
	if (game->player_s->dir_x < 0)
	{
		game->camera_s->step_x = -1;
		game->camera_s->side_dist_x = (x0 - map_x) * game->camera_s->ddx;
	}
	else
	{
		game->camera_s->step_x = 1;
		game->camera_s->side_dist_x = (map_x + 1.0 - x0) * game->camera_s->ddx;
	}
	if (game->player_s->dir_y < 0)
	{
		game->camera_s->step_y = -1;
		game->camera_s->side_dist_y = (y0 - map_y) * game->camera_s->ddy;
	}
	else
	{
		game->camera_s->step_y = 1;
		game->camera_s->side_dist_y = (map_y + 1.0 - y0) * game->camera_s->ddy;
	}
}


void render_3d_map(t_game *game)
{
//    double fov = game->player_s->fov;

    for (int x = 0; x < S_WIDTH; x++)
    {
        // calculate direction of ray
        double ray_dir_x = game->player_s->dir_x + game->camera_s->plane_x * (2 * x / (double)S_WIDTH - 1);
        double ray_dir_y = game->player_s->dir_y + game->camera_s->plane_y * (2 * x / (double)S_WIDTH - 1);

        // cast the ray
        game->player_s->dir_x = ray_dir_x;
        game->player_s->dir_y = ray_dir_y;
        double perp_wall_dist = dda_rays(game);

        // calculate height of line to draw
        int line_height = (int)(S_HEIGHT / perp_wall_dist);

        // calculate lowest and highest pixel to fill in current stripe
        int draw_start = -line_height / 2 + S_HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + S_HEIGHT / 2;
        if (draw_end >= S_HEIGHT)
            draw_end = S_HEIGHT - 1;

        // draw the vertical line
        for (int y = draw_start; y < draw_end; y++)
        {
            mlx_pixel_put(game->mlx_s->mlx_p, game->mlx_s->pov, x, y, 0x0BBFF00);
        }
    }
}
*/
