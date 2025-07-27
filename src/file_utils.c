/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:11:17 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/23 22:54:55 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

//Debug
void	print_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		ft_printf("%s", map[i]);
	ft_printf("\n");
}
