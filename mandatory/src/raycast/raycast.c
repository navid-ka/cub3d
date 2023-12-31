/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:33:34 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/31 19:00:00 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// to start, we need the player position and the player direction
void    ray_init(t_game *game)
{
	double	Xo = game->player_s->pos_x * 32 + 16;
	double	Yo = game->player_s->pos_y * 32 + 16;
//	double	Xf = 2 * game->player_s->dir_x;
//	double	Yf = 2 * game->player_s->dir_y;
//	double	slope;
	game->player_s->dir_x = cos(game->player_s->angle);
	game->player_s->dir_y = sin(game->player_s->angle);
//	slope = tan(game->player_s->angle);
	for (int i = 0 ; i < RENDER_DIST ; i++)
	{
		mlx_pixel_put(game->mlx_s->mlx_p, game->mlx_s->win, (Xo), (Yo), 0x00FFFF00);
		Xo += 1 * cos(game->player_s->angle);
		Yo += 1 * sin(game->player_s->angle);
	}
	return ;
}

void    raycast(t_game *game)
{
	ray_init(game);	
	return ;
}
