#include "../include/cub3d.h"

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

void	put_perror(char *msg)
{
	ft_putendl_fd("Error", 2);
	perror(msg);
}
