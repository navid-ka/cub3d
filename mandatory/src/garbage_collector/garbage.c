/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/02/05 21:15:43 by plinscho         ###   ########.fr       */
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
			free(args[i]);	//ojo
			i++;
		}
		free(args);
		args = NULL;
	}
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

void free_img(t_mlx *g, t_img *img)
{
    if (img)
    {
        if (img->img)
        {
            mlx_destroy_image(g->mlx_p, img->img); // Liberar la imagen cargada
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
	free_textures(game->cub_s);	//ok
	free_tab(game->cub_s->map);	//ok
	free_tab(game->map_s->map);	//ok
	free_images(game->mlx_s);
	free(game->mlx_s->buffer);
	mlx_destroy_image(game->mlx_s->mlx_p, game->mlx_s->buffer->img);
	mlx_destroy_window(game->mlx_s->mlx_p, game->mlx_s->pov);
	free(game->map_s);			//ok
	free(game->cub_s);			//ok
	free(game->mlx_s);			//ok
	free(game->player_s);		//ok
	free(game->camera_s);
	printf("garbage collector\n");
}
