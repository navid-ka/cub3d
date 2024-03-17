/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:50:45 by plinscho          #+#    #+#             */
/*   Updated: 2024/03/17 17:29:50 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	fd_error_1(t_cub *cub, t_map *map)
{
	free_textures(cub);
	free(cub);
	free(map);
	ft_printf("Error\nTexture could not be loaded\n");
	exit(1);
}

void	fd_error_2(t_cub *cub, t_map *map)
{
	free_textures(cub);
	if (cub->map)
		free_tab(cub->map);
	free(cub->tmp);
	free(cub);
	free(map);
	printf("Error\nMap not valid, level 2\n");
	exit(1);
}

void	fd_error_3(t_game *game, t_cub *cub, t_map *map)
{
	free_textures(cub);
	if (cub->map)
		free_tab(cub->map);
	free(cub);
	if (map->map)
		free_tab(map->map);
	free(map);
	free(game->player_s);
	free(game->mlx_s);
	free(game->camera_s);
	printf("Map not valid, level 3\n");
	exit(1);
}

void	fd_error(t_cub *cub, t_map *map, int err)
{
	if (err == -1)
		free_null(&cub->path);
	if (err == 1)
		fd_error_1(cub, map);
	else if (err == 2)
		fd_error_2(cub, map);
	free(map);
	exit(1);
}

void	free_img(t_mlx *g, t_img *img)
{
	if (img)
	{
		if (img->img)
		{
			mlx_destroy_image(g->mlx_p, img->img);
			img->img = NULL;
		}
	}
}
