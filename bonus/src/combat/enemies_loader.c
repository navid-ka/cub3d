/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:01:07 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/13 12:40:05 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	load_enemy_img(t_mlx *g)
{
	t_img	original0;
	t_img	original1;

	original0 = load_img(g, "textures/enemies/enemy0.xpm", 64, 64);
	original1 = load_img(g, "textures/enemies/enemy1.xpm", 32, 32);
	g->enemy[0] = resize_image(g, original0, 256, 256);
	g->enemy[1] = resize_image(g, original1, 256, 256);
	free_img(g, &original0);
	free_img(g, &original1);
}

void	load_enemy_hit(t_mlx *g)
{
	t_img	original0_hit;
	t_img	original1_hit;

	original0_hit = load_img(g, "textures/enemies/enemy0_hit.xpm", 64, 64);
	original1_hit = load_img(g, "textures/enemies/enemy1_hit.xpm", 32, 32);
	g->enemy_hit[0] = resize_image(g, original0_hit, 256, 256);
	g->enemy_hit[1] = resize_image(g, original1_hit, 256, 256);
	free_img(g, &original0_hit);
	free_img(g, &original1_hit);
}

int	enemy_type_stats(t_game *g, int type)
{
	if (type == 0)
		g->enemy->type = NORMAL;
	else if (type == 1)
		g->enemy->type = BOSS;
	if (g->enemy->type == NORMAL)
	{
		g->enemy->hp = ceil(HP_ENEMY_BASE + (g->enemy->lvl * 1.15));
		return (NORMAL);
	}
	else if (g->enemy->type == BOSS)
	{
		g->enemy->hp = ceil(HP_BOSS_BASE + (g->enemy->lvl * 1.75));
		return (BOSS);
	}
	return (-1);
}

void	move_and_draw_enemy(t_game *g, int enemy_index, int *x, int *direction)
{
	*x += *direction * MOVE_DISTANCE;
	if (abs(*x) >= MAX_DISTANCE)
		*direction *= -1;
	put_img_to_img(g->mlx_s->buffer, &g->mlx_s->enemy[enemy_index],
		(g->mlx_s->screen_width - g->mlx_s->enemy[enemy_index].width) / 2 + *x,
		(g->mlx_s->screen_height - g->mlx_s->enemy[enemy_index].height) / 2);
}

int	enemy_type_sprites(t_game *g, int type)
{
	static int	x = 0;
	static int	direction = 1;

	if (type == 0)
	{
		g->enemy->type = NORMAL;
		move_and_draw_enemy(g, 0, &x, &direction);
		return (NORMAL);
	}
	else if (type == 1)
	{
		g->enemy->type = BOSS;
		move_and_draw_enemy(g, 1, &x, &direction);
		return (BOSS);
	}
	return (-1);
}
