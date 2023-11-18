/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_map_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/18 01:14:21 by nkeyani-         ###   ########.fr       */
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
char *fd_setter(char *line)
{
	char	**opt;
	char	*dup;
	
	opt = ft_split(line, ' ');
	dup = ft_strdup(opt[1]);
	free_tab(opt);
	return(dup);
}
char *fd_getter(char *line, char *value)
{
	
}

void    check_fd_integrity(t_cub *cub)
{
	int			fd;
	char		*line;

	fd = open(cub->path, O_RDONLY);
	printf("%d\n", fd);
	line = ft_strdup("");
	while (line)
	{
		line = get_next_line(fd);
		if (line && ft_strnstr(line, "SO", 3))
			cub->so = fd_setter(line);
	}
	printf("%s", cub->so);
	close(fd);
}
