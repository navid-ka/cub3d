/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:08:42 by bifrost           #+#    #+#             */
/*   Updated: 2024/03/13 12:45:13 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_ceil(t_game *game, t_img *img, t_line *line, int *i)
{
	while (*i < (S_HEIGHT / 2 - line->line_height / 2))
		img_pix_put(img, line->x_start, (*i)++, colors(&game->cub_s->ceiling));
}

void	draw_floor(t_game *game, t_img *img, t_line *line, int *i)
{
	while (*i < S_HEIGHT)
		img_pix_put(img, line->x_start, (*i)++, colors(&game->cub_s->floor));
}

void	calc_line_props(t_game *game, t_line *line, t_img *img, t_img *src_img)
{
	line->text_x = (int)(game->camera_s->wall_x * (double)(src_img->width));
	if (game->camera_s->side == 0 && game->camera_s->ray_dir_x > 0)
		line->text_x = src_img->width - line->text_x - 1;
	if (game->camera_s->side == 1 && game->camera_s->ray_dir_y < 0)
		line->text_x = src_img->width - line->text_x - 1;
	line->step = 1.0 * src_img->height / line->line_height;
	line->text_pos = (line->draw_start - img->height / 2 + \
		(line->line_height) / 2) * line->step;
}

void	draw_line(t_game *game, t_line *line, t_img *img, t_img *src_img)
{
	int	i;

	calc_line_props(game, line, img, src_img);
	line->brightness = apply_fog(game);
	i = 0;
	draw_ceil(game, img, line, &i);
	while (i < S_HEIGHT && i < (S_HEIGHT / 2 + line->line_height / 2))
	{
		line->text_y = (int)line->text_pos & (src_img->height - 1);
		line->text_pos += line->step;
		if (line->text_y <= 62)
		{
			line->offset = line->w;
			if (line->offset >= 0 && line->offset < img->width)
			{
				img_pix_put(img, line->offset, i,
					get_pixel_color(src_img, line->text_x, line->text_y,
						line->brightness));
			}
		}
		i++;
	}
	draw_floor(game, img, line, &i);
}

void	draw(t_game *g, t_camera *cub, t_img *image, t_line *line)
{
	if (cub->type == '1')
		draw_line(g, line, image, &g->mlx_s->wall[0]);
	else if (cub->type == '2')
		draw_line(g, line, image, &g->mlx_s->wall[1]);
	else if (cub->type == '3')
		draw_line(g, line, image, &g->mlx_s->wall[2]);
	else if (cub->type == '4')
		draw_line(g, line, image, &g->mlx_s->wall[3]);
	else if (cub->type == 'D')
	{
		draw_line(g, line, image, &g->mlx_s->door[g->door_frame_index]);
		door_handler(g);
	}
}
