/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:05:41 by bifrost           #+#    #+#             */
/*   Updated: 2024/03/13 12:26:59 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	char_to_int(uic8 t, uic8 r, uic8 g, uic8 b)
{
	return (*(int *)(uic8 [4]){b, g, r, t});
}

int	get_pixel_color(t_img *img, int x, int y, double brightness)
{
	char	*addr;
	int		color;

	color = 0;
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	addr = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = char_to_int(addr[3] * brightness, addr[2] * brightness,
			addr[1] * brightness, addr[0] * brightness);
	return (color);
}

int	colors(t_color *c)
{
	return (c->r << 16 | c->g << 8 | c->b);
}
