/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/26 12:14:05 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	fd_texture_checker(char *line)
{
	int	fd;

	fd = open(line, O_RDONLY);
	printf("line: [%s] fd: [%d]\n", line, fd);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	orientation_checker(t_cub *cub, char *line, int *flag)
{
	if (line && ft_strnstr(line, "NO", 3))
	{
		cub->no = fd_setter(line);
		if (fd_texture_checker(cub->no))
			flag += 1;
	}
	if (line && ft_strnstr(line, "SO", 3))
	{
		cub->so = fd_setter(line);
		if (fd_texture_checker(cub->so))
			flag += 1;
	}
	if (line && ft_strnstr(line, "WE", 3))
	{
		cub->we = fd_setter(line);
		if (fd_texture_checker(cub->we))
			flag += 1;
	}
	if (line && ft_strnstr(line, "EA", 3))
	{
		cub->ea = fd_setter(line);
		if (fd_texture_checker(cub->ea))
			flag += 1;
	}
	return (*flag);
}