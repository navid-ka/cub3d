/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:14:03 by bifrost           #+#    #+#             */
/*   Updated: 2023/12/06 17:50:22 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    fd_parser(t_cub *cub, t_map *map, char **argv)
{

	//int		i;

	//i = 0;
	cub_init(cub, argv);
	map_init(map);
	fd_check_extension(cub);
	fd_check_integrity(cub, map);
	map_parser(cub, map);
	/*while (map.map[i])
	{
		printf("%s\n", map.map[i]);
		i++;
	}*/
	//free_tab(cub->map);
}