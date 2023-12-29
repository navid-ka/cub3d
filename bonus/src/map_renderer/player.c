/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:19:23 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/11 12:41:27 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#define MOVE_SPEED 4
#define ROTATION_SPEED 5

int     key_press(int keycode, t_game *game)
{
    t_player *player;
    static  double    counter = 1;

    player = game->player_s;
    if (keycode == 13) // 'w' key
    {
        //player->pos_x += cos(player->fov) * MOVE_SPEED;
        printf("counter: %f\n", counter);
        mlx_clear_window(game->mlx_s->mlx_p, game->mlx_s->win);
        player->pos_y -= MOVE_SPEED * (counter * 0.06);
        counter++;
        draw_player(game);
    }
    else if (keycode == 1) // 's' key
    {
        if (counter > 1)
            counter--;
 //       player->pos_x -= cos(player->fov) * MOVE_SPEED;
        mlx_clear_window(game->mlx_s->mlx_p, game->mlx_s->win);
        player->pos_y += MOVE_SPEED;
        draw_player(game);
    }
    else if (keycode == 0) // 'a' key
    {
        mlx_clear_window(game->mlx_s->mlx_p, game->mlx_s->win);
        player->pos_x -= MOVE_SPEED;
        draw_player(game);
//        player->pos_y += cos(player->fov) * MOVE_SPEED;
    }
    else if (keycode == 2) // 'd' key
    {
        mlx_clear_window(game->mlx_s->mlx_p, game->mlx_s->win);
        player->pos_x += MOVE_SPEED;
        draw_player(game);
//      player->pos_y -= cos(player->fov) * MOVE_SPEED;
    }
    return (0);
}

// LA MIERDA AQUI ABAJO

/*
void player_init(t_player* player, float a, float b, float angle) 
{
	player->pos_x = a;
	player->pos_y = b;
	player->fov = angle;
}

// Podemos utilizar la variable forward con las keys W e S pos_y la variable side con las keys A pos_y D
void update_position(t_player* player, float forward, float side) 
{
	float move_step = MOVE_SPEED;
	float new_x = player->pos_x + cos(player->fov) * forward * move_step + cos(player->fov + PI / 2) * side * move_step;
	float new_y = player->pos_y + sin(player->fov) * forward * move_step + sin(player->fov + PI / 2) * side * move_step;
	player->pos_x = new_x;
	player->pos_y = new_y;
}
*/

/*
int     mouse_move(int pos_x, int pos_y, t_player *player)
{
    (void)pos_y;
    static int last_x = 0;

    // Calculate the difference between the current and last mouse position
    int dx = pos_x - last_x;

    // Rotate the player based on the mouse movement
    player->fov += dx * ROTATION_SPEED;

    // Store the current mouse position for the next frame
    last_x = pos_x;

    return (0);
}

// Other functions related to the player struct can be implemented here
*/

/*
	PASO 1. JUGADOR INMOVIL
	PASO 2. EVENTO KEY PRESIONADA
		PASO 2.1	SABER QUE TECLA SE PRESIONA
		PASO 2.2	ACTUALIZAR POSICION DEL JUGADOR
	PASO 3. JUGADOR SE MUEVE
*/
