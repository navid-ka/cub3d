/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:14:03 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/28 18:43:23 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	angle_init(t_player *player, t_map *map)
{
	player->dg_angle = map->orientation;
	player->angle = map->orientation * PI / 180;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
}

//	Initialize the cub struct and parse the map
void	fd_parser(t_game *game, char **argv)
{
	game->cub_s = malloc(sizeof(t_cub));
	if (!game->cub_s)
		(printf("Error Malloc\n"), exit(0));
	cub_init(game->cub_s, argv);
	fd_check_extension(game->cub_s);
	fd_check_integrity(game->cub_s, game->map_s);
	map_parser(game, game->cub_s, game->map_s);
	game_init(game);
	map_init(game->map_s);
	player_init(game->player_s);
	angle_init(game->player_s, game->map_s);
	camera_init(game->camera_s, game->player_s);
}
