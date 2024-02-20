/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:31:38 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/20 17:34:29 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_null(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	fd_error_1(t_cub *cub)
{
	free_textures(cub);
	ft_printf("Error\nTexture could not be loaded\n");
	exit(1);
}

void	fd_error_2(t_cub *cub)
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
