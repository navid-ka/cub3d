/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:58:54 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/27 18:37:17 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_collision_x(t_game *game, double dx, char *wall, double margin)
{
	t_player	*player;
	double		new_x;

	player = game->player_s;
	new_x = player->pos_x + dx;
	if (new_x + dx - margin >= 0 && new_x + dx + margin < game->map_s->width
		&& !ft_strchr(wall,
			game->map_s->map[(int)player->pos_y][(int)(new_x + dx - margin)])
		&& !ft_strchr(wall,
		game->map_s->map[(int)player->pos_y][(int)(new_x + dx + margin)]))
	{
		player->pos_x = new_x;
		return (1);
	}
	return (0);
}

int	check_collision_y(t_game *game, double dy, char *wall, double margin)
{
	t_player	*player;
	double		new_y;

	player = game->player_s;
	new_y = player->pos_y + dy;
	if (new_y + dy - margin >= 0 && new_y + dy + margin < game->map_s->height
		&& !ft_strchr(wall, 
			game->map_s->map[(int)(new_y + dy - margin)][(int)player->pos_x])
		&& !ft_strchr(wall, 
			game->map_s->map[(int)(new_y + dy + margin)][(int)player->pos_x]))
	{
		player->pos_y = new_y;
		return (1);
	}
	return (0);
}

int	collision_checker(t_game *game, double dx, double dy)
{
	static double	margin = 0.07;
	char			*wall;

	wall = "1";
	check_collision_x(game, dx, wall, margin);
	check_collision_y(game, dy, wall, margin);
	return (0);
}

double	move_rot(t_camera *cam, t_player *p, char **map, int dir)
{
	double	increment;

	(void)map;
	if (dir == ARROW_RIGHT)
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

int	on_key_press(int keycode, t_game *game)
{
	t_camera	*camera;
	t_player	*player;

	player = game->player_s;
	camera = game->camera_s;
	player->speed = 0.25;
	if (keycode == ESC)
		return (window_destroy(game));
	player_move(keycode, player, game);
	if (player->pos_x != 0 || player->pos_y != 0)
		collision_checker(game, player->dx, player->dy);
	if (keycode == ARROW_RIGHT || keycode == ARROW_LEFT)
		player->angle = move_rot(camera, player, game->map_s->map, keycode);
	return (0);
}

int	on_key_release(int keycode, t_game *game)
{
	t_player	*player;

	player = game->player_s;
	if (keycode == W)
		player->pos_y -= 0;
	else if (keycode == S)
		player->pos_y += 0;
	else if (keycode == A)
		player->pos_x -= 0;
	else if (keycode == D)
		player->pos_x += 0;
	return (0);
}
