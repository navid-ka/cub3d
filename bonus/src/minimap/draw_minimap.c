/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:15:10 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/02 19:33:54 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void draw_square(t_mlx *g, int x, int y, int width, int height)
{
    int i = 0;
    int j;

    while (i < width)
    {
        j = 0;
        while (j < height)
        {
            if (i == 0 || j == 0 || i == width - 1 || j == height - 1)
            {
                mlx_pixel_put(g->mlx_p, g->win, x + i, y + j, 0xFFFFFF); // 0xFFFFFF es blanco
            }
            /*else
            {
                mlx_pixel_put(g->mlx_p, g->win, x + i, y + j, 0x000000); // 0x000000 es negro
            }*/
            j++;
        }
        i++;
    }
}

void	draw_minimap(t_game *g)
{
    int		i;
    int		j;
    t_img	*img;
    t_img	*resized_img;
    int x;
    int y;

    i = 0;
    while (i < g->map_s->height)
    {
        j = 0;
        while (j < g->map_s->width)
        {
            if (g->map_s->map[i][j] == '1')
            {
                img = &g->mlx_s->img[0];
                resized_img = resize_image(g->mlx_s, img, 8, 8);
                x = 1250 - (g->map_s->width - j) * 8;
                y = 10 + i * 8;
                mlx_put_image_to_window(g->mlx_s->mlx_p, g->mlx_s->win, resized_img->img, x, y);
                mlx_destroy_image(g->mlx_s->mlx_p, resized_img->img);
                free(resized_img);
            }
            j++;
        }
        i++;
    }
	draw_square(g->mlx_s, 1250 - (g->map_s->width) * 8, 10, g->map_s->width * 8, g->map_s->height * 8);
}

void clear_minimap(t_game *g, int color)
{
    int i;
    int j;

    i = 0;
    while (i < g->map_s->height)
    {
        j = 0;
        while (j < g->map_s->width)
        {
            mlx_pixel_put(g->mlx_s->mlx_p, g->mlx_s->win, j * 8, i * 8, color);
            j++;
        }
        i++;
    }
}