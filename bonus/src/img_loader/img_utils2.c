/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:51:03 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/29 10:45:34 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int *)pixel = color;
}

t_img load_img(t_mlx *g, char *path, int w, int h)
{
    t_img img;

    img.img = mlx_xpm_file_to_image(g->mlx_p, path, &w, &h);
    img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
    img.width = w;
    img.height = h;
    return img;
}

t_img *create_buffer(t_mlx *g, int w, int h)
{
    t_img *buffer = malloc(sizeof(t_img));
    if (!buffer)
    {
        printf("Error\n[errno: %d] Malloc failed\n", errno);
        exit(0);
    }

    buffer->img = mlx_new_image(g->mlx_p, w, h);
    buffer->addr = mlx_get_data_addr(buffer->img, &buffer->bpp, &buffer->line_len, &buffer->endian);
    buffer->width = w;
    buffer->height = h;

    return buffer;
}