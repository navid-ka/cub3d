/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:19:26 by bifrost           #+#    #+#             */
/*   Updated: 2024/03/15 17:54:38 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	window_destroy(t_game *game)
{
	mlx_destroy_window(game->mlx_s->mlx_p, game->mlx_s->win);
	garbage_collector(game);
	exit(0);
}

int	check_input(t_game *game)
{
	mlx_mouse_hook(game->mlx_s->win, &on_mouse_click, game);
	mlx_hook(game->mlx_s->win, 2, 0, &on_key_press, game);
	mlx_hook(game->mlx_s->win, 3, 0, &on_key_release, game);
	if (game->state == GAME)
		mlx_hook(game->mlx_s->win, 4, 0x4, &on_key_press, game);
	mlx_hook(game->mlx_s->win, 17, 1L << 0, &window_destroy, game);
	return (0);
}

void	clear_image(t_img *img)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			put_pixel_img(img, x, y, 0);
			x++;
		}
		y++;
	}
}

int	game_start(t_game *game)
{
	unsigned int	randi;

	randi = f_randi(game->steps);
	if (game->state == TITLE && game->state != GAME)
	{
		game->state = screen_manager(game, TITLE);
		mlx_put_image_to_window(game->mlx_s->mlx_p, game->mlx_s->win,
			game->mlx_s->buffer->img, 0, 0);
	}
	if (game->state == GAME)
	{
		clear_image(game->mlx_s->buffer);
		update(game);
		if (randi % 3 == 0 && game->steps > 160)
		{
			game->state = screen_manager(game, COMBAT);
		}
	}
	if (game->state == COMBAT)
	{
		clear_image(game->mlx_s->buffer);
		update(game);
	}
	return (GAME);
}

void	mlx_window(t_game *game)
{
	t_mlx		*window;
	static int	fact = 80;

	game->mlx_s->screen_width = fact * 16;
	game->mlx_s->screen_height = fact * 9;
	game->fps = 30;
	window = game->mlx_s;
	window->mlx_p = mlx_init();
	window->win = mlx_new_window(window->mlx_p, fact * 16, fact * 9, "Cub3D");
	window->buffer = create_buffer(window, fact * 16, fact * 9);
	mlx_clear_window(window->mlx_p, window->win);
	game->state = TITLE;
	game->sword_state = IDLE;
	game->door_state = CLOSE;
	sl_image_init(window);
	walls_image_init(game);
	load_sword_img(window);
	load_door_img(window);
	load_enemy_img(window);
	load_enemy_hit(window);
	load_fonts(window);
	check_input(game);
	mlx_loop_hook(window->mlx_p, &game_start, game);
	mlx_loop(window->mlx_p);
}
