/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:31:05 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/27 19:31:41 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_collision_x(t_game *game, double dx, char *wall, double margin)
{
	t_player	*player;
	double		new_x;

	player = game->player_s;
	new_x = player->pos_x + dx;
	if (new_x + dx - margin >= 0 && new_x + dx + margin < game->map_s->width
		&& !ft_strchr(wall,
			game->map_s->map[(int)player->pos_y][(int)(new_x + dx - margin)])
		&& !ft_strchr(wall,
		game->map_s->map[(int)player->pos_y][(int)(new_x + dx + margin)]))
	{
		player->pos_x = new_x;
		return (1);
	}
	return (0);
}

int	check_collision_y(t_game *game, double dy, char *wall, double margin)
{
	t_player	*player;
	double		new_y;

	player = game->player_s;
	new_y = player->pos_y + dy;
	if (new_y + dy - margin >= 0 && new_y + dy + margin < game->map_s->height
		&& !ft_strchr(wall,
			game->map_s->map[(int)(new_y + dy - margin)][(int)player->pos_x])
		&& !ft_strchr(wall,
			game->map_s->map[(int)(new_y + dy + margin)][(int)player->pos_x]))
	{
		player->pos_y = new_y;
		return (1);
	}
	return (0);
}
