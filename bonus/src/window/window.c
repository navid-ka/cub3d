/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:19:26 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/01 15:44:38 by nkeyani-         ###   ########.fr       */
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
	mlx_mouse_hook(game->mlx_s->win, &on_mouse_click, game);
	mlx_hook(game->mlx_s->win, 2, 0, &on_key_press, game);
	mlx_hook(game->mlx_s->win, 3, 0, &on_key_release, game);
	if (game->state == GAME)
		mlx_hook(game->mlx_s->win, 4, 0x4, &on_key_press, game);
	mlx_hook(game->mlx_s->win, 17, 1L<<0, &window_destroy, game);
	return (0);
}

void clear_image(t_img *img)
{
    int x, y;

    for (y = 0; y < img->height; y++)
    {
        for (x = 0; x < img->width; x++)
        {
            put_pixel_img(img, x, y, 0);
        }
    }
}

int game_start(t_game *game)
{
	unsigned int randi = f_randi(game->steps);

    if (game->state == TITLE && game->state != GAME)
	{
        game->state = screen_manager(game, TITLE);
		mlx_put_image_to_window(game->mlx_s->mlx_p, game->mlx_s->win, game->mlx_s->buffer->img, 0, 0);
	}
    if (game->state == GAME)
    {
		clear_image(game->mlx_s->buffer);
        update(game);
		look_with_mouse(game);
		//printf("randi: %d\n", randi % 3);
		if (randi % 3 == 0 && game->steps > 60)
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

void    mlx_window(t_game *game)
{
	t_mlx   *window;
	static int	    fact = 80;

	//ft_memset(&window, 0, sizeof(t_mlx));
	//window_init(window);
	game->mlx_s->screen_width = fact * 16;
	game->mlx_s->screen_height = fact * 9;
	game->fps = 30;
	window = game->mlx_s;
	window->mlx_p = mlx_init();
	window->win = mlx_new_window(window->mlx_p, fact*16, fact*9, "Cub3D");
	window->buffer = create_buffer(window, fact*16, fact*9);
	mlx_clear_window(window->mlx_p, window->win);
	game->state = TITLE;
	game->sword_state = 0;
	sl_image_init(window);
	walls_image_init(game);
	load_sword_img(window);
	load_enemy_img(window);
	load_enemy_hit(window);
	load_fonts(window);
	check_input(game);
	mlx_loop_hook(window->mlx_p, &game_start, game);
	mlx_loop(window->mlx_p);
}
