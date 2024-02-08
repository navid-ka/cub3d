/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 23:16:11 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/08 12:53:53 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <sys/time.h>
#include <stdint.h>

#include <time.h>

#define FPS 60
#define FRAME_TIME (1000 / FPS)
#define ANIMATION_TIME 4000 // Duración de la animación en milisegundos
#define DOOR_MOVE_DISTANCE (DOOR_MAX_DISTANCE / (ANIMATION_TIME / FRAME_TIME))

int door_handler(t_game *game)
{
    static clock_t last_time = 0;
    clock_t current_time = clock();
    clock_t elapsed_time = (current_time - last_time) * 1000 / CLOCKS_PER_SEC;

    if (elapsed_time >= FRAME_TIME)
    {
        if (game->door_state == OPENING)
        {
            if (game->door_offset < DOOR_MAX_DISTANCE)
            {
                game->door_offset += DOOR_MOVE_DISTANCE;
            }
            else
            {
                game->door_state = OPEN;
            }
        }
        else if (game->door_state == CLOSING)
        {
            if (game->door_offset > 0)
            {
                game->door_offset -= DOOR_MOVE_DISTANCE;
            }
            else
            {
                game->door_state = CLOSED;
            }
        }

        last_time = current_time;
    }

    return game->door_state;
}

int door_manager(t_game *g, enum e_door state)
{
    static const t_state_manager door_state_lookup[5] = {
        [CLOSED] = {door_handler},
        [OPEN] = {door_handler},
        [CLOSING] = {door_handler},
        [OPENING] = {door_handler},
    };

    g->door_state = state;
    return door_state_lookup[state].f(g);
}
