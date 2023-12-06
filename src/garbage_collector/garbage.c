/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/12/06 17:52:36 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_tab(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	if (args)
	{
		while (args[i] != NULL)
		{
			free(args[i]);
			i++;
		}
		free(args);
		args = NULL;
	}
}

void free_null(char **ptr)
{
    free(*ptr);
    *ptr = NULL;
}

void free_textures(t_cub *cub)
{
	if (cub->path)
        free_null(&cub->path);
    if (cub->no)
        free_null(&cub->no);
    if (cub->so)
        free_null(&cub->so);
    if (cub->ea)
        free_null(&cub->ea);
    if (cub->we)
		free_null(&cub->we);
}

void fd_error_1(t_cub *cub)
{
    free_textures(cub);
    ft_printf("Error\nTexture could not be loaded\n");
    exit(1);
}

void fd_error_2(t_cub *cub)
{
    free_textures(cub);
    if (cub->map)
        free_tab(cub->map);
    printf("Error\nMap not valid\n");
    exit(1);
}

void	fd_error(t_cub *cub, int err)
{
    if (err == -1)
        free_null(&cub->path);
    if (err == 1)
        fd_error_1(cub);
    else if (err == 2)
        fd_error_2(cub);
    exit(1);
}

void garbage_collector(t_cub *cub, t_map *map)
{
    free_textures(cub);
    free_tab(cub->map);
    free_tab(map->map);
    printf("garbage collector\n");
}
