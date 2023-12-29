/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:14:03 by bifrost           #+#    #+#             */
/*   Updated: 2023/12/10 17:19:32 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//	Initialize the cub struct and parse the map
void    fd_parser(t_game *game, char **argv)
{
	cub_init(game->cub_s, argv);
	map_init(game->map_s);
	fd_check_extension(game->cub_s);
	fd_check_integrity(game->cub_s, game->map_s);
	map_parser(game, game->cub_s, game->map_s);

}