/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:38:30 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/13 18:39:41 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_map	*st_map;

	st_map = NULL;
	if (is_valid_map_path(argc, argv))
	{
		st_map = build_st_map(argv[1]);
	//	print_map(st_map->map);
		parse_elements(st_map);
	}
	clean_st_map(st_map);
	return (0);
}
