/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:11:38 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/13 10:40:47 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	load_fonts(t_mlx *g)
{
	int		i;
	char	filename[50];

	i = 0;
	while (i <= 93)
	{
		sprintf(filename, "textures/font/%d.xpm", i + 33);
		g->fonts[i] = load_img(g, filename, 25, 25);
		i++;
	}
}

void	draw_str_to_font(t_mlx *g, char *str, int x, int y)
{
	const char			*is_printable = "!\"#$%&'()*+,-./0123456789:;<=>\
	?@ABCDEFGHIJKLM\
	NOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ ";
	static const int	padding = 12;
	char				*char_pos;
	int					font_index;
	int					i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == ' ')
			x += padding;
		else
		{
			char_pos = ft_strchr(is_printable, str[i]);
			if (char_pos != NULL)
			{
				font_index = (int)str[i] - 33;
				put_img_to_img(g->buffer, &g->fonts[font_index], x, y);
				x += padding;
			}
		}
	}
}
