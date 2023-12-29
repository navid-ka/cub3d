/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_linux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:51:39 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/12/29 21:20:36 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <X11/keysym.h>

#define XK_Left                          0xff51  /* Move left, left arrow */
#define XK_Up                            0xff52  /* Move up, up arrow */
#define XK_Right                         0xff53  /* Move right, right arrow */
#define XK_Down                          0xff54  /* Move down, down arrow */

//https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h for keycodes

int     on_key_press(int keycode, t_game *game)
{
	t_player *player;

	player = game->player_s;
	clear_player(game);
	if (keycode == XK_Escape)
		return (window_destroy(game));
	if (keycode == 0x77 || keycode == XK_W) // 'w' key
		player->pos_y -= 1;
	else if (keycode == 0x73 || keycode == XK_S) // 's' key
		player->pos_y += 1;
	else if (keycode == 0x61 || keycode == XK_A) // 'a' key
		player->pos_x -= 1;
	else if (keycode == 0x64 || keycode == XK_D) // 'd' key
		player->pos_x += 1;
	else if (keycode == 0xff51 || keycode == XK_Left) // 'left arrow' key
		player->angle -= ROTATE_SPEED;
	else if (keycode ==  0xff53 || keycode == XK_Right) // 'right arrow' key
		player->angle += ROTATE_SPEED;
	printf("x: %f, y: %f\n \nAngle: %f degrees\n(from looking right)", player->pos_x, player->pos_y, player->angle);
	return (0);
}

int     on_key_release(int keycode, t_game *game)
{
	t_player *player;

	player = game->player_s;
	mlx_clear_window(game->mlx_s->mlx_p, game->mlx_s->win);
	if (keycode == 0x77 || keycode == XK_W) // 'w' key
		player->pos_y -= 0;
	else if (keycode == 0x73 || keycode == XK_S) // 's' key
		player->pos_y += 0;
	else if (keycode == 0x61 || keycode == XK_A) // 'a' key
		player->pos_x -= 0;
	else if (keycode == 0x64 || keycode == XK_D) // 'd' key
		player->pos_x += 0;
	return (0);
}
