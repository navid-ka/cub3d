/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:15:10 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/07 13:55:25 by nkeyani-         ###   ########.fr       */
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
                img_pix_put(g->buffer, x + i, y + j, 0xFFFFFF);
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
    static int x = 0;
    static int y = 0;

    img = &g->mlx_s->img[0];
    i = -1;
    while (++i < g->map_s->height)
    {
        j = -1;
        while (++j < g->map_s->width)
        {
            if (ft_strchr(" 123", g->map_s->map[i][j]))
            {
                x = 1250 - (g->map_s->width - j) * img->width;
                y = 10 + i * img->height;
                put_img_to_img(g->mlx_s->buffer, img, x, y);
            }
            if (i == (int)g->player_s->pos_y && j == (int)g->player_s->pos_x)
            {
                x = 1250 - (g->map_s->width - j) * img->width;
                y = 10 + i * img->height;
                put_img_to_img(g->mlx_s->buffer, img, x, y);
            }
        }
    }
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
