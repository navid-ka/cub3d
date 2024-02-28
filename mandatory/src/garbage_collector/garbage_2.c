/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:50:45 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/28 18:52:15 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	free(cub->tmp);
	free(cub);
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

void	free_images(t_mlx *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free_img(g, &(g->img[i]));
		i++;
	}
}
