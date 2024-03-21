/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/03/21 22:33:52 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_digit_str(char *str)
{
	while (str && *str)
	{
		if (!ft_isdigit(*str))
		{
			return (0);
		}
		str++;
	}
	return (1);
}

int	validate_color_fd(char **colors)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!is_digit_str(colors[i]) && !ft_strlen(colors[i]))
		{
			ft_printf("Error\nNon-numeric value in color\n");
			free_tab(colors);
			return (1);
		}
		i++;
	}
	return (0);
}

void	append_colors(t_cub *cub, char **colors, char type)
{
	if (type == 'c')
	{
		cub->ceiling.r = cub_atoi(colors[0], cub);
		cub->ceiling.g = cub_atoi(colors[1], cub);
		cub->ceiling.b = cub_atoi(colors[2], cub);
	}
	if (type == 'f')
	{
		cub->floor.r = cub_atoi(colors[0], cub);
		cub->floor.g = cub_atoi(colors[1], cub);
		cub->floor.b = cub_atoi(colors[2], cub);
	}
}

int	color_validator(t_cub *cub, char *color, char type)
{
	char	**colors;
	int		i;

	colors = ft_split(color, ',');
	i = 0;
	while (colors[i])
		i++;
	if (i != 3)
	{
		ft_printf("Error\nColor format is not correct\n");
		free_tab(colors);
		return (1);
	}
	if (validate_color_fd(colors))
		return (1);
	append_colors(cub, colors, type);
	free_tab(colors);
	return (0);
}

int	fd_color_checker(t_cub *cub, char *line, int *flag)
{
	if (line && ft_strnstr(line, "F", 2))
	{
		cub->f_color = fd_setter(cub, line);
		if (cub->f_color == NULL)
		{
			flag += 1;
			return (*flag);
		}
		if (color_validator(cub, cub->f_color, 'f'))
			flag += 1;
		free(cub->f_color);
	}
	if (line && ft_strnstr(line, "C", 2))
	{
		cub->c_color = fd_setter(cub, line);
		if (!cub->c_color)
		{
			flag += 1;
			return (*flag);
		}
		if (color_validator(cub, cub->c_color, 'c'))
			flag += 1;
		free(cub->c_color);
	}
	return (*flag);
}
