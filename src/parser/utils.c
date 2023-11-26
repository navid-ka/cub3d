/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/26 12:15:03 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char *fd_setter(char *line)
{
	char	**opt;
	char	*dup;
	
	opt = ft_split(line, ' ');
	if (opt[2])
	{
		free_tab(opt);
		return (NULL);
	}
	dup = ft_strtrim(opt[1], "\n");
	printf("setter: %s \n", dup);
	free_tab(opt);
	return(dup);
}