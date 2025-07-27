/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:49:11 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/27 12:34:06 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_color_elements_size(int rgb_values[3], char *elem)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (rgb_values[i] < 0 || rgb_values[i] > 255)
		{
			put_error("RGB values must range between 0 and 255", elem);
			return (0);
		}
	}
	return (1);
}

int	check_c_color_element(char elem, char *line, t_file *st_file)
{
	char	**args;

	(void)elem;
	if (*line == 'C')
	{
		if (st_file->c_color[0] != -1)
		{
			put_error("Repated color element", "C");
			return (0);
		}
		if (!check_color_line(line, elem))
			return (0);
		line++;
		args = ft_split(line, ',');
		st_file->c_color[0] = ft_atoi(args[0]);
		st_file->c_color[1] = ft_atoi(args[1]);
		st_file->c_color[2] = ft_atoi(args[2]);
		clean_args(args);
		if (!check_color_elements_size(st_file->c_color, "C"))
			return (0);
	}
	return (1);
}

int	check_f_color_element(char elem, char *line, t_file *st_file)
{
	char	**args;

	(void)elem;
	if (*line == 'F')
	{
		if (st_file->f_color[0] != -1)
		{
			put_error("Repated color element", "F");
			return (0);
		}
		if (!check_color_line(line, elem))
			return (0);
		line++;
		args = ft_split(line, ',');
		st_file->f_color[0] = ft_atoi(args[0]);
		st_file->f_color[1] = ft_atoi(args[1]);
		st_file->f_color[2] = ft_atoi(args[2]);
		clean_args(args);
		if (!check_color_elements_size(st_file->f_color, "F"))
			return (0);
	}
	return (1);
}

int	check_element(char *line, t_file *st_file)
{
	if (!check_texture_element("NO", line, st_file)
		|| !check_texture_element("SO", line, st_file)
		|| !check_texture_element("WE", line, st_file)
		|| !check_texture_element("EA", line, st_file)
		|| !check_f_color_element('F', line, st_file)
		|| !check_c_color_element('C', line, st_file)
		|| invalid_line(line))
		return (0);
	if (is_map(line))
	{
		put_error("Map character misplaced in file or element missing", NULL);
		return (0);
	}
	return (1);
}

int	parse_elements(t_file *st_file)
{
	char	**file_content;

	file_content = st_file->file_content;
	while (*file_content)
	{
		if (!check_element(*file_content, st_file))
			return (0);
		file_content++;
		if (elements_complete(st_file))
			break ;
	}
	if (!elements_complete(st_file))
	{
		put_error("An element is missing", NULL);
		return (0);
	}
	while (is_blank_line(*file_content))
		file_content++;
	if (!check_map(file_content, st_file))
		return (0);
	return (1);
}

/*
	//Debug print elements
	int		i;
	i = -1;
	ft_printf("%s\n", st_file->no_texture);
	ft_printf("%s\n", st_file->so_texture);
	ft_printf("%s\n", st_file->we_texture);
	ft_printf("%s\n", st_file->ea_texture);
	ft_printf("F -> ");
	while (++i < 3)
		ft_printf("%d ", st_file->f_color[i]);
	ft_printf("\n");
	i = -1;
	ft_printf("C -> ");
	while (++i < 3)
		ft_printf("%d ", st_file->c_color[i]);
	ft_printf("\n");
*/

/* Debug print map validation
	i = 0;
	ft_printf("----Map Validation----\n");
	while (st_file->map[i])
	{
		ft_printf("%s", st_file->map[i]);
		i++;
	}
	ft_printf("\n");
	if (!valid_map(st_file))
	{
		ft_printf("Invalid Map ❌ ");
		clean_st_file(st_file);
		exit(1);
	}
	ft_printf("Valid Map ✅");
	return (1);
*/
