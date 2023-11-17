/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:26:27 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/17 23:33:22 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H_
# define _CUB3D_H_
# include <libft.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

#define ARGC "Error\nToo many arguments\n"

typedef struct s_cub
{
	char **map;
	char *path;
	char *no;
	char *so;
	char *we;
	char *ea;
	char *f_color;
	char *c_color;
} t_cub;

// Parser

void    parser(t_cub *cub, char **argv);
// Init structs 

void    cub_init(t_cub *init, char **argv);

// FD checker
void    check_extension(t_cub *cub);
void    check_fd_integrity(t_cub *cub);

#endif
