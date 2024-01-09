/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:01:07 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/09 20:59:29 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void load_enemy_img(t_mlx *g)
{
    int h = 64;
    int w = 64;

    g->enemy = malloc(sizeof(t_img) * (2 + 1));
    if (!g->enemy)
    {
        printf("Error\n[errno: %d] Malloc failed\n", errno);
        exit(0);
    }
    g->enemy[0].img = mlx_xpm_file_to_image(g->mlx_p, "textures/enemies/enemy0.xpm", &w, &h);
    g->enemy[0].addr = mlx_get_data_addr(g->enemy[0].img, &g->enemy[0].bpp, &g->enemy[0].line_len, &g->enemy[0].endian);
    g->enemy[0].width = w;
    g->enemy[0].height = h;
    g->enemy[0] = *resize_image(g, &g->enemy[0], 256, 256);
}

