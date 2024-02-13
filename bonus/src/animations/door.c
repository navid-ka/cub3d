/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 23:16:11 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/13 12:34:23 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <sys/time.h>
#include <stdint.h>
#include <time.h>

void	load_door_img(t_mlx *g)
{
	static int	width = 64;
	static int	height = 64;
	int			i;
	char		*file;
	char		*file_with_extension;

	file = "textures/door/door";
	i = 0;
	while (i < 16)
	{
		file_with_extension = add_file_extension(file, i);
		g->door[i].img = mlx_xpm_file_to_image(g->mlx_p,
				file_with_extension, &width, &height);
		g->door[i].addr = mlx_get_data_addr(g->door[i].img, &g->door[i].bpp,
				&g->door[i].line_len, &g->door[i].endian);
		g->door[i].width = width;
		g->door[i].height = height;
		free(file_with_extension);
		i++;
	}
}

int	door_handler(t_game *game)
{
	if (game->door_state == OPEN)
	{
		if (game->door_frame_index < 15)
		{
			game->door_frame_index++;
		}
	}
	else if (game->door_state == CLOSE)
	{
		if (game->door_frame_index > 0)
		{
			game->door_frame_index--;
		}
	}
	return (game->door_state);
}

int	door_manager(t_game *g, enum e_door state)
{
	static const t_state_manager	door_state_lookup[2] = {
	[CLOSE] = {door_handler},
	[OPEN] = {door_handler},
	};

	g->door_state = state;
	return (door_state_lookup[state].f(g));
}
