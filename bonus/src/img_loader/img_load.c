/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:51:06 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/29 11:58:52 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void sl_image_init(t_mlx *g)
{
    t_img original;

    g->img[0] = load_img(g, "textures/map/wall.xpm", 32, 32);
    original = g->img[0];
    g->img[0] = resize_image(g, original, 8, 8);
    free_img(g, &original);
    g->img[1] = load_img(g, "textures/map/path.xpm", 32, 32);
    g->img[2] = load_img(g, "textures/map/clear.xpm", 32, 32);
    g->img[3] = load_img(g, "textures/map/start.xpm", 1280, 720);
    g->img[4] = load_img(g, "textures/player/portrait.xpm", 128, 128);
}

void walls_image_init(t_game *g)
{
    g->mlx_s->wall[0] = load_img(g->mlx_s, g->cub_s->no, 32, 32);
    g->mlx_s->wall[1] = load_img(g->mlx_s, g->cub_s->so, 32, 32);
    g->mlx_s->wall[2] = load_img(g->mlx_s, g->cub_s->we, 32, 32);
    g->mlx_s->wall[3] = load_img(g->mlx_s, g->cub_s->ea, 32, 32);
    g->mlx_s->wall[4] = load_img(g->mlx_s, "textures/walls.xpm", 32, 32);
}
