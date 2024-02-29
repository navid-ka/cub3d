/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/02/29 18:41:43 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	xpm_check_extension(char *str)
{
	int	len;

	len = ft_strlen(str);
	printf("str: %s\n", str);
	if (!(str[len - 1] == 'm' && str[len - 2] == 'p' && str[len - 3] == 'x'
			&& str[len - 4] == '.'))
	{
		ft_printf("Incorrect file extension\n");
		return (1);
	}
	return (0);
}

int	fd_texture_checker(char *line)
{
	int	fd;

	if (xpm_check_extension(line) == 1)
		return (-1);
	fd = open(line, O_RDONLY);
	printf("Texture: [%s] fd: [%d]\n", line, fd);
	if (fd == -1)
	{
		ft_printf("[errno: %d] Texture could not be loaded.\n", errno);
		return (-1);
	}
	close(fd);
	return (0);
}

int	fd_orientation_checker(t_cub *cub, char *line, int *flag)
{
	if (line && ft_strnstr(line, "NO", 3))
	{
		cub->no = fd_setter(cub, line);
		if (fd_texture_checker(cub->no) < 0)
			flag += 1;
	}
	if (line && ft_strnstr(line, "SO", 3))
	{
		cub->so = fd_setter(cub, line);
		if (fd_texture_checker(cub->so) < 0)
			flag += 1;
	}
	if (line && ft_strnstr(line, "WE", 3))
	{
		cub->we = fd_setter(cub, line);
		if (fd_texture_checker(cub->we) < 0)
			flag += 1;
	}
	if (line && ft_strnstr(line, "EA", 3))
	{
		cub->ea = fd_setter(cub, line);
		if (fd_texture_checker(cub->ea) < 0)
			flag += 1;
	}
	return (*flag);
}
