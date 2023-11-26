/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:05:37 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/26 13:14:37 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	cub_atoi(const char *str)
{
    int num = 0;
    int i = 0;

    while (str[i] >= '0' && str[i] <= '9')
    {
        num = num * 10 + (str[i] - '0');
        if (num > 255) 
		{
            ft_printf("Error\nNumber out of range (0-255)\n");
            exit (1); //TODO; aqui puede que tengamos que hacer garbage collection
        }
        i++;
    }
    return (num);
}

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