/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_element_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 03:45:04 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/19 04:44:04 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_start_line(char **line)
{
	if ((**line == 'C' || **line == 'F') && *(*line + 1) != ' ')
	{
		if (*(*line + 1) == '\n')
			put_error("Color line is not complete", NULL);
		else
			put_error("Color line must start with only F or C", NULL);
		return (0);
	}
	(*line)++;
	while (**line && !ft_isdigit(**line))
	{
		if (**line != ' ' && **line != '\n')
		{
			put_error("Invalid character in color line", NULL);
			return (0);
		}
		(*line)++;
	}
	return (1);
}

int	check_misplaced_elements(char **line)
{
	while (**line && **line != '\n' && **line != ',')
	{
		if (**line && ft_isdigit(**line))
		{
			put_error("Misplaced color element", NULL);
			return (0);
		}
		if (**line != ' ')
		{
			put_error("Invalid character in color line", NULL);
			return (0);
		}
		(*line)++;
	}
	return (1);
}

int	check_last_elements(char **line, int *i)
{
	while (**line && **line != '\n' && ++(*i) < 2)
	{
		while (ft_isdigit(**line))
		{
			if (**line && !ft_isdigit(**line))
			{
				put_error("Invalid character in color line", NULL);
				return (0);
			}
			(*line)++;
		}
		if (!check_misplaced_elements(line))
			return (0);
		(*line)++;
		while (**line && **line != '\n' && !ft_isdigit(**line))
		{
			if (**line != ' ')
			{
				put_error("Invalid character in color line", NULL);
				return (0);
			}
			(*line)++;
		}
	}
	return (1);
}

int	check_end_line(char **line)
{
	int	comma_flag;

	comma_flag = 0;
	while (**line && **line != '\n')
	{
		if (**line == ',')
			comma_flag = 1;
		if (ft_isdigit(**line))
		{
			put_error("Too many elements in color line", NULL);
			return (0);
		}
		if (**line != ' ' && **line != '\n' && **line != ',')
		{
			put_error("Invalid character in color line", NULL);
			return (0);
		}
		(*line)++;
	}
	if (comma_flag)
	{
		put_error("Invalid character in color line", NULL);
		return (0);
	}
	return (1);
}

int	check_color_line(char *line)
{
	int	i;

	i = -1;
	if (!check_start_line(&line))
		return (0);
	line++;
	if (!check_last_elements(&line, &i))
		return (0);
	if (i < 2)
	{
		put_error("Not enough color elements", NULL);
		return (0);
	}
	while (ft_isdigit(*line))
		line++;
	if (*line)
		if (!check_end_line(&line))
			return (0);
	return (1);
}
