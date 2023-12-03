/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:26:27 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/12/03 02:22:22 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H_
# define _CUB3D_H_
# include <libft.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

#define ARGC "Error\nToo many arguments\n"

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
} t_color;

typedef struct s_cub
{
	char	**map;
	char	*tmp;
	char	*new_tmp;
	char	*path;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f_color;
	t_color	floor;
	char	*c_color;
	t_color	ceiling;
	int		err;
} t_cub;

// Parser
void    parser(t_cub *cub, char **argv);

// Init structs 
void    cub_init(t_cub *init, char **argv);


// FD utils 
char	*fd_setter(char *line);
int		cub_atoi(const char *str);
void    fd_print(t_cub *cub);

// orientation
int		orientation_checker(t_cub *cub, char *line, int *flag);

// colors
int		fd_color_checker(t_cub *cub, char *line, int *flag);

// FD checker
void    check_extension(t_cub *cub);
void    check_fd_integrity(t_cub *cub);
void	fd_map_checker(t_cub *cub);

//Garbage collectors
void	free_tab(char **args);
void	fd_error(t_cub *cub, int err);
void	garbage_collector(t_cub *cub);

#endif
