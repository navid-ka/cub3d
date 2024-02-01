/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:11:38 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/01 10:12:20 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void load_fonts(t_mlx *g)
{
    int i = 0;
    char filename[50];
    
    while (i <= 93)
    {
        sprintf(filename, "textures/font/%d.xpm", i + 33);
        g->fonts[i] = load_img(g, filename, 25, 25);
        i++;
    }
}

void draw_str_to_font(t_mlx *g, char *str, int x, int y)
{
    const char *is_printable = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLM\
    NOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ ";
    int i = 0;
    int padding = 12;

    while (str[i] != '\0')
    {
        if (str[i] == ' ')
        {
            x += padding;
        }
        else
        {
            char *char_pos = ft_strchr(is_printable, str[i]);
            if (char_pos != NULL)
            {
                int font_index = (int)str[i] - 33;
                put_img_to_img(g->buffer, &g->fonts[font_index], x, y);
                x += padding;
            }
        }
        i++;
    }
}
