/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_linux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:51:39 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/12/28 18:33:47 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <X11/keysym.h>
//https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h for keycodes

int     on_key_press(int keycode, t_game *game)
{
	t_player *player;

	player = game->player_s;
	clear_player(game);
	if (game->state == TITLE && keycode == XK_Return)
	{
		printf("Game state\n %d\n", GAME);
		mlx_clear_window(game->mlx_s->mlx_p, game->mlx_s->win);
		game->state = screen_manager(game, GAME);
	}
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
