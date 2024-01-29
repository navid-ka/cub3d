/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/01/29 16:30:45 by bifrost          ###   ########.fr       */
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
/*
void free_fonts(t_mlx *g) 
{
    int i = 33;

    if (g->fonts) 
	{
        while (i <= 126) 
		{
            free_img(g, &(g->fonts[i]));
            i++;
        }
        free(g->fonts);
        g->fonts = NULL;
    }
}

void free_sword(t_mlx *g) 
{
    int i = 0;

    if (g->sword) 
	{
        while (i < 30) 
		{
            free_img(g, &(g->sword[i]));
            i++;
        }
        free(g->sword);
        g->sword = NULL;
    }
}

void free_enemies(t_mlx *g)
{
    int i = 0;
    if (g->enemy)
    {
        while (i < 2) 
        {
            free_img(g, &(g->enemy[i]));
            i++;
        }
        free(g->enemy);
        g->enemy = NULL;
    }
}

void free_images(t_mlx *g)
{
    int i = 0;

    if (g->img) 
	{
        while (i < 5) 
        {
            free_img(g, &(g->img[i]));
            i++;
        }
        free(g->img);
        g->img = NULL;
    }
    i = 0;
    if (g->wall) 
	{
        while (i < 5) 
		{
            free_img(g, &(g->wall[i]));
            i++;
        }
        free(g->wall);
        g->wall = NULL;
    }
}
*/

void free_images(t_mlx *g)
{
    int i;

    for (i = 0; i < 5; i++)
    {
        free_img(g, &(g->img[i]));
    }
    for (i = 0; i < 5; i++)
    {
        printf("free img %p\n", g->wall[i].img);
        free_img(g, &(g->wall[i]));
        printf("free img %p\n", g->wall[i].img);
    }
    for (i = 0; i < 30; i++)
    {
        free_img(g, &(g->sword[i]));
    }
    for (i = 0; i < 2; i++)
    {
        printf("free img %p\n", g->enemy[i].img);
        free_img(g, &(g->enemy[i]));
        printf("free img %p\n", g->enemy[i].img);
    }
    for (i = 0; i <= 93; i++)
    {
        free_img(g, &(g->fonts[i]));
    }
    for (i = 0; i < 2; i++)
    {
        free_img(g, &(g->enemy_hit[i]));
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
    free_textures(game->cub_s);
    free_tab(game->cub_s->map);
    free_tab(game->map_s->map);
    free_images(game->mlx_s);
    mlx_destroy_image(game->mlx_s->mlx_p, game->mlx_s->buffer->img);
	free(game->mlx_s->buffer);
    free(game->enemy);
    free(game->camera_s);
    free(game->map_s);
    free(game->cub_s);
    free(game->mlx_s);
    free(game->player_s);
    printf("garbage collector\n");
}
