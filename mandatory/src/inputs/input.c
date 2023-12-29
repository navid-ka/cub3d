/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:51:39 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/12/29 21:17:16 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int     on_key_press(int keycode, t_game *game)
{
	t_player *player;

	player = game->player_s;
	clear_player(game);
	if (keycode == ESC)
		return (window_destroy(game));
	if (keycode == W) // 'w' key
		player->pos_y -= 1;
	else if (keycode == S) // 's' key
		player->pos_y += 1;
	else if (keycode == A) // 'a' key
		player->pos_x -= 1;
	else if (keycode == D) // 'd' key
		player->pos_x += 1;
	return (0);
}

int     on_key_release(int keycode, t_game *game)
{
	t_player *player;

	player = game->player_s;
	//mlx_clear_window(game->mlx_s->mlx_p, game->mlx_s->win);
	if (keycode == W) // 'w' key
		player->pos_y -= 0;
	else if (keycode == S) // 's' key
		player->pos_y += 0;
	else if (keycode == A) // 'a' key
		player->pos_x -= 0;
	else if (keycode == D) // 'd' key
		player->pos_x += 0;
	return (0);
}
