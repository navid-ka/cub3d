/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/02/20 17:35:19 by plinscho         ###   ########.fr       */
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

void	garbage_collector(t_game *game)
{
	free_textures(game->cub_s);
	free_tab(game->cub_s->map);
	free_tab(game->map_s->map);
	free_images(game->mlx_s);
	free(game->mlx_s->buffer);
	mlx_destroy_image(game->mlx_s->mlx_p, game->mlx_s->buffer->img);
	mlx_destroy_window(game->mlx_s->mlx_p, game->mlx_s->pov);
	free(game->map_s);
	free(game->cub_s);
	free(game->mlx_s);
	free(game->player_s);
	free(game->camera_s);
	printf("garbage collector\n");
}
