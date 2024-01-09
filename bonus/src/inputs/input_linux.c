/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_linux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:51:39 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/01/09 20:44:14 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <X11/keysym.h>
//https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h for keycodes

int on_mouse_click(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
    if (button == 1 && game->state == COMBAT)
        game->sword_state = draw_sword_animation(game);
    return (0);
}

int     on_key_press(int keycode, t_game *game)
{
	t_player *player;
	static int flag = 0;

	player = game->player_s;
	//clear_player(game);
	if (keycode == XK_Escape)
		return (window_destroy(game));
	if (game->state == TITLE && keycode == XK_Return)
	{
		printf("Game state\n %d\n", GAME);
		mlx_clear_window(game->mlx_s->mlx_p, game->mlx_s->win);
		game->state = screen_manager(game, GAME);
	}
	if (game->state == GAME)
	{
		printf("keycode: %d\n", keycode);
		if (keycode == 32)
			game->sword_state = draw_sword_animation(game);
		if (keycode == 0x77 || keycode == XK_W) // 'w' key
			player->pos_y -= 1;
		else if (keycode == 0x73 || keycode == XK_S) // 's' key
			player->pos_y += 1;
		else if (keycode == 0x61 || keycode == XK_A) // 'a' key
			player->pos_x -= 1;
		else if (keycode == 0x64 || keycode == XK_D) // 'd' key
			player->pos_x += 1;
		game->steps++;
		if (game->steps % 150 == 0)
			game->steps = 0;
		printf("steps: %d\n", game->steps);
	}
	if (keycode == XK_Tab)
	{
		printf("Game state\n %d\n", PAUSE);
		if (flag == 0)
		{
			game->state = screen_manager(game, PAUSE);
			//draw_minimap(game);
			flag = 1;
		}
		else if (flag == 1) 
		{
			game->state = screen_manager(game, GAME);
			flag = 0;
		}
	}

	return (0);
}

int     on_key_release(int keycode, t_game *game)
{
	t_player *player;

	player = game->player_s;
	//mlx_clear_window(game->mlx_s->mlx_p, game->mlx_s->win);
	if (keycode == 0x77 || keycode == XK_W) // 'w' key
		player->pos_y -= 0;
	else if (keycode == 0x73 || keycode == XK_S) // 's' key
		player->pos_y += 0;
	else if (keycode == 0x61 || keycode == XK_A) // 'a' key
		player->pos_x -= 0;
	else if (keycode == 0x64 || keycode == XK_D) // 'd' key
		player->pos_x += 0;
	return (0);
}
