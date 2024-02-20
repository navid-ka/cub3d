/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_linux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:51:39 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/02/20 18:31:59 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <X11/keysym.h>

#define XK_L                             0xff51  /* Move left, left arrow */
#define XK_U                             0xff52  /* Move up, up arrow */
#define XK_R                             0xff53  /* Move right, right arrow */
#define XK_D                             0xff54  /* Move down, down arrow */

//https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h for keycodes

int	move_player(t_game *game, double dx, double dy)
{
	char		**map;
	t_player	*player;
	double		new_pos_x;
	double		new_pos_y;
	double		margin;

	margin = 0.03;
	map = game->map_s->map;
	new_pos_x = player->pos_x + dx;
	new_pos_y = player->pos_y + dy;
	player = game->player_s;
	if (new_pos_x + dx - margin >= 0 && new_pos_x + dx + margin < width &&
		map[(int)player->pos_y][(int)(new_pos_x + dx - margin)] != '1' &&
		map[(int)player->pos_y][(int)(new_pos_x + dx + margin)] != '1')
	{
		player->pos_x = new_pos_x;
	}
	if (new_pos_y + dy - margin >= 0 && new_pos_y + dy + margin < height &&
		map[(int)(new_pos_y + dy - margin)][(int)player->pos_x] != '1' &&
		map[(int)(new_pos_y + dy + margin)][(int)player->pos_x] != '1')
	{
		player->pos_y = new_pos_y;
	}
	return (0);
}

int	on_key_press(int keycode, t_game *game)
{
	t_camera *camera = game->camera_s;
	t_player *player = game->player_s;
	player->speed = 0.5;

	if (keycode == XK_Escape)
		return (window_destroy(game));
	double dx = 0, dy = 0;
	if (keycode == 0x77 || keycode == XK_W) // 'w' key
	{
		dx += player->dir_x * player->speed;
		dy += player->dir_y *  player->speed;
    }
	if (keycode == 0x73 || keycode == XK_S) // 's' key
    {
		dx -= player->dir_x * player->speed;
		dy -= player->dir_y * player->speed;
	}
	if (keycode == 0x61 || keycode == XK_A) // 'a' key
	{
		dx -= player->dir_y * player->speed;
		dy += player->dir_x * player->speed;
	}
	if (keycode == 0x64 || keycode == XK_D) // 'd' key
	{
		dx += player->dir_y * player->speed;
		dy -= player->dir_x * player->speed;
	}
	if (player->pos_x != 0 || player->pos_y != 0)
		move_player(game, dx, dy);
	if (keycode == XK_Right || keycode == XK_Left) // 'left arrow' key
	player->angle = move_rot(camera, player, map, keycode);
	return (0);
}
/*
int     on_key_release(int keycode, t_game *game)
{
	t_player *player;

	player = game->player_s;
	//mlx_clear_window(game->mlx_s->mlx_p, game->mlx_s->win);
	if (keycode == 0x77 || keycode == XK_W) // 'w' key
		player->pos_y -= move_y(player, map, XK_W);
	else if (keycode == 0x73 || keycode == XK_S) // 's' key
		player->pos_y += move_y(player, map, XK_S);
	else if (keycode == 0x61 || keycode == XK_A) // 'a' key
		player->pos_x -= move_x(player, map, XK_A);
	else if (keycode == 0x64 || keycode == XK_D) // 'd' key
		player->pos_x += move_x(player, map, XK_D);
	return (0);
}*/
