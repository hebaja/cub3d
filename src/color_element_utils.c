#include "../include/cub3d.h"

int	validate_color(char *str_color)
{
	int	i;
	int	len;
	int	color;	

	i = -1;
	len = ft_strlen(str_color);
	color = 0;
	while (*str_color && ++i < len)
	{
		if (str_color[i] == ' ' || str_color[i] == ',' || str_color[i] == '\n')
			break ;
		if (!ft_isdigit(str_color[i]) || i > 2)
			return (-1);
	}
	color = ft_atoi(str_color);
	return (color);
}

int	is_color_line_valid(char *line)
{
	char	type;

	type = *line;
	while (*line)
	{
		if (*line != 'F' && *line != 'C' && *line != ' ' && *line != ','
			&& *line != '\n' && !ft_isdigit(*line))
		{
			if (type == 'F')
				put_error("Invalid F color element", NULL);
			else
				put_error("Invalid C color element", NULL);
			return (0);
		}
		line++;
	}
	return (1);
}

int	validate_end_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
		{
			put_error("Color: Too many elements", NULL);
			return (0);
		}
		line++;
	}
	return (1);
}

int	is_number(char *line, char **args)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!ft_isdigit(line[i]))
		{
			put_error("line contains invalid charcter", line);
			clean_args(args);
			free(line);
			return (0);
		}
	}
	return (1);
}

int	check_color_element(char elem, char *line, t_map *st_map)
{
	int		i;
	int		empty_flag;
	int		size;
	int		limit;
	char	**args;
	char	*filtered;

	if (elem != 'C')
		return (1);

	i = -1;
	empty_flag = 0;
	args = ft_split(&line[1], ' ');
	limit = -1;
	while (args[++i])
	{
		filtered = ft_strtrim(args[i], ",");
		size = ft_strlen(filtered);
		if (!size || filtered[0] == '\n')
		{
			if (empty_flag)
			{
				put_error("empty element", line);
				clean_args(args);
				free(filtered);
				return (0);
			}
			free(filtered);
			filtered = NULL;
			empty_flag = 1;
		}
		else if (!is_number(filtered, args))
			return (0);
		else
		{
			limit++;
			if (limit > 2)
			{
				put_error("wrong quantity of elements", line);
				clean_args(args);
				free(filtered);
				return (0);
			}

			int	n = ft_atoi(filtered);

			if (elem == 'F')
				st_map->f_color[limit] = n;
			else
				st_map->c_color[limit] = n;
			free(filtered);
			filtered = NULL;
			empty_flag = 0;
		}
	}
	if (limit != 2)
	{
		put_error("wrong quantity of elements", line);
		clean_args(args);
		return (0);
	}
	clean_args(args);
	return (1);
}

/*
int	check_color_element(char elem, char *line, t_map *st_map)
{
	int	i;
	int	tmp_color;

	i = 0;
	if (elem == line[0] && line[1] == ' ')
	{
		if (!is_color_line_valid(line))
			return (0);
		line++;
		while (*line)
		{
			while (!ft_isdigit(*line) && *line != '\n')
				line++;
			if (*line == '\n' || i > 3)
				break ;
			tmp_color = validate_color(line);
			if (tmp_color < 0)
				return (0);
			if (elem == 'F')
				st_map->f_color[i] = tmp_color;
			else
				st_map->c_color[i] = tmp_color;
			while (ft_isdigit(*line) || *line == '\n')
				line++;
			i++;	
		}
		if (i != 3)
		{
			put_error("Color: Wrong quantity of elements", NULL);
			return (0);
		}
		if (!validate_end_line(line))
			return (0);
	}
	return (1);
}
*/
