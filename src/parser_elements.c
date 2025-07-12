/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:49:11 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/12 19:49:12 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_valid_map_path(int argc, char **argv)
{
	char	*dot_extension;
	
	if (argc < 2)
		ft_putendl_fd("You must input a map", 2);
	else if (argc > 2)
		ft_putendl_fd("Wrong quantity of arguments", 2);
	else
	{
		dot_extension = ft_strchr(argv[1], '.');
		if (!dot_extension || argv[1][0] == '.' || ft_strcmp(dot_extension, ".cub") != 0)
			ft_putendl_fd("Invalid map path or name", 2);
		else
			return (1);
	}
	return (0);
}
