/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:19:26 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/20 19:11:27 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int window_destroy(t_game *game)
{
	garbage_collector(game);
	exit(0);
}

int check_input(t_game *game)
{
	mlx_hook(game->mlx_s->pov, 2, 0, &on_key_press, game);
	mlx_hook(game->mlx_s->pov, 17, 1L<<0, &window_destroy, game);
	return (0);
}

int    game_start(t_game *game)
{
	raycast(game);
	mlx_put_image_to_window(game->mlx_s->mlx_p, game->mlx_s->pov, 
					game->mlx_s->buffer->img, 0, 0);
	return (0);
}

void    mlx_window(t_game *game)
{
	t_mlx   *window;
	int 	fact;

	fact = 80;
	window = game->mlx_s;
	window->mlx_p = mlx_init();
	window->pov = mlx_new_window(window->mlx_p, fact*16, fact*9, "Cub3d");
	window->buffer = create_buffer(window, fact*16, fact*9);
	mlx_clear_window(window->mlx_p, window->pov);
	sl_image_init(game);
	check_input(game);
	mlx_loop_hook(window->mlx_p, &game_start, game);
	mlx_loop(window->mlx_p);
}
