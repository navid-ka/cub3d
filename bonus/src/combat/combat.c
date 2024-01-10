/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:01:07 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/11 00:11:16 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

unsigned int f_randi(uint32_t idx)
{
	idx = (idx << 13) ^ idx;
	return ((idx * (idx * idx * 15731 + 789221) + 1376312589) & 0x7fffffff);
}

int in_combat(t_game *g)
{
    if (g->state == COMBAT)
    {
        if (g->enemy->hp > 0 && g->player_s->hp > 0)
        {
            if (g->sword_state == 1)
            {
                g->enemy->hp -= 10;
                printf("enemy hp: %d\n", g->enemy->hp);
            }
        }
        if (g->enemy->hp <= 0)
        {
            g->enemy->lvl++;
            printf("enemy lvl: %d\n", g->enemy->lvl);
            g->state = screen_manager(g, GAME);
            return (GAME);
        }
        if (g->player_s->hp <= 0)
        {
            g->state = screen_manager(g, END);
            return (END);
        }
    }
    return (GAME);
}

int combat(t_game *g)
{
    g->player_s->hp = 100;
    g->enemy->hp = 100;
    g->steps = 0;
    in_combat(g);
    printf("entered combat\n");
    return (COMBAT);
}