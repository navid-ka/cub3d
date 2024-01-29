/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:01:07 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/29 12:06:48 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void load_enemy_img(t_mlx *g)
{
    t_img original0, original1;

    original0 = load_img(g, "textures/enemies/enemy0.xpm", 64, 64);
    original1 = load_img(g, "textures/enemies/enemy1.xpm", 32, 32);

    g->enemy[0] = resize_image(g, original0, 256, 256);
    g->enemy[1] = resize_image(g, original1, 512, 512);

    free_img(g, &original0);
    free_img(g, &original1);
}

int enemy_type_stats(t_game *g, int type)
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

int enemy_type_sprites(t_game *g, int type)
{
    if (type == 0)
        g->enemy->type = NORMAL;
    else if (type == 1)
        g->enemy->type = BOSS;
    if (g->enemy->type == NORMAL)
    {
        put_img_to_img(g->mlx_s->buffer, &g->mlx_s->enemy[0], 
            (g->mlx_s->screen_width - g->mlx_s->enemy[0].width) / 2, 
            (g->mlx_s->screen_height - g->mlx_s->enemy[0].height) / 2);
        return (NORMAL);
    }
    else if (g->enemy->type == BOSS)
    {
        put_img_to_img(g->mlx_s->buffer, &g->mlx_s->enemy[1], 
            (g->mlx_s->screen_width - g->mlx_s->enemy[1].width) / 2, 
            (g->mlx_s->screen_height - g->mlx_s->enemy[1].height) / 2);
        return (BOSS);
    }
    return (-1);
}

