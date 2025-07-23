/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:42:24 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/17 18:34:35 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int					i;
	int					len;
	unsigned char		ch;

	i = 0;
	len = ft_strlen(s) + 1;
	ch = c;
	while (i < len)
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}
