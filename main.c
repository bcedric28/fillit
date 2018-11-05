/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 14:20:24 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/03 15:33:05 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int				free_tab(char **sq_tab)
{
	ft_2dtabdel((void**)sq_tab);
	return (0);
}

static void		print_error(void)
{
	ft_putendl("error");
	exit(EXIT_FAILURE);
}

int				main(int argc, char **argv)
{
	int		fd;
	char	*line;
	char	*tab;
	char	**tab_split;

	line = NULL;
	tab = NULL;
	if (argc != 2)
	{
		ft_putendl("usage: fillit 'file'");
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (read_line(fd, line, &tab))
	{
		close(fd);
		tab_split = ft_strsplit(tab, '\n');
		if (!(solver(tab_split)))
			print_error();
	}
	else
		print_error();
	exit(EXIT_SUCCESS);
	return (0);
}
