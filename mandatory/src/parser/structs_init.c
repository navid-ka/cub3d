/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:14:03 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/23 19:01:47 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	cub_init(t_cub *init, char **argv)
{
	init->path = ft_strdup(*argv);
	init->no = NULL;
	init->so = NULL;
	init->we = NULL;
	init->ea = NULL;
	init->f_color = NULL;
	init->c_color = NULL;
	init->map = NULL;
	init->tmp = NULL;
	init->new_tmp = NULL;
	init->err = 0;
	init->count = 0;
	ft_memset(&init->floor, 0, sizeof(t_color));
	ft_memset(&init->ceiling, 0, sizeof(t_color));
}

void	map_init(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->map = NULL;
	map->orientation = 0;
}

void	camera_init(t_camera *camera, t_player *player)
{
	camera->plane_multiplier = plane_mult(FOV);
	camera->plane_x = player->dir_y;
	camera->plane_y = -player->dir_x;
	camera->wall_x = 0;
	camera->ray_dir_x = 0;
	camera->ray_dir_y = 0;
	camera->camera_x = 0;
	camera->camera_y = 0;
	camera->ddx = 0;
	camera->ddy = 0;
	camera->side_dist_x = 0;
	camera->side_dist_y = 0;
	camera->perp_wall_dist = 0;
	camera->step_x = 0;
	camera->step_y = 0;
}

void	player_init(t_player *player)
{
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->fov = FOV * (PI / 180);
	player->angle = 0;
	player->dg_angle = 0;
}

void	game_init(t_game *game)
{
	game->cub_s = malloc(sizeof(t_cub));
	game->map_s = malloc(sizeof(t_map));
	game->mlx_s = malloc(sizeof(t_mlx));
	game->player_s = malloc(sizeof(t_player));
	game->camera_s = malloc(sizeof(t_camera));
	if (!game->cub_s || !game->map_s || !game->mlx_s || !game->player_s
		|| !game->camera_s)
	{
		ft_printf("Error\nMalloc error\n");
		exit(1);
	}
}

// void	window_init(t_mlx *window)
// {
// 	window->mlx_p = NULL;
// 	window->pov = NULL;
// }
