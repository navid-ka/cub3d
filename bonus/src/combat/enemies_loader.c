/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:01:07 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/11 21:22:15 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void load_enemy_img(t_mlx *g)
{
    g->enemy = malloc(sizeof(t_img) * (2 + 1));
    if (!g->enemy)
    {
        printf("Error\n[errno: %d] Malloc failed\n", errno);
        exit(0);
    }
    g->enemy[0] = *load_img(g, "textures/enemies/enemy0.xpm", 64, 64);
    g->enemy[0] = *resize_image(g, &g->enemy[0], 256, 256);
    g->enemy[1] = *load_img(g, "textures/enemies/enemy1.xpm", 32, 32);
    g->enemy[1] = *resize_image(g, &g->enemy[1], 512, 512);
}

