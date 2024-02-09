/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:24:47 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/02/09 01:27:59 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int set_save(char *line)
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
	return(value);
}


void	load_save_file(t_game *game)
{
	int fd;
	char *line;

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

void game_save(t_game *game)
{
    int fd;
    char *lvl;
    char *exp;
	char *enemy;

    lvl = ft_itoa(game->player_s->lvl);
    exp = ft_itoa(game->player_s->exp);
	enemy = ft_itoa(game->enemy->lvl);
	printf("lvl: %s\n", lvl);
	printf("exp: %s\n", exp);
    fd = open("./save/game.save", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    if (write(fd, "lvl ", 4) == -1 || write(fd, lvl, ft_strlen(lvl)) == -1 
		|| write(fd, "\n", 1) == -1 ||
        write(fd, "exp ", 4) == -1 || write(fd, exp, ft_strlen(exp)) == -1 
		|| write(fd, "\n", 1) == -1 ||        
		 write(fd, "enemy ", 6) == -1 || write(fd, enemy, ft_strlen(exp)) == -1 
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


void	game_init(t_game *game)
{
	game->cub_s = malloc(sizeof(t_cub));
	game->map_s = malloc(sizeof(t_map));
	game->mlx_s = malloc(sizeof(t_mlx));
	game->player_s = malloc(sizeof(t_player));
	game->enemy = malloc(sizeof(t_enemy));
	game->camera_s = malloc(sizeof(t_camera));
	if (!game->cub_s || !game->map_s || !game->mlx_s || !game->player_s)
	{
		ft_printf("Error\nMalloc error\n");
		exit(1);
	}
	game->frame_count = 0;
	game->text_draw_frame = 0;
	game->steps = 0;
	game->created_at = 0;
	game->updated_at = 0;
	game->total_dmg = 0;
	game->door_offset = 0;
	game->door_frame_index = 0;
	game->combat_started_at = 0;
	game->enemy->lvl = 1;
	game->enemy->hp = 0;
	game->enemy->dmg = 0.5;
	game->enemy->armor = 0;
	game->player_s->lvl = 1;
	game->player_s->exp = 0;
	game->player_s->dmg = 2;
	game->player_s->hp = HP_PLAYER;
	player_init(game->player_s);
	load_save_file(game);
}

int main(int argc, char **argv)
{
	t_game		game;

	if (argc > 2 || argc < 2)
		return (printf(ARGC));

	game_init(&game);
	fd_parser(&game, argv + 1);
	mlx_window(&game);
	garbage_collector(&game);
	return (0);
}

