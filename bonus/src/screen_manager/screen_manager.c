/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:08:51 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/11 00:06:39 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	end_menu(t_game *game)
{
	game->state = TITLE;
	return (TITLE);
}

int	title_menu(t_game *game)
{
    put_img_to_img(game->mlx_s->buffer, &game->mlx_s->img[3], 0, 0);
	return (TITLE);
}

int	pause_menu(t_game *game)
{
	//put_img_to_img(game->mlx_s->buffer, &game->mlx_s->img[4], 0, 0);
	(void)game;
	return (PAUSE);
}
int	screen_manager(t_game *g, enum e_state state)
{
	static const t_state_manager	screen_state_lookup[5] = {
	[TITLE] = {title_menu},
	[GAME] = {game_start},
	[COMBAT] = {combat},
	[PAUSE] = {pause_menu},
	[END] = {end_menu}
	};

	g->state = state;
	return (screen_state_lookup[state].f(g));
}
