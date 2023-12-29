/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:08:51 by bifrost           #+#    #+#             */
/*   Updated: 2023/12/29 14:42:32 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	end_menu(t_game *game)
{
	(void)game;
	return (TITLE);
}

int	title_menu(t_game *game)
{
	mlx_put_image_to_window(game->mlx_s->mlx_p, game->mlx_s->win,
		game->mlx_s->img[3].img, 0, 0);
	return (TITLE);
}

int	screen_manager(t_game *g, enum e_state state)
{
	static const t_state_manager	screen_state_lookup[3] = {
	[TITLE] = {title_menu},
	[GAME] = {game_start},
	[END] = {end_menu}
	};

	g->state = state;
	return (screen_state_lookup[state].f(g));
}
