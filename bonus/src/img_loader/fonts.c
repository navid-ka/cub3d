/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:11:38 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/11 23:33:23 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void load_fonts(t_mlx *g)
{
    int i = 33;
    char filename[50];
    
    g->fonts = malloc(sizeof(t_img) * (94 + 1));
    if (!g->fonts)
    {
        printf("Error\n[errno: %d] Malloc failed\n", errno);
        exit(0);
    }
    while (i <= 126)
    {
        sprintf(filename, "textures/font/%d.xpm", i);
        g->fonts[i] = *load_img(g, filename, 25, 25);
        i++;
    }
}

void draw_str_to_font(t_mlx *g, char *str, int x, int y)
{
    const char *is_printable = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    int i = 0;
    int char_width = 25;

    while (str[i] != '\0')
    {
        if (ft_strchr(is_printable, str[i]) != NULL)
        {
            put_img_to_img(g->buffer, &g->fonts[(int)str[i]], x, y);
            x += char_width;
        }
        i++;
    }
}
