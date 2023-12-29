/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:26:27 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/12/28 23:52:04 by bifrost          ###   ########.fr       */
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
# include <errno.h>

#define PI 3.14159265358979323846
# define ESC	53
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_UP 126
# define ARROW_DOWN 125
# define A 0
# define W 13
# define S 1
# define D 2

# include "raycast.h"

# define KEY_ESC 53

#define ARGC "Error\nToo many arguments\n"

typedef struct s_player
{
    double  pos_x; //position
    double  pos_y;
	double	dir_x; //direction
	double	dir_y;
    double  fov;
	int		is_moving;
}t_player;


typedef struct s_map
{
	int			width;
	int			height;
	char		**map;
	char		**tmp_map;
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

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_img;

typedef struct s_mlx
{
	void	*mlx_p;
	void	*win;
	t_img	*sword;
	t_img	*img;
	int		screen_height;
	int		screen_width;
	
} t_mlx;



// New struct for game.
typedef struct s_game
{
	t_mlx		*mlx_s;
	t_map		*map_s;
	t_cub		*cub_s;
	t_player	*player_s;
	int 		state;
} t_game;

enum e_state
{
	TITLE,
	GAME,
	END
};

typedef struct state_manager
{
    int (*f)(t_game *);
} t_state_manager;

int screen_manager(t_game *g, enum e_state state);
int    game_start(t_game *game);

// Parser
void    fd_parser(t_game *game, char **argv);

// Init structs 
void    cub_init(t_cub *init, char **argv);
void	map_init(t_map *map);
void    window_init(t_mlx *window);
int     key_press(int keycode, t_game *game);
void	sl_image_init(t_mlx *g);

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
void    map_parser(t_game *game, t_cub *cub, t_map *map);

// Mlx
void    mlx_window(t_game *game);

// Draw player
void	draw_player(t_game *game);
void	clear_player(t_game *game);

//Inputs
int     on_key_press(int keycode, t_game *game);
int     on_key_release(int keycode, t_game *game);

// Sword
void    load_sword_img(t_mlx *g);
void    draw_single_sword(t_game *game);

//Garbage collectors
int		window_destroy(t_game *game);
void	free_tab(char **args);
void	fd_error(t_cub *cub, int err);
void	garbage_collector(t_game *game);

#endif