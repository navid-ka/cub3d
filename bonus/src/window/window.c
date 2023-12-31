/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:19:26 by bifrost           #+#    #+#             */
/*   Updated: 2023/12/31 01:22:36 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int window_destroy(t_game *game)
{
	mlx_destroy_window(game->mlx_s->mlx_p, game->mlx_s->win);
	garbage_collector(game);
	exit(0);
}

void draw_map(t_game *game)
{
	int i;
	int j;
	
	i = 0;
	while (game->map_s->map[i])
	{
		j = 0;
		while (game->map_s->map[i][j])
		{
			if (game->map_s->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx_s->mlx_p, game->mlx_s->win, 
					game->mlx_s->img[0].img, j * 32, i *32);
			j++;
		}
		i++;
	}
}

int check_input(t_game *game)
{
	mlx_hook(game->mlx_s->win, 2, 0, &on_key_press, game);
	mlx_hook(game->mlx_s->win, 3, 0, &on_key_release, game);
	if (game->state == GAME)
		mlx_hook(game->mlx_s->win, 4, 0x4, &on_key_press, game);
	mlx_hook(game->mlx_s->win, 17, 1L<<0, &window_destroy, game);
	return (0);
}

int    game_start(t_game *game)
{
	
	if (game->state == TITLE && game->state != GAME)
		game->state = screen_manager(game, TITLE);
	if (game->state == GAME)
	{
		//draw_map(game);
		//clear_player(game);
		//draw_player(game);
		//draw_single_sword(game);
		
		//game->sword_state = draw_sword_animation(game);
		//game->sword_state = sword_manager(game, IDLE);
		update(game);
	}
	return (GAME);
}

void    mlx_window(t_game *game)
{
	t_mlx   *window;
	int	    fact;

	fact = 80;
	game->fps = 30;
	ft_memset(&window, 0, sizeof(t_mlx));
	window = game->mlx_s;
	window_init(window);
	window->mlx_p = mlx_init();
	window->win = mlx_new_window(window->mlx_p, fact*16, fact*9, "Cub3D");
	sl_image_init(window);
	load_sword_img(window);
	check_input(game);
	mlx_loop_hook(window->mlx_p, &game_start, game);
	mlx_loop(window->mlx_p);
}
