/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:51:39 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/02/20 17:58:36 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	on_key_press(int keycode, t_game *game)
{
	t_player	*player;

	player = game->player_s;
	if (keycode == ESC)
		return (window_destroy(game));
	if (keycode == W)
		player->pos_y -= 1;
	else if (keycode == S)
		player->pos_y += 1;
	else if (keycode == A)
		player->pos_x -= 1;
	else if (keycode == D)
		player->pos_x += 1;
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
