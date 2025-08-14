/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 04:45:54 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/19 04:45:55 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_common.h"

void	put_error(char *msg, char *data)
{
	ft_putendl_fd("Error", 2);
	if (data)
	{
		ft_putstr_fd(data, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}

void	put_error_char(char *msg, char elem)
{
	ft_putendl_fd("Error", 2);
	if (elem)
	{
		ft_putchar_fd(elem, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}

void	put_perror(char *msg)
{
	ft_putendl_fd("Error", 2);
	perror(msg);
}
