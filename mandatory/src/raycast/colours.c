/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:44:51 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/23 19:11:49 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	char_to_int(uint8_t t, uint8_t r, uint8_t g, uint8_t b)
{
	return (*(int *)(uint8_t [4]){b, g, r, t});
}

int	get_pixel_color(t_img *img, int x, int y)
{
	char	*addr;
	int		color;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	addr = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = char_to_int(addr[3], addr[2], addr[1], addr[0]);
	return (color);
}

void	test_get_pixel_color(t_img *img, int x, int y)
{
	int	color;

	color = get_pixel_color(img, x, y);
	printf("Color at (%d, %d): %d\n", x, y, color);
}
