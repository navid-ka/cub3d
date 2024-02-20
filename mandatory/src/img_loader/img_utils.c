/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:51:03 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/20 17:49:22 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_img	create_new_img(t_mlx *g, int width, int height)
{
	t_img	new_img;

	new_img.img = mlx_new_image(g->mlx_p, width, height);
	new_img.addr = mlx_get_data_addr(new_img.img, &new_img.bpp,
			&new_img.line_len, &new_img.endian);
	new_img.width = width;
	new_img.height = height;
	return (new_img);
}

unsigned int	get_pixel_img(t_img *img, int x, int y)
{
	return (*(unsigned int *)((img->addr
			+ (y * img->line_len) + (x * img->bpp / 8))));
}

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return (NULL);
	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *) dst = color;
	}
}

void	put_img_to_img(t_img *dst, t_img *src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < src->width)
	{
		j = 0;
		while (j < src->height)
		{
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}
