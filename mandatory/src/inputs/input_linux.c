/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_linux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:51:39 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/02/27 19:30:02 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <X11/keysym.h>

#define XK_Left                          0xff51  /* Move left, left arrow */
#define XK_Up                            0xff52  /* Move up, up arrow */
#define XK_Right                         0xff53  /* Move right, right arrow */
#define XK_Down                          0xff54  /* Move down, down arrow */

//https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h for keycodes

int move_player(t_game *game, double dx, double dy)
{
    t_player *player = game->player_s;
    double new_pos_x = player->pos_x + dx;
    double new_pos_y = player->pos_y + dy;
    double margin = 0.03;

    // Comprueba el movimiento en la dirección x
    if (new_pos_x + dx - margin >= 0 && new_pos_x + dx + margin < game->map_s->width &&
        game->map_s->map[(int)player->pos_y][(int)(new_pos_x + dx - margin)] != '1' &&
        game->map_s->map[(int)player->pos_y][(int)(new_pos_x + dx + margin)] != '1')
    {
        player->pos_x = new_pos_x;
    }

    // Comprueba el movimiento en la dirección y
    if (new_pos_y + dy - margin >= 0 && new_pos_y + dy + margin < game->map_s->height &&
        game->map_s->map[(int)(new_pos_y + dy - margin)][(int)player->pos_x] != '1' &&
        game->map_s->map[(int)(new_pos_y + dy + margin)][(int)player->pos_x] != '1')
    {
        player->pos_y = new_pos_y;
    }

    return 0;
}

int on_key_press(int keycode, t_game *game)
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
        player->angle = move_rot(camera, player, game->map_s->map, keycode);
    return (0);
}
/*
int     on_key_release(int keycode, t_game *game)
{
	t_player *player;

	player = game->player_s;
	//mlx_clear_window(game->mlx_s->mlx_p, game->mlx_s->win);
	if (keycode == 0x77 || keycode == XK_W) // 'w' key
		player->pos_y -= move_y(player, game->map_s->map, XK_W);
	else if (keycode == 0x73 || keycode == XK_S) // 's' key
		player->pos_y += move_y(player, game->map_s->map, XK_S);
	else if (keycode == 0x61 || keycode == XK_A) // 'a' key
		player->pos_x -= move_x(player, game->map_s->map, XK_A);
	else if (keycode == 0x64 || keycode == XK_D) // 'd' key
		player->pos_x += move_x(player, game->map_s->map, XK_D);
	return (0);
}*/
