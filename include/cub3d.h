/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:26:27 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/15 20:20:51 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H_
# define _CUB3D_H_
#include <libft.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_cub
{
    char *path;
} t_cub;

// PARSER
// Init structs 
void    cub_init(t_cub *init, char **argv);

void    parser(t_cub *cub, char **argv);


#endif
