/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:01:07 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/11 15:00:48 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

unsigned int f_randi(uint32_t idx)
{
	idx = (idx << 13) ^ idx;
	return ((idx * (idx * idx * 15731 + 789221) + 1376312589) & 0x7fffffff);
}

unsigned int f_rand(void) 
{
    return rand() % 100;    
}


void level_enemy_up(t_game *g) 
{
    g->enemy->lvl++;
    g->enemy->dmg += 0.50;
    g->enemy->armor += 0.15;
    printf("Enemy lvl: %f\n", g->enemy->lvl);
}

void hit_enemy(t_game *g) 
{
    g->enemy->hp -= (g->player_s->dmg - g->enemy->armor);
    printf("Enemy hp: %f\n", g->enemy->hp);
}

void handle_battle_click(t_game *g) 
{
    if(g->sword_state == 1)
        hit_enemy(g);
}

int check_hp_players(t_game *g) 
{
    if(g->enemy->hp <= 0) {
        level_enemy_up(g);
        g->state = screen_manager(g, GAME);
        return (GAME);
    }
    if(g->player_s->hp <= 0)
    {
        printf("You died\n");
        g->combat_started_at = 0;
        g->state = screen_manager(g, END);
        return (END);
    }
    return (g->state);
}

void recieve_damage_afk(t_game *game) 
{
    game->player_s->hp -= 1;
    printf("Recibimos daño por no matarlo antes de tiempo\n");
    printf("Vida actual %d\n", game->player_s->hp);
}

void check_combat_status(t_game *g)
{
    int status_end;
    status_end = g->state;
    status_end = check_hp_players(g);
    if(status_end == GAME) {
        g->state = screen_manager(g, GAME);
    }
    else if(status_end == END) {
        g->player_s->hp = HP_PLAYER;
        g->state = screen_manager(g, END);
    }

    if(g->updated_at - g->combat_started_at > TIMETOGETHIT && status_end != END) {
        recieve_damage_afk(g);
        g->combat_started_at = g->updated_at;
    }
}

int combat(t_game *g)
{
    g->combat_started_at = timestamp_in_ms(g);
    g->player_s->dmg = 1;
    g->enemy->hp = ceil(HP_ENEMY_BASE + (g->enemy->lvl * 1.15));
    g->steps = 0;
    printf("Enemy hp: %f Enemy lvl: %f\n", g->enemy->hp, g->enemy->lvl);
    printf("Entered combat\n");
    return (COMBAT);
}

/// 
void combat_manager(t_game *g) 
{
    
    mlx_string_put(g->mlx_s->mlx_p, g->mlx_s->win, 
        50,
        (g->mlx_s->screen_width) / 2, 
        0x00FFFFFF, ft_itoa(g->enemy->hp));
    check_combat_status(g);
}