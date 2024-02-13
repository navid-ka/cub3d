/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat_draws.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:14:11 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/13 12:26:48 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	paint_mid_wall(t_game *g)
{
	int		i;
	int		j;
	t_img	img;
	int		spr_y;

	img = create_new_img(g->mlx_s, S_WIDTH, S_HEIGHT);
	i = -1;
	while (++i < S_WIDTH)
	{
		j = S_HEIGHT / 2 - g->mlx_s->wall[4].height / 2;
		while (j < S_HEIGHT / 2 + g->mlx_s->wall[4].height / 2)
		{
			if (j >= 0 && j < S_HEIGHT)
			{
				spr_y = (j - (S_HEIGHT / 2 - g->mlx_s->wall[0].height / 2)) * \
					g->mlx_s->wall[0].height / g->mlx_s->wall[0].height;
				img_pix_put(&img, i, j, get_pixel_img(&g->mlx_s->wall[3],
						i % g->mlx_s->wall[0].width, spr_y));
			}
			j++;
		}
	}
	put_img_to_img(g->mlx_s->buffer, &img, 0, 0);
	mlx_destroy_image(g->mlx_s->mlx_p, img.img);
}

void	paint_enemy_sprite_white(t_game *g)
{
	put_img_to_img(g->mlx_s->buffer, &g->mlx_s->enemy_hit[g->random],
		(g->mlx_s->screen_width - g->mlx_s->enemy_hit[g->random].width) / 2,
		(g->mlx_s->screen_height - g->mlx_s->enemy_hit[g->random].height) / 2);
	mlx_put_image_to_window(g->mlx_s->mlx_p, g->mlx_s->win,
		g->mlx_s->buffer->img, 0, 0);
}

void	combat_stats_ui(t_game *g)
{
	char	*hit_in;
	char	*dps;

	dps = ft_itoa(g->total_dmg);
	hit_in = ft_itoa((TIMETOGETHIT - \
			(g->updated_at - g->combat_started_at) - 1) / 1000);
	draw_str_to_font(g->mlx_s, "Getting hit in",
		(g->mlx_s->screen_width - (g->mlx_s->enemy->width - \
		(g->mlx_s->enemy->width / 2))) / 2 + 150, 250);
	draw_str_to_font(g->mlx_s, hit_in,
		(g->mlx_s->screen_width - (g->mlx_s->enemy->width - \
		(g->mlx_s->enemy->width / 2))) / 2 + 150, 300);
	draw_str_to_font(g->mlx_s, "DPS METER",
		(g->mlx_s->screen_width - (g->mlx_s->enemy->width - \
		(g->mlx_s->enemy->width / 2))) / 2 - 150, 250);
	draw_str_to_font(g->mlx_s, dps,
		(g->mlx_s->screen_width - (g->mlx_s->enemy->width - \
		(g->mlx_s->enemy->width / 2))) / 2 - 150, 300);
	free_null(&hit_in);
	free_null(&dps);
}
