/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:51:03 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/11 21:09:14 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_img *create_new_img(t_mlx *g, int width, int height)
{
    t_img *new_img;

    new_img = malloc(sizeof(t_img));
    if (!new_img)
    {
        printf("Error\n[errno: %d] Malloc failed\n", errno);
        exit(0);
    }
    new_img->img = mlx_new_image(g->mlx_p, width, height);
    new_img->addr = mlx_get_data_addr(new_img->img, &new_img->bpp, &new_img->line_len, &new_img->endian);
    new_img->width = width;
    new_img->height = height;
    return (new_img);
}

unsigned int	get_pixel_img(t_img *img, int x, int y) 
{
    return (*(unsigned int *)((img->addr
            + (y * img->line_len) + (x * img->bpp / 8))));
}

t_img	*resize_image(t_mlx *g, t_img *img, int nw, int nh)
{
    t_position	od;
    t_img		*ri;
    int			c;
    t_position	p = {0, 0};
    t_position	op;

    od.x = img->height;
    od.y = img->width;
    ri = create_new_img(g, nw, nh);
    while (p.y < nh)
    {
        p.x = 0;
        while (p.x < nw)
        {
            op.x = p.x * od.x / nw;
            op.y = p.y * od.y / nh;
            c = ((int *)img->addr)[op.y * od.x + op.x];
            img_pix_put(ri, p.x, p.y, c);
            p.x++;
        }
        p.y++;
    }
    return (ri);
}

void	put_pixel_img(t_img *img, int x, int y, int color)
{
    char	*dst;

	if (color == (int)0xFF000000)
		return ;
    if (x >= 0 && y >= 0 && x < img->width && y < img->height) {
        dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
        *(unsigned int *) dst = color;
    }
}

void	put_img_to_img(t_img *dst, t_img *src, int x, int y) 
{
    int i;
    int j;

    i = 0;
    while(i < src->width) {
        j = 0;
        while (j < src->height) {
            put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
            j++;
        }
        i++;
    }
}
