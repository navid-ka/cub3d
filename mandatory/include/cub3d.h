/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:26:27 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/02/20 17:37:57 by plinscho         ###   ########.fr       */
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

# define NORTH 100
# define SOUTH 200
# define EAST 300
# define WEST 400

# define PI 3.14159265358979323846
# define S_WIDTH 1280
# define S_HEIGHT 720
# define MOVE_SPEED 0.025
# define ROTATE_SPEED 0.050
# define FOV 90
# define RENDER_DIST 10 //* 32 + 16
# define ESC	53
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_UP 126
# define ARROW_DOWN 125
# define A 0
# define W 13
# define S 1
# define D 2

# define KEY_ESC 53

# define ARGC "Error\nToo many arguments\n"

typedef struct s_line
{
	int		text_x;
	int		text_y;
	double	step;
	double	text_pos;
	double	y_start;
	double	y_end;
	double	x_start;
	double	x_end;
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		color;
	int		color_fader;
}	t_line;

typedef struct s_camera
{
	double	plane_multiplier;	// used to calculate the camera plane
	double	plane_x;	// camera plane ortogonal to the direction vector
	double	plane_y;
	double	camera_x;	// x-coordinate in camera space
	double	camera_y;
	double	wall_x;
	int		map_x;	// which box of the map we're in
	int		map_y;
	double	ray_dir_x;	// direction vector
	double	ray_dir_y;
	double	side_dist_x;	// len of ray from current position to next x side
	double	side_dist_y;
	double	delta_dist_x;	// len of ray from one x-side to next x
	double	delta_dist_y;
	double	perp_wall_dist;	// length of ray from position to next x or y-side
	int		step_x;	// what direction to step in x or y-direction (+1 or -1)
	int		step_y;
	int		hit;	// was there a wall hit?
	int		side;	// was a NS or a EW wall hit?
	int		hit_direction;		
}	t_camera;

typedef struct s_player
{
	double	fov;	// field of view is 90 degrees
	double	pos_x;	//position
	double	pos_y;
	double	dir_x;	//direction
	double	dir_y;
	double	angle;	// in radians
	double	speed;
	int		dg_angle;
	double	distance;
}	t_player;

typedef struct s_map
{
	int			width;
	int			height;
	char		**map;
	char		**tmp_map;
	int			orientation;
}	t_map;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

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
}	t_cub;

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_mlx
{
	void	*mlx_p;	// mlx pointer
	void	*pov;	// raycaster window
	t_img	*buffer;
	t_img	img[4];
	int		screen_height;
	int		screen_width;
}	t_mlx;

// New struct for game.
typedef struct s_game
{
	t_mlx		*mlx_s;
	t_map		*map_s;
	t_cub		*cub_s;
	t_player	*player_s;
	t_camera	*camera_s;

}	t_game;

// Parser
void	fd_parser(t_game *game, char **argv);
void	camera_init(t_camera *camera, t_player *player);
double	plane_mult(int fov);

//Movement
double	move_x(t_player *p, char **map, int dir);
double	move_y(t_player *p, char **map, int dir);
double	move_rot(t_camera *cam, t_player *p, char **map, int dir);

//Raycast or angles
void	raycast(t_game *game);
double	deg_to_rad(int dg_angle);
int		rad_to_dg(double angle);
void	draw_line(t_game *game, t_line *line, int i, t_img *img, t_img *s_img);
double	dda_rays(t_game *game);
void	render_3d_map(t_game *game);

// Init structs
void	game_init(t_game *game);
void	cub_init(t_cub *init, char **argv);
void	map_init(t_map *map);
void	player_init(t_player *player);
void	window_init(t_mlx *window);
void	sl_image_init(t_game *g);

// FD utils 
int		open_path(t_cub *cub);
char	*fd_setter(t_cub *cub, char *line);
int		cub_atoi(const char *str);
void	fd_print(t_cub *cub);

// orientation
int		fd_orientation_checker(t_cub *cub, char *line, int *flag);

// colors
int		fd_color_checker(t_cub *cub, char *line, int *flag);

// FD checker
void	fd_check_extension(t_cub *cub);
void	fd_check_integrity(t_cub *cub, t_map *map);

// Map parser
void	map_parser(t_game *game, t_cub *cub, t_map *map);

// Mlx
void	mlx_window(t_game *game);

// Img utils
t_img	*create_buffer(t_mlx *g, int w, int h);
t_img	create_new_img(t_mlx *g, int width, int height);
void	put_pixel_img(t_img *img, int x, int y, int color);
void	put_img_to_img(t_img *dst, t_img *src, int x, int y);
unsigned int	get_pixel_img(t_img *img, int x, int y);
t_img	*resize_image(t_mlx *g, t_img *img, int nw, int nh);
void	img_pix_put(t_img *img, int x, int y, int color);
t_img	load_img(t_mlx *g, char *path, int w, int h);

//Inputs
int		on_key_press(int keycode, t_game *game);
int		on_key_release(int keycode, t_game *game);

//Garbage collectors
int		window_destroy(t_game *game);
void	free_tab(char **args);
void	fd_error(t_cub *cub, int err);
void	garbage_collector(t_game *game);
void	free_textures(t_cub *cub);
void	free_null(char **ptr);
void	fd_error_1(t_cub *cub);
void	fd_error_2(t_cub *cub);
void	fd_error(t_cub *cub, int err);

#endif
