/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_linux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:51:39 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/02/13 01:08:46 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <X11/keysym.h>
//https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h for keycodes

void look_with_mouse(t_game *game)
{
    int x;
    int y;
    double angle;
    double sensitivity = 0.5; // Adjust this value to your liking

    mlx_mouse_get_pos(game->mlx_s->mlx_p, game->mlx_s->win, &x, &y);
    mlx_mouse_hide(game->mlx_s->mlx_p, game->mlx_s->win);
    // Move the mouse back to the center of the screen
    mlx_mouse_move(game->mlx_s->mlx_p, game->mlx_s->win, game->mlx_s->screen_width / 2, game->mlx_s->screen_height / 2);

    // Calculate the angle based on the mouse movement from the center of the screen
    angle = -2 * PI * (x - game->mlx_s->screen_width / 2) / S_WIDTH * sensitivity;

    game->player_s->angle += angle;
    game->player_s->dir_x = cos(game->player_s->angle);
    game->player_s->dir_y = sin(game->player_s->angle);
    game->camera_s->plane_x = game->player_s->dir_y * game->camera_s->plane_multiplier;
    game->camera_s->plane_y = -game->player_s->dir_x * game->camera_s->plane_multiplier;
}

int on_mouse_click(int button, int x, int y, t_game *game)
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
int move_player(t_game *game, double dx, double dy)
{
    t_player *player = game->player_s;
    double new_pos_x = player->pos_x + dx;
    double new_pos_y = player->pos_y + dy;

    // Introduce un pequeño margen alrededor de los bloques
    double margin = 0.07;

    // Crea una cadena con todos los tipos de bloques que quieres evitar
    char *blocks_to_avoid = "1234D";

	if (game->door_state == OPEN)

		blocks_to_avoid = "1234";

    // Comprueba el movimiento en la dirección x
    if (new_pos_x + dx - margin >= 0 && new_pos_x + dx + margin < game->map_s->width &&
        !ft_strchr(blocks_to_avoid, game->map_s->map[(int)player->pos_y][(int)(new_pos_x + dx - margin)]) &&
        !ft_strchr(blocks_to_avoid, game->map_s->map[(int)player->pos_y][(int)(new_pos_x + dx + margin)]))
    {
        player->pos_x = new_pos_x;
    }

    // Comprueba el movimiento en la dirección y
    if (new_pos_y + dy - margin >= 0 && new_pos_y + dy + margin < game->map_s->height &&
        !ft_strchr(blocks_to_avoid, game->map_s->map[(int)(new_pos_y + dy - margin)][(int)player->pos_x]) &&
        !ft_strchr(blocks_to_avoid, game->map_s->map[(int)(new_pos_y + dy + margin)][(int)player->pos_x]))
    {
        player->pos_y = new_pos_y;
    }

    return 0;
}



int check_door_collision(t_game *game)
{
    t_player *player;
	static double distance = 2.0f;
	int x;
	int y;

	player = game->player_s;
    player->door_collision = false;
    x = (int)(player->pos_x + player->dir_x * distance);
    y = (int)(player->pos_y + player->dir_y * distance);
    if (game->map_s->map[y][x] == 'D')
    {
        player->door_collision = true;
    }
    return (0);
}

double	move_rot(t_camera *cam, t_player *p, char **map, int dir)
{
	double increment;
	
	(void)map;
	if (dir == XK_Right) // moving left
		increment = -ROTATE_SPEED;
	else// if (dir == 0x64) // moving right
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

int     on_key_press(int keycode, t_game *game)
{
	static int flag = 0;
	t_camera *camera = game->camera_s;
    t_player *player = game->player_s;
    player->speed = 0.25;

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
		player->dx = 0, player->dy = 0;
		if (keycode == 0x77 || keycode == XK_W) // 'w' key
		{
			player->dx += player->dir_x * player->speed;
			player->dy += player->dir_y *  player->speed;
			game->steps++;
		}
		if (keycode == 0x73 || keycode == XK_S) // 's' key
		{
			player->dx -= player->dir_x * player->speed;
			player->dy -= player->dir_y * player->speed;
			game->steps++;
		}
		if (keycode == 0x61 || keycode == XK_A) // 'a' key
		{
			player->dx -= player->dir_y * player->speed;
			player->dy += player->dir_x * player->speed;
			game->steps++;
		}
		if (keycode == 0x64 || keycode == XK_D) // 'd' key
		{
			player->dx += player->dir_y * player->speed;
			player->dy -= player->dir_x * player->speed;
			game->steps++;
		}
		if (keycode == XK_space)
		{
			//dash forward
			player->dx += player->dir_x * 2;
			player->dy += player->dir_y * 2;

		}
		check_door_collision(game);
		if (player->door_collision == true)
		{
			if (player->door_collision == true)
			{
				if (keycode == XK_e)
				{
					if (game->door_state == CLOSE)
					{
						game->door_state = OPEN;
					}
					else if (game->door_state == OPEN)
					{
						game->door_state = CLOSE;
					}
					printf("door state: %d\n", game->door_state);
				}
			}
		}
		if (player->pos_x != 0 || player->pos_y != 0)
			move_player(game, player->dx, player->dy);

		//player->angle = look_with_mouse(game);

		if (keycode == XK_Right || keycode == XK_Left) // 'left arrow' key
        	player->angle = move_rot(camera, player, game->map_s->map, keycode);

		if (game->steps % 300 == 0)
			game->steps = 0;
		printf("steps: %d\n", game->steps);
	}
	if (keycode == XK_Tab)
	{
		printf("Game state\n %d\n", PAUSE);
		if (flag == 0)
		{
			game->state = screen_manager(game, PAUSE);
			mlx_string_put(game->mlx_s->mlx_p, game->mlx_s->win, (game->mlx_s->screen_width - sizeof "PAUSE") / 2, 
				(game->mlx_s->screen_height - sizeof "PAUSE") / 2, 0x00FFFFFF, "PAUSE");
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
