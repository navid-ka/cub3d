/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:14:03 by bifrost           #+#    #+#             */
/*   Updated: 2023/12/06 12:38:23 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    cub_init(t_cub *init, char **argv)
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
	map->pos_x = 0;
	map->pos_y = 0;
	map->orientation = 0;
}
