/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_linux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:19:26 by bifrost           #+#    #+#             */
/*   Updated: 2023/12/17 12:05:49 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <X11/keysym.h>

//https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h for keycodes

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

int     on_key_press(int keycode, t_game *game)
{
	t_player *player;

	player = game->player_s;
	mlx_clear_window(game->mlx_s->mlx_p, game->mlx_s->win);
	if (keycode == XK_Escape)
		return (window_destroy(game));
	if (keycode == 0x77 || keycode == XK_W) // 'w' key
		player->pos_y -= 1;
	else if (keycode == 0x73 || keycode == XK_S) // 's' key
		player->pos_y += 1;
	else if (keycode == 0x61 || keycode == XK_A) // 'a' key
		player->pos_x -= 1;
	else if (keycode == 0x64 || keycode == XK_D) // 'd' key
		player->pos_x += 1;
	return (0);
}

int     on_key_release(int keycode, t_game *game)
{
	t_player *player;

	player = game->player_s;
	mlx_clear_window(game->mlx_s->mlx_p, game->mlx_s->win);
	if (keycode == 0x77 || keycode == XK_W) // 'w' key
		player->pos_y -= 1;
	else if (keycode == 0x73 || keycode == XK_S) // 's' key
		player->pos_y += 1;
	else if (keycode == 0x61 || keycode == XK_A) // 'a' key
		player->pos_x -= 1;
	else if (keycode == 0x64 || keycode == XK_D) // 'd' key
		player->pos_x += 1;
	return (0);
}

int check_input(t_game *game)
{
	mlx_hook(game->mlx_s->win, 2, 0, &on_key_press, game);
	mlx_hook(game->mlx_s->win, 3, 0, &on_key_release, game);
	mlx_hook(game->mlx_s->win, 17, 1L<<0, &window_destroy, game);
	return (0);
}

int    game_start(t_game *game)
{
	draw_map(game);
	draw_player(game);
	return (0);
}

void    mlx_window(t_game *game)
{
	t_mlx   *window;

	window = game->mlx_s;
	window_init(window);
	window->mlx_p = mlx_init();
	window->win = mlx_new_window(window->mlx_p, game->map_s->width * 32, game->map_s->height * 32, "Cub3D");
	sl_image_init(game->mlx_s);
	check_input(game);
	mlx_loop_hook(window->mlx_p, &game_start, game);
	mlx_loop(window->mlx_p);
}
