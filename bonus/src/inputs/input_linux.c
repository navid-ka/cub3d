/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_linux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:51:39 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/03/15 17:06:48 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
//#include <X11/keysym.h>

void	look_with_mouse(t_game *game)
{
	static double	sens = 0.5;
	int				x;
	int				y;
	double			angle;

	mlx_mouse_get_pos(game->mlx_s->mlx_p, game->mlx_s->win, &x, &y);
	mlx_mouse_hide(game->mlx_s->mlx_p, game->mlx_s->win);
	mlx_mouse_move(game->mlx_s->mlx_p, game->mlx_s->win,
		game->mlx_s->screen_width / 2, game->mlx_s->screen_height / 2);
	angle = -2 * PI * (x - game->mlx_s->screen_width / 2) / S_WIDTH * sens;
	game->player_s->angle += angle;
	game->player_s->dir_x = cos(game->player_s->angle);
	game->player_s->dir_y = sin(game->player_s->angle);
	game->camera_s->plane_x = game->player_s->dir_y \
		* game->camera_s->plane_multiplier;
	game->camera_s->plane_y = -game->player_s->dir_x \
		* game->camera_s->plane_multiplier;
}

double	move_rot(t_camera *cam, t_player *p, char **map, int dir)
{
	double	increment;

	(void)map;
	if (dir == XK_Right)
		increment = -ROTATE_SPEED;
	else
		increment = ROTATE_SPEED;
	p->angle += increment;
	if (p->angle < 0)
		p->angle += 2 * PI;
	else if (p->angle > 2 * PI)
		p->angle -= 2 * PI;
	p->dir_x = cos(p->angle);
	p->dir_y = sin(p->angle);
	cam->plane_x = p->dir_y * cam->plane_multiplier;
	cam->plane_y = -p->dir_x * cam->plane_multiplier;
	return (p->angle);
}

void	toggle_pause(t_game *game, int keycode, int *flag)
{
	if (keycode == XK_Tab)
	{
		printf("Game state\n %d\n", PAUSE);
		if (*flag == 0)
		{
			game->state = screen_manager(game, PAUSE);
			mlx_string_put(game->mlx_s->mlx_p, game->mlx_s->win,
				(game->mlx_s->screen_width - sizeof "PAUSE") / 2,
				(game->mlx_s->screen_height - sizeof "PAUSE") / 2,
				0x00FFFFFF, "PAUSE");
			*flag = 1;
		}
		else if (*flag == 1)
		{
			game->state = screen_manager(game, GAME);
			*flag = 0;
		}
	}
}

int	on_key_press(int keycode, t_game *game)
{
	static int	flag = 0;
	t_camera	*camera;
	t_player	*player;

	player = game->player_s;
	camera = game->camera_s;
	player->speed = 0.25;
	if (keycode == XK_Escape)
		return (window_destroy(game));
	if (game->state == TITLE && keycode == XK_Return)
		game->state = screen_manager(game, GAME);
	if (game->state == GAME)
	{
		player_move(keycode, player, game);
		check_door_collision(game);
		toggle_door_state(player, keycode, game);
		if (player->pos_x != 0 || player->pos_y != 0)
			collision_checker(game, player->dx, player->dy);
		if (keycode == XK_Right || keycode == XK_Left)
			player->angle = move_rot(camera, player, game->map_s->map, keycode);
		if (game->steps % 300 == 0)
			game->steps = 0;
	}
	toggle_pause(game, keycode, &flag);
	return (0);
}

int	on_key_release(int keycode, t_game *game)
{
	t_player	*player;

	player = game->player_s;
	if (keycode == 0x77 || keycode == XK_W)
		player->pos_y -= 0;
	else if (keycode == 0x73 || keycode == XK_S)
		player->pos_y += 0;
	else if (keycode == 0x61 || keycode == XK_A)
		player->pos_x -= 0;
	else if (keycode == 0x64 || keycode == XK_D)
		player->pos_x += 0;
	return (0);
}
