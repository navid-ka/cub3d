/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:24:47 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/12/10 18:04:12 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	game_init(t_game *game)
{
	
	game->cub_s = malloc(sizeof(t_cub));
	game->map_s = malloc(sizeof(t_map));
	game->mlx_s = malloc(sizeof(t_mlx));
	game->player_s = malloc(sizeof(t_player));

	if (!game->cub_s || !game->map_s || !game->mlx_s || !game->player_s)
	{
		ft_printf("Error\nMalloc error\n");
		exit(1);
	}
}

int main(int argc, char **argv)
{
	t_game		game;

	if (argc > 2 || argc < 2)
		return (printf(ARGC));

	game_init(&game);
	fd_parser(&game, argv + 1);	
	mlx_window(&game);
	garbage_collector(&game);
	return (0);
}
