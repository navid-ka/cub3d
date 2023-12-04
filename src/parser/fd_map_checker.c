/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_map_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/12/03 22:59:19 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

int	is_map(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '1' || line[i] == '0' || line[i] == ' ')
            return (1);
        else if (line[i] != ' ')
            return (0);
        i++;
    }
    return (0);
}

void    read_map(t_cub *cub, char *line)
{
    cub->new_tmp = ft_strjoin(cub->tmp, line);
    free(cub->tmp);
    cub->tmp = cub->new_tmp;
}

int	check_map_fd(t_cub *cub, int map_started)
{
    int     fd;
    char    *line;

    fd = open_path(cub);
    cub->tmp = ft_strdup("");
    line = ft_strdup("");
    while (line)
    {
		free(line);
		line = get_next_line(fd);
        if (line && is_map(line))
        {
            map_started = 1;
            read_map(cub, line);
        }
        if (line && map_started && line[0] == '\n' && line[1] == '\0')
            cub->err = 2;
    }
    close(fd);
    return (cub->err);
}

void    check_fd_integrity(t_cub *cub)
{
	int		fd;
	char	*line;
	int		flag;

    fd = open_path(cub);
	line = ft_strdup("");
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		flag = 0;
		if (line && !is_map(line)\
			&& (orientation_checker(cub, line, &flag) \
			|| fd_color_checker(cub, line, &flag)))
			cub->err = 1;
	}
	close(fd);
	if (cub->count < 6)
		cub->err = 1;
	check_map_fd(cub, 0);
	if (cub->err)
		fd_error(cub, cub->err);
	cub->map = ft_split(cub->tmp, '\n');
	free(cub->tmp);
	fd_print(cub);
}
