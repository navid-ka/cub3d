/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:11:38 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/27 22:24:30 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void load_fonts(t_mlx *g)
{
    t_img *tmp;
    int i = 33;
    char filename[50];
    
    g->fonts = malloc(sizeof(t_img) * (133 + 1));
    if (!g->fonts)
    {
        printf("Error\n[errno: %d] Malloc failed\n", errno);
        exit(0);
    }
    while (i <= 126)
    {
        sprintf(filename, "textures/font/%d.xpm", i);
        tmp = load_img(g, filename, 25, 25);
        g->fonts[i] = *tmp;
        free(tmp);
        tmp = NULL;
        i++;
    }
}

void draw_str_to_font(t_mlx *g, char *str, int x, int y)
{
    const char *is_printable = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLM\
    NOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    int i = 0;
    int padding = 8;

    while (str[i] != '\0')
    {
        if (ft_strchr(is_printable, ' ') != NULL)
            x += padding;
        if (ft_strchr(is_printable, str[i]) != NULL)
        {
            put_img_to_img(g->buffer, &g->fonts[(int)str[i]], x, y);
            x += padding;
        }
        i++;
    }
}
