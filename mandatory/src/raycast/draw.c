/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:06:59 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/27 19:24:28 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	colors(t_color *c)
{
	return (c->r << 16 | c->g << 8 | c->b);
}

int	set_texture(t_game *game, t_img *src_image)
{
	int	text_x;

	text_x = (int)(game->camera_s->wall_x * (double)(src_image->width));
	if (game->camera_s->side == 0 && game->camera_s->ray_dir_x > 0)
		text_x = src_image->width - text_x - 1;
	if (game->camera_s->side == 1 && game->camera_s->ray_dir_y < 0)
		text_x = src_image->width - text_x - 1;
	return (text_x);
}

void	draw_line(t_game *game, t_line *line, t_img *img, t_img *source_img)
{
	int	i;

	i = 0;
	line->text_x = set_texture(game, source_img);
	line->step = 1.0 * source_img->height / line->line_height;
	line->text_pos = (line->draw_start - img->height / 2 + \
			(line->line_height) / 2) * line->step;
	line->line_height = (int)(S_HEIGHT / game->camera_s->perp_wall_dist) - 1;
	while (i < (S_HEIGHT / 2 - line->line_height / 2))
		img_pix_put(img, line->x_start, i++, colors(&game->cub_s->ceiling));
	while (i < S_HEIGHT && i < (S_HEIGHT / 2 + line->line_height / 2))
	{
		line->text_y = (int)line->text_pos & (source_img->height - 1);
		line->text_pos += line->step;
		if (line->text_y <= 62)
			img_pix_put(img, line->x_start, i,
				get_pixel_img(source_img,
					line->text_x, line->text_y));
		i++;
	}
	while (i < S_HEIGHT)
		img_pix_put(img, line->x_start, i++, colors(&game->cub_s->floor));
}

void	draw(t_game *g, t_camera *cub, t_img *image, t_line *line)
{
	if (cub->hit_direction == NORTH)
		draw_line(g, line, image, &g->mlx_s->img[0]);
	else if (cub->hit_direction == SOUTH)
		draw_line(g, line, image, &g->mlx_s->img[1]);
	else if (cub->hit_direction == WEST)
		draw_line(g, line, image, &g->mlx_s->img[2]);
	else if (cub->hit_direction == EAST)
		draw_line(g, line, image, &g->mlx_s->img[3]);
}
