/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:51:06 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/19 22:55:53 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	sl_image_init(t_game *g)
{
    g->mlx_s->img = malloc(sizeof(t_img) * (5 + 1));
    if (!g->mlx_s->img)
    {
        printf("Error\n[errno: %d] Malloc failed\n", errno);
        exit(0);
    }
    g->mlx_s->img[0] = *load_img(g->mlx_s, g->cub_s->so, 32, 32);
    //g->mlx_s->img[0] = *resize_image(g, &g->mlx_s->img[0], 8, 8);
	printf("g->mlx_s->img[0].img = %p\n", g->mlx_s->img[0].img);
    g->mlx_s->img[1] = *load_img(g->mlx_s, "textures/map/path.xpm", 32, 32);
	printf("g->mlx_s->img[1].img = %p\n", g->mlx_s->img[1].img);
    g->mlx_s->img[2] = *load_img(g->mlx_s, "textures/map/clear.xpm", 32, 32);
	printf("g->mlx_s->img[2].img = %p\n", g->mlx_s->img[2].img);
	g->mlx_s->img[3] = *load_img(g->mlx_s, "textures/map/pareh.xpm", 32, 32);
	printf("g->mlx_s->img[3].img = %p\n", g->mlx_s->img[3].img);
	g->mlx_s->img[4] = *load_img(g->mlx_s, g->cub_s->no, 32, 32);
	printf("g->mlx_s->img[4].img = %p\n", g->mlx_s->img[4].img);
}

