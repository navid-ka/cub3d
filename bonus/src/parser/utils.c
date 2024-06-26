/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/03/21 22:50:48 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	cub_atoi(const char *str, t_cub *cub)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	if (str[i] == '-')
	{
		ft_printf("Negative numbers are not allowed\n");
		cub->err = 1;
	}
	while (str[i] >= '0' && str[i] <= '9' && cub->err == 0)
	{
		num = num * 10 + (str[i] - '0');
		if (num > 255)
		{
			ft_printf("Number out of range (0-255)\n");
			cub->err = 1;
		}
		i++;
	}
	return (num);
}

char	*fd_setter(t_cub *cub, char *line)
{
	char	**opt;
	char	*trimmed;
	char	*dup;
	int		i;

	if (!line)
		return (NULL);
	opt = ft_split(line, ' ');
	i = 0;
	while (opt[i])
		i++;
	if (i != 2)
	{
		ft_printf("Error\n[errno: %d] .cub file is not well formatted.\n",
			errno);
		cub->err = 1;
		free_tab(opt);
		return (NULL);
	}
	trimmed = ft_strtrim(opt[1], "\n");
	dup = ft_strdup(trimmed);
	free(trimmed);
	free_tab(opt);
	cub->count++;
	return (dup);
}

void	fd_print(t_cub *cub)
{
	int	i;

	i = 0;
	printf("floor [%d,%d,%d]\n", cub->floor.r, cub->floor.g, cub->floor.b);
	printf("ceiling [%d,%d,%d]\n", cub->ceiling.r, \
		cub->ceiling.g, cub->ceiling.b);
	while (cub->map[i])
	{
		printf("map :%s\n", cub->map[i]);
		i++;
	}
}

int	open_path(t_cub *cub, t_map *map)
{
	int	fd;

	fd = open(cub->path, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\n[errno: %d] .cub file could not be loaded.\n", errno);
		cub->err = -1;
		fd_error(cub, map, cub->err);
	}
	return (fd);
}
