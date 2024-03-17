/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:11:31 by bifrost           #+#    #+#             */
/*   Updated: 2024/03/17 16:20:12 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
//#include <X11/keysym.h>

int	on_mouse_click(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1 && game->state == COMBAT)
	{
		game->sword_state = draw_sword_animation(game);
		handle_battle_click(game);
	}
	return (0);
}

int	check_door_collision(t_game *game)
{
	t_player		*player;
	int				x;
	int				y;

	player = game->player_s;
	player->door_collision = false;
	x = (int)(player->pos_x + player->dir_x);
	y = (int)(player->pos_y + player->dir_y);
	if (game->map_s->map[y][x] == 'D')
	{
		player->door_collision = true;
	}
	return (0);
}

void	toggle_door_state(t_player *player, int keycode, t_game *game)
{
	if (player->door_collision == true)
	{
		if (keycode == E)
		{
			if (game->door_state == CLOSE)
				game->door_state = OPEN;
			else if (game->door_state == OPEN)
				game->door_state = CLOSE;
			printf("door state: %d\n", game->door_state);
		}
	}
}

int	check_collision_x(t_game *game, double dx, char *wall, double margin)
{
	t_player	*player;
	double		new_x;

	player = game->player_s;
	new_x = player->pos_x + dx;
	if (new_x + dx - margin >= 0 && new_x + dx + margin < game->map_s->width
		&& !ft_strchr(wall,
			game->map_s->map[(int)player->pos_y][(int)(new_x + dx - margin)])
		&& !ft_strchr(wall,
		game->map_s->map[(int)player->pos_y][(int)(new_x + dx + margin)]))
	{
		player->pos_x = new_x;
		return (1);
	}
	return (0);
}

int	check_collision_y(t_game *game, double dy, char *wall, double margin)
{
	t_player	*player;
	double		new_y;

	player = game->player_s;
	new_y = player->pos_y + dy;
	if (new_y + dy - margin >= 0 && new_y + dy + margin < game->map_s->height
		&& !ft_strchr(wall, \
			game->map_s->map[(int)(new_y + dy - margin)][(int)player->pos_x])
		&& !ft_strchr(wall, \
			game->map_s->map[(int)(new_y + dy + margin)][(int)player->pos_x]))
	{
		player->pos_y = new_y;
		return (1);
	}
	return (0);
}
