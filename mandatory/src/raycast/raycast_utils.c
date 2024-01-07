/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:33:30 by plinscho          #+#    #+#             */
/*   Updated: 2024/01/07 17:53:42 by plinscho         ###   ########.fr       */
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

double	deg_to_rad(int dg_angle)
{
	return (dg_angle * PI / 180);
}

int		rad_to_dg(double angle)
{
	return ((int)(angle * 180 / PI));
}

double dda_rays(t_game *game)
{
	double	x0;
	double	y0;

	x0 = game->player_s->pos_x;
	y0 = game->player_s->pos_y;
	int map_x = (int)game->player_s->pos_x;
    int map_y = (int)game->player_s->pos_y;

    // calculate step and initial sideDist
    game->camera_s->delta_dist_x = fabs(1 / game->player_s->dir_x);
    game->camera_s->delta_dist_y = fabs(1 / game->player_s->dir_y);
    if (game->player_s->dir_x < 0)
    {
        game->camera_s->step_x = -1;
        game->camera_s->side_dist_x = (x0 - map_x) * game->camera_s->delta_dist_x;
    }
    else
    {
        game->camera_s->step_x = 1;
        game->camera_s->side_dist_x = (map_x + 1.0 - x0) * game->camera_s->delta_dist_x;
    }
    if (game->player_s->dir_y < 0)
    {
        game->camera_s->step_y = -1;
        game->camera_s->side_dist_y = (y0 - map_y) * game->camera_s->delta_dist_y;
    }
    else
    {
        game->camera_s->step_y = 1;
        game->camera_s->side_dist_y = (map_y + 1.0 - y0) * game->camera_s->delta_dist_y;
    }

    // perform DDA
    int hit = 0;
    while (hit == 0)
    {
        if (game->camera_s->side_dist_x < game->camera_s->side_dist_y)
        {
            game->camera_s->side_dist_x += game->camera_s->delta_dist_x;
            map_x += game->camera_s->step_x;
        }
        else
        {
            game->camera_s->side_dist_y += game->camera_s->delta_dist_y;
            map_y += game->camera_s->step_y;
        }
        if (game->map_s->map[map_y][map_x] == '1')
            hit = 1;
    }

    // calculate distance to the point of impact
    if (game->camera_s->side_dist_x < game->camera_s->side_dist_y)
        return (map_x - x0 + (1 - game->camera_s->step_x) / 2) / game->player_s->dir_x;
    else
        return (map_y - y0 + (1 - game->camera_s->step_y) / 2) / game->player_s->dir_y;
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