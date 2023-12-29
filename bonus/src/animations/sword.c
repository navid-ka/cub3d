/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sword.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 23:16:11 by bifrost           #+#    #+#             */
/*   Updated: 2023/12/29 11:35:22 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char *add_file_extension(char *file, int num)
{
    char *new_file;
    char *num_str;

    new_file = malloc(ft_strlen(file) + 10);
    num_str = ft_itoa(num);
    ft_memcpy(new_file, file, ft_strlen(file) + 1); // Copia también el carácter nulo
    ft_strlcat(new_file, num_str, ft_strlen(file) + ft_strlen(num_str) + 1);
    ft_strlcat(new_file, ".xpm", ft_strlen(file) + ft_strlen(num_str) + 5);
    free(num_str);
    return new_file;
}

void    load_sword_img(t_mlx *g)
{
    int i;
    int sword_width;
    int sword_height;
    char *file;

    sword_width = 1008;
    sword_height = 874;
    file = "textures/sword/sword";
    i = 0;
    g->sword = malloc(sizeof(t_img) * 31 + 1);
    while (i < 30)
    {
        //printf("file: %s\n", add_file_extension(file, i));
        g->sword[i].img = mlx_xpm_file_to_image(g->mlx_p,
        add_file_extension(file, i), &sword_width, &sword_height);
        i++;
    }
    
}

void    draw_single_sword(t_game *game)
{
    int y = (int)game->player_s->pos_y;
    int x = (int)game->player_s->pos_x;
    mlx_put_image_to_window(game->mlx_s->mlx_p, game->mlx_s->win, game->mlx_s->sword[2].img, x, y + 90);
}