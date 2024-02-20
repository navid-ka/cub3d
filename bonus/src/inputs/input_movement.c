/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:17:47 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/13 18:21:34 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAC
# define XK_W W
# define XK_S S
# define XK_A A
# define XK_D D
#else
# include "../../include/keysym.h"
#endif
#include "../../include/cub3d.h"

void	move_forward(t_player *player, t_game *game)
{
	player->dx += player->dir_x * player->speed;
	player->dy += player->dir_y * player->speed;
	game->steps++;
}

void	move_backward(t_player *player, t_game *game)
{
	player->dx -= player->dir_x * player->speed;
	player->dy -= player->dir_y * player->speed;
	game->steps++;
}

void	move_left(t_player *player, t_game *game)
{
	player->dx -= player->dir_y * player->speed;
	player->dy += player->dir_x * player->speed;
	game->steps++;
}

void	move_right(t_player *player, t_game *game)
{
	player->dx += player->dir_y * player->speed;
	player->dy -= player->dir_x * player->speed;
	game->steps++;
}

void	player_move(int keycode, t_player *player, t_game *game)
{
	player->dx = 0;
	player->dy = 0;
	if (keycode == 0x77 || keycode == XK_W || keycode == W)
		move_forward(player, game);
	if (keycode == 0x73 || keycode == XK_S || keycode == S)
		move_backward(player, game);
	if (keycode == 0x61 || keycode == XK_A || keycode == A)
		move_left(player, game);
	if (keycode == 0x64 || keycode == XK_D || keycode == D)
		move_right(player, game);
}
