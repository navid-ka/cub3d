/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/12/11 15:19:47 by nkeyani-         ###   ########.fr       */
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

void	garbage_collector(t_game *game)
{
	free_textures(game->cub_s);	//ok
	//free_tab(game->cub_s->map);	//ok
	//free_tab(game->map_s->map);	//ok
	//free(game->map_s);			//ok
	//free(game->cub_s);			//ok
	//free(game->mlx_s);			//ok
	free(game->player_s);		//ok
	printf("garbage collector\n");
}
