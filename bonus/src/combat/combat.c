/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:01:07 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/13 12:38:19 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	level_enemy_up(t_game *g)
{
	g->enemy->lvl++;
	g->enemy->dmg += 0.50;
	g->enemy->armor += 0.15;
	printf("Enemy lvl: %f\n", g->enemy->lvl);
}

void	level_player_up(t_game *g)
{
	g->player_s->exp += ((g->enemy->lvl / 2) * 10);
	if (g->player_s->exp > 100)
	{
		g->player_s->lvl++;
		g->player_s->exp = 0;
		g->player_s->dmg += 3 * 0.75;
	}
}

void	check_combat_status(t_game *g)
{
	int	status_end;

	status_end = g->state;
	status_end = check_hp_players(g);
	if (status_end == GAME)
		g->state = screen_manager(g, GAME);
	else if (status_end == END)
	{
		g->player_s->hp = HP_PLAYER;
		g->state = screen_manager(g, END);
	}
	combat_stats_ui(g);
	if (g->updated_at - g->combat_started_at > TIMETOGETHIT
		&& status_end != END)
	{
		recieve_damage_afk(g);
		g->combat_started_at = g->updated_at;
	}
}

int	combat(t_game *g)
{
	g->random = f_rand() % 2;
	g->combat_started_at = timestamp_in_ms(g);
	enemy_type_stats(g, g->random);
	g->steps = 0;
	g->total_dmg = 0;
	printf("Enemy hp: %f Enemy lvl: %f\n", g->enemy->hp, g->enemy->lvl);
	printf("Entered combat\n");
	return (COMBAT);
}

void	combat_manager(t_game *g)
{
	char	*str;

	str = NULL;
	str = ft_itoa(g->enemy->hp);
	draw_str_to_font(g->mlx_s, str,
		(g->mlx_s->screen_width - (g->mlx_s->enemy->width - \
		(g->mlx_s->enemy->width))) / 2, 200);
	free_null(&str);
	enemy_type_sprites(g, g->random);
	check_combat_status(g);
}
