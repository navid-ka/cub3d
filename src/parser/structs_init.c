/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:14:03 by bifrost           #+#    #+#             */
/*   Updated: 2023/11/15 20:46:08 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    cub_init(t_cub *init, char **argv)
{
	init->path = ft_strdup(*argv);
	init->no = NULL;
	init->so = NULL;
	init->we = NULL;
    init->ea = NULL;
    init->f_color = NULL;
    init->c_color = NULL;
}
