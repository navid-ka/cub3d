/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:24:47 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/17 23:09:19 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(int argc, char **argv)
{
	t_cub	cub;

	if (argc > 2 || argc < 2)
		return (printf(ARGC));
	parser(&cub, argv + 1);
	printf("%s\n", cub.path);
	return (0);
}
