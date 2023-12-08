/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:26:27 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/12/08 14:03:48 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H_
# define _CUB3D_H_
# include <libft.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>

# include "raycast.h"

# define KEY_ESC 53


#define ARGC "Error\nToo many arguments\n"

typedef struct s_player t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_img;

typedef struct s_map
{
	int			width;
	int			height;
	char		**map;
	int			pos_x;
	int			pos_y;
	int			orientation;
} t_map;

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
	int		count;
	int		err;
} t_cub;

typedef struct s_mlx
{
	t_cub	*cub;
	t_map	*map;
	void	*mlx;
	void	*win;
	t_img	*img;
} t_mlx;

// Parser
void    fd_parser(t_cub *cub, t_map *map, char **argv);

// Init structs 
void    cub_init(t_cub *init, char **argv);
void	map_init(t_map *map);
void    window_init(t_mlx *window);

// FD utils 
int		open_path(t_cub *cub);
char	*fd_setter(t_cub *cub, char *line);
int		cub_atoi(const char *str);
void    fd_print(t_cub *cub);

// orientation
int		fd_orientation_checker(t_cub *cub, char *line, int *flag);

// colors
int		fd_color_checker(t_cub *cub, char *line, int *flag);

// FD checker
void    fd_check_extension(t_cub *cub);
void    fd_check_integrity(t_cub *cub, t_map *map);

// Map parser
void    map_parser(t_cub *cub, t_map *map);

// Mlx
void    mlx_window(t_mlx *window);

//Garbage collectors
void	free_tab(char **args);
void	fd_error(t_cub *cub, int err);
void	garbage_collector(t_cub *cub, t_map *map);

#endif
