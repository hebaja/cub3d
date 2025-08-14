/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:38:30 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/12 12:37:36 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_main.h"

int	main(int argc, char **argv)
{
	t_mlx	*st_mlx;

	if (is_valid_map_path(argc, argv))
	{
		st_mlx = prepare_game(argv[1]);
		if (!st_mlx)
		{
			clean_all(st_mlx);
			exit(EXIT_FAILURE);
		}
		init_gameplay(st_mlx);
		clean_all(st_mlx);
	}
	return (0);
}
