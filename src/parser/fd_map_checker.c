/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_map_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/26 12:14:57 by bifrost          ###   ########.fr       */
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
