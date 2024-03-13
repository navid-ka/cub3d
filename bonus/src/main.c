/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:24:47 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/03/13 10:42:59 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	var_init(t_game *game)
{
	game->frame_count = 0;
	game->text_draw_frame = 0;
	game->steps = 0;
	game->created_at = 0;
	game->updated_at = 0;
	game->total_dmg = 0;
	game->door_offset = 0;
	game->door_frame_index = 0;
	game->combat_started_at = 0;
	game->enemy->lvl = 1;
	game->enemy->hp = 0;
	game->enemy->dmg = 0.5;
	game->enemy->armor = 0;
	game->player_s->lvl = 1;
	game->player_s->exp = 0;
	game->player_s->dmg = 2;
	game->player_s->hp = HP_PLAYER;
}

void	game_init(t_game *game)
{
	game->mlx_s = malloc(sizeof(t_mlx));
	game->player_s = malloc(sizeof(t_player));
	game->enemy = malloc(sizeof(t_enemy));
	game->camera_s = malloc(sizeof(t_camera));
	if (!game->mlx_s || !game->player_s || !game->enemy || !game->camera_s)
	{
		ft_printf("Error\nMalloc error\n");
		exit(1);
	}
	var_init(game);
	player_init(game->player_s);
	load_save_file(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc > 2 || argc < 2)
		return (printf(ARGC));
	fd_parser(&game, argv + 1);
	mlx_window(&game);
	garbage_collector(&game);
	return (0);
}
