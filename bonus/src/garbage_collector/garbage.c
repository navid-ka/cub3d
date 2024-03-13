/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/03/13 11:20:14 by bifrost          ###   ########.fr       */
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

void	garbage_collector(t_game *game)
{
	free_textures(game->cub_s);
	free_tab(game->cub_s->map);
	free_tab(game->map_s->map);
	free_images(game->mlx_s);
	mlx_destroy_image(game->mlx_s->mlx_p, game->mlx_s->buffer->img);
	free(game->mlx_s->buffer);
	free(game->enemy);
	free(game->camera_s);
	free(game->map_s);
	free(game->cub_s);
	free(game->mlx_s);
	free(game->player_s);
	printf("garbage collector\n");
}
