/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:11:17 by hebatist          #+#    #+#             */
/*   Updated: 2025/09/08 04:50:44 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_common.h"

int	rgb_to_int(int t, int r, int g, int b)
{
	int	dec;

	dec = t << 24 | r << 16 | g << 8 | b;
	return (dec);
}

void	open_map_error(void)
{
	put_perror("Map file not found");
	exit(EXIT_FAILURE);
}

void	case_error_reading_file(t_file *st_file)
{
	put_perror("Problem reading map file");
	clean_st_file(st_file);
	exit(EXIT_FAILURE);
}

int	get_last_valid(char *line)
{
	int	len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\n'))
		len--;
	return (len);
}

int	is_valid_map_path(int argc, char **argv)
{
	char	*dot_extension;
	char	*map_name;

	if (argc < 2)
		put_error("You must input a map", NULL);
	else if (argc > 2)
		put_error("Wrong quantity of arguments", NULL);
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
			put_error("Invalid map path or name", map_name);
		else
			return (1);
	}
	return (0);
}
