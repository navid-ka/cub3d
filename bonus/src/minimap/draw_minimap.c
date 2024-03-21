/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:15:10 by bifrost           #+#    #+#             */
/*   Updated: 2024/03/21 19:46:16 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#define DIR_LEN 30

void	draw_minimap_dir(t_game *g, t_img *img, int i, int j)
{
	int		ray_dist;
	double	mod_dx;
	double	mod_dy;

	ray_dist = 0;
	mod_dx = 1;
	mod_dy = 1;
	while (ray_dist < DIR_LEN)
	{
		mod_dx = 1250 - (g->map_s->width - j) * img->width;
		mod_dx += ray_dist * -g->player_s->dir_x + 4;
		mod_dy = 10 + i * img->height;
		mod_dy += ray_dist * -g->player_s->dir_y + 4;
		put_pixel_img(g->mlx_s->buffer, (int)mod_dx, (int)mod_dy, 0xFFFFFF);
		ray_dist++;
	}
}

void	draw_minimap_player(int i, int j, t_img *img, t_game *g)
{
	int		x;
	int		y;

	if (i == (int)g->player_s->pos_y && j == (int)g->player_s->pos_x)
	{
		x = 1250 - (g->map_s->width - j) * img->width;
		y = 10 + i * img->height;
		draw_minimap_dir(g, img, i, j);
		put_img_to_img(g->mlx_s->buffer, img, x, y);
	}
}

void	draw_minimap(t_game *g)
{
	int			i;
	int			j;
	t_img		*img;
	static int	x = 0;
	static int	y = 0;

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
			draw_minimap_player(i, j, &g->mlx_s->img[5], g);
		}
	}
}

void	clear_minimap(t_game *g, int color)
{
	int	i;
	int	j;

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
