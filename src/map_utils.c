/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:11:17 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/13 19:12:01 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	open_map_error(void)
{
	perror("Error\nMap file not found");
	exit(EXIT_FAILURE);
}

void	case_error_reading_file(void)
{
	perror("Error\nProblem reading map file");
	exit(EXIT_FAILURE);
}

void	print_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		ft_printf("%s", map[i]);
}

int	is_valid_map_path(int argc, char **argv)
{
	char	*dot_extension;
	char	*map_name;

	if (argc < 2)
		ft_putendl_fd("Error\nYou must input a map", 2);
	else if (argc > 2)
		ft_putendl_fd("Error\nWrong quantity of arguments", 2);
	else
	{
		dot_extension = ft_strrchr(argv[1], '.');
		map_name = ft_strrchr(argv[1], '/');
		if (map_name)
			map_name++;
		else
			map_name = argv[1];
		if (!dot_extension || ft_strlen(map_name) < 5
			|| ft_strcmp(dot_extension, ".cub") != 0)
			ft_putendl_fd("Error\nInvalid map path or name", 2);
		else
			return (1);
	}
	return (0);
}
