/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:51:06 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/05 21:05:50 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_img *create_buffer(t_mlx *g, int w, int h)
{
    t_img *buffer = malloc(sizeof(t_img));
    if (!buffer)
    {
        printf("Error\n[errno: %d] Malloc failed\n", errno);
        exit(0);
    }
    buffer->img = mlx_new_image(g->mlx_p, w, h);
    buffer->addr = mlx_get_data_addr(buffer->img, &buffer->bpp, \
		&buffer->line_len, &buffer->endian);
    buffer->width = w;
    buffer->height = h;
    return (buffer);
}

t_img	load_img(t_mlx *g, char *path, int w, int h)
{
    t_img img;

    img.img = mlx_xpm_file_to_image(g->mlx_p, path, &w, &h);
    img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
    img.width = w;
    img.height = h;
    return (img);
}

void	sl_image_init(t_game *g)
{
	g->mlx_s->img[0] = load_img(g->mlx_s, g->cub_s->no, 32, 32);
    g->mlx_s->img[1] = load_img(g->mlx_s, g->cub_s->so, 32, 32);
	g->mlx_s->img[2] = load_img(g->mlx_s, g->cub_s->we, 32, 32);
	g->mlx_s->img[3] = load_img(g->mlx_s, g->cub_s->ea, 32, 32);
}

