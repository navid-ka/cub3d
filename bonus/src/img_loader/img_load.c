/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:51:06 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/27 21:48:31 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void sl_image_init(t_mlx *g)
{
    t_img *temp_img;
    t_img *resized_img;
    g->img = malloc(sizeof(t_img) * (5 + 1));
    if (!g->img)
    {
        printf("Error\n[errno: %d] Malloc failed\n", errno);
        exit(0);
    }
    temp_img = load_img(g, "textures/map/wall.xpm", 32, 32);
    resized_img = resize_image(g, temp_img, 8, 8);
    g->img[0] = *resized_img;
    free_img(g, temp_img);
    free(resized_img);
    temp_img = load_img(g, "textures/map/path.xpm", 32, 32);
    g->img[1] = *temp_img;
    free(temp_img);
    temp_img = load_img(g, "textures/map/clear.xpm", 32, 32);
    g->img[2] = *temp_img;
    free(temp_img);
    temp_img = load_img(g, "textures/map/start.xpm", 1280, 720);
    g->img[3] = *temp_img;
    free(temp_img);
    temp_img = load_img(g, "textures/player/portrait.xpm", 128, 128);
    g->img[4] = *temp_img;
    free(temp_img);
}

void walls_image_init(t_game *g)
{
    t_img *temp_img;
    g->mlx_s->wall = malloc(sizeof(t_img) * (5 + 1));
    if (!g->mlx_s->wall)
    {
        printf("Error\n[errno: %d] Malloc failed\n", errno);
        exit(0);
    }
    temp_img = load_img(g->mlx_s, g->cub_s->no, 32, 32);
    g->mlx_s->wall[0] = *temp_img;
    free(temp_img);
    temp_img = load_img(g->mlx_s, g->cub_s->so, 32, 32);
    g->mlx_s->wall[1] = *temp_img;
    free(temp_img);
    temp_img = load_img(g->mlx_s, g->cub_s->we, 32, 32);
    g->mlx_s->wall[2] = *temp_img;
    free(temp_img);
    temp_img = load_img(g->mlx_s, g->cub_s->ea, 32, 32);
    g->mlx_s->wall[3] = *temp_img;
    free(temp_img);
    temp_img = load_img(g->mlx_s, "textures/walls.xpm", 32, 32);
    g->mlx_s->wall[4] = *temp_img;
    free(temp_img);
}

