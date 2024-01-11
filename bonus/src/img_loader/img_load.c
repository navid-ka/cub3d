/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:51:06 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/11 21:18:00 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void sl_image_init(t_mlx *g)
{
    g->img = malloc(sizeof(t_img) * (5 + 1));
    if (!g->img)
    {
        printf("Error\n[errno: %d] Malloc failed\n", errno);
        exit(0);
    }
    g->img[0] = *load_img(g, "textures/map/wall.xpm", 32, 32);
    g->img[0] = *resize_image(g, &g->img[0], 8, 8);
	printf("g->img[0].img = %p\n", g->img[0].img);
    g->img[1] = *load_img(g, "textures/map/path.xpm", 32, 32);
	printf("g->img[1].img = %p\n", g->img[1].img);
    g->img[2] = *load_img(g, "textures/map/clear.xpm", 32, 32);
	printf("g->img[2].img = %p\n", g->img[2].img);
    g->img[3] = *load_img(g, "textures/map/start.xpm", 1280, 720);
	printf("g->img[3].img = %p\n", g->img[3].img);
    g->img[4] = *load_img(g, "textures/player/portrait.xpm", 128, 128);
	printf("g->img[4].img = %p\n", g->img[4].img);
}
