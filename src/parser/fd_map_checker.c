/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_map_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/26 11:51:35 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void fd_error(t_cub *cub)
{
	if (cub->no)
		free(cub->no);
	if (cub->so)
		free(cub->so);
	if (cub->ea)
		free(cub->ea);
	if (cub->we)
		free(cub->we);
	ft_printf("Error\nTexture could not be loaded\n");
	exit(1);
}
void    check_extension(t_cub *cub)
{
	char    *str;
	int     len;

	str = cub->path;
	len = ft_strlen(str);
	if (!(str[len - 1] == 'b' && str[len - 2] == 'u' && str[len - 3] == 'c'
			&& str[len - 4] == '.'))
	{
		free(str);
		ft_printf("Error\nIncorrect file extension\n");
		exit(1);
	}
}
char *fd_setter(char *line)
{
	char	**opt;
	char	*dup;
	
	opt = ft_split(line, ' ');
	if (opt[2])
	{
		free_tab(opt);
		return (NULL);
	}
	dup = ft_strtrim(opt[1], "\n");
	printf("setter: %s \n", dup);
	free_tab(opt);
	return(dup);
}

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

int is_digit_str(char *str) 
{
    while (*str) 
	{
        if (!ft_isdigit(*str)) 
		{
            return (0);
        }
        str++;
    }
    return (1);
}

int	validate_color_component(char **colors)
{
    int i;

	i = 0;
    while (i < 3) 
	{
        if (!is_digit_str(colors[i])) 
		{
            ft_printf("Error\nNon-numeric value in color\n");
            free_tab(colors);
            return (1);
        }
        i++;
    }
    return (0);
}
int	color_validator(t_cub *cub, char *color, char type)
{
	char **colors;

	colors = ft_split(color, ',');
	if (colors[3])
	{
		ft_printf("Error\nColors could not be loaded\n");
		free_tab(colors);
		return (1);
	}
	if (validate_color_component(colors))
        return (1);
	if (type == 'c')
	{
		cub->ceiling.r = ft_atoi(colors[0]);
		cub->ceiling.g = ft_atoi(colors[1]);
		cub->ceiling.b = ft_atoi(colors[2]);
	}
	if (type == 'f')
	{
		cub->floor.r = ft_atoi(colors[0]);
		cub->floor.g = ft_atoi(colors[1]);
		cub->floor.b = ft_atoi(colors[2]);
	}
	free_tab(colors);
	return (0);
}

int	fd_color_checker(t_cub *cub, char *line, int *flag)
{
	if (line && ft_strnstr(line, "F", 2))
	{
		cub->f_color = fd_setter(line);
		if (color_validator(cub, cub->f_color, 'f'))
			flag += 1;
		free(cub->f_color);
	}
	if (line && ft_strnstr(line, "C", 2))
	{
		cub->c_color = fd_setter(line);
		if (color_validator(cub, cub->c_color, 'c'))
			flag += 1;
		free(cub->c_color);
	}
	return (*flag);
}

void    check_fd_integrity(t_cub *cub)
{
	int			fd;
	char		*line;
	int			flag;

	fd = open(cub->path, O_RDONLY);
	if (fd == -1)
		ft_printf("Error\n.cub file could not be loaded\n");
	line = ft_strdup("");
	while (line)
	{
		free(line);
		flag = 0;
		line = get_next_line(fd);
		if (orientation_checker(cub, line, &flag) \
			|| fd_color_checker(cub, line, &flag))
			fd_error(cub);
	}
	printf("%s\n", cub->so);
	close(fd);
}
