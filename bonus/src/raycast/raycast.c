/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:33:34 by plinscho          #+#    #+#             */
/*   Updated: 2024/03/13 12:43:18 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	raycast(t_game *game)
{
	t_line	line;
	int		i;
	t_img	img;

	i = 0;
	line.w = 0;
	img = create_new_img(game->mlx_s, 1280, 720);
	while (i < S_WIDTH)
	{
		init_ray(game->player_s, game->camera_s, i);
		init_step(game->player_s, game->camera_s);
		init_dda(&line, game->player_s, game->camera_s, game->map_s->map);
		init_line(&line, game->camera_s, i);
		draw(game, game->camera_s, &img, &line);
		i++;
		line.w = i;
	}
	put_img_to_img(game->mlx_s->buffer, &img, 0, 0);
	mlx_destroy_image(game->mlx_s->mlx_p, img.img);
}
