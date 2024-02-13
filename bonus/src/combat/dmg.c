/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dmg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:28:37 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/13 12:35:36 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_hp_players(t_game *g)
{
	if (g->enemy->hp <= 0)
	{
		level_enemy_up(g);
		level_player_up(g);
		game_save(g);
		g->state = screen_manager(g, GAME);
		return (GAME);
	}
	if (g->player_s->hp <= 0)
	{
		printf("You died\n");
		g->combat_started_at = 0;
		g->state = screen_manager(g, END);
		return (END);
	}
	return (g->state);
}

void	recieve_damage_afk(t_game *game)
{
	game->player_s->hp -= 1;
	printf("Recibimos daño por no matarlo antes de tiempo\n");
	printf("Vida actual %d\n", game->player_s->hp);
}

void	hit_enemy(t_game *g)
{
	g->enemy->hp -= (int)(g->player_s->dmg - g->enemy->armor);
	paint_enemy_sprite_white(g);
	printf("Enemy hp: %f\n", g->enemy->hp);
}

void	handle_battle_click(t_game *g)
{
	if (g->sword_state == 1)
	{
		hit_enemy(g);
		g->total_dmg += (int)(g->player_s->dmg - g->enemy->armor);
	}
}
