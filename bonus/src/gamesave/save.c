/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:26:33 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/13 10:44:13 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	set_save(char *line)
{
	char	**opt;
	char	*trimmed;
	char	*dup;
	int		value;

	value = 0;
	ft_printf("line: %s", line);
	opt = ft_split(line, ' ');
	if (opt[2])
	{
		free_tab(opt);
		return (-1);
	}
	trimmed = ft_strtrim(opt[1], "\n");
	dup = ft_strdup(trimmed);
	free(trimmed);
	free_tab(opt);
	value = ft_atoi(dup);
	printf("value: %d\n", value);
	free(dup);
	return (value);
}

void	load_save_file(t_game *game)
{
	int		fd;
	char	*line;

	fd = open("./save/game.save", O_RDONLY);
	printf("%d\n", fd);
	line = ft_strdup("");
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line && ft_strnstr(line, "lvl", 4))
			game->player_s->lvl = set_save(line);
		else if (line && ft_strnstr(line, "exp", 4))
			game->player_s->exp = set_save(line);
		else if (line && ft_strnstr(line, "enemy", 6))
			game->enemy->lvl = set_save(line);
	}
	close(fd);
}

void	game_save(t_game *game)
{
	int		fd;
	char	*lvl;
	char	*exp;
	char	*enemy;

	lvl = ft_itoa(game->player_s->lvl);
	exp = ft_itoa(game->player_s->exp);
	enemy = ft_itoa(game->enemy->lvl);
	fd = open("./save/game.save", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (write(fd, "lvl ", 4) == -1 || write(fd, lvl, ft_strlen(lvl)) == -1
		|| write(fd, "\n", 1) == -1
		|| write(fd, "exp ", 4) == -1 || write(fd, exp, ft_strlen(exp)) == -1
		|| write(fd, "\n", 1) == -1 || write(fd, "enemy ", 6) == -1
		|| write(fd, enemy, ft_strlen(exp)) == -1
		|| write(fd, "\n", 1) == -1)
	{
		perror("Error writing to file");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	free(lvl);
	free(exp);
	free(enemy);
	printf("Save successful.\n");
}
