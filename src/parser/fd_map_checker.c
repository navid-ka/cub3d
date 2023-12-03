/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_map_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/12/03 12:39:18 by bifrost          ###   ########.fr       */
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

int read_map(t_cub *cub, char *line)
{
    if (line && line[0] == '\n')
        return (1);
    cub->new_tmp = ft_strjoin(cub->tmp, line);
    free(cub->tmp);
    cub->tmp = cub->new_tmp;
    return (0);
}

int	check_map_fd(t_cub *cub, int map_started)
{
    int fd;
    char *line;

    cub->tmp = ft_strdup("");
    fd = open(cub->path, O_RDONLY);
    if (fd == -1)
        return (0);
    line = ft_strdup("");
    while (line)
    {
		free(line);
		line = get_next_line(fd);
        if (line && is_map(line)) // TODO: check if map line has only spaces
        {
            map_started = 1;
            cub->new_tmp = ft_strjoin(cub->tmp, line);
            free(cub->tmp);
            cub->tmp = cub->new_tmp;
        }
        if (line && map_started && line[0] == '\n' && line[1] == '\0')
            cub->err = 2;
    }
    close(fd);
    return (cub->err);
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
		line = get_next_line(fd);
		flag = 0;
		if (line && !is_map(line) && (orientation_checker(cub, line, &flag) \
			|| fd_color_checker(cub, line, &flag)))
			cub->err = 1;
	}
	close(fd);
	check_map_fd(cub, 0);
	if (cub->err)
		fd_error(cub, cub->err);
	if (!cub->err)
		cub->map = ft_split(cub->tmp, '\n');
	free(cub->new_tmp);
	fd_print(cub);
}
