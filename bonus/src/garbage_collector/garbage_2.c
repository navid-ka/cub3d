/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/03/13 11:21:00 by bifrost          ###   ########.fr       */
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

	i = -1;
	while (++i < 5)
		free_img(g, &(g->img[i]));
	i = -1;
	while (++i < 5)
		free_img(g, &(g->wall[i]));
	i = -1;
	while (++i < 30)
		free_img(g, &(g->sword[i]));
	i = -1;
	while (++i < 2)
		free_img(g, &(g->enemy[i]));
	i = -1;
	while (++i <= 93)
		free_img(g, &(g->fonts[i]));
	i = -1;
	while (++i < 2)
		free_img(g, &(g->enemy_hit[i]));
	i = -1;
	while (++i <= 15)
		free_img(g, &(g->door[i]));
}

void	free_null(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	free_textures(t_cub *cub)
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
